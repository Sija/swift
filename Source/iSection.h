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

#ifndef __SWIFT_ISECTION_TOKEN_H__
#define __SWIFT_ISECTION_TOKEN_H__

#include "iToken.h"
#include "iArgContainer.h"
#include "iValue.h"
#include "iValueProxy.h"
#include "Exception.h"

namespace Swift {
  class iVariableManager;

  /*
   * iSection < iToken
   */
  class iSection : public iToken {
  public:
    enum enArgsMode {
      noArgs,
      argsOrdered,
      argsNamed
    };

  public:
    iSection(enArgsMode argsMode = noArgs, iVariableManager* vm = 0) : _vm(vm), _args(0), _argsMode(argsMode) {
      if (argsMode == argsNamed) {
        _args = new NamedContainer;
      } else if (argsMode == argsOrdered) {
        _args = new OrderedContainer;
      }
    }
    ~iSection() {
      if (this->getArgsMode()) delete _args;
    }

  protected:
    template <class C>
    inline C* _getArgs(enArgsMode mode) const {
      if (supportArgs(mode)) {
        return static_cast<C*>(_args);
      }
      throw SwiftException();
    }

  public:
    inline enArgsMode getArgsMode() const {
      return _argsMode;
    }
    inline bool supportArgs(enArgsMode mode) const {
      return getArgsMode() == mode;
    }
    inline bool supportArgs() const {
      return getArgsMode() != noArgs;
    }

    virtual inline string getName() const {
      return _name;
    }
    virtual inline void setName(const string& name) {
      _name = name;
    }

    inline OrderedContainer* orderedArgs() const {
      return _getArgs<OrderedContainer>(argsOrdered);
    }
    inline NamedContainer* namedArgs() const {
      return _getArgs<NamedContainer>(argsNamed);
    }

    inline iArgContainer* getArgs() const {
      return _args;
    }
    inline iVariableManager* getVM() const {
      return _vm;
    }

  protected:
    iVariableManager* _vm;
    iArgContainer* _args;
    enArgsMode _argsMode;
    string _name;
  };
}

#endif // __SWIFT_ISECTION_TOKEN_H__