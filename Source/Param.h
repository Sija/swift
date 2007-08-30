/**
  *  Swift Parser Library
  *
  *  Licensed under The MIT License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @filesource
  *  @copyright    Copyright (c) 2007 Sijawusz Pur Rahnama
  *  @copyright    Copyright (c) 2007 Pawe³ Z³omaniec
  *  @version      $Revision: 89 $
  *  @modifiedby   $LastChangedBy: Sija $
  *  @lastmodified $Date: 2007-07-22 21:38:08 +0200 (N, 22 lip 2007) $
  */

#pragma once

#ifndef __SWIFT_PARAM_H__
#define __SWIFT_PARAM_H__

#include "iValue.h"
#include "iValueProxy.h"

namespace Swift {
  // forward declarations
  class iVariableManager;

  enum enOperators {
    operatorUnknown = -1,
    operatorNone,
    operatorAssign,
    operatorIn,
    operatorAnd,
    operatorOr,
    operatorEqual,
    operatorNotEqual,
    operatorRegExEqual,
    operatorRegExNotEqual,
    operatorPlus,
    operatorMinus,
    operatorNot
  };

  class Param: public iValueProxy {
  public:
    struct sArgument {
      enOperators preOperator;
      enOperators postOperator;
      oValue value;

      sArgument(const oValue& value, enOperators preOperator, enOperators postOperator):
        value(value), preOperator(preOperator), postOperator(postOperator) { }
    };

    typedef vector<sArgument> tArguments;

  public:
    Param(iVariableManager* vm) : _vm(vm) { }
    Param(const Param& param);

  public:
    inline void add(const oValue& value, enOperators preOperator, enOperators postOperator) {
      _arguments.push_back(sArgument(value, preOperator, postOperator));
    }
    inline void clear() {
      _arguments.clear();
    }
    inline size_t count() const {
      return _arguments.size();
    }
    inline oValue convertValue(enOperators preOperator, const oValue& value) const {
      return (preOperator == operatorNot) ? !value : (preOperator == operatorMinus) ? -value : value;
    }
    inline iVariableManager* getVM() const {
      return _vm;
    }
    oValue getValue();

  protected:
    tArguments _arguments;
    iVariableManager* _vm;
  };
}

#endif // __SWIFT_PARAM_H__