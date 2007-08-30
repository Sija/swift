/**
  *  Swift Parser Library
  *
  *  Licensed under The MIT License
  *  Redistributions of files must retain the above copyright notice.
  *
  *  @filesource
  *  @copyright    Copyright (c) 2007 Sijawusz Pur Rahnama
  *  @copyright    Copyright (c) 2007 Pawe³ Z³omaniec
  *  @version      $Revision: 90 $
  *  @modifiedby   $LastChangedBy: ursus6 $
  *  @lastmodified $Date: 2007-08-06 11:41:22 +0200 (Pn, 06 sie 2007) $
  */

#include "stdafx.h"
#include "Array.h"

namespace Swift {
  Array& Array::add(const oValue& value) {
    _array.push_back(value);
    return *this;
  }

  oValue Array::get(size_t id) const {
    if (id < count()) {
      return _array[id];
    }
    if (_default.isValid()) {
      return _default;
    }
    throw SwiftException("No such value");
  }

  void Array::set(size_t id, oValue value) {
    if (id < count()) {
      _array[id] = value;
    }
  }

  void Array::remove(size_t id) {
    if (id >= count()) return;

    tArray::iterator it = _array.begin();
    UINT i = 0;
    while (i < id) {
      i++;
      it++;
    }
    _array.erase(it);
  }

  bool Array::has(const oValue& value) const {
    for each(const oValue& col in _array) {
      if (col.isValid() && col->isType(value->getID()) && (col == value) >> bool()) return true;
    }
    return false;
  }
}