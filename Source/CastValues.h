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

#pragma once

#ifndef __SWIFT_CASTVALUES_H__
#define __SWIFT_CASTVALUES_H__

#include "values/String.h"
#include "values/Int.h"
#include "values/Int64.h"
#include "values/Bool.h"
#include "values/Date.h"
#include "values/RegExPattern.h"
#include "values/Array.h"
#include "values/Hash.h"
#include "values/Proxy.h"
#include "values/Void.h"

namespace Swift {
  inline oValue strToInt(const oValue& value) {
    return _wtoi(((Values::String*)value.get())->output().w_str());
  }
  inline oValue strToInt64(const oValue& value) {
    return _wtoi64(((Values::String*)value.get())->output().w_str());
  }
  inline oValue strToBool(const oValue& value) {
    const String& retValue = ((Values::String*)value.get())->output();
    return !(!retValue.size() || retValue == "false");
  }

  inline oValue intToStr(const oValue& value) {
    char buff[128];
    _itoa_s(((Values::Int*)value.get())->output(), buff, 128, 10);
    return buff;
  }
  inline oValue intToBool(const oValue& value) {
    return ((Values::Int*)value.get())->output() != 0 ? true : false;
  }
  inline oValue intToInt64(const oValue& value) {
    return (__int64) ((Values::Int*)value.get())->output();
  }

  inline oValue int64ToStr(const oValue& value) {
    char buff[128];
    _i64toa_s(((Values::Int64*)value.get())->output(), buff, 128, 10);
    return buff;
  }
  inline oValue int64ToBool(const oValue& value) {
    return ((Values::Int64*)value.get())->output() != 0 ? true : false;
  }
  inline oValue int64ToInt(const oValue& value) {
    return (int) ((Values::Int64*)value.get())->output();
  }

  inline oValue boolToStr(const oValue& value) {
    return ((Values::Bool*)value.get())->output() ? "true" : "false";
  }
  inline oValue dateToStr(const oValue& value) {
    return ((Values::Date*)value.get())->output().strftime("%X, %x");
  }
  inline oValue regExpToStr(const oValue& value) {
    return ((Values::RegExPattern*)value.get())->output();
  }
  inline oValue voidToStr(const oValue& value) {
    return "";
  }
  inline oValue hashToStr(const oValue& value) {
    return value->getName();
  }
  inline oValue arrayToStr(const oValue& value) {
    return value->getName();
  }
}

#endif // __SWIFT_CASTVALUES_H__