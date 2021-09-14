//#include <iostream>
//#include "calculator.h"
//#include <string>
//int main() {
//    string str;
//    cin >> str;
//    calculator ca;
//    if (ca.check(str))
//        cout << "True" << endl;
//    else
//        cout << "False" << endl;
//    return 0;
//}


#include "gtest/gtest.h"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}