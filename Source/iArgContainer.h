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

#ifndef __SWIFT_IARGCONTAINER_H__
#define __SWIFT_IARGCONTAINER_H__

#include "iValue.h"
#include "iValueProxy.h"
#include "Exception.h"

namespace Swift {
  class iVariableManager;

  /*
   * iArgContainer
   */
  class iArgContainer {
  public:
    static const size_t allArgs = -1;

  public:
    iArgContainer() : _reqArgs(allArgs ) { }
  public:
    virtual void checkRequired() const = 0;

    inline size_t countRequired() const {
      return _reqArgs;
    }
    inline size_t size() const {
      return count();
    }

    virtual size_t count() const = 0;
    virtual bool empty() const = 0;
    virtual void clear() = 0;

  protected:
    size_t _reqArgs;
  };

  /*
   * ArgContainerT < iArgContainer
   */
  template <class T>
  class ArgContainerT : public iArgContainer {
  public:
    struct sArg {
      T key;

      oValueProxy value;
      oValue defValue;

      bool required;
      int required_type;

      sArg(const T& key, const oValueProxy& value, const oValue& defValue): value(value), 
        key(key), defValue(defValue), required_type(0), required(false) { }
      sArg(const T& key, const oValueProxy& value): value(value), key(key),
        required_type(0), required(false) { }
      sArg(): required_type(0), required(false) { }

      inline bool hasValue() const {
        return value.isValid();
      }
      inline bool hasDefault() const {
        return defValue.isValid();
      }
      inline bool isRequired() const {
        return required;
      }
      inline bool typeMatch(int type) const {
        return !required_type || (required_type == type);
      }

      inline oValue getValue() const {
        return hasValue() ? value->getValue() : new Values::Void;
      }

      inline sArg& setKey(const T& value) {
        key = value;
        return *this;
      }
      inline sArg& setRequiredType(int type) {
        required_type = type;
        return *this;
      }
      inline sArg& setRequired(bool value = true) {
        required = value;
        return *this;
      }
      inline sArg& setDefault(const oValue& value) {
        defValue = value;
        return *this;
      }
      inline sArg& setValue(const oValueProxy& value) {
        value = value;
        return *this;
      }
    };

  public:
    typedef list<sArg> tArgs;

  public:
    inline bool empty() const {
      return _args.empty();
    }
    inline void clear() {
      _args.clear();
    }
    inline size_t count() const {
      return _args.size();
    }
    inline const tArgs& getAll() const {
      return _args;
    }

    inline bool has(const T& key) const {
      for each (const sArg& arg in _args) {
        if (arg.key == key) return true;
      }
      return false;
    }
    inline bool hasValue(const T& key) const {
      for each (const sArg& arg in _args) {
        if (arg.key == key && arg.hasValue()) return true;
      }
      return false;
    }
    inline const sArg& get(const T& key) const {
      for each (const sArg& arg in _args) {
        if (arg.key == key) return arg;
      }
      throw SwiftException();
    }
    inline oValue getValue(const T& key, const oValue& defValue) const {
      try {
        const sArg& arg = get(key);

        if (arg.hasValue()) {
          return arg.value->getValue();
        }
        throw Exception();
      } catch (...) {
        return defValue;
      }
    }
    inline oValue getValue(const T& key) const {
      sArg arg;
      try {
        arg = get(key);
      } catch (...) {
        return new Values::Void;
      }
      oValue v = arg.hasValue() 
        ? arg.getValue() 
        : arg.defValue;

      if (!v.isValid() || !arg.typeMatch(v->getID())) {
        throw SwiftException("Incorrect argument '\" + name + \"' type, should be " + iValue::getName(arg.required_type));
      }
      return v;
    }
    inline void add(const T& key, const oValueProxy& value) {
      if (has(key)) {
        throw SwiftException("Argument redefinition");
      }
      _args.push_back(sArg(key, value));
    }
    inline void add(const sArg& arg) {
      if (has(arg.key)) {
        throw SwiftException("Argument redefinition");
      }
      _args.push_back(arg);
    }
    inline void set(const T& key, const oValueProxy& value) {
      try {
        get(key).value = value;
      } catch (...) {
        add(key, value);
      }
    }
    inline void checkRequired() const {
      for each (const sArg& arg in _args) {
        if (!arg.hasValue() && !arg.hasDefault()) {
          throw SwiftException("Missing argument: " /* + arg.name */);
        }
      }
    }

  protected:
    tArgs _args;
  };

  typedef ArgContainerT<string> NamedContainer;
  typedef ArgContainerT<int> OrderedContainer;
}

#endif // __SWIFT_IARGCONTAINER_H__
