#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[]) {
  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  CPPUNIT_NS::CompilerOutputter outputter(&result, std::cerr);
  outputter.write();

  return result.wasSuccessful() ? 0 : 1;
}