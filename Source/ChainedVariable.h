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

#ifndef __SWIFT_CHAIN_VARIABLE_H__
#define __SWIFT_CHAIN_VARIABLE_H__

#include "iValueProxy.h"
#include "Variable.h"

#include "values/Hash.h"
#include "values/Array.h"
#include "values/Int.h"

namespace Swift {
  class ChainedVariable: public iValueProxy {
  public:
    struct sLink {
      string name;
      oValueProxy index;
      bool isArray;

      sLink(const oValueProxy& proxy) : index(proxy), isArray(true) { }
      sLink(const string& name) : name(name), isArray(false) { }
    };
    typedef list<sLink> tLinks;

  public:
    ChainedVariable(const oValueProxy& base) : _base(base) { }

  public:
    inline void addLink(const string& key) {
      _links.push_back(key);
    }
    inline void addLink(const oValueProxy& proxy) {
      _links.push_back(proxy);
    }

  public:
    oValue getValue() {
      oValue value = _base->getValue();

      for each (const sLink& link in _links) {
        try {
          if (link.isArray) {
            if (!value->isType<Values::Array>()) {
              throw SwiftException("Element is not a Array");
            }
            value = ((Values::Array*)value.get())->output().get(link.index->getValue() >> int());
          } else {
            if (!value->isType<Values::Hash>()) {
              throw SwiftException("Element is not a Hash");
            }
            value = ((Values::Hash*)value.get())->output().get(link.name);
          }
        } catch (NoValueException) {
          throw SwiftException(stringf("Element is not a %s", link.isArray ? "Array" : "Hash"));
        }
      }
      return value;
    }

    void setValue(const oValue& v) {
      if (!dynamic_cast<Variable*>(_base.get())) {
        throw SwiftException("You cannot assign to temporary var or empty value");
      }
      oValue value = _base->getValue();

      size_t i = 0;
      for (tLinks::iterator it = _links.begin(); it != _links.end(), i < _links.size() - 1; it++, i++) {
        try {
          if (it->isArray) {
            if (!value->isType<Values::Array>()) {
              throw SwiftException("Element is not a Array");
            }
            value = ((Values::Array*)value.get())->output().get(it->index->getValue() >> int());
          } else {
            if (!value->isType<Values::Hash>()) {
              throw SwiftException("Element is not a Hash");
            }
            value = ((Values::Hash*)value.get())->output().get(it->name);
          }
        } catch (NoValueException) {
          throw SwiftException(stringf("Element is not a %s", it->isArray ? "Array" : "Hash"));
        }
      }

      const sLink& link = _links.back();
      try {
        if (link.isArray) {
          if (!value->isType<Values::Array>()) {
            throw SwiftException("Element is not a Array");
          }
          ((Values::Array*)value.get())->getArray().set(link.index->getValue() >> int(), v);
        } else {
          if (!value->isType<Values::Hash>()) {
            throw SwiftException("Element is not a Hash");
          }
          ((Values::Hash*)value.get())->getHash().set(link.name, v);
        }
      } catch (NoValueException) {
        throw SwiftException(stringf("Element is not a %s", link.isArray ? "Array" : "Hash"));
      }
    }

  protected:
    oValueProxy _base;
    tLinks _links;
  };
}

#endif // __SWIFT_CHAIN_VARIABLE_H__