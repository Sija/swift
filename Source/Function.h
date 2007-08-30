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

#ifndef __SWIFT_FUNCTION_H__
#define __SWIFT_FUNCTION_H__

#include "iValueProxy.h"
#include "Param.h"

namespace Swift {
  class Function: public iValueProxy {
  public:
    typedef vector<oValueProxy> tParams;

  public:
    Function(const Function& func): _name(func._name), _params(func._params) { };
    Function(const string& name): _name(name) { }

  public:
    void addParam(const oValueProxy& param);
    oValue getValue();

  protected:
    tParams _params;
    string _name;
  };
}

#endif // __SWIFT_FUNCTION_H__