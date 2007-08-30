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

#ifndef __SWIFT_EXPRESSION_TOKEN_H__
#define __SWIFT_EXPRESSION_TOKEN_H__

#include "../iToken.h"
#include "../Expression.h"

#include "../values/String.h"

namespace Swift { namespace Tokens {
  class Expression: public iToken, public Swift::Expression {
  public:
    Expression(iVariableManager* vm) : Swift::Expression(vm) { }

  public:
    inline string getName() const {
      return "Expression";
    }

  public:
    inline String output() {
      return getValue() >> String();
    }
  };
}}

#endif // __SWIFT_EXPRESSION_TOKEN_H__
