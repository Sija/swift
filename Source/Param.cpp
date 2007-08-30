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

#include "Param.h"
#include "Parser.h"
#include "Variable.h"
#include "ChainedVariable.h"

#include "iValueProxy.h"
#include "iValue.h"

#include "values/String.h"
#include "values/Hash.h"
#include "values/Array.h"
#include "values/Proxy.h"
#include "values/Void.h"
#include "values/RegExPattern.h"

namespace Swift {
  Param::Param(const Param& param) {
    for (tArguments::const_iterator it = param._arguments.begin(); it != param._arguments.end(); it++) {
      add(it->value, it->preOperator, it->postOperator);
    }
    _vm = param._vm;
  }

  oValue Param::getValue() {
    if (_arguments.empty()) {
      return new Values::Void;
    }

    tArguments::iterator it = _arguments.begin();
    tArguments::iterator itEnd = _arguments.end();

    bool assign = false;

    if (it->postOperator == operatorAssign) {
      iValueProxy* proxy = it->value.isValid() && it->value->isType<Values::Proxy>() 
        ? ((Values::Proxy*) it->value.get())->output().get() : 0;

      if (!proxy || !(dynamic_cast<Variable*>(proxy) || dynamic_cast<ChainedVariable*>(proxy))) {
        throw SwiftException("You can assign value only to variable or chain.");
      }
      if (it->preOperator != operatorNone) {
        throw SwiftException("Cannot use pre operators before variable.");
      }
      if (++it == itEnd) {
        throw SwiftException("No value to assign.");
      }
      assign = true;
    }

    oValue v, value;
    try {
      value = convertValue(it->preOperator, it->value)->get();
    } catch (NoValueException) {
      value = convertValue(it->preOperator, new Values::Void);
    }

    enOperators currPostOperator = it->postOperator;
    it++;

    while (it != itEnd) {
      try {
        v = convertValue(it->preOperator, it->value)->get();
      } catch (NoValueException) {
        v = convertValue(it->preOperator, new Values::Void);
      }

      try {
        switch (currPostOperator) {
          case operatorNone:
            break;
          case operatorPlus:
            value = value + v;
            break;
          case operatorMinus:
            value = value - v;
            break;
          case operatorOr:
            if (value >> bool()) {
              break;
            } else if (v >> bool()) {
              value = v;
            } else {
              value = false;
            }
            break;
          case operatorAnd:
            if (!(value >> bool()) || !(v >> bool())) {
              value = false;
            } else {
              value = true;
            }
            break;
          case operatorNotEqual:
            value = value != v;
            break;
          case operatorEqual:
            value = value == v;
            break;
          case operatorRegExEqual:
          case operatorRegExNotEqual: {
            String pattern, subject;
            if (value->isType<Values::RegExPattern>()) {
              pattern = value >> String();
              subject = v >> String();
            } else if (v->isType<Values::RegExPattern>()) {
              pattern = v >> String();
              subject = value >> String();
            } else {
              throw SwiftException("Incorrect use of regex operator");
            }
            bool matched = RegEx::doMatch(pattern.a_str(), subject.a_str()) > 0;
            value = (currPostOperator == operatorRegExEqual) ? matched : !matched;
            break;
          }
          case operatorAssign:
            throw SwiftException("Incorrect use of assign operator");
            break;
          case operatorIn: {
            try {
              oValue val = it->value->get();

              if (val->isType<Values::Hash>()) {
                if (it->preOperator != operatorNot) {
                  if (!value->isType<Values::String>()) {
                    throw SwiftException("Value must be a string");
                  }
                  value = (val >> Hash()).hasKey((value >> String()).a_str());
                } else {
                  value = (val >> Hash()).hasValue(value);
                }
              } else if (val->isType<Values::Array>()) {
                value = (val >> Array()).has(value);
              } else {
                throw SwiftException("Operator 'in' cannot be used with '" + val->getName() + "' type");
              }
              break;
            } catch (NoValueException) {
              throw SwiftException("Operator 'in' cannot work with empty value");
            }
          }
        }
        currPostOperator = it->postOperator;
        it++;
      } catch (NoValueException) {
        value = new Values::Void;
      }
    }
    if (assign) {
      iValueProxy* proxy = ((Values::Proxy*) _arguments[0].value.get())->output().get();
      if (Variable* var = dynamic_cast<Variable*>(proxy)) {
        var->setValue(value);
      } else {
        if (ChainedVariable* cvar = dynamic_cast<ChainedVariable*>(proxy)) {
          cvar->setValue(value);
        }
      }
      return new Values::Void;
    }
    return value.isValid() ? value : new Values::Void;
  }
}