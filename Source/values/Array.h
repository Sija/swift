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

#ifndef __SWIFT_ARRAY_VALUE_H__
#define __SWIFT_ARRAY_VALUE_H__

#include "../iValueBase.h"
#include "../Array.h"

namespace Swift { namespace Values {
  class Array : public iValueBase<Array, Swift::Array, 40> {
  public:
    Array(const Swift::Array& a = Swift::Array()) : _items(a) { }

  public:
    oValue operator [] (int i) {
      return _items[i];
    }

  public:
    void set(const Swift::Array& a) {
      _items = a;
    }
    const Swift::Array& output() {
      return _items;
    }
    void clear() {
      _items = Swift::Array();
    }
    Swift::Array& getArray() {
      return _items;
    }

  public:
    oValue not() const {
      return !_items.count();
    }

  protected:
    Swift::Array _items;
  };

  SWIFT_REGISTER_TYPE(Array, "Array");

  inline oValue& operator << (oValue& value, Swift::Array& a) {
    return value = new Array(a);
  }
  inline oValue& operator << (oValue& value, const Swift::Array& a) {
    return value = new Array(a);
  }
  inline Swift::Array& operator >> (const oValue& value, Swift::Array& a) {
    return a = Array::assimilate(value);
  }
}
  using Values::operator<<;
  using Values::operator>>;
}

#endif // __SWIFT_ARRAY_VALUE_H__