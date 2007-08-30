#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/Iterate.h"
#include "../../Source/tokens/IF.h"
#include "../../Source/values/String.h"
#include "../../Source/TextTemplate.h"
#include "../../Source/Factory.h"
#include "../../Source/Globals.h"
#include "../../Source/Parser.h"
#include "../../Source/Hash.h"
#include "../../Source/Array.h"

using namespace Swift;

class TestTokenIterate : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTokenIterate);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
    Factory::get()->bind("iterate", &Tokens::Iterate::getInstance);
    Factory::get()->bind("if", &Tokens::IF::getInstance);
    Factory::get()->bind("continue", &Tokens::Continue::getInstance);
    Factory::get()->bind("break", &Tokens::Break::getInstance);
  }
  void tearDown() { }

protected:
  void testOutput() {
    Hash h(0);
    h.set("a", "1");
    h.set("b", "2");
    h.set("c", "3");
    h.set("d", "4");

    Array a(0);
    a << "q" << "w" << "e" << "r" << "t" << "y";

    Globals::get()->addVariable("h", h);
    Globals::get()->addVariable("a", a);
    Globals::get()->addVariable("t", "txt");

    oTemplate tpl;
    Parser parser;

    parser.parse(tpl = new TextTemplate(L"{iterate it='str', it2='str2'}{\"text\"}{/iterate}"));
    try {
      tpl->output();
      CPPUNIT_ASSERT(!"two or more args are one arg?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{iterate it='str'}{\"text\"}{/iterate}"));
    try {
      tpl->output();
      CPPUNIT_ASSERT(!"arg is hash/array type?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{iterate it=$h}{if $it.first}-Begin-{/if}{$it.key}-{$it.value}{if $it.last}-End-{/if}{/iterate}"));
    CPPUNIT_ASSERT(tpl->output() == L"-Begin-a-1b-2c-3d-4-End-");

    parser.parse(tpl = new TextTemplate(L"{iterate it=$h}{if $it.first}-Begin-{/if}{if $it.value == '2'}{continue}{/if}{$it.key}-{$it.value}{if $it.last}-End-{/if}{/iterate}"));
    CPPUNIT_ASSERT(tpl->output() == L"-Begin-a-1c-3d-4-End-");

    parser.parse(tpl = new TextTemplate(L"{iterate it=$h}{if $it.first}-Begin-{/if}{if $it.value == '3'}{break}{/if}{$it.key}-{$it.value}{if $it.last}-End-{/if}{/iterate}"));
    CPPUNIT_ASSERT(tpl->output() == L"-Begin-a-1b-2");
    
    parser.parse(tpl = new TextTemplate(L"{iterate it=$a}{if $it.first}-Begin-{/if}{$it.value}{if $it.last}-End-{/if}{/iterate}"));
    CPPUNIT_ASSERT(tpl->output() == L"-Begin-qwerty-End-");

    parser.parse(tpl = new TextTemplate(L"{iterate it=$a}{if $it.first}-Begin-{/if}{if $it.value == 'e'}{continue}{/if}{$it.value}{if $it.last}-End-{/if}{/iterate}"));
    CPPUNIT_ASSERT(tpl->output() == L"-Begin-qwrty-End-");

    parser.parse(tpl = new TextTemplate(L"{iterate it=$a}{if $it.first}-Begin-{/if}{if $it.value == 'r'}{break}{/if}{$it.value}{if $it.last}-End-{/if}{/iterate}"));
    CPPUNIT_ASSERT(tpl->output() == L"-Begin-qwe");

    Globals::get()->clearVariables();
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenIterate);