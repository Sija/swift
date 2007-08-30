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

#ifndef __SWIFT_HASH_H__
#define __SWIFT_HASH_H__

#include "iValue.h"

#include "values/Void.h"
#include "values/Bool.h"

namespace Swift {
  class Hash {
  public:
    typedef tHashMap<string, oValue> tValues;

  public:
    oValue operator [] (const string& key) {
      return get(key);
    }

  public:
    Hash(const oValue& defValue = (iValue*) 0) : _default(defValue) { }

  public:
    void set(const string& name, oValue value);
    oValue get(const string& name) const;

    bool hasValue(const oValue& value) const;

    inline bool hasKey(const string& name) const {
      return _values.find(name) != _values.end();
    }
    inline size_t count() const {
      return _values.size();
    }
    const tValues& getData() const {
      return _values;
    }

  protected:
    tValues _values;
    oValue _default;
  };
}

#endif // __SWIFT_HASH_H__