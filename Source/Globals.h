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

#ifndef __SWIFT_GLOBALS_H__
#define __SWIFT_GLOBALS_H__

#include "iVariableManager.h"

namespace Swift {
  typedef SharedPtr<class Globals> oGlobals;

  class Globals: public iVariableManager, public SharedObject<iSharedObject, LockableObject<iSharedObject, FastMutex>> {
    /* Class version */
    STAMINA_OBJECT_CLASS_VERSION(Globals, iSharedObject, Version(0,0,0,1));

  public:
    typedef vector<oValue> tFuncArguments;
    typedef function<oValue(const tFuncArguments&)> fOnCallFunction;

    struct sFunction {
      fOnCallFunction callback;
      int argsNum;

      sFunction(const fOnCallFunction& func, int argsNum): callback(func), argsNum(argsNum) { }
      sFunction(): argsNum(0) { }
    };
    typedef tHashMap<string, sFunction> tFunctions;

  public:
    static const int argsAll = -1;

  private:
    Globals(const Globals& self) { }
    Globals() { }

  public:
    static inline Globals* get() {
      if (!_instance) {
        _instance = new Globals;
      }
      return _instance.get();
    }

    bool addFunction(const string& name, const fOnCallFunction& func, int args = argsAll);
    bool hasFunction(const string& name) const;
    void removeFunction(const string& name);

    inline oValue callFunction(const string& name, const oValue& arg) {
      tFuncArguments args;
      args.push_back(arg);

      return callFunction(name, args);
    }
    oValue callFunction(const string& name, const tFuncArguments& arguments);

  protected:
    tFunctions _functions;

  private:
    static oGlobals _instance;
  };
}

#endif // __SWIFT_GLOBALS_H__