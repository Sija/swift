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

#ifndef __SWIFT_OPERATOR_H__
#define __SWIFT_OPERATOR_H__

namespace Swift {
  class Operator {
  public:
    typedef function<void(oValue&, const oValue&)> fOperator;

    enum enOperatorType {
      undefOperator,
      preOperator,
      postOperator
    };

    struct sOperator {
      enOperatorType type;
      fOperator f;

      sOperator(const fOperator& f, enOperatorType type) : f(f), type(type) { }
      sOperator() : f(0), type(undefOperator) { }

      inline void operator ()(oValue& l) {
        f(l, l);
      }
      inline void operator ()(oValue& l, const oValue& r) {
        f(l, r);
      }
    };
    typedef tHashMap<string, sOperator> tOperators;

    struct NoOperatorException {};

  public:
    static inline bool hasOperator(const string& name, enOperatorType type) {
      return _operators.find(getName(name, type)) != _operators.end();
    }
    static inline void bindOperator(const string& name, const fOperator& f, enOperatorType type = postOperator) {
      _operators[getName(name, type)] = sOperator(f, type);
    }
    static inline sOperator& getOperator(const string& name, enOperatorType type = postOperator) {
      tOperators::iterator it = _operators.find(getName(name, type));
      if (it != _operators.end()) {
        return it->second;
      }
      throw NoOperatorException();
    }

  public:
    static inline string getName(const string& name, enOperatorType type) {
      return stringf("%s|%s", type == preOperator ? "pre" : "post", name.c_str());
    }

  protected:
    static tOperators _operators;
  };

  __declspec(selectany) Operator::tOperators Operator::_operators;
}

#endif // __SWIFT_OPERATOR_H__