#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/tokens/IF.h"
#include "../../Source/tokens/Text.h"
#include "../../Source/values/Bool.h"
#include "../../Source/Param.h"

using namespace Swift;

class TestTokenIF : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestTokenIF);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testOutput() {
    Tokens::IF* token = new Tokens::IF(0);

    token->add(new Tokens::Text("hi world"));

    Param* param = new Param(0);
    param->add(true, operatorNone, operatorNone);
    token->addArg(0, param);

    CPPUNIT_ASSERT(token->output() == "hi world");

    param = new Param(0);
    param->add(false, operatorNone, operatorNone);
    token->setArg(0, param);

    CPPUNIT_ASSERT(token->output() == "");

    iBlock* block = new iBlock((iBlock*) 0);
    block->add(new Tokens::Text("hi hell"));

    token->setAltToken(block);
    CPPUNIT_ASSERT(token->output() == "hi hell");

    param = new Param(0);
    param->add(true, operatorNone, operatorNone);
    token->setArg(0, param);

    CPPUNIT_ASSERT(token->output() == "hi world");

    delete token;
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestTokenIF);
