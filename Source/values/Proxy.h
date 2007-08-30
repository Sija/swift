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

#ifndef __SWIFT_PROXY_VALUE_H__
#define __SWIFT_PROXY_VALUE_H__

#include "../iValueBase.h"
#include "../iValueProxy.h"

namespace Swift { namespace Values {
  class Proxy : public iValueBase<Proxy, oValueProxy, 45> {
  public:
    Proxy(const oValueProxy& p = oValueProxy()) : _value(p) { }

  public:
    void set(const oValueProxy& p) {
      _value = p;
    }
    const oValueProxy& output() {
      return _value;
    }
    oValue get() const {
      return _value->getValue()->get();
    }
    void clear() {
      _value = 0;
    }

  protected:
    oValueProxy _value;
  };

  SWIFT_REGISTER_TYPE(Proxy, "Proxy");

  inline oValue& operator << (oValue& value, oValueProxy p) {
    return value = new Proxy(p);
  }
  inline oValue& operator << (oValue& value, iValueProxy* p) {
    return value = new Proxy(p);
  }
  inline oValueProxy operator >> (const oValue& value, const oValueProxy& p) {
    return Proxy::assimilate(value);
  }
  inline oValueProxy& operator >> (const oValue& value, oValueProxy& p) {
    return p = Proxy::assimilate(value);
  }
}
  using Values::operator <<;
  using Values::operator >>;
}

#endif // __SWIFT_PROXY_VALUE_H__