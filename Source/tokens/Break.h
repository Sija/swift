/**
  *  Swift Parser Library
  *
  *  Licensed under The MIT License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @filesource
  *  @copyright    Copyright (c) 2007 Sijawusz Pur Rahnama
  *  @copyright    Copyright (c) 2007 Pawe� Z�omaniec
  *  @version      $Revision: 90 $
  *  @modifiedby   $LastChangedBy: ursus6 $
  *  @lastmodified $Date: 2007-08-06 11:41:22 +0200 (Pn, 06 sie 2007) $
  */

#pragma once

#ifndef __SWIFT_BREAK_TOKEN_H__
#define __SWIFT_BREAK_TOKEN_H__

#include "../iSection.h"

namespace Swift { namespace Tokens {
  class BreakException : public SwiftException {
  public:
    BreakException() : SwiftException("Invalid use of break") { }
  };

  class Break: public iSection {
  public:
    static iSection* __stdcall getInstance(class iBlock* parent) {
      return new Break;
    }

  public:
    inline String output() {
      throw BreakException();
    }
  };

  SWIFT_REGISTER_TOKEN(Break, "break");
}}

#endif // __SWIFT_BREAK_TOKEN_H__