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

#ifndef __SWIFT_PARSER_EXCEPTION_H__
#define __SWIFT_PARSER_EXCEPTION_H__

#include "Exception.h"
#include "Parser.h"

namespace Swift {
  class ParserException: public SwiftException {
  public:
    ParserException(Parser* parser, const StringRef& reason) :
      SwiftException(stringf("%s at %s", reason.c_str(), parser->getPosition().c_str())) { }
  };
};

#endif // __SWIFT_PARSER_EXCEPTION_H__