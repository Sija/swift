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

#ifndef __SWIFT_IVALUE_PROXY_H__
#define __SWIFT_IVALUE_PROXY_H__

namespace Swift {
  class iValueProxy : public SharedObject<iSharedObject, LockableObject<iSharedObject, FastMutex>> {
  public:
    virtual class oValue getValue() = 0;
  };

  typedef SharedPtr<iValueProxy> oValueProxy;
}

#endif // __SWIFT_IVALUE_PROXY_H__