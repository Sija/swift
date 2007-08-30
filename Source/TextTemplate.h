#pragma once

#ifndef __SWIFT_TEXT_TEMPLATE_H__
#define __SWIFT_TEXT_TEMPLATE_H__

#include <fstream>

#include "iTemplate.h"
#include "Exception.h"

namespace Swift {
  class TextTemplate : public iTemplate {
  public:
    TextTemplate(const StringRef& data, iVariableManager* parent = NULL) : 
      iTemplate(parent), _data(data) { }

  public:
    inline void set(const StringRef& data) {
      _data = data;
    }
    inline const String& getData() const {
      return _data;
    }
    inline void load() { }

  protected:
    String _data;
  };
}

#endif // __SWIFT_TEXT_TEMPLATE_H__