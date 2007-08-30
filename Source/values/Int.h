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

#ifndef __SWIFT_INT_VALUE_H__
#define __SWIFT_INT_VALUE_H__

#include "../iValueBase.h"

namespace Swift { namespace Values {
  class Int : public iValueBase<Int, int, 10> {
  public:
    Int(int i = 0) : _value(i) { }

  public:
    void set(int i) {
      _value = i;
    }
    const int& output() {
      return _value;
    }
    void clear() {
      _value = 0;
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
    oValue minus() const {
      return -_value;
    }
    oValue add(const oValue& value) const {
      return _value + assimilate(value);
    }
    oValue sub(const oValue& value) const {
      return _value - assimilate(value);
    }

  protected:
    int _value;
  };

  SWIFT_REGISTER_TYPE(Int, "Int");

  inline oValue& operator << (oValue& value, int i) {
    return value = new Int(i);
  }
  inline oValue& operator << (oValue& value, size_t i) {
    return value = new Int((int) i);
  }
  inline int operator >> (const oValue& value, int i) {
    return Int::assimilate(value);
  }
}
  using Values::operator <<;
  using Values::operator >>;
}

#endif // __SWIFT_INT_VALUE_H__