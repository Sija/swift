/**
  *  Swift Parser Library
  *
  *  Licensed under The MIT License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @filesource
  *  @copyright    Copyright (c) 2007 Sijawusz Pur Rahnama
  *  @copyright    Copyright (c) 2007 Pawe³ Z³omaniec
  *  @version      $Revision: 90 $
  *  @modifiedby   $LastChangedBy: ursus6 $
  *  @lastmodified $Date: 2007-08-06 11:41:22 +0200 (Pn, 06 sie 2007) $
  */

#include "stdafx.h"

#include "Parser.h"
#include "ParserException.h"

#include "iTemplate.h"
#include "iSection.h"
#include "iBlock.h"

#include "Factory.h"
#include "Globals.h"
#include "Function.h"
#include "Param.h"
#include "Operator.h"

#include "HashVariable.h"
#include "ArrayVariable.h"
#include "ChainedVariable.h"

#include "tokens/Text.h"
#include "tokens/Expression.h"

#include "values/RegExPattern.h"
#include "values/Proxy.h"
#include "values/Int64.h"

namespace Swift {
  String Parser::parse(const StringRef& data) {
    wstring d = data.w_string();

    itBegin = itCurrPos = d.begin();
    itEnd = d.end();

    auto_ptr<iBlock> block(new iBlock(Globals::get()));

    try {
      _parse(block.get());
      return block->output();
    } catch (...) {
      throw;
    }
    return "";
  }

  void Parser::parse(oTemplate& tpl) {
    if (!tpl->loaded()) {
      tpl->load();
    }

    wstring data = tpl->getData().w_string();
    itBegin = itCurrPos = data.begin();
    itEnd = data.end();

    iBlock* wrapper = new iBlock(tpl.get());
    tpl->setToken(wrapper);
    _parse(wrapper);
  }

  void Parser::_parse(iBlock* block) {
    wstring::const_iterator itBack = itCurrPos;
    iBlock* currentBlock = block;

    stack<iBlock*> stBlocks;
    stBlocks.push(block);

    while (itCurrPos != itEnd) {
      // find '{' symbol
      while (itCurrPos != itEnd && *itCurrPos != '{') {
        itCurrPos++;
      }

      // symbol '{' found
      if (itCurrPos != itEnd) {
        itCurrPos++;

        // validating token
        if (itCurrPos != itEnd && !isWhite(itCurrPos, true)) {
          // getting text
          if (itBack != itCurrPos - 1) {
            currentBlock->addToken(new Tokens::Text(string(itBack, itCurrPos - 1)));
          }

          // detecting end token
          bool isEndToken;
          if (isEndToken = *itCurrPos == '/') {
            itCurrPos++;
          }

          // reading name
          itBack = itCurrPos;
          while (itCurrPos != itEnd && isAlpha(itCurrPos)) {
            itCurrPos++;
          }

          // checking token name
          if (itCurrPos != itBack) {
            string name(itBack, itCurrPos);

            // base token
            if (!isEndToken) {

              // expression token
              if (name == "not" || name == "true" || name == "false" || (itCurrPos != itEnd && *itCurrPos == '(')) {
                itCurrPos = itBack;

                Tokens::Expression* expression = new Tokens::Expression(stBlocks.top());
                currentBlock->addToken(expression);
                _parseExpression(expression);

              // named token
              } else {
                // alt token
                if (stBlocks.top()->getAltName() == name) {
                  iBlock* base = stBlocks.top();

                  if (base->getAlt()) {
                    throw ParserException(this, "alt token already exist");
                  }
                  currentBlock = new iBlock(base);
                  base->setAlt(currentBlock);

                // token
                } else if (Factory::get()->isBinded(name)) {
                  // getting instance of token
                  if (iSection* token = Factory::get(name, stBlocks.top())) {
                    currentBlock->addToken(token);
                    _parseSection(token->getArgs(), currentBlock);

                    // detecting block token instance
                    if (dynamic_cast<iBlock*>(token)) {
                      stBlocks.push(currentBlock = (iBlock*)token);

#ifdef SWIFT_BLOCK_RECURSION_LIMIT
                      if (stBlocks.size() > SWIFT_BLOCK_RECURSION_LIMIT) {
                        throw ParserException(this, "recurse limit (SWIFT_BLOCK_RECURSION_LIMIT) has been reached");
                      }
#endif // SWIFT_BLOCK_RECURSION_LIMIT

                    }
                  } else {
                    throw ParserException(this, "token callback returned null pointer");
                  }
                // unknown token
                } else {
                  bool backSlash = false;

                  while (itCurrPos != itEnd) {
                    if (backSlash) {
                      backSlash = false;
                    } else if (*itCurrPos == '}') {
                      break;
                    } else if (*itCurrPos == '\\') {
                      backSlash = true;
                    }
                    ++itCurrPos;
                  }
                }
              }
            // end token
            } else {
              if (stBlocks.top()->getName() == name) {
                stBlocks.pop();
                currentBlock = stBlocks.top();
              } else if (Factory::get()->isBinded(name)) {
                throw ParserException(this, "extra ending token '" + name + "' found");
              }
            }

          // propably token is expression
          } else if (itCurrPos != itEnd && !isEndToken && (isOperatorSpecialChar(itCurrPos) || 
            isNum(itCurrPos) || *itCurrPos == '(')) {
            Tokens::Expression* expression = new Tokens::Expression(stBlocks.top());
            currentBlock->addToken(expression);
            _parseExpression(expression);

          // unknown format token, skip it
          } else {
            throw ParserException(this, "empty name in end token");
          }

          // validating token syntax
          if (itCurrPos == itEnd || *itCurrPos != '}') {
            throw ParserException(this, "no end sign '}' in token");
          }
          itBack = ++itCurrPos;
        // empty token
        } else {
          throw ParserException(this, "empty token");
        }
      }
    }

    if (stBlocks.size() > 1) {
      throw ParserException(this, stringf("no ending token in %s token", 
        stBlocks.top()->getName()));
    }

    if (itBack != itCurrPos) {
      currentBlock->addToken(new Tokens::Text(string(itBack, itCurrPos)));
    }
  }

  // end non recursion parsing

  void Parser::_parseSection(iArgContainer* container, iVariableManager* vm) {
    if (!container) {
      return;
    }
    Expression* argument = 0;
    size_t cArgs = 0;

    bool hasNamedArgument = dynamic_cast<NamedContainer*>(container) != 0;
    bool isCommaSign;

    wstring::const_iterator itNamePos, itNameEndPos;

    while(itCurrPos != itEnd) {
      isCommaSign = false;

      while (itCurrPos != itEnd && isWhite(itCurrPos)) {
        ++itCurrPos;
      }
      if (hasNamedArgument) {
        itNamePos = itCurrPos;

        while (itCurrPos != itEnd && isName(itCurrPos)) {
          itCurrPos++;
        }
        if (itCurrPos == itEnd || (itNameEndPos = itCurrPos) == itNamePos) {
          throw ParserException(this, "no argument name");
        }
        while (itCurrPos != itEnd && isWhite(itCurrPos)) {
          itCurrPos++;
        }
        if (itCurrPos == itEnd || *itCurrPos != '=') {
          throw ParserException(this, "no assign symbol");
        }
        ++itCurrPos;
        while (itCurrPos != itEnd && isWhite(itCurrPos)) {
          ++itCurrPos;
        }
      }

      argument = new Expression(vm);
      _parseExpression(argument);

      if (argument->count()) {
        ++cArgs;
        if (hasNamedArgument) {
          string name(itNamePos, itNameEndPos);

          if (((NamedContainer*) container)->hasValue(name)) {
            delete argument;
            throw ParserException(this, "argument '" + name + "' redefinition");
          }
          ((NamedContainer*) container)->add(name, argument);
        } else {
          ((OrderedContainer*) container)->add((const int)cArgs - 1, argument);
        }
      } else {
        delete argument;
      }

      while (itCurrPos != itEnd && isWhite(itCurrPos)) {
        ++itCurrPos;
      }
      if (!(isCommaSign = itCurrPos != itEnd && *itCurrPos == ',')) {
        break;
      }
      ++itCurrPos;
    }
    if (isCommaSign) {
      throw ParserException(this, "too many ',' signs");

    } else if (container->countRequired() != (size_t) iArgContainer::allArgs && 
      container->countRequired() != cArgs) {

      throw ParserException(this, 
        stringf("invalid quantity of argument(s) (%d / required %d)",
        cArgs, container->countRequired()));
    }
  }

  void Parser::_parseExpression(Expression* expression) {
    bool isAlpha_;
    wstring::const_iterator itBack;

    Operator::sOperator *preOperator, *postOperator;
    oValue value;

    while (itCurrPos != itEnd) {
      preOperator = postOperator = 0;
      isAlpha_ = false;

      while (itCurrPos != itEnd && isWhite(itCurrPos)) {
        ++itCurrPos;
      }
      itBack = itCurrPos;

      if (isAlpha_ = (itCurrPos != itEnd && isAlpha(itCurrPos))) {
        ++itCurrPos;

        while (itCurrPos != itEnd && isAlpha(itCurrPos)) {
          ++itCurrPos;
        }
      } else {
        while (itCurrPos != itEnd && isOperatorSpecialChar(itCurrPos)) {
          ++itCurrPos;
        }
      }
      preOperator = 0;
      if (itBack != itCurrPos) {
        try {
          preOperator = &Operator::getOperator(string(itBack, itCurrPos), Operator::preOperator);
        } catch (Operator::NoOperatorException) { }
      }

      if (preOperator) {
        while (itCurrPos != itEnd && isWhite(itCurrPos)) {
          ++itCurrPos;
        }
        if (isAlpha_) {
          itBack = itCurrPos;

          while (itCurrPos != itEnd && isAlpha(itCurrPos)) {
            ++itCurrPos;
          }
        }
      } else {
        if (!isAlpha_) {
          itCurrPos = itBack;
        }
      }

      if (itCurrPos != itEnd) {
        if (*itCurrPos == '$') {
          value = _parseVar(expression->getVM());
        } else if (*itCurrPos == '\"' || *itCurrPos == '\'') {
          value = _parseText();
        } else if (*itCurrPos == '/') {
          value = _parseRegExp();
        } else if (itCurrPos == itBack && *itCurrPos == '(') {
          value = _parseBracket(expression->getVM());
        } else if (isNum(itCurrPos)) {
          value = _parseInt();
        } else if (isAlpha(itBack)) {
          string name(itBack, itCurrPos);

          if (*itCurrPos == '(') {
            itCurrPos = itBack;
            value = _parseFunc(expression->getVM());
          } else if (name == "true") {
            value = true;
          } else if (name == "false") {
            value = false;
          } else {
            throw ParserException(this, "unknown type or preoperator");
          }
        } else {
          throw ParserException(this, "unknown type or preoperator");
        }
      }

      while (itCurrPos != itEnd && isWhite(itCurrPos)) {
        ++itCurrPos;
      }

      itBack = itCurrPos;
      if (isAlpha_ = (itCurrPos != itEnd && isAlpha(itCurrPos))) {
        ++itCurrPos;
        while (itCurrPos != itEnd && isAlpha(itCurrPos)) {
          ++itCurrPos;
        }
      } else {
        while (itCurrPos != itEnd && isOperatorSpecialChar(itCurrPos)) {
          ++itCurrPos;
        }
      }

      postOperator = 0;
      if (itBack != itCurrPos) {
        try {
          postOperator = &Operator::getOperator(string(itBack, itCurrPos), Operator::postOperator);
        } catch (Operator::NoOperatorException) { }
      }

      expression->add(preOperator, postOperator, value);

      if (!postOperator) {
        if (itBack != itCurrPos) {
          throw ParserException(this, "unknown postoperator " + string(itBack, itCurrPos));
        }
        break;
      }
    }
  }

  oValue Parser::_parseFunc(iVariableManager* vm) {
    wstring::const_iterator itNamePos = itCurrPos;

    while (itCurrPos != itEnd && isName(itCurrPos)) {
      ++itCurrPos;
    }
    if (itCurrPos == itNamePos) {
      throw ParserException(this, "missing function name");
    }
   if (itCurrPos == itEnd || *itCurrPos != '(') {
     throw ParserException(this, "left bracket not found");
   }

    Function* func = new Function(string(itNamePos, itCurrPos));
    itCurrPos++;

    if (itCurrPos != itEnd && *itCurrPos != ')') {
      Expression* argument = 0;
      bool lastComma = false;

      --itCurrPos;
      do {
        ++itCurrPos;
        argument = new Expression(vm);
        _parseExpression(argument);

        if ((lastComma || (itCurrPos != itEnd && *itCurrPos == ',')) && !argument->count()) {
          delete argument;
          throw ParserException(this, "too many comma signs");
        }
        if (argument->count()) {
          func->addParam(argument);
          lastComma = true;
        } else {
          delete argument;
        }
      } while (itCurrPos != itEnd && *itCurrPos == ',');
    }
    if (itCurrPos == itEnd || *itCurrPos != ')') {
      throw ParserException(this, "right bracked not found");
    }
    ++itCurrPos;
    return _parseChain(vm, func);
  }

  oValueProxy Parser::_parseChain(iVariableManager* vm, const oValueProxy& base) {
    if (itCurrPos != itEnd && (*itCurrPos == '.' || *itCurrPos == '[')) {
      ChainedVariable* chv = new ChainedVariable(base);

      do {
        if (*itCurrPos++ == '.') {
          wstring::const_iterator itKey = itCurrPos;

          while(itCurrPos != itEnd && isName(itCurrPos)) {
            ++itCurrPos;
          }
          if (itKey == itCurrPos) {
            throw ParserException(this, "missing hash key");
          }
          chv->addLink(string(itKey, itCurrPos));

        } else {
          Expression* index = new Expression(vm);
          _parseExpression(index);

          if (!index->count() || itCurrPos == itEnd || *itCurrPos != ']') {
            delete index;
            throw ParserException(this, "syntax error in index definition");
          }

          chv->addLink(index);
          ++itCurrPos;
        }
      } while (itCurrPos != itEnd && (*itCurrPos == '.' || *itCurrPos == '['));

      return chv;
    }
    return base;
  }

  oValue Parser::_parseInt() {
    wstring::const_iterator itB = itCurrPos;
    bool hex = false;

    if (itCurrPos != itEnd && *itCurrPos == '0') {
      ++itCurrPos;
      if (itCurrPos != itEnd && *itCurrPos == 'x') {
        ++itCurrPos;
        hex = true;
      }
    }

    if (hex) {
      __int64 h = 0;
      size_t signs = 0;

      while (itCurrPos != itEnd) {
        if (isNum(itCurrPos)) {
          h = (h << 4) + (*itCurrPos - '0');
        } else if (*itCurrPos >= 'A' && *itCurrPos <= 'F') {
          h = (h << 4) + (*itCurrPos - 'A') + 10;
        } else {
          break;
        }
        ++itCurrPos;
        ++signs;
      }
      if (signs == 0) {
        throw ParserException(this, "empty hex value");
      } else if (signs < 9) {
        return (int) h;
      } else if (signs < 17) {
        return h;
      } else {
        throw ParserException(this, "too high hex value");
      }
    }

    while (itCurrPos != itEnd && isNum(itCurrPos)) {
      ++itCurrPos;
    }
    return _wtoi(wstring(itB, itCurrPos).c_str());
  }

  oValue Parser::_parseText() {
    bool apostrophe = (*itCurrPos++) == '\'';
    bool backSlash = false;

    wstring text;
    wstring::const_iterator itBack = itCurrPos;

    while (itCurrPos != itEnd) {
      if (backSlash) {
        switch (*itCurrPos) {
          case 'n':
            text += '\n';
            break;
          case 'r':
            text += '\r';
            break;
          case '\\':
            text += '\\';
            break;
          case '\'':
            text += '\'';
            break;
          case '\"':
            text += '\"';
            break;
          case '0': {
            ++itCurrPos;

            if (itCurrPos != itEnd && *itCurrPos == 'x') {
              ++itCurrPos;

              size_t signs = 0, h = 0;
              while (itCurrPos != itEnd && (*itCurrPos >= '0' && *itCurrPos <= '9') ||
                (*itCurrPos >= 'A' && *itCurrPos <= 'F') && signs < 2) {
                  if (*itCurrPos >= '0' && *itCurrPos <= '9') {
                    h = (h << 4) + (*itCurrPos - '0');
                  } else {
                    h = (h << 4) + (*itCurrPos - 'A') + 10;
                  }
                ++itCurrPos;
                ++signs;
              }
              if (itCurrPos == itEnd || signs == 0) {
                throw ParserException(this, "empty hex character");
              }

              text += (char) h;
              backSlash = false;

              continue;
            } else {
              throw ParserException(this, "invalid hex character");
            }
            break;
          }
          default:
          throw ParserException(this, "cannot escape character" + *itCurrPos);
        };
        backSlash = false;

        itBack = itCurrPos++;
        continue;

      } else if (*itCurrPos == '\\') {
        backSlash = true;
        text += wstring(itBack, itCurrPos);

      } else if ((*itCurrPos == '\"' && !apostrophe) || (*itCurrPos == '\'' && apostrophe)) {
        break;
      }
      ++itCurrPos;
    }
    if (itCurrPos == itEnd || (*itCurrPos != '\"' && !apostrophe) || 
      (*itCurrPos != '\'' && apostrophe) || backSlash) {
      throw ParserException(this, "unexpected end in text");
    }
    text += wstring(itBack, itCurrPos++);
    return text;
  }

  oValue Parser::_parseRegExp() {
    wstring text;
    wstring::const_iterator itBack = itCurrPos++;

    bool backSlash = false;

    // expr
    while (itCurrPos != itEnd) {
      if (backSlash) {
        backSlash = false;

        if (*itCurrPos == '/') {
          text += wstring(itBack, itCurrPos);
          itBack = ++itCurrPos;
        }
        continue;
      }
      if (*itCurrPos == '/') {
        break;
      } else if (*itCurrPos == '\\') {
        backSlash = true;
      }
      itCurrPos++;
    }
    if (itCurrPos == itEnd || *itCurrPos != '/') {
      throw ParserException(this, "no sign '/' in regexp expression");
    }
    ++itCurrPos;

    // flags
    while (itCurrPos != itEnd && isAlpha(itCurrPos)) {
      ++itCurrPos;
    }
    text += wstring(itBack, itCurrPos);

    return iValue::create<Values::RegExPattern>(text);
  }

  oValue Parser::_parseVar(iVariableManager* vm) {
    wstring::const_iterator itBack = ++itCurrPos;
    while (itCurrPos != itEnd && isAlpha(itCurrPos)) {
      itCurrPos++;
    }
    // extra sign
    if (itCurrPos != itEnd && *itCurrPos == '?') {
      itCurrPos++;
    }

    if (itBack == itCurrPos) {
      throw ParserException(this, "missing variable name after '$' sign");
    }
    return _parseChain(vm, new Variable(string(itBack, itCurrPos), vm));
  }

  oValue Parser::_parseBracket(iVariableManager* vm) {
    ++itCurrPos;

    Expression* bracket = new Expression(vm);
    _parseExpression(bracket);

    if (itCurrPos == itEnd || *itCurrPos != ')') {
      delete bracket;
      throw ParserException(this, "right bracket not found");
    }
    ++itCurrPos;
    return bracket;
  }
}
