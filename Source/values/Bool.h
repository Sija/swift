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

#ifndef __SWIFT_BOOL_VALUE_H__
#define __SWIFT_BOOL_VALUE_H__

#include "../iValueBase.h"

namespace Swift { namespace Values {
  class Bool : public iValueBase<Bool, bool, 15> {
  public:
    Bool(bool b = false) : _value(b) { }

  public:
    void set(bool b) {
      _value = b;
    }
    const bool& output() {
      return _value;
    }
    void clear() {
      _value = false;
    }

  public:
    oValue not() const {
      return !_value;
    }
    oValue equal(const oValue& value) const {
      return _value == assimilate(value);
    }
    oValue notEqual(const oValue& value) const {
      return _value != assimilate(value);
    }

  protected:
    bool _value;
  };

  SWIFT_REGISTER_TYPE(Bool, "Bool");

  inline oValue& operator << (oValue& value, bool b) {
    return value = new Bool(b);
  }
  inline bool operator >> (const oValue& value, bool b) {
    return Bool::assimilate(value);
  }
}
  using Values::operator <<;
  using Values::operator >>;
}

#endif // __SWIFT_BOOL_VALUE_H__