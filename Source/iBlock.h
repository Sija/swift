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

#ifndef __SWIFT_IBLOCK_TOKEN_H__
#define __SWIFT_IBLOCK_TOKEN_H__

#include "iVariableManager.h"
#include "iSection.h"

namespace Swift {
  /*
   * iBlock < iSection
   */
  class iBlock : public iSection, public iVariableManager {
  public:
    typedef vector<iToken*> tTokenList;

  public:
    iBlock(iBlock* parent = 0, enArgsMode argMode = noArgs) :
      iSection(argMode, parent), _parent(parent), _alt(0), iVariableManager(parent) { }
    iBlock(iVariableManager* vm, enArgsMode argMode = noArgs, iBlock* parent = 0) :
      iSection(argMode, vm), _parent(parent), _alt(0), iVariableManager(vm) { }

    virtual ~iBlock() {
      if (this->getAlt()) {
        delete _alt;
      }
      this->clearTokens();
    }

  public:
    virtual string getAltName() const {
      return "";
    }

    virtual iBlock* getAlt() const {
      return _alt;
    }
    inline void setAlt(iBlock* alt) {
      _alt = alt;
    }
    inline iBlock* getParent() const {
      return _parent;
    }

    inline void addToken(iToken* token) {
      _tokens.push_back(token);
    }
    inline iToken* getToken(UINT id) const {
      return tokensCount() > id ? 0 : _tokens[id];
    }
    inline bool removeToken(UINT id) {
      if (tokensCount() > id) return false;
      int i = 0;

      for (tTokenList::iterator it = _tokens.begin(); it != _tokens.end(); it++, i++) {
        if (i == id) {
          _tokens.erase(it); return true;
        }
      }
      return false;
    }
<<<<<<< .mine
    inline void clearTokens() {
      for (tTokenList::iterator it = _tokens.begin(); it != _tokens.end(); it++) {
        //delete *it;
      }
      _tokens.clear();
    }
=======
    inline void clearTokens() {
      for (tTokenList::iterator it = _tokens.begin(); it != _tokens.end(); it++) {
        delete *it;
      }
      _tokens.clear();
    }
>>>>>>> .r90
    inline size_t tokensCount() const {
      return _tokens.size();
    }
<<<<<<< .mine

    virtual inline void output(StringRef& out) {
      for (tTokenList::iterator it = _tokens.begin(); it != _tokens.end(); it++) {
        (*it)->output(out);
=======

    virtual inline void output(StringRef& out) {
      if (evaluates()) {
        for (tTokenList::iterator it = _tokens.begin(); it != _tokens.end(); it++) {
          (*it)->output(out);
        }
      } else if (getAlt()) {
        _alt->output(out);
>>>>>>> .r90
      }
    }
    virtual inline String output() {
      String out;
      
      if (evaluates()) {
        output(out);
      } else if (getAlt()) {
        _alt->output(out);
      }
      return out;
    }

    virtual bool evaluates() const {
      return true;
    }

  protected:
    tTokenList _tokens;

    iBlock* _parent;
    iBlock* _alt;
  };
}

#endif // __SWIFT_IBLOCK_TOKEN_H__