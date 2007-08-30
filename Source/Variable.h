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

#ifndef __SWIFT_VARIABLE_H__
#define __SWIFT_VARIABLE_H__

#include "iVariableManager.h"
#include "iValueProxy.h"

#include "values/Void.h"

namespace Swift {
  class Variable: public iValueProxy {
  public:
    Variable(const Variable& var): _name(var._name), _vm(var._vm), _lVM(var._lVM) { }
    Variable(const string& name, iVariableManager* lVM) : _name(name), _lVM(lVM) {
      if (lVM) _vm = lVM->find(name);
    }

  public:
    virtual oValue getValue();
    virtual void setValue(const oValue& value);

  protected:
    iVariableManager* _vm;
    iVariableManager* _lVM;
    string _name;
  };
}

#endif // __SWIFT_VARIABLE_H__