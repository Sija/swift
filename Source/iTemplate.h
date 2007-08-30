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

#ifndef __SWIFT_ITEMPLATE_H__
#define __SWIFT_ITEMPLATE_H__

#include "Globals.h"
#include "iBlock.h"

namespace Swift {
  class iTemplate : public SharedObject<iSharedObject, LockableObject<iSharedObject, FastMutex>>, public iVariableManager {
    /* Class version */
    STAMINA_OBJECT_CLASS_VERSION(iTemplate, iSharedObject, Version(1,0,0,0));

  public:
    iTemplate(iVariableManager* parent = NULL) : _token(0), _loaded(false),
      iVariableManager(parent ? parent : Globals::get()) { }
    inline ~iTemplate() {
      clear();
    }

  public:
    virtual iBlock* getToken() const {
      return _token;
    }
    virtual void setToken(iBlock* token) {
      if (_token) delete _token;
      _token = token;
    }
    virtual String output() {
      if (_token) {
        return _token->output();
      }
      return String();
    }
    virtual const String& getData() const = 0;

    virtual void clear() {
      _loaded = false;
      setToken(0);
    }
    virtual bool loaded() const {
      return _loaded;
    }
    virtual void reload() {
      clear();
      load();
    }
    virtual void load() = 0;

  protected:
    iBlock* _token;
    bool _loaded;
  };

  typedef SharedPtr<iTemplate> oTemplate;
}

#endif // __SWIFT_ITEMPLATE_H__