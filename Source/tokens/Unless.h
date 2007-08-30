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

#pragma once

#ifndef __SWIFT_UNLESS_TOKEN_H__
#define __SWIFT_UNLESS_TOKEN_H__

#include "IF.h"

namespace Swift { namespace Tokens {
  class Unless: public IF {
  public:
    Unless(iBlock* parent) : IF(parent) { }

  public:
    static iSection* __stdcall getInstance(iBlock* parent) {
      return new Unless(parent);
    }

  public:
    inline bool evaluates() const {
      return !IF::evaluates();
    }
  };

  SWIFT_REGISTER_TOKEN(Unless, "unless");
}}

#endif // __SWIFT_UNLESS_TOKEN_H__