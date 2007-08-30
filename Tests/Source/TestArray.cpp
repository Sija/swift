#include "stdafx.h"
#include <cppunit/extensions/HelperMacros.h>

#include "../../Source/stdafx.h"
#include "../../Source/Array.h"
#include "../../Source/values/String.h"
#include "../../Source/values/Int.h"
#include "../../Source/values/Void.h"

using namespace Swift;

class TestArray : public CPPUNIT_NS::TestFixture {
public:
  CPPUNIT_TEST_SUITE(TestArray);

  CPPUNIT_TEST(testManaging);

  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() { }
  void tearDown() { }

protected:
  void testManaging() {
    Array a;
    Array a_d(12); // with default value

    CPPUNIT_ASSERT(!a.count());

    a << "hello" << "2020";

    CPPUNIT_ASSERT(a.count());
    CPPUNIT_ASSERT(!a.has("Swift"));
    CPPUNIT_ASSERT(a.has("hello"));
    CPPUNIT_ASSERT(a.get(0) >> String() == "hello");
    CPPUNIT_ASSERT(a.get(2)->getID() == Values::Void::id);
    CPPUNIT_ASSERT(a_d.get(2) >> int() == 12);

    a.set(0, 5050);
    a.set(2, "text");

    CPPUNIT_ASSERT(a.get(0) >> int() == 5050);

    a.remove(0);

    CPPUNIT_ASSERT(a.get(0) >> String() == "2020");

    a.remove(0);
    CPPUNIT_ASSERT(!a.count());
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestArray);