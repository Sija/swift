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

#ifndef __SWIFT_TEXT_TOKEN_H__
#define __SWIFT_TEXT_TOKEN_H__

#include "../iToken.h"

namespace Swift { namespace Tokens {
  class Text: public iToken {
  public:
    Text(const StringRef& text = "") : _text(text) { }

  public:
    inline string getName() const {
      return "Text";
    }
    void set(const StringRef& text) {
      _text = text;
    }

  public:
    inline String output() {
      return _text;
    }

  protected:
    String _text;
  };
}}

#endif // __SWIFT_TEXT_TOKEN_H__