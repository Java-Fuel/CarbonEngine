add_test([=[FakeTest.TestingFakeTestsWork]=]  D:/JavaFuel/CarbonEngine/bin/Debug/CarbonEngineTests.exe [==[--gtest_filter=FakeTest.TestingFakeTestsWork]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FakeTest.TestingFakeTestsWork]=]  PROPERTIES WORKING_DIRECTORY D:/JavaFuel/CarbonEngine/build/Tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  CarbonEngineTests_TESTS FakeTest.TestingFakeTestsWork)
