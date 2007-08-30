#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/Text.h"

using namespace Swift;

class TestTokenText : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTokenText);

  CPPUNIT_TEST(testOutput);
  CPPUNIT_TEST(testSet);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testOutput() {
    iToken* token = new Tokens::Text("example");

    CPPUNIT_ASSERT(token->output() == "example");

    delete token;
  }

  void testSet() {
    Tokens::Text* token = new Tokens::Text;
    token->set("texttoken");

    CPPUNIT_ASSERT(token->output() == "texttoken");
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenText);