#include "gtest/gtest.h"
#include "stats/CChi2.h"
#include "globals.h"

TEST(CChi2Test, ContingencyTable) {
    VectorXd x(14);
    VectorXd y(14);

    x << 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2;
    y << 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 2;

    MatrixXd table = CChi2::get2DContingencyTable(x, y);

    MatrixXd exp(2,3);
    exp << 1, 2, 1,
           4, 3, 3;

    ASSERT_EQ(table, exp);

}

TEST(CChi2Test, Chi2Calculation) {

    MatrixXd table(2,3);
    table << 9000, 3000, 1000,
             4500, 10000, 7000;

    float64 chisq = CChi2::calculateChi2(table);
    float64 exp = 8171.02;

    ASSERT_NEAR(chisq, exp, 0.01);

}

TEST(CChi2Test, Chi2TrendCalculation) {

    MatrixXd table(2,3);
    table << 9000, 3000, 1000,
             4500, 10000, 7000;
    VectorXd w(3);
    w << 1, 1, 0;

    float64 T = CChi2::calculateChi2Trend(table, w);
    float64 exp = 2812.4;

    ASSERT_NEAR(T, exp, 0.2);

}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}