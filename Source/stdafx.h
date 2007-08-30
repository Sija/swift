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

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER        // Allow use of features specific to Windows XP or later.
#define WINVER 0x0501    // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT    // Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501  // Change this to the appropriate value to target other versions of Windows.
#endif            

#ifndef _WIN32_WINDOWS    // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

#include <iostream>
#include <stdio.h>
#include <process.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// #include <google/dense_hash_map>
// #include <google/sparse_hash_map>

#include <hash_map>
#include <list>
#include <deque>
#include <stack>
#include <stdstring.h>
#include <string>

#include <boost/signal.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <Stamina/Object.h>
#include <Stamina/ObjectImpl.h>
#include <Stamina/Exception.h>
#include <Stamina/Criticalsection.h>
#include <Stamina/String.h>
#include <Stamina/Time64.h>
#include <Stamina/Regex.h>
#include <Stamina/Helpers.h>

using namespace Stamina;
using namespace std;
using namespace stdext;
using namespace boost;

#define tHashMap hash_map