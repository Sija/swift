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
#include "Hash.h"

namespace Swift {
  void Hash::set(const string& name, oValue value) {
    _values[name] = value;
  }

  oValue Hash::get(const string& name) const {
    tValues::const_iterator it = _values.find(name);

    if (it == _values.end()) {
      if (_default.isValid()) {
        return _default;
      }
      throw SwiftException("No such value");
    }
    return it->second;
  }

  bool Hash::hasValue(const oValue& value) const {
    for each(const pair<string, oValue>& val in _values) {
      if (val.second.isValid() && value->isType(val.second->getID())
        && (value == val.second) >> bool()) return true;
    }
    return false;
  }
}