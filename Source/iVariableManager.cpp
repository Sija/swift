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
#include "iVariableManager.h"
#include "values/Void.h"

namespace Swift {
  bool iVariableManager::addVariable(const string& name, const oValue& value, bool attrWrite) {
    if (hasVariable(name)) {
      return false;
    }
    _variables[name] = sVariable(value, attrWrite);
    return true;
  }

  bool iVariableManager::hasVariable(const string& name) {
    return name.length() && _variables.find(name) != _variables.end();
  }

  oValue iVariableManager::getVariable(const string& name) {
    if (!hasVariable(name)) {
      return (iValue*) 0;
    }
    return _variables[name].value;
  }

  iVariableManager* iVariableManager::find(const string& name) {
    iVariableManager *pVM = this;
    while (pVM != NULL && !pVM->hasVariable(name)) {
      pVM = pVM->_vm_parent;
    }
    return pVM;
  }

  bool iVariableManager::isWritableVariable(const string& name) {
    if (!hasVariable(name)) {
      return false;
    }
    return _variables[name].attrWrite;
  }

  bool iVariableManager::setVariable(const string& name, const oValue& value, bool create) {
    if (!hasVariable(name)) {
      if (create) {
        addVariable(name, value);
        return true;
      }
      return false;
    }
    _variables[name].value = value;
    return true;
  }

  void iVariableManager::setData(const iVariableManager::tVariableData& data) {
    for (tVariableData::const_iterator it = data.begin(); it != data.end(); it++) {
      setVariable(it->first, it->second, true);
    }
  }

  bool iVariableManager::removeVariable(const string& name) {
    if (!hasVariable(name)) {
      return false;
    }
    _variables.erase(_variables.find(name));
    return true;
  }

  void iVariableManager::clearVariables() {
    _variables.clear();
  }
}