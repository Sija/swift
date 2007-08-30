#pragma once

#ifndef __SWIFT_EXPRESSION_H__
#define __SWIFT_EXPRESSION_H__

#include "iValueProxy.h"
#include "Operator.h"
#include "Values/Void.h"

namespace Swift {
  class Expression : public iValueProxy {
  public:
    struct sArgument {
      Operator::sOperator* preOperator;
      Operator::sOperator* postOperator;

      oValue value;

      sArgument(Operator::sOperator* preOperator, Operator::sOperator* postOperator, const oValue& value) : 
        preOperator(preOperator), postOperator(postOperator), value(value) { }
    };

    typedef list<sArgument> tArguments;

  public:
    Expression(iVariableManager* vm) : _vm(vm) { }

  public:
    oValue getValue() {
      if (_arguments.size()) {
        tArguments::const_iterator it = _arguments.begin();
        Operator::sOperator* postOperator = it->postOperator;

        oValue l, r;
        try {
          l = it->value->get();

          if (it->preOperator) {
            (*it->preOperator)(l);
          }
        } catch (NoValueException) {
          l = new Values::Void;
        }

        it++;

        while (postOperator && it != _arguments.end()) {
          try {
            r = it->value->get();

            if (it->preOperator) {
              (*it->preOperator)(r);
            }
          } catch (NoValueException) {
            r = new Values::Void;
          }
          try {
            (*postOperator)(l, r);
          } catch (NoValueException) {
            l = new Values::Void;
          }
          postOperator = it->postOperator;
          it++;
        }
        return l;
      }
      return new Values::Void;
    }

  public:
    inline void add(Operator::sOperator* preOperator, Operator::sOperator* postOperator, 
      const oValue& value) {
      _arguments.push_back(sArgument(preOperator, postOperator, value));
    }
    inline size_t count() const {
      return _arguments.size();
    }
    inline void clear() {
      _arguments.clear();
    }
    inline iVariableManager* getVM() {
      return _vm;
    };

  protected:
    tArguments _arguments;
    iVariableManager* _vm;
  };
}

#endif // __SWIFT_EXPRESSION_H__