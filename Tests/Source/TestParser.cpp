#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/Iterate.h"
#include "../../Source/tokens/Include.h"
#include "../../Source/tokens/IF.h"
#include "../../Source/tokens/Continue.h"
#include "../../Source/values/String.h"
#include "../../Source/TextTemplate.h"
#include "../../Source/Factory.h"
#include "../../Source/Globals.h"
#include "../../Source/Parser.h"

using namespace Swift;

class TestParser : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestParser);

  CPPUNIT_TEST(testParserFunctions);
  CPPUNIT_TEST(testParseToken);
  CPPUNIT_TEST(testParseSection);
  CPPUNIT_TEST(testParseArgument);
  CPPUNIT_TEST(testParseArgumentsWithOperators);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {
    Factory::get()->bind("iterate", &Tokens::Iterate::getInstance);
    Factory::get()->bind("if", &Tokens::IF::getInstance);
    Factory::get()->bind("continue", &Tokens::Continue::getInstance);
    Factory::get()->bind("include", &Tokens::Include::getInstance);
  }

  void tearDown() {
    Globals::get()->clearVariables();
  }

protected:
  void testParserFunctions() {
    Parser parser;

    CPPUNIT_ASSERT(parser.parse("{'valid token'}") == "valid token");

    try {
      parser.parse("{'invalid token");
      CPPUNIT_ASSERT(!"valid token?");
    } catch (Stamina::Exception& e) {
    }

    oTemplate tpl = new TextTemplate("{'valid token'}");
    parser.parse(tpl);

    CPPUNIT_ASSERT(tpl->output() == "valid token");
  }
  void testParseToken() {
    oTemplate tpl;

    Parser parser;
    parser.parse(tpl = new TextTemplate(L"text"));
    CPPUNIT_ASSERT(tpl->output() == L"text");

    parser.parse(tpl = new TextTemplate(L"some t{ ext"));
    CPPUNIT_ASSERT(tpl->output() == L"some t{ ext");

    parser.parse(tpl = new TextTemplate(L"{token}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"text{token}"));
    CPPUNIT_ASSERT(tpl->output() == L"text");

    parser.parse(tpl = new TextTemplate(L"{token}text"));
    CPPUNIT_ASSERT(tpl->output() == L"text");

    parser.parse(tpl = new TextTemplate(L"{token 123}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"{token 123='bh'}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"{token}{/token}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"{token}text{/token}"));
    CPPUNIT_ASSERT(tpl->output() == L"text");

    parser.parse(tpl = new TextTemplate(L"{token true}{/token}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"{token bh=333}{/token}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"{token bh=333}{tokenalt}{/token}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"{token bh=333}text{tokenalt}text{/token}"));
    CPPUNIT_ASSERT(tpl->output() == L"texttext");

    try {
      parser.parse(tpl = new TextTemplate(L"{token bh=333}{/token"));
      CPPUNIT_ASSERT(!"end token have end?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{token bh=333}{/token#}"));
      CPPUNIT_ASSERT(!"end token syntax ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{token bh=333}{/$}"));
      CPPUNIT_ASSERT(!"end token syntax ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if true}{/if}{/if}"));
      CPPUNIT_ASSERT(!"double end are good syntax?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if true}{else}{else}{/if}"));
      CPPUNIT_ASSERT(!"next alt token?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if true}"));
      CPPUNIT_ASSERT(!"has end token?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{\"string\"} {'string'}"));
    CPPUNIT_ASSERT(tpl->output() == L"string string");

    parser.parse(tpl = new TextTemplate(L"{1234} {0xFF} {-1040}"));
    CPPUNIT_ASSERT(tpl->output() == L"1234 255 -1040");

    parser.parse(tpl = new TextTemplate(L"{true} {false}"));
    CPPUNIT_ASSERT(tpl->output() == L"true false");

    parser.parse(tpl = new TextTemplate(L"{$var}"));
    CPPUNIT_ASSERT(tpl->output() == L"");

    parser.parse(tpl = new TextTemplate(L"{$var.key.arr[12].key}"));
    parser.parse(tpl = new TextTemplate(L"{$var[12].key}"));

    parser.parse(tpl = new TextTemplate(L"{func()}"));
    // CPPUNIT_ASSERT(tpl->output() == L""); //?

    parser.parse(tpl = new TextTemplate(L"{('str')}"));
    CPPUNIT_ASSERT(tpl->output() == L"str");

    parser.parse(tpl = new TextTemplate(L"{!true}"));
    CPPUNIT_ASSERT(tpl->output() == L"false");

    try {
      parser.parse(tpl = new TextTemplate(L"{#type}"));
      CPPUNIT_ASSERT(!"accepting new type?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{token"));
      CPPUNIT_ASSERT(!"token has end?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{}"));
      CPPUNIT_ASSERT(!"empty token?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{/if}"));
      CPPUNIT_ASSERT(!"orphan end token is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if}{/if}"));
      CPPUNIT_ASSERT(!"if has args?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if arg='tre'}{/if}"));
      CPPUNIT_ASSERT(!"if has unnamed args?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{iterate true}{/iterate"));
      CPPUNIT_ASSERT(!"iterate has named args?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{iterate}{/iterate"));
      CPPUNIT_ASSERT(!"iterate has args?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{continue false}"));
      CPPUNIT_ASSERT(!"continue has not got args?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{continue arg=false}"));
      CPPUNIT_ASSERT(!"continue has not got args?");
    } catch (Stamina::Exception& e) {
    }
  }

  void testParseSection() {
    oTemplate tpl;

    Parser parser;
    parser.parse(tpl = new TextTemplate(L"{if false, true}{/if}"));

    try {
      parser.parse(tpl = new TextTemplate(L"{if ,false, true}{/if}"));
      CPPUNIT_ASSERT(!"comma is not on begin?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if false,, true}{/if}"));
      CPPUNIT_ASSERT(!"double comma is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if false, , true}{/if}"));
      CPPUNIT_ASSERT(!"double comma is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{if false, true,}{/if}"));
      CPPUNIT_ASSERT(!"comma is not on end?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{include arg = false}"));
      CPPUNIT_ASSERT(!"required arg exist?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{include file}"));
      CPPUNIT_ASSERT(!"argument have a value?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{include ^$#$}"));
      CPPUNIT_ASSERT(!"good argument syntax?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{include file="));
      CPPUNIT_ASSERT(!"good argument syntax?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{include ,file=false}"));
      CPPUNIT_ASSERT(!"comma is not on begin?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{include file=12, ,b=false}"));
      CPPUNIT_ASSERT(!"double comma signs is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{include file=12, b=false,}"));
      CPPUNIT_ASSERT(!"comma is not on end?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{continue}"));

    try {
      parser.parse(tpl = new TextTemplate(L"{continue }"));
      CPPUNIT_ASSERT(!"syntax {token} ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{iterate ar;=34}"));
      CPPUNIT_ASSERT(!"argument name is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{iterate it=45, it=65}"));
      CPPUNIT_ASSERT(!"double argument is ok?");
    } catch (Stamina::Exception& e) {
    }
  }

  void testParseArgument() {
    oTemplate tpl;

    Parser parser;

    parser.parse(tpl = new TextTemplate(L"{'text'}"));
    CPPUNIT_ASSERT(tpl->output() == "text");

    try {
      parser.parse(tpl = new TextTemplate(L"{'text"));
      CPPUNIT_ASSERT(!"text argument has end?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{\"text'}"));
      CPPUNIT_ASSERT(!"good bracked are used?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{'text\\0xx'}"));
      CPPUNIT_ASSERT(!"good hex char?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{'text\\0x'}"));
      CPPUNIT_ASSERT(!"good hex char?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{'text\\0x0AF'}"));

    CPPUNIT_ASSERT(tpl->output() == "text\nF");


    parser.parse(tpl = new TextTemplate(L"{'text\\0xAtext2'}"));
    String s = tpl->output();

    CPPUNIT_ASSERT(tpl->output() == L"text\ntext2");

    try {
      parser.parse(tpl = new TextTemplate(L"{'text\\x'}"));
      CPPUNIT_ASSERT(!"escape character is ok?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{'\r\n\t\v\\\\\\\"\\'\\}'}"));

    CPPUNIT_ASSERT(tpl->output() == "\r\n\t\v\\\"'}");

    parser.parse(tpl = new TextTemplate(L"{123456}"));

    CPPUNIT_ASSERT(tpl->output() == "123456");

    try {
      parser.parse(tpl = new TextTemplate(L"{0x}"));
      CPPUNIT_ASSERT(!"hex value is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{0x10101010101010101}"));
      CPPUNIT_ASSERT(!"hex value is ok?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{('text')}"));

    CPPUNIT_ASSERT(tpl->output() == "text");

    try {
      parser.parse(tpl = new TextTemplate(L"{('text'}"));
      CPPUNIT_ASSERT(!"end bracked exist?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{(/regex/flags)}"));

    try {
      parser.parse(tpl = new TextTemplate(L"{((/regex)}"));
      CPPUNIT_ASSERT(!"second slash exist?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{((/re//gex)}"));
      CPPUNIT_ASSERT(!"second slash exist?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{$var}"));

    try {
      parser.parse(tpl = new TextTemplate(L"{$}"));
      CPPUNIT_ASSERT(!"var have name?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{func()}"));

    try {
      parser.parse(tpl = new TextTemplate(L"{func(,false)}"));
      CPPUNIT_ASSERT(!"comma is not on begin?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{func(false,)}"));
      CPPUNIT_ASSERT(!"comma is not on end?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{func(false,, true)}"));
      CPPUNIT_ASSERT(!"double comma signs is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{func(false"));
      CPPUNIT_ASSERT(!"function has end bracket?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{fun%c()"));
      CPPUNIT_ASSERT(!"function name is ok?");
    } catch (Stamina::Exception& e) {
    }

    parser.parse(tpl = new TextTemplate(L"{$var.arg1[2]}"));

    try {
      parser.parse(tpl = new TextTemplate(L"{$var[]}"));
      CPPUNIT_ASSERT(!"array have index?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{$var[}"));
      CPPUNIT_ASSERT(!"right bracket exist?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{$var.[]}"));
      CPPUNIT_ASSERT(!"hash key is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{$var."));
      CPPUNIT_ASSERT(!"hash key is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{$var[]."));
      CPPUNIT_ASSERT(!"hash key is ok?");
    } catch (Stamina::Exception& e) {
    }
  }

  void testParseArgumentsWithOperators() {
    oTemplate tpl;

    Parser parser;
    parser.parse(tpl = new TextTemplate(L"{'text' && 1234}"));

    try {
      parser.parse(tpl = new TextTemplate(L"{not not 6}"));
      CPPUNIT_ASSERT(!"double 'not' operators are ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{(add 6)}"));
      CPPUNIT_ASSERT(!"postoperators as preoperators are ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{6 not 6}"));
      CPPUNIT_ASSERT(!"'not' as postoperator is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{6 and not 6 and}"));
      CPPUNIT_ASSERT(!"third argument exist?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{%666}"));
      CPPUNIT_ASSERT(!"new type is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{777 && strrr}"));
      CPPUNIT_ASSERT(!"new string type is ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{not "));
      CPPUNIT_ASSERT(!"full syntax?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{344 && && 564}"));
      CPPUNIT_ASSERT(!"double postoperators are ok?");
    } catch (Stamina::Exception& e) {
    }

    try {
      parser.parse(tpl = new TextTemplate(L"{344 564}"));
      CPPUNIT_ASSERT(!"double arguments are ok?");
    } catch (Stamina::Exception& e) {
    }
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestParser);