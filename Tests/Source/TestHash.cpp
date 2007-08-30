#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/Hash.h"
#include "../../Source/Values/Int.h"
#include "../../Source/Values/String.h"

using namespace Swift;

class TestHash : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestHash);

  CPPUNIT_TEST(testManaging);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testManaging() {
    Hash h;
    Hash h_d(12); // with default value

    CPPUNIT_ASSERT(!h.hasKey("new"));
    CPPUNIT_ASSERT(!h.hasValue("sun"));

    h.set("new", "sun");

    CPPUNIT_ASSERT(h.hasKey("new"));
    CPPUNIT_ASSERT(h.get("new") >> String() == "sun");
    CPPUNIT_ASSERT(h.get("old")->getID() == Values::Void::id);
    CPPUNIT_ASSERT(h_d.get("old") >> int() == 12);
    CPPUNIT_ASSERT(h.hasValue("sun"));
    CPPUNIT_ASSERT(!h.hasValue("abc"));
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestHash);