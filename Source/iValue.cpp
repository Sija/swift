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
#include "iValue.h"

#include "Values/Void.h"

namespace Swift {
  iValue::tCastFunctions iValue::_castFunctions;

  oValue __stdcall iValue::cast(int toType, const oValue& value) {
    try {
      int fromType = value->getID();
      if (fromType == toType) {
        return value;
      }
      if (!fromType) {
        return iValue::create(toType);
      }
      try {
        return getCastFunction(fromType, toType)(value);
      } catch (NoValueException) {
        throw;
      } catch (...) {
        throw SwiftException(stringf("Cannot convert value (from %s to %s)", 
          value->getName().c_str(), getName(toType).c_str()));
      }
    } catch (NoValueException) {
      return iValue::create(toType);
    }
  }

  oValue oValue::operator + (const oValue& value) const {
    return (*this)->add(value);
  }
  oValue oValue::operator - (const oValue& value) const {
    return (*this)->sub(value);
  }
  oValue oValue::operator ! () const {
    return (*this)->not();
  }
  oValue oValue::operator - () const {
    return (*this)->minus();
  }
  oValue oValue::operator == (const oValue& value) const {
    return (*this)->equal(value);
  }
  oValue oValue::operator != (const oValue& value) const {
    return (*this)->notEqual(value);
  }

  UnsupportedOperatorException::UnsupportedOperatorException(const oValue& value, const string& op) : 
    SwiftException(stringf("Operator '%s' for '%s' type is not supported", op.c_str(), value->getName().c_str())) { }
}