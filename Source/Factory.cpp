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

#include "stdafx.h"

#include "Exception.h"
#include "Factory.h"

#include "iSection.h"
#include "iBlock.h"

namespace Swift {
  iSection* Factory::getInstance(const string& name, iBlock* parent) {
    tCallbacks::iterator it = _callbacks.find(name);

    if (it != _callbacks.end()) {
      iSection* obj = it->second(parent);
      if (obj) obj->setName(name);

      return obj;
    }
    throw SwiftException("No instance of " + name);
  }
}