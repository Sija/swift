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
#include "Globals.h"

#include "values/Void.h"

namespace Swift {
  oGlobals Globals::_instance;

  bool Globals::addFunction(const string& name, const Globals::fOnCallFunction& func, int args) {
    if (hasFunction(name)) {
      return false;
    }
    _functions[name] = sFunction(func, args);
    return true;
  }

  oValue Globals::callFunction(const string& name, const tFuncArguments& arguments) {
    if (!hasFunction(name)) {
      throw SwiftException(stringf("Function '%s' does not exists", name.c_str()));
    }
    int argsNum = _functions[name].argsNum;
    if (!(argsNum == Globals::argsAll || argsNum >= arguments.size())) {
      throw SwiftException(stringf("Function(%s): incorrect # of arguments %d/%d", name.c_str(), arguments.size(), argsNum));
    }
    return _functions[name].callback(arguments);
  }

  bool Globals::hasFunction(const string& name) const {
    return name.size() && _functions.find(name) != _functions.end();
  }

  void Globals::removeFunction(const string& name) {
    if (!hasFunction(name)) {
      return;
    }
    _functions.erase(_functions.find(name));
  }
}