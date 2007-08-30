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

#ifndef __SWIFT_IVALUEBASE_H__
#define __SWIFT_IVALUEBASE_H__

#include "iValue.h"

#define SWIFT_REGISTER_TYPE(klass, name) \
  __declspec(selectany) iValue::_init _type_init_##klass(klass::id, name, &iValue::create<klass>);

namespace Swift {
  template <class V, class T, int id>
  class iValueBase : public iValue {
  public:
    static inline T assimilate(const oValue& value) {
      return iValue::assimilate<V,T>(value);
    }
    inline oValue getCopy() {
      V* v = new V;
      __if_exists(V::set) {
        v->set(output());
      }
      return v;
    }

    inline string getName() const {
      return iValue::getName(id);
    }
    inline int getID() const {
      return id;
    }
    virtual const T& output() = 0;

  public:
    const static int id = id;
  };
}

#endif // __SWIFT_IVALUEBASE_H__