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

#ifndef __SWIFT_H__
#define __SWIFT_H__

#include "stdafx.h"

#include "TextTemplate.h"
#include "FileTemplate.h"

#include "Factory.h"
#include "Parser.h"

#ifndef SWIFT_NO_DEFAULT_CASTS
  #include "CastValues.h"
#endif

#ifndef SWIFT_NO_DEFAULT_TOKENS
  #include "tokens/Unless.h"
  #include "tokens/IF.h"
  #include "tokens/Include.h"
  #include "tokens/Iterate.h"
#endif

#endif // __SWIFT_H__