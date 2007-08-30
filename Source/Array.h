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

#ifndef __SWIFT_ARRAY_H__
#define __SWIFT_ARRAY_H__

#include "iValue.h"

#include "values/Void.h"
#include "values/Bool.h"

namespace Swift {
  class Array {
  public:
    typedef vector<oValue> tArray;

  public:
    Array(const oValue& defValue = (iValue*) 0) : _default(defValue) { }

  public:
    Array& operator << (oValue value) {
      return add(value);
    }
    oValue operator [] (size_t id) {
      return get(id);
    }

  public:
    void set(size_t id, oValue value);
    oValue get(size_t id) const;

    bool has(const oValue& value) const;

    Array& add(const oValue& value);
    void remove(size_t id);

    inline size_t count() const {
      return _array.size();
    }

  protected:
    tArray _array;
    oValue _default;
  };
}

#endif // __SWIFT_ARRAY_H__