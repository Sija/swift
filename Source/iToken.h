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

#ifndef __SWIFT_ITOKEN_H__
#define __SWIFT_ITOKEN_H__

#include "Factory.h"

#define SWIFT_REGISTER_TOKEN(klass, name) \
  __declspec(selectany) iToken::_init _token_init_##klass(name, &klass::getInstance);

namespace Swift {
  class iToken /*: public iObject*/ {
  public:
    const static struct _init {
      _init(const string& name, const Factory::fCallback& callback) {
        Factory::get()->bind(name, callback);
      }
    };

  public:
    virtual string getName() const = 0;

    virtual void output(StringRef& out) {
      out += PassStringRef(output());
    }
    virtual String output() = 0;
  };
}

#endif // __SWIFT_ITOKEN_H__