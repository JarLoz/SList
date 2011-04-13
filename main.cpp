#define NDEBUG
#include <iostream>
#include <sstream>
#include "SList.h"
bool checkCorrectString(std::string expected, std::string result, int& errorcount);
int testDriver();

int main() {
    try {
        testDriver();
    } catch (...) {
        std::cout << "Unknown exception thrown\n";
    }
    return 0;
}

/* The testDriver function is a test driver for the SList-class declared in
 * SList.h. It runs a number of tests, checking all the member functions of the
 * class and their results. In the end, it reports the number of errors encountered
 * and returns this number.
 */
int testDriver() {
    int errorcount = 0;
    bool errorflag = false;
    SList test1, test3;
    std::string tempString;


    /* Simple input, push_front()*/
    test1 = SList();
    std::cout << "Testing simple input with SList::push_front()\n";
    std::cout << "Sample words: \"Hello\", \"World\"\n";
    try {
        test1.push_front("Hello");
        test1.push_front("World");
    } catch (SList::bad_alloc) {
        errorflag = true;
        std::cout << "Error, bad allocation\n";
        errorcount++;
        if (!test1.check()) {
            std::cout << "Class invariant failure, resetting the list, aborting next test\n";
            test1 = SList();
        }
    }
    /*Invariant check*/

    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure, resetting the list, aborting next test\n";
        test1 = SList();
        errorcount++;
        errorflag = true;
    }

    /*Simple output, front()*/

    if (!errorflag) {
        try {
            std::cout << "Success. Testing simple output with front()\n";
            checkCorrectString(test1.front(), "World", errorcount);
            std::cout << "Testing simple output with pop_front()\n";
            tempString = test1.pop_front();
            checkCorrectString(tempString, "World", errorcount);
            tempString = test1.pop_front();
            checkCorrectString(tempString, "Hello", errorcount);
        } catch (SList::empty_list) {
            errorcount++;
            std::cout << "Error, empty_list exception thrown\n";
        }

    }

    /*Invariant check*/


    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure, resetting the list.\n";
        test1 = SList();
        errorcount++;
    }
    errorflag = false;


    /*empty_list() exception throwing*/


    std::cout << "Testing empty_list() exeption throwing using pop_front()\n";
    try {
        test1.pop_front();

        std::cout << "Error, no exception thrown.\n";
        errorcount++;
        if (!test1.check()) {
            std::cout << "Class invariant failure, resetting the list.\n";
            test1 = SList();
        }
    } catch (SList::empty_list) {
        std::cout << "Success, empty_list() exception thrown and catched\n";
    }

    /*Invariant check*/


    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure, resetting the list.\n";
        test1 = SList();
        errorcount++;
    }

    /*assignment constructor*/


    std::cout << "Testing assignment constructor using words \"Hello\" and \"World\".\n";
    test1.push_front("Hello");
    test1.push_front("World");
    try {
        SList test2 = test1;
        tempString = test2.pop_front();
        checkCorrectString(tempString, "World", errorcount);
        tempString = test2.pop_front();
        checkCorrectString(tempString, "Hello", errorcount);
    } catch (SList::bad_alloc) {
        errorflag = true;
        std::cout << "Error, bad_alloc thrown, test aborted\n";
        errorcount++;
    } catch (SList::empty_list) {
        errorcount++;
        std::cout << "Error, empty_list thrown.\n";
    }

    /*Destructor*/



    if (!errorflag) {
        std::cout << "Testing that destructor didn't affect the original list\n";
        try {
            tempString = test1.pop_front();
            checkCorrectString(tempString, "World", errorcount);
            tempString = test1.pop_front();
            checkCorrectString(tempString, "Hello", errorcount);
        } catch (SList::empty_list) {
            errorcount++;
            std::cout << "Error, empty_list thrown, destructor has failed.\n";
        }
    }
    errorflag = false;


    /* Copy constructor */


    std::cout << "Testing copy constructor using words \"Hello\" and \"World\".\n";
    test1.push_front("Hello");
    test1.push_front("World");
    try {
        test3 = test1;
        tempString = test3.pop_front();
        checkCorrectString(tempString, "World", errorcount);
        tempString = test3.pop_front();
        checkCorrectString(tempString, "Hello", errorcount);
    } catch (SList::bad_alloc) {
        errorflag = true;
        std::cout << "Error, bad_alloc thrown, test aborted\n";
        errorcount++;
    } catch (SList::empty_list) {
        errorcount++;
        std::cout << "Error, empty_list thrown.\n";
    }


    /* Overloaded input operator >>*/



    std::cout << "Testing overloaded input operator >> using stringstream \"{ Hello World }\".\n"
            << "(Also testing swap(), used in the operator overloading)\n";
    std::istringstream testStream1("{ Hello World}", std::ios_base::in);

    errorflag = false;
    std::cout << "Resetting the list\n";
    test1 = SList();

    testStream1 >> test1;

    if (testStream1.fail()) {
        std::cout << "Error, failbit enabled in stream.\n";
        errorcount++;
        if (!test1.check()) {
            errorflag = true;
            std::cout << "Class invariant failure, resetting the list, aborting next test\n";
            test1 = SList();
        }
    } else
        std::cout << "Success.\n";


    /*Invariant check*/



    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure, resetting the list, aborting next test\n";
        test1 = SList();
        errorcount++;
        errorflag = true;
    }


    /* Overloaded output operator <<*/


    if (!errorflag) {
        std::cout << "Testing overloaded output operator <<\n";
        std::ostringstream testOutput;
        testOutput << test1;
        tempString = testOutput.str();
        checkCorrectString("World\nHello\n", tempString, errorcount);
    }


    /*Invariant check*/



    std::cout << "Testing invariant.\n";

    if (test1.check() && !errorflag) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure.\n";
        errorcount++;
    }

    errorflag = false;
    std::cout << "Resetting the list\n";
    test1 = SList();


    /*Overloaded input operator, invalid input*/


    std::cout << "Testing invalid input with overloaded input operator >>\n";
    std::cout << "Case number one: no leading \'{\'.\n";
    std::istringstream testStream2("Hello}", std::ios_base::in);
    testStream2 >> test1;
    if (testStream2.fail()) {
        try {
            test1.pop_front();
            std::cout << "Error, failbit is enabled but the stream is not empty\n";
            errorcount++;
        } catch (SList::empty_list) {
            std::cout << "Success, failbit enabled and the stream is empty\n";
        }
    } else {
        std::cout << "Error, failbit is not enabled.\n";
        errorcount++;
    }

    /*Invariant check*/


    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure\n";
        errorcount++;
    }
    std::cout << "Resetting the list\n";
    test1 = SList();


    /*Overloaded input operator, more invalid input*/


    std::cout << "Case number two: no trailing \'}\'.\n";
    std::istringstream testStream3("Hello}", std::ios_base::in);
    testStream3 >> test1;
    if (testStream3.fail()) {
        try {
            test1.pop_front();
            std::cout << "Error, failbit is enabled but the stream is not empty\n";
            errorcount++;
        } catch (SList::empty_list) {
            std::cout << "Success, failbit enabled and the stream is empty\n";
        }
    } else {
        std::cout << "Error, failbit is not enabled.\n";
        errorcount++;
    }

    std::cout << "Resetting the list\n";
    test1 = SList();


    /* reverse() function*/


    std::cout << "Testing reverse() using words \"Hello\" and \"World\".\n";
    test1.push_front("Hello");
    test1.push_front("World");
    test1.reverse();
    checkCorrectString("Hello", test1.pop_front(), errorcount);
    checkCorrectString("World", test1.pop_front(), errorcount);

    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure.\n";
        errorcount++;
    }

    std::cout << "Resetting the list\n";
    test1 = SList();


    /* Iterator tests */


    std::cout << "Beginning the iterator test set.\n";
    std::cout << "Formatting the list with words \"Hello\" and \"World\".\n";
    test1.push_front("Hello");
    test1.push_front("World");


    /* Normal iteration*/


    std::cout << "Iterating over the list using normal iterator\n";
    int counter = 0;


    for (SList::iterator i = test1.begin(); i != test1.end(); ++i) {
        if (counter == 0)
            checkCorrectString("World", *i, errorcount);
        else
            checkCorrectString("Hello", *i, errorcount);
        counter++;
    }


    /*Invariant check*/


    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure, resetting the list, aborting next test\n";
        test1 = SList();
        errorcount++;
        errorflag = true;
    }


    //SList::iterator testIterator;


    /* const_iterator*/


    if (!errorflag) {
        std::cout << "Iterating over the list using constant iterator\n";
        counter = 0;
        const SList test4 = test1;
        for (SList::const_iterator i = test4.begin(); i != test4.end(); ++i) {
            if (counter == 0)
                checkCorrectString("World", *i, errorcount);
            else
                checkCorrectString("Hello", *i, errorcount);
            counter++;
        }


        /* insert_after*/


        std::cout << "Testing insert_after by inserting the word \"Awesome\" as the second word in the list.\n";
        SList::iterator testIterator = test1.begin();
        test1.insert_after("Awesome", testIterator);
        ++testIterator;
        checkCorrectString("Awesome", *testIterator, errorcount);

        /* delete_after */

        std::cout << "Testing delete_after on the last word of the list.\n";
        test1.delete_after(testIterator);

        try {
            checkCorrectString("World", test1.pop_front(), errorcount);
            checkCorrectString("Awesome", test1.pop_front(), errorcount);
            test1.pop_front();
            std::cout << "Error, no empty_list exception caught.\n";
            errorcount++;
        } catch (SList::empty_list) {
            std::cout << "Success, empty_list exception caught after the last word.\n";
        }
    }

    errorflag = false;


    /*Invariant check*/


    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure.\n";
        errorcount++;
    }

    std::cout << "Resetting the list\n";
    test1 = SList();
    test3 = SList();

    /* bad_iterator exceptions*/


    std::cout << "Testing the throwing of bad_iterator exceptions by using the wrong iterator.\n";

    test1.push_front("Hello");
    test3.push_front("World");
    SList::iterator testIterator = test1.begin();
    std::cout << "Beginning with insert_after()\n";
    try {
        test3.insert_after("Awesome", testIterator);
        std::cout << "Error, no bad_iterator exception thrown.\n";
        errorcount++;
    } catch (SList::bad_iterator) {
        std::cout << "Success, bad_iterator exception caught.\n";
    }
    std::cout << "Continuing with delete_after()\n";
    try {
        test3.delete_after(testIterator);
        std::cout << "Error, no bad_iterator exception thrown.\n";
        errorcount++;
    } catch (SList::bad_iterator) {
        std::cout << "Success, bad_iterator exception caught.\n";
    }


    /*Invariant check*/


    std::cout << "Testing invariant.\n";
    if (test1.check()) {
        std::cout << "Success!\n";
    } else {
        std::cout << "Class invariant failure, resetting the list.\n";
        test1 = SList();
        errorcount++;
    }

    std::cout << "Number of errors: " << errorcount << "\n";
    return errorcount;
}

/* checkCorrectString is a simple function that compares two strings together.
 * it also increments the given error counter for every failed comparison.
 */
bool checkCorrectString(std::string expected, std::string result, int& errorcount) {
    if (expected == result) {
        std::cout << "Success. Expected: " << expected << " Result: " << result << "\n";
        return true;
    }
    std::cout << "Error. Expected: " << expected << " Result: " << result << "\n";
    errorcount++;
    return false;
}