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

#pragma once

#ifndef __SWIFT_PARSER_H__
#define __SWIFT_PARSER_H__

#include "iTemplate.h"
#include "Expression.h"

// #define SWIFT_BLOCK_RECURSION_LIMIT 10000

namespace Swift {
  class iSection;
  class iBlock;

  class Parser /* : public iLockableObject */ {
  public:
    String parse(const StringRef& data);
    void parse(oTemplate& tpl);

  protected:
    void _parse(iBlock* block);
    void _parseSection(iArgContainer* container, iVariableManager* vm);
    void _parseExpression(Expression* expression);

    oValue _parseVar(iVariableManager* vm);
    oValue _parseBracket(iVariableManager* vm);
    oValue _parseText();
    oValue _parseRegExp();
    oValue _parseInt();
    oValue _parseFunc(iVariableManager* vm);
    oValueProxy _parseChain(iVariableManager* vm, const oValueProxy& base);

  public:
    inline bool isWhite(const wstring::const_iterator& it, bool countNL = false) const {
      return *it == ' ' || *it == '\t' || (countNL && *it == '\n');
    }
    inline bool isAlpha(const wstring::const_iterator& it) const {
      return (*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z');
    }
    inline bool isNum(const wstring::const_iterator& it) const {
      return (*it >= '0' && *it <= '9');
    }
    inline bool isAlphaNum(const wstring::const_iterator& it) const {
      return isAlpha(it) || isNum(it);
    }
    inline bool isName(const wstring::const_iterator& it) const {
      return isAlpha(it) || isNum(it) || *it == '_' || *it == '?';
    }
    inline bool isOperatorSpecialChar(const wstring::const_iterator& it) const {
      return !(isAlphaNum(it) || isWhite(it, true) || *it == '}' || *it == ',' || 
        *it == ')' || *it == '('|| *it == '{' || *it == '[' || *it == ']');
    }

  public:
    inline string getPosition() const {
      return getPosition(itCurrPos);
    }
    string getPosition(const wstring::const_iterator& itPos) const {
      int line = 1, pos = 0;

      for (wstring::const_iterator it = itBegin; it != itPos; it++) {
        pos++;
        if (*it == '\n') {
          pos = 0;
          line++;
        }
      }
      return stringf("line: %d, pos: %d", line, pos);
    }

  protected:
    wstring::const_iterator itBegin;
    wstring::const_iterator itCurrPos;
    wstring::const_iterator itEnd;
  };
}

#endif // __SWIFT_PARSER_H__
