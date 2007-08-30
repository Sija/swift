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

#include "stdafx.h"
#include "Variable.h"
#include "values/Void.h"

namespace Swift {
  oValue Variable::getValue() {
    if (!_vm) {
      _vm = _lVM->find(_name);
    }
    if (_vm) {
      return _vm->getVariable(_name);
    }
    return (iValue*) 0;
  }

  void Variable::setValue(const oValue& value) {
    if (_vm) {
      _vm->setVariable(_name, value, false);
    } else if (_lVM) {
      _lVM->setVariable(_name, value);
      _vm = _lVM;
    }
  }
}