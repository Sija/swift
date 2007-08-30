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

#ifndef __SWIFT_FILE_TEMPLATE_H__
#define __SWIFT_FILE_TEMPLATE_H__

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include "iTemplate.h"
#include "Exception.h"

namespace Swift {
  enum enCodePage {
    CP_UNKNOWN = -1,
    CP_ANSI,
    CP_UTF_16,
    CP_UTF_16_BE,
    CP_UTF_8
  };

  inline bool hasUTF16Bom(const char* buffer) {
    return buffer[0] == (char) 0xFF && buffer[1] == (char) 0xFE;
  }
  inline bool hasUTF16BEBom(const char* buffer) {
    return buffer[0] == (char) 0xFE && buffer[1] == (char) 0xFF;
  }
  inline bool hasUTF8Bom(const char* buffer) {
    return buffer[0] == (char) 0xEF && buffer[1] == (char) 0xBB && buffer[2] == (char) 0xBF;
  }

  inline enCodePage detectTextCodePage(const char* buffer, size_t size, size_t checksize = (size_t) -1) {
    if (size >= 2) {
      if (hasUTF16BEBom(buffer)) {
        return CP_UTF_16_BE;
      } else if (hasUTF16Bom(buffer)) {
        return CP_UTF_16;
      } else if (size >= 3 && hasUTF8Bom(buffer)) {
        return CP_UTF_8;
      }
    }
    if (checksize == (size_t) -1 && checksize > size) {
      checksize = size;
    }
    for (size_t i = 0; i < checksize; i++) {
      if ((buffer[i] & 0xC0) == 0xC0) {
        if ((buffer[i] & 0xFE) == 0xFE) {
          // warn! this string propably saved as UTF_16 little endian
          return CP_UTF_16;

        // utf-8 standard restrictions of lead byte
        } else if (buffer[i] > (char) 0xF4 && buffer[i] < (char) 0xFE ||
          buffer[i] == 0xC0 || buffer[i] == 0xC1) {
          continue;
        }

        size_t bytes = 0;

        while ((buffer[i] & (0x60 >> bytes)) == (0x40 >> bytes) && bytes < 6) {
          bytes++;
        }
        if (bytes && !(buffer[i] & (0x40 >> bytes))) {
          size_t j = i + 1;
          size_t k = j + bytes;

          bool isUTF = true;
          for (; j < k && isUTF && j < checksize; j++) {
            isUTF = isUTF && ((buffer[j] & 0xC0) == 0x80);
          }
          if (isUTF && j < checksize && j == k) {
            return CP_UTF_8;
          }
        }
      }
    }
    return CP_ANSI;
  }

  class FileTemplate : public iTemplate {
  public:
    FileTemplate(const StringRef& path, iVariableManager* parent = NULL, enCodePage codepage = CP_UNKNOWN) : 
      iTemplate(parent), _path(path), _codepage(CP_UNKNOWN), _reqCodepage(codepage) { }

  public:
    inline void load(const StringRef& path) {
      _codepage = CP_UNKNOWN;
      _data.clear();

      int file;
      _wsopen_s(&file, path.w_str(), _O_RDONLY | O_BINARY, SH_DENYNO, _S_IREAD | _S_IWRITE);

      if (file == -1) {
        throw SwiftException("Cannot open file " + path);
      }

      long size = _filelength(file);
      char* buff = new char[size + 2];

      _read(file, buff, size);
      _close(file);

      buff[size] = 0;
      enCodePage cp = detectTextCodePage(buff, size);

      if (_reqCodepage != CP_UNKNOWN && _reqCodepage != cp) {
        delete [] buff;
        throw SwiftException(stringf("File '%s' is saved in different codepage.", path.a_str()));
      }

      /* if (_reqCodepage != CP_UNKNOWN) {
        cp = _reqCodepage;
      } */

      switch (cp) {
        case CP_ANSI: {
          _data = buff;
          break;
        }
        case CP_UTF_8: {
          wchar_t* wbuff = new wchar_t[2 * (size + 1)];
          bool hasBOM = hasUTF8Bom(buff);

          MultiByteToWideChar(CP_UTF8, 0, hasBOM ? buff + 3 : buff, 
            hasBOM ? size - 3 : size, wbuff, 2 * (size + 1));

          _data = wbuff;
          delete [] wbuff;
          break;
        }
        case CP_UTF_16: {
          buff[size + 1] = 0;

          if (hasUTF16Bom(buff)) {
            _data = (wchar_t*) &buff[2];
          } else {
            _data = (wchar_t*) buff;
          }
          break;
        }
        case CP_UTF_16_BE: {
          buff[size + 1] = 0;

          char tmp;
          int i = 2;

          while (i < size + 2) {
            tmp = buff[i];
            buff[i] = buff[i + 1];
            buff[i + 1] = tmp;
            i += 2;
          }
          _data = (wchar_t*) &buff[2];
          break;
        }
      }
      _loaded = true;
      _codepage = cp;

      delete [] buff;
    }
    inline void load() {
      load(_path);
    }

    inline const String& getData() const {
      return _data;
    }
    inline const String& getPath() const {
      return _path;
    }

    inline enCodePage getCodePage() const {
      return _codepage;
    }
    inline enCodePage getReqCodePage() const {
      return _reqCodepage;
    }
    inline void setReqCodePage(enCodePage codepage) {
      _reqCodepage = codepage;
    }

  protected:
    String _path;
    String _data;

    enCodePage _reqCodepage;
    enCodePage _codepage;
  };
}

#endif // __SWIFT_FILE_TEMPLATE_H__