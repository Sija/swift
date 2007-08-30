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

#ifndef __SWIFT_IVARIABLE_MANAGER_H__
#define __SWIFT_IVARIABLE_MANAGER_H__

#include "iValue.h"

namespace Swift {
  class iVariableManager /* : public iObject */ {
  public:
    struct sVariable {
      oValue value;
      bool attrWrite;

      sVariable(const oValue& value, bool attrWrite): value(value), attrWrite(attrWrite) { }
      sVariable() : attrWrite(false) { }
    };

    typedef tHashMap<string, oValue> tVariableData;
    typedef tHashMap<string, sVariable> tVariables;

  public:
    iVariableManager(iVariableManager* parent = NULL): _vm_parent(parent) { }

  public:
    virtual bool addVariable(const string& name, const oValue& value, bool attrWrite = false);
    virtual oValue getVariable(const string& name);
    virtual bool hasVariable(const string& name);

    virtual iVariableManager* find(const string& name);
    virtual bool isWritableVariable(const string& name);
    virtual bool removeVariable(const string& name);

    virtual bool setVariable(const string& name, const oValue& value, bool create = true);
    virtual void setData(const tVariableData& data);
    virtual void clearVariables();

  protected:
    iVariableManager* _vm_parent;
    tVariables _variables;
  };
}

#endif // __SWIFT_IVARIABLE_MANAGER_H__