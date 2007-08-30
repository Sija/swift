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

#ifndef __SWIFT_VOID_VALUE_H__
#define __SWIFT_VOID_VALUE_H__

#include "../iValueBase.h"
#include "Bool.h"

namespace Swift { namespace Values {
  class Void : public iValue {
  public:
    inline string getName() const {
      return iValue::getName(id);
    }
    inline int getID() const {
      return 0;
    }
    inline oValue getCopy() {
      return new Void;
    }
    inline void clear() { }

  public:
    oValue not() const {
      return true;
    }
    oValue equal(const oValue& value) const {
      return !Bool::assimilate(value);
    }
    oValue notEqual(const oValue& value) const {
      return Bool::assimilate(value);
    }

  public:
    const static int id = 0;
  };

  SWIFT_REGISTER_TYPE(Void, "Void");
}}

#endif // __SWIFT_VOID_VALUE_H__