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

#ifndef __SWIFT_ARRAY_VARIABLE_H__
#define __SWIFT_ARRAY_VARIABLE_H__

#include "Variable.h"
#include "Array.h"

#include "values/Array.h"
#include "values/Int.h"

namespace Swift {
  class ArrayVariable: public Variable {
  public:
    ArrayVariable(const string& name, const oValueProxy& index, iVariableManager* lVM) : Variable(name, lVM), _index(index) { }
    ArrayVariable(const ArrayVariable& var): Variable(var._name, var._vm), _index(var._index) { }

  public:
    inline oValue getValue() {
      return (Variable::getValue() >> Array()).get(_index->getValue() >> int());
    }
    inline void setValue(const oValue& value) {
      if (!_vm) {
        _vm = _lVM->find(_name);
      }
      if (_vm) {
        Array arr = Variable::getValue() >> Array();
        arr.set(_index->getValue() >> int(), value);

        _vm->setVariable(_name, arr);
      }
    }

  protected:
    oValueProxy _index;
  };
}

#endif // __SWIFT_ARRAY_VARIABLE_H__