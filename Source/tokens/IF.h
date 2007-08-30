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

#ifndef __SWIFT_IF_TOKEN_H__
#define __SWIFT_IF_TOKEN_H__

#include "../iBlock.h"
#include "../values/Bool.h"

namespace Swift { namespace Tokens {
  class IF: public iBlock {
  public:
    IF(iBlock* parent) : iBlock(parent, argsOrdered) { }

  public:
    static iSection* __stdcall getInstance(iBlock* parent) {
      return new IF(parent);
    }

  public:
    inline string getAltName() const {
      return "else";
    }

  public:
    bool evaluates() const {
      const OrderedContainer::tArgs& args = orderedArgs()->getAll();
      bool value = false;

      for each (const OrderedContainer::sArg& arg in args) {
        value |= arg.getValue() >> bool();
      }
      return value;
    }
  };

  SWIFT_REGISTER_TOKEN(IF, "if");
}}

#endif // __SWIFT_IF_TOKEN_H__