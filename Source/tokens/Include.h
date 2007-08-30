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

#ifndef __SWIFT_INCLUDE_TOKEN_H__
#define __SWIFT_INCLUDE_TOKEN_H__

#include "../iSection.h"
#include "../FileTemplate.h"
#include "../Parser.h"
#include "../Exception.h"

#include "../values/String.h"

namespace Swift { namespace Tokens {
  class Include: public iSection {
  public:
    Include(iVariableManager* vm) : iSection(argsNamed, vm) {
      // setRequired("file", Values::String::id);
      NamedContainer::sArg fileArg("file", 0, oValue());

      fileArg.setRequired().setRequiredType(Values::String::id);
      namedArgs()->add(fileArg);

      namedArgs()->add(NamedContainer::sArg("inherit", 0, true));
      // setDefault("inherit", true);

      _mtime.dwHighDateTime = 0;
      _mtime.dwLowDateTime = 0;
    }

  public:
    static iSection* __stdcall getInstance(class iBlock* parent) {
      return new Include(parent);
    }

  public:
    inline String output() {
      String path = namedArgs()->getValue("file") >> String();
      FILETIME ftWrite = {0};

      HANDLE hFile = CreateFileW(path.w_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
      if (hFile == INVALID_HANDLE_VALUE || !GetFileTime(hFile, 0, 0, &ftWrite)) {
        throw SwiftException(stringf("Cannot open file: %s", path.a_str()));
      }
      CloseHandle(hFile);

      if (_mtime.dwHighDateTime != ftWrite.dwHighDateTime || _mtime.dwLowDateTime != ftWrite.dwLowDateTime) {
        _file = new FileTemplate(path, namedArgs()->getValue("inherit") >> bool() ? _vm : 0);
        _mtime.dwHighDateTime = ftWrite.dwHighDateTime;
        _mtime.dwLowDateTime = ftWrite.dwLowDateTime;

        try {
          copyArgumentsToVariables();

          Parser parser;
          parser.parse(_file);
        } catch (const Exception& e) {
          throw SwiftException(stringf("Error while including file: '%s', %s", path.a_str(), e.getReason().a_str()));
        }
      }
      if (_file.isValid()) {
        return _file->output();
      }
      return "";
    }

    void copyArgumentsToVariables() {
      for each (const NamedContainer::sArg& arg in namedArgs()->getAll()) {
        // _file->addVariable(arg.name, arg.getValue());
      }
    }

  protected:
    FILETIME _mtime;
    oTemplate _file;
  };

  SWIFT_REGISTER_TOKEN(Include, "include");
}}

#endif // __SWIFT_INCLUDE_TOKEN_H__