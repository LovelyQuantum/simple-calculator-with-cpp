//
// Created by 13495 on 9/13/2021.
//

#include "calculator.h"
#include "gtest/gtest.h"
#include <string>

TEST(InputCheckTest, Correct) {
    calculator ca;
    EXPECT_TRUE(ca.check("(1)"));
    EXPECT_TRUE(ca.check("( )"));
    EXPECT_TRUE(ca.check("(100)"));
    EXPECT_TRUE(ca.check("(1+3)"));
    EXPECT_TRUE(ca.check("(1+3+2)"));
    EXPECT_TRUE(ca.check("(1*3+2)"));
    EXPECT_TRUE(ca.check("(1*382+2)"));
    EXPECT_TRUE(ca.check("()"));
    EXPECT_TRUE(ca.check("(1*1)"));
    EXPECT_TRUE(ca.check("(1/1)"));
    EXPECT_TRUE(ca.check("(1-1-1)"));
    EXPECT_TRUE(ca.check("(1/[1])"));
    EXPECT_TRUE(ca.check("(1/{1})"));
}

TEST(InputCheckTest, IncorrectMark) {
    calculator ca;
    EXPECT_FALSE(ca.check("(1+2"));
    EXPECT_FALSE(ca.check("1+2)"));
    EXPECT_FALSE(ca.check("{"));
    EXPECT_FALSE(ca.check("}"));
    EXPECT_FALSE(ca.check("["));
    EXPECT_FALSE(ca.check("]"));
    EXPECT_FALSE(ca.check("(1+2))"));
    EXPECT_FALSE(ca.check("((1+2)"));
    EXPECT_FALSE(ca.check("((1+2"));
}

TEST(String2VectorTest, Correct) {
    calculator ca;
    vector<string> test_string;

    ca.check("(1+3)*4");
    ca.convert_string_to_vector();
    test_string = {"(", "1", "+", "3", ")", "*", "4"};
    EXPECT_EQ(ca.expression_vector, test_string);

    ca.check("1+(3*4)");
    ca.convert_string_to_vector();
    test_string = {"1", "+", "(", "3", "*", "4", ")"};
    EXPECT_EQ(ca.expression_vector, test_string);

    ca.check("(1265+325)*415");
    ca.convert_string_to_vector();
    test_string = {"(", "1265", "+", "325", ")", "*", "415"};
    EXPECT_EQ(ca.expression_vector, test_string);

    ca.check("{[1265+325]*415}");
    ca.convert_string_to_vector();
    test_string = {"{", "[", "1265", "+", "325", "]", "*", "415", "}"};
    EXPECT_EQ(ca.expression_vector, test_string);

    ca.check("{[1265+325-100]*415/3*2}");
    ca.convert_string_to_vector();
    test_string = {"{", "[", "1265", "+", "325", "-", "100", "]", "*", "415", "/", "3", "*", "2", "}"};
    EXPECT_EQ(ca.expression_vector, test_string);
}

TEST(Convert2SuffixTest, Correct) {
    calculator ca;
    vector<string> test_string;

    ca.check("1+3");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    test_string = {"1", "3", "+"};
    EXPECT_EQ(ca.suffix_vector, test_string);

    ca.check("(1+3)");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    test_string = {"1", "3", "+"};
    EXPECT_EQ(ca.suffix_vector, test_string);

    ca.check("1+2-3*4/5+6");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    test_string = {"1", "2", "+", "3", "4", "*", "5", "/", "-", "6", "+"};
    EXPECT_EQ(ca.suffix_vector, test_string);

    ca.check("1+2*(3-4)-5/6");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    test_string = {"1", "2", "3", "4", "-", "*", "+", "5", "6", "/", "-"};
    EXPECT_EQ(ca.suffix_vector, test_string);

    ca.check("((15/(7-{1+1}))*3)-(2+[1+1])");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    test_string = {"15", "7", "1", "1", "+", "-", "/", "3", "*", "2", "1", "1", "+", "+", "-"};
    EXPECT_EQ(ca.suffix_vector, test_string);
}

TEST(CalculateSuffixTest, Correct) {
    calculator ca;

    ca.check("1+2");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    ca.calculate_suffix_expression();
    EXPECT_DOUBLE_EQ(ca.result, 3);

    ca.check("(1+2)");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    ca.calculate_suffix_expression();
    EXPECT_DOUBLE_EQ(ca.result, 3);

    ca.check("1+4*3/(2+2+2)");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    ca.calculate_suffix_expression();
    EXPECT_DOUBLE_EQ(ca.result, 3);

    ca.check("1+2*(3-4)-5/6");
    ca.convert_string_to_vector();
    ca.convert_to_suffix();
    ca.calculate_suffix_expression();
    EXPECT_DOUBLE_EQ(ca.result, stod("-1.833333"));
}