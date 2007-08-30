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

#ifndef __SWIFT_INT64_VALUE_H__
#define __SWIFT_INT64_VALUE_H__

#include "../iValueBase.h"

namespace Swift { namespace Values {
  class Int64 : public iValueBase<Int64, __int64, 30> {
  public:
    Int64(__int64 i = 0) : _value(i) { }

  public:
    string getName() const {
      return "Int64";
    }
    void set(__int64 i) {
      _value = i;
    }
    const __int64& output() {
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
    oValue minus(){
      return -_value;
    }
    oValue add(const oValue& value) const {
      return _value + assimilate(value);
    }
    oValue sub(const oValue& value) const {
      return _value - assimilate(value);
    }

  protected:
    __int64 _value;
  };

  SWIFT_REGISTER_TYPE(Int64, "Int64");

  inline oValue& operator << (oValue& value, __int64 i) {
    return value = new Int64(i);
  }
  inline __int64 operator >> (const oValue& value, __int64 i) {
    return Int64::assimilate(value);
  }
}
  using Values::operator <<;
  using Values::operator >>;
}

#endif // __SWIFT_INT64_VALUE_H__