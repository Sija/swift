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

#ifndef __SWIFT_DATE_VALUE_H__
#define __SWIFT_DATE_VALUE_H__

#include "../iValueBase.h"

namespace Swift { namespace Values {
  class Date : public iValueBase<Date, Date64, 20> {
  public:
    Date(const Date64& d = Date64()) : _date(d) { }

  public:
    void set(const Date64& d) {
      _date = d;
    }
    const Date64& output() {
      return _date;
    }
    void clear() {
      _date = Date64();
    }

  public:
    oValue add(const oValue& value) const {
      return Date64(_date.getTime64() + assimilate(value).getTime64());
    }
    oValue sub(const oValue& value) const {
      return Date64(_date.getTime64() - assimilate(value).getTime64());
    }
    oValue equal(const oValue& value) const {
      return _date == assimilate(value);
    }
    oValue notEqual(const oValue& value) const {
      return _date != assimilate(value);
    }

  protected:
    Date64 _date;
  };

  SWIFT_REGISTER_TYPE(Date, "Date");

  inline oValue& operator << (oValue& value, Date64& d) {
    return value = new Date(d);
  }
  inline oValue& operator << (oValue& value, const Date64& d) {
    return value = new Date(d);
  }
  inline Date64& operator >> (const oValue& value, Date64& d) {
    return d = Date::assimilate(value);
  }
}
  using Values::operator <<;
  using Values::operator >>;
}

#endif // __SWIFT_DATE_VALUE_H__