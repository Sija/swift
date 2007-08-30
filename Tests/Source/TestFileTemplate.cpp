#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/FileTemplate.h"
#include "../../Source/Parser.h"

using namespace Swift;

class TestFileTemplate : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestFileTemplate);

  CPPUNIT_TEST(testOutput);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testOutput() {
    oTemplate tpl = new FileTemplate("testt.tpl");

    CPPUNIT_ASSERT(((FileTemplate*) tpl.get())->getPath() == "testt.tpl");

    {
      wofstream o("testt.tpl");
      o << "{'file'} template";
      o.close();
    }

    Parser parser;
    parser.parse(tpl);

    CPPUNIT_ASSERT(tpl->output() == "file template");

    {
      wofstream o("testt.tpl");
      o << "{'file'} template {'reloaded'}";
      o.close();
    }

    tpl->reload();
    parser.parse(tpl);

    CPPUNIT_ASSERT(tpl->output() == "file template reloaded");
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestFileTemplate);
