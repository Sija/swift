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

#ifndef __SWIFT_CONTINUE_TOKEN_H__
#define __SWIFT_CONTINUE_TOKEN_H__

#include "../iSection.h"

namespace Swift { namespace Tokens {
  class ContinueException : public SwiftException {
  public:
    ContinueException() : SwiftException("Invalid use of continue") { }
  };

  class Continue: public iSection {
  public:
    static iSection* __stdcall getInstance(class iBlock* parent) {
      return new Continue;
    }

  public:
    inline String output() {
      throw ContinueException();
    }
  };

  SWIFT_REGISTER_TOKEN(Continue, "continue");
}}

#endif // __SWIFT_CONTINUE_TOKEN_H__