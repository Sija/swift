#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/TextTemplate.h"
#include "../../Source/Parser.h"

using namespace Swift;

class TestTextTemplate : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTextTemplate);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testOutput() {
    oTemplate tpl = new TextTemplate("test {'text'} template");
    Parser parser;
    parser.parse(tpl);

    CPPUNIT_ASSERT(tpl->output() == "test text template");
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTextTemplate);