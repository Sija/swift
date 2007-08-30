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

#ifndef __SWIFT_REGEXPATTERN_VALUE_H__
#define __SWIFT_REGEXPATTERN_VALUE_H__

#include "../iValueBase.h"
#include "String.h"

namespace Swift { namespace Values {
  class RegExPattern : public iValueBase<RegExPattern, ::String, 25> {
  public:
    RegExPattern(const StringRef& pattern = "") : _pattern(pattern) { }

  public:
    void set(const StringRef& pattern) {
      _pattern = pattern;
    }
    const ::String& output() {
      return _pattern;
    }
    void clear() {
      _pattern.clear();
    }

  protected:
    ::String _pattern;
  };

  SWIFT_REGISTER_TYPE(RegExPattern, "RegExPattern");
}}

#endif // __SWIFT_REGEXPATTERN_VALUE_H__
