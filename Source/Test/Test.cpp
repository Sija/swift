#include "stdafx.h"
#include "../Swift.h"

using namespace Swift;

void neg(oValue& l) {
  l = -l;
}
void not(oValue& l) {
  l = !l;
}

void add(oValue& l, const oValue& r) {
  l = l + r;
}
void sub(oValue& l, const oValue& r) {
  l = l - r;
}

void assign(oValue& l, const oValue& r) {
  l = r;  
}
void equal(oValue& l, const oValue& r) {
  l = l == r;
}
void notEqual(oValue& l, const oValue& r) {
  l = l != r;
}

void and(oValue& l, const oValue& r) {
  l = l >> bool() && r >> bool();
}
void or(oValue& l, const oValue& r) {
  if (l >> bool()) {
    return;
  }
  if (r >> bool()) {
    l = r;
  } else {
    l = false;
  }
}

void regex_equal(oValue& l, const oValue& r) {
  String pattern, subject;
  if (l->isType<Values::RegExPattern>()) {
    pattern = l >> String();
    subject = r >> String();
  } else if (r->isType<Values::RegExPattern>()) {
    pattern = r >> String();
    subject = l >> String();
  } else {
    throw SwiftException("Incorrect use of regex operator");
  }
  l = RegEx::doMatch(pattern.a_str(), subject.a_str()) > 0;
}
void regex_notEqual(oValue& l, const oValue& r) {
  regex_equal(l, r);
  l = !l;
}


oValue tFunc(const Globals::tFuncArguments& args) {
  return args.size() ? args[0] : false;
}

int _tmain(int argc, _TCHAR* argv[]) {
  try {
    /**
     * default casts
     */
    iValue::addCastFunction(Values::Int::id, Values::Int64::id, &intToInt64);
    iValue::addCastFunction(Values::Int::id, Values::String::id, &intToStr);
    iValue::addCastFunction(Values::Int::id, Values::Bool::id, &intToBool);

    iValue::addCastFunction(Values::Int64::id, Values::String::id, &int64ToStr);
    iValue::addCastFunction(Values::Int64::id, Values::Int::id, &int64ToInt);
    iValue::addCastFunction(Values::Int64::id, Values::Bool::id, &int64ToBool);

    iValue::addCastFunction(Values::String::id, Values::Bool::id, &strToBool);
    iValue::addCastFunction(Values::String::id, Values::Int::id, &strToInt);
    iValue::addCastFunction(Values::String::id, Values::Int64::id, &strToInt64);

    iValue::addCastFunction(Values::Void::id, Values::String::id, &voidToStr);
    iValue::addCastFunction(Values::Bool::id, Values::String::id, &boolToStr);
    iValue::addCastFunction(Values::Date::id, Values::String::id, &dateToStr);
    iValue::addCastFunction(Values::RegExPattern::id, Values::String::id, &regExpToStr);
    iValue::addCastFunction(Values::Hash::id, Values::String::id, &hashToStr);
    iValue::addCastFunction(Values::Array::id, Values::String::id, &arrayToStr);

    /**
     * default short operators
     */
    Operator::bindOperator("!", reinterpret_cast<void(*)(oValue&, const oValue&)>(&not), Operator::preOperator);
    Operator::bindOperator("-", reinterpret_cast<void(*)(oValue&, const oValue&)>(&neg), Operator::preOperator);

    Operator::bindOperator("=", &assign);
    Operator::bindOperator("=~", &regex_equal);
    Operator::bindOperator("!~", &regex_notEqual);

    Operator::bindOperator("==", &equal);
    Operator::bindOperator("!=", &notEqual);

    Operator::bindOperator("&&", &and);
    Operator::bindOperator("||", &or);

    Operator::bindOperator("+", &add);
    Operator::bindOperator("-", &sub);

    /**
     * default textual operators
     */
    Operator::bindOperator("not", reinterpret_cast<void(*)(oValue&, const oValue&)>(&not), Operator::preOperator);

    Operator::bindOperator("is", &assign);
    Operator::bindOperator("req", &regex_equal);
    Operator::bindOperator("rneq", &regex_notEqual);

    Operator::bindOperator("eq", &equal);
    Operator::bindOperator("neq", &notEqual);

    Operator::bindOperator("and", &and);
    Operator::bindOperator("or", &or);

    Operator::bindOperator("add", &add);
    Operator::bindOperator("sub", &sub);

    /**
     * war zone, no passaran
     */
    oTemplate tpl = new FileTemplate("test.tpl", 0, CP_ANSI);

    Globals* vars = Globals::get();
    vars->addFunction("tFunc", &tFunc);

    vars->addVariable("x", "sssaj !");
    vars->addVariable("y", 324324324);
    vars->addVariable("z", false);

    Hash h(0);
    h.set("abc", "tak");
    h.set("xorg", 158922);
    h.set("zing", false);

    Array a("there's no dick in the village");
    a << "ssaj" << "mego" << "bena" << 10 << false << h;

    h.set("da", a);

    tpl->addVariable("tablic", a);
    tpl->addVariable("hasz", h);

    Parser parser;
    parser.parse(tpl);

    if (argc == 1) {
      String out = tpl->output();
      std::cout << out;
    } else {
      for (int i = 0; i < 100; i++) {
        vars->setVariable("y", i);
        std::cout << "\r\n" << tpl->output();
      }
    }
  } catch (Stamina::Exception &e) {
    std::cout << "(Stamina) Exception: " << e.getReason();
  } catch (exception &e) {
    std::cout << "(std) Exception: " << e.what();
  }
	return 0;
}