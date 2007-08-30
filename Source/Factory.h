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

#ifndef __SWIFT_FACTORY_H__
#define __SWIFT_FACTORY_H__

namespace Swift {
  class iSection;
  class iBlock;

  typedef SharedPtr<class Factory> oFactory;

  class Factory : public SharedObject<iSharedObject, LockableObject<iSharedObject, FastMutex>> {
    /* Class version */
    STAMINA_OBJECT_CLASS_VERSION(Factory, iSharedObject, Version(1,0,0,0));

  public:
    typedef iSection* (__stdcall *fCallback)(iBlock* parent);
    typedef tHashMap<string, fCallback> tCallbacks;

  private:
    Factory(const Factory& copy) { }
    Factory() { }

  public:
    static inline Factory* get() {
      if (!_instance/*.isValid()*/) {
        _instance = new Factory;
      }
      return _instance.get();
    }
    static inline iSection* get(const string& name, iBlock* parent = 0) {
      return get()->getInstance(name, parent);
    }

  public:
    iSection* getInstance(const string& name, iBlock* parent);

    inline void bind(const string& name, fCallback callback) {
      _callbacks[name] = callback;
    }
    inline void unbind(const string& name) {
      tCallbacks::iterator it = _callbacks.find(name);
      if (it != _callbacks.end()) {
        _callbacks.erase(it);
      }
    }
    inline bool isBinded(const string& name) {
      return _callbacks.find(name) != _callbacks.end();
    }

  protected:
    tCallbacks _callbacks;

  private:
    static oFactory _instance;
  };

  __declspec(selectany) oFactory Factory::_instance;
}

#endif // __SWIFT_FACTORY_H__
