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

#ifndef __SWIFT_HASH_VALUE_H__
#define __SWIFT_HASH_VALUE_H__

#include "../iValueBase.h"
#include "../Hash.h"

namespace Swift { namespace Values {
  class Hash : public iValueBase<Hash, Swift::Hash, 45> {
  public:
    Hash(const Swift::Hash& h = Swift::Hash()) : _items(h) { }

  public:
    oValue operator [] (const string& s) {
      return _items[s];
    }

  public:
    void set(const Swift::Hash& h) {
      _items = h;
    }
    const Swift::Hash& output() {
      return _items;
    }
    void clear() {
      _items = Swift::Hash();
    }
    Swift::Hash& getHash() {
      return _items;
    }

  public:
    oValue not() const {
      return !_items.count();
    }

  protected:
    Swift::Hash _items;
  };

  SWIFT_REGISTER_TYPE(Hash, "Hash");

  inline oValue& operator << (oValue& value, Swift::Hash& h) {
    return value = new Hash(h);
  }
  inline oValue& operator << (oValue& value, const Swift::Hash& h) {
    return value = new Hash(h);
  }
  inline Swift::Hash& operator >> (const oValue& value, Swift::Hash& h) {
    return h = Hash::assimilate(value);
  }
}
  using Values::operator <<;
  using Values::operator >>;
}

#endif // __SWIFT_ARRAY_VALUE_H__