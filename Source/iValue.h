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

#ifndef __SWIFT_IVALUE_H__
#define __SWIFT_IVALUE_H__

#include "Exception.h"

using namespace std;
using namespace Stamina;

namespace Swift {
  class iValue;
  class oValue;

  /**
   * Unsupported Operator Exception
   */
  class UnsupportedOperatorException : public SwiftException {
  public:
    UnsupportedOperatorException(const oValue& value, const string& op);
  };

  /**
   * No Value Exception
   */
  class NoValueException : public SwiftException {
  public:
    NoValueException() : SwiftException("Value is empty, cannot proceed.") { }
  };

  /**
   * Export operator
   */
  oValue operator >> (const oValue& v, oValue& value);

  /**
   * SharedPtr wrapper for iValue*
   */
  class oValue : public SharedPtr<iValue> {
  public:
    template <class T>
    oValue(const T& value) {
      *this << value;
    }

    template <class T>
    oValue(T* value) {
      __if_not_exists(T::iValueType) {
        *this << value;
      }
      __if_exists(T::iValueType) {
        set(value);
      }
    }

    oValue(iValue* obj = 0) : SharedPtr<iValue>(obj) { }
    oValue(const iValue* obj) : SharedPtr<iValue>((iValue*) obj) { }
    oValue(iValue& obj) : SharedPtr<iValue>(obj) { }
    oValue(const oValue& obj) : SharedPtr<iValue>(&*obj) { }

  public:
    inline oValue& operator = (const oValue& value) {
      set(&*value);
      return *this;
    }

    inline iValue* operator -> () const {
      if (!isValid()) {
        throw NoValueException();
      }
      return get();
    }

#ifdef __SWIFT_STRING_VALUE_H__
    inline operator String () const {
      return (*this >> String());
    }
    inline operator wstring () const {
      return (*this >> String()).w_string();
    }
    inline operator string () const {
      return (*this >> String()).a_string();
    }
#endif

#ifdef __SWIFT_DATE_VALUE_H__
    inline operator Date64 () const {
      return (*this >> Date64());
    }
#endif

  public:
    oValue operator + (const oValue& value) const;
    oValue operator - (const oValue& value) const;
    oValue operator ! () const;
    oValue operator - () const;
    oValue operator == (const oValue& value) const;
    oValue operator != (const oValue& value) const;
  };

  /**
   * Base Value class
   */
  class iValue : public SharedObject<iSharedObject, LockableObject<iSharedObject, FastMutex>> {
  public:
    /* Class version */
    STAMINA_OBJECT_CLASS_VERSION(iValue, iSharedObject, Version(0,0,0,1));

  public:
    typedef oValue (*cValueCreate)(void);
    typedef void iValueType;

  public:
    const static struct _init {
      _init(int id, const string& name, const cValueCreate& callback) {
        iValue::registerValue(id, name, callback);
      }
    };

  public:
    struct sValueData {
      sValueData(const string& name, const cValueCreate& callback): 
        name(name), callback(callback) { }
      sValueData(): callback(0) { }

      cValueCreate callback;
      string name;
    };

    typedef function<oValue(const oValue&)> fCastValue;

    typedef tHashMap<int, fCastValue> tCastFunctions;
    typedef tHashMap<int, sValueData> tValuesData;

  /*
   * Cast related methods
   */
  public:
    static inline int getCastID(int fromType, int toType) {
      return fromType << 16 | toType & 0xFFFF;
    }
    template <class T, class V>
    static inline V assimilate(const oValue& value) {
      return ((T*)cast<T>(value).get())->output();
    }
    template <class T>
    static inline oValue cast(const oValue& value) {
      return cast(T::id, value);
    }
    static oValue __stdcall cast(int toType, const oValue& value);

    static inline bool hasCastFunction(int fromType, int toType) {
      return _castFunctions.find(getCastID(fromType, toType)) != _castFunctions.end();
    }
    static void __stdcall addCastFunction(int fromType, int toType, const fCastValue& func) {
      if (hasCastFunction(fromType, toType)) {
        throw SwiftException("There's already assigned cast function");
      }
      _castFunctions[getCastID(fromType, toType)] = func;
    }
    static const fCastValue& __stdcall getCastFunction(int fromType, int toType) {
      tCastFunctions::iterator it = _castFunctions.find(getCastID(fromType, toType));
      if (it != _castFunctions.end()) {
        return it->second;
      }
      throw SwiftException("No cast function assigned");
    }
    static void __stdcall removeCastFunction(int fromType, int toType) {
      tCastFunctions::iterator it = _castFunctions.find(getCastID(fromType, toType));
      if (it != _castFunctions.end()) {
        _castFunctions.erase(it);
      }
    }

  /*
   * Value data
   */
  public:
    static inline bool isValueRegistered(int id) {
      return _valuesData.find(id) != _valuesData.end();
    }
    static void inline registerValue(int id, const string& name, const cValueCreate& callback) {
      if (!isValueRegistered(id)) {
        _valuesData[id] = sValueData(name, callback);
      }
    }
    static const sValueData& __stdcall getValueData(int id) {
      if (!isValueRegistered(id)) {
        throw NoValueException();
      }
      return _valuesData[id];
    }
    static void __stdcall removeValueData(int id) {
      tValuesData::iterator it = _valuesData.find(id);
      if (it != _valuesData.end()) {
        _valuesData.erase(it);
      }
    }

  /*
   * Factory methods
   */
  public:
    static inline oValue create(int id) {
      cValueCreate callback = getValueData(id).callback;
      if (callback) {
        return callback();
      }
      throw SwiftException(stringf("Cannot create value (%s)", getName(id).c_str()));
    }
    template <class T>
    static inline oValue create() {
      return new T;
    }
    template <class T, class Z>
    static inline oValue create(const Z& z) {
      return new T(z);
    }
    template <class T, class Z>
    static inline oValue create(Z* z) {
      return new T(z);
    }

    virtual oValue getCopy() = 0;
    virtual oValue get() const {
      return this;
    }

  /*
   * Other methods
   */
    inline bool isType(int id) {
      return getID() == id;
    }
    template <class T> inline bool isType() {
      return isType(T::id);
    }

    static string __stdcall getName(int id) {
      if (!isValueRegistered(id)) {
        return "unknown";
      }
      return getValueData(id).name;
    }

    virtual string getName() const = 0;
    virtual int getID() const = 0;

    virtual void clear() = 0;

  /*
   * Overloadable operators
   */
  public:
    virtual oValue add(const oValue& value) const {
      throw UnsupportedOperatorException(this, "+");
    }
    virtual oValue sub(const oValue& value) const {
      throw UnsupportedOperatorException(this, "-");
    }
    virtual oValue not() const {
      throw UnsupportedOperatorException(this, "!");
    }
    virtual oValue minus() const {
      throw UnsupportedOperatorException(this, "-");
    }
    virtual oValue equal(const oValue& value) const {
      throw UnsupportedOperatorException(this, "==");
    }
    virtual oValue notEqual(const oValue& value) const {
      throw UnsupportedOperatorException(this, "!=");
    }

  protected:
    static tCastFunctions _castFunctions;
    static tValuesData _valuesData;
  };

  __declspec(selectany) iValue::tValuesData iValue::_valuesData;
}

#endif //__SWIFT_IVALUE_H__