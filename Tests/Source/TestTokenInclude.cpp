#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/Include.h"
#include "../../Source/values/String.h"
#include "../../Source/TextTemplate.h"
#include "../../Source/Factory.h"
#include "../../Source/Globals.h"
#include "../../Source/Parser.h"

using namespace Swift;

class TestTokenInclude : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTokenInclude);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
    Factory::get()->bind("include", &Tokens::Include::getInstance);
  }
  void tearDown() { }

protected:
  void testOutput() {
    oTemplate tpl;
    Parser parser;
    parser.parse(tpl = new TextTemplate(L"{include file='test.tpl'}"));

    tpl->addVariable("ab", "bc");
    Globals::get()->addVariable("de", "fh");

    try {
      tpl->output();
      CPPUNIT_ASSERT("file exist?");
    } catch (Stamina::Exception& e) {
    }

    {
      wofstream o("test.tpl");
      o << L"{'hello'}";
      o.close();
    }

    Sleep(10);
    CPPUNIT_ASSERT(tpl->output() == L"hello");

    {
      wofstream o("test.tpl");
      o << L"{'hi'}";
      o.close();
    }

    Sleep(10);
    CPPUNIT_ASSERT(tpl->output() == L"hi");

    {
      wofstream o("test.tpl");
      o << L"{$de}{$ab}";
      o.close();
    }

    Sleep(10);
    CPPUNIT_ASSERT(tpl->output() == L"fhbc");

    parser.parse(tpl = new TextTemplate(L"{$no = 'two'}{include file='test.tpl', arg='argument', inherit=false}"));
    tpl->addVariable("ab", "bc");

    {
      wofstream o("test.tpl");
      o << L"{$de}{$ab} {$arg}{$no}";
      o.close();
    }

    Sleep(10);
    String s = tpl->output();
    CPPUNIT_ASSERT(tpl->output() == L"fh argument");

    parser.parse(tpl = new TextTemplate(L"{$no = 'two'}{include file='test.tpl', arg='argument', inherit=true}"));
    tpl->addVariable("ab", "bc");
    s = tpl->output();
    CPPUNIT_ASSERT(tpl->output() == L"fhbc argumenttwo");

    {
      wofstream o("test.tpl");
      o << L"{/7}";
      o.close();
    }

    Sleep(10);

    try {
      tpl->output();
      CPPUNIT_ASSERT(!"good syntax?");
    } catch (Stamina::Exception& e) {
    }

    Globals::get()->clearVariables();
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenInclude);