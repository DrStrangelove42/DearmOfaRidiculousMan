#include "main.h"
#include "Base/configTest.h"

int RunTests(void)
{
    cout << "\n\n----------- Test suite ------------\n";
    // Get the top level suite from the registry
    CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

    // Adds the test to the list of test to run
    // CppUnit::TextUi::TestRunner runner;
    CppUnit::TextTestRunner runner;
    runner.addTest(suite);

    // Change the default outputter to a compiler error format outputter
    runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
        std::cerr));
    // Run the tests.
    bool wasSucessful = runner.run();

    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}

int main(void) {
    return RunTests();
}