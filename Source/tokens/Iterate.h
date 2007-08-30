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

#ifndef __SWIFT_ITERATE_TOKEN_H__
#define __SWIFT_ITERATE_TOKEN_H__

#include "../values/Hash.h"
#include "../values/Array.h"
#include "../values/Int.h"
#include "../values/String.h"

#include "../iBlock.h"

#include "Continue.h"
#include "Break.h"

namespace Swift { namespace Tokens {
  class Iterate: public iBlock {
  public:
    Iterate(iBlock* parent) : iBlock(parent, argsNamed) { }

  public:
    static iSection* __stdcall getInstance(iBlock* parent) {
      return new Iterate(parent);
    }

  public:
    inline string getName() const {
      return "iterate";
    }
    inline string getAltName() const {
      return "rescue";
    }
    inline bool evaluates() const {
      return _args->size() > 0;
    }

  public:
    inline void output(StringRef& out) {
      if (_args->size() != 1) {
        throw SwiftException("You must provide exactly one argument");
      }

      const NamedContainer::sArg& arg = namedArgs()->getAll().front();
      oValue value = arg.getValue();

      Hash h(false);

      bool breakFound = false;
      size_t count = 0;

      if (value->isType<Values::Array>()) {
        const Array& arr = ((Values::Array*)value.get())->output();
        count = arr.count();

        for (size_t i = 0; (i < count) && !breakFound; i++) {
          h.set("first", i == 0);
          h.set("last", i == count - 1);
          h.set("key", i);
          h.set("value", arr.get(i));

          setVariable(arg.key, h);

          for each (iToken* token in _tokens) {
            try {
              token->output(out);
            } catch (ContinueException) {
              break;
            } catch (BreakException) {
              breakFound = true;
              break;
            }
          }
        }
        return;
      } else if (value->isType<Values::Hash>()) {
        const Hash::tValues& values = ((Values::Hash*)value.get())->output().getData();
        count = values.size();

        int i = 0;
        for (Hash::tValues::const_iterator it = values.begin(); (it != values.end()) && !breakFound; it++, i++) {
          h.set("first", i == 0);
          h.set("last", i == count - 1);
          h.set("key", it->first);
          h.set("value", it->second);

          setVariable(arg.key, h);

          for each (iToken* token in _tokens) {
            try {
              token->output(out);
            } catch (ContinueException) {
              break;
            } catch (BreakException) {
              breakFound = true;
              break;
            }
          }
        }
        return;
      }
      throw SwiftException("You can iterate only through Array/Hash types");
    }
  };

  SWIFT_REGISTER_TOKEN(Iterate, "iterate");
}}

#endif // __SWIFT_ITERATE_TOKEN_H__