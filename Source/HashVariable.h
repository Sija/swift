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

#ifndef __SWIFT_HASH_VARIABLE_H__
#define __SWIFT_HASH_VARIABLE_H__

#include "Variable.h"
#include "Hash.h"

#include "values/Hash.h"

namespace Swift {
  class HashVariable: public Variable {
  public:
    HashVariable(const string& name, const string& key, iVariableManager* lVM): Variable(name, lVM), _key(key) { }
    HashVariable(const HashVariable& var): Variable(var._name, var._vm), _key(var._key) { }

  public:
    inline oValue getValue() {
      return (Variable::getValue() >> Hash()).get(_key);
    }
    inline void setValue(const oValue& value) {
      if (!_vm) {
        _vm = _lVM->find(_name);
      }
      if (_vm) {
        Hash hash = (Variable::getValue() >> Hash());
        hash.set(_key, value);

        _vm->setVariable(_name, hash);
      }
    }

  protected:
    string _key;
  };
}

#endif // __SWIFT_HASH_VARIABLE_H__