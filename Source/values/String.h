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

#ifndef __SWIFT_STRING_VALUE_H__
#define __SWIFT_STRING_VALUE_H__

#include "../iValueBase.h"
#include "Bool.h"

namespace Swift { namespace Values {
  class String : public iValueBase<String, ::String, 5> {
  public:
    String(const StringRef& text = "") : _value(text) { }

  public:
    void set(const ::StringRef& text) {
      _value = text;
    }
    const ::String& output() {
      return _value;
    }
    void clear() {
      _value.clear();
    }

  public:
    oValue not() const {
      return _value.empty();
    }
    oValue equal(const oValue& value) const {
      return _value == assimilate(value);
    }
    oValue notEqual(const oValue& value) const {
      return _value != assimilate(value);
    }
    oValue add(const oValue& value) const {
      return _value + assimilate(value);
    }

  protected:
    ::String _value;
  };

  SWIFT_REGISTER_TYPE(String, "String");

  inline oValue& operator << (oValue& value, const ::StringRef& text) {
    return value = new String(text);
  }
  inline oValue& operator << (oValue& value, const ::string& text) {
    return value = new String(text);
  }
  inline oValue& operator << (oValue& value, const ::wstring& text) {
    return value = new String(text);
  }
  inline oValue& operator << (oValue& value, const char* text) {
    return value = new String(text);
  }
  inline oValue& operator << (oValue& value, const wchar_t* text) {
    return value = new String(text);
  }
  inline ::String& operator >> (const oValue& value, ::String& s) {
    return s = String::assimilate(value);
  }
}
  using Values::operator <<;
  using Values::operator >>;
}

#endif // __SWIFT_STRING_VALUE_H__