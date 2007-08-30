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

#include "Function.h"
#include "Globals.h"

namespace Swift {
  void Function::addParam(const oValueProxy& param) {
    _params.push_back(param);
  }

  oValue Function::getValue() {
    Globals::tFuncArguments arguments;

    for (tParams::iterator it = _params.begin(); it != _params.end(); it++) {
      arguments.push_back((*it)->getValue()->get());
    }
    return Globals::get()->callFunction(_name, arguments);
  }
}