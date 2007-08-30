#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/Argument.h"
#include "../../Source/values/String.h";

using namespace Swift;

class TestTokenArgument : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTokenArgument);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testOutput() {
    Tokens::Argument* token = new Tokens::Argument(0);

    Param* param = new Param(0);
    param->add("sample", operatorNone, operatorNone);
    token->addArg(0, param);

    CPPUNIT_ASSERT(token->output() == "sample");

    param = new Param(0);
    param->add("mm's shop", operatorNone, operatorNone);
    token->addArg(1, param);

    CPPUNIT_ASSERT(token->output() == "sample");

    delete token;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenArgument);