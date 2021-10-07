//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Tomas Bartu <xbartu11@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Tomas Bartu
 *
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"
#include "vector"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech
//    matic.
//============================================================================//

TEST(SetGetCon, Constructor) {
    EXPECT_ANY_THROW(Matrix matrix (0, 0));
}

TEST(SetGetCon, ByValue) {
    Matrix matrixDefault{};
    EXPECT_TRUE(matrixDefault.set(0, 0, 1.0f));
    EXPECT_FALSE(matrixDefault.set(1, 1, 1.0f));
}

TEST(SetGetCon, ByVector) {
    Matrix matrixDefault{};
    Matrix matrixVector{2, 2};
    std::vector<std::vector<double> > vectorBad { { 1.0f, 1.0f, 1.0f, 1.0f, }, { } };
    std::vector<std::vector<double> > vectorGood { { 1.0f, 1.0f },
                                                   { 1.0f, 1.0f } };
    EXPECT_TRUE(matrixVector.set(vectorGood));
    EXPECT_FALSE(matrixDefault.set(vectorGood));
    EXPECT_FALSE(matrixVector.set(vectorBad));
}

TEST(SetGetCon, Get) {
    Matrix matrixDefault{};
    EXPECT_ANY_THROW(matrixDefault.get(1,1));
    EXPECT_TRUE(matrixDefault.set(0, 0, 1.0f));
    EXPECT_EQ(matrixDefault.get(0,0), 1.0f );
}

TEST(Operators, Equalation) {
    int row = 3;
    int col = 3;
    Matrix matrixV1 = Matrix (row, col);
    Matrix matrixV2 = Matrix (row, col);
    Matrix matrixV3 = Matrix (row, col);

    for (int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            matrixV1.set(i, j, 1.0f);
            matrixV2.set(i, j, 1.0f);
            matrixV3.set(i, j, 2.0f);
        }
    }
    Matrix matrixBad {1,1};
    EXPECT_ANY_THROW(matrixBad.operator==(matrixV1));

    EXPECT_TRUE(matrixV1.operator==(matrixV2));
    EXPECT_FALSE(matrixV1.operator==(matrixV3));

}

TEST(Operators, Add) {
    int row = 3;
    int col = 3;
    Matrix matrixV1 = Matrix (row, col);
    Matrix matrixV2 = Matrix (row, col);
    Matrix matrixV3 = Matrix (row, col);

    for (int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            matrixV1.set(i, j, 1.0f);
            matrixV2.set(i, j, 1.0f);
            matrixV3.set(i, j, 2.0f);
        }
    }
    Matrix matrixBad {1,1};
    EXPECT_ANY_THROW(matrixBad.operator+(matrixV1));

    EXPECT_EQ(matrixV1.operator+(matrixV2), matrixV3);

}

TEST(Operators, MultiplyByMatrix) {
    int row = 3;
    int col = 3;
    Matrix matrixV1 = Matrix (row, col);
    Matrix matrixV3 = Matrix (row, col);

    for (int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            matrixV1.set(i, j, 1.0f);
            matrixV3.set(i, j, 2.0f);
        }
    }

    Matrix matrixBad {1,1};
    EXPECT_ANY_THROW(matrixBad.operator*(matrixV1));

    Matrix matrixResult = Matrix (row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixResult.set(i, j, 6.0f);
        }
    }

    EXPECT_EQ(matrixV1.operator*(matrixV3), matrixResult);

}

TEST(Operators, MultiplyByValue) {
    int row = 3;
    int col = 3;
    Matrix matrixV1 = Matrix (row, col);
    Matrix matrixV3 = Matrix (row, col);

    for (int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            matrixV1.set(i, j, 1.0f);
            matrixV3.set(i, j, 2.0f);
        }
    }
    Matrix matrixBad {1,1};
    EXPECT_ANY_THROW(matrixBad.operator*(matrixV1));

    Matrix matrixResult = Matrix (row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrixResult.set(i, j, 4.0f);
        }
    }

    EXPECT_EQ(matrixV3.operator*(2.0f), matrixResult);
}

TEST(Operations, Equation) {
    int row = 3;
    int col = 3;
    std::vector<std::vector<double> > vectored4x4 { { 1.0f, 3.0f, 3.0f, 4.0f },
                                                    { 1.0f, 2.0f, 3.0f, 4.0f },
                                                    { 4.0f, 1.0f, 2.0f, 1.0f},
                                                    { 2.0f, 1.0f, 4.0f, 3.0f } };
    std::vector<std::vector<double> > vectored3x3 { { 2.0f, 5.0f, 7.0f},
                                                    { 6.0f, 3.0f, 4.0f },
                                                    { 5.0f, -2.0f, -3.0f} };
    std::vector<std::vector<double> > vectored2x2 { { 2.0f, 2.0f}, { 1.0f, 2.0f, } };

    Matrix matrixDefault = Matrix();
    Matrix matrixSingular = Matrix(row - 1, col - 1);
    Matrix matrix2x2 = Matrix(row - 1, col - 1);
    Matrix matrix3x3 = Matrix(row, col);
    Matrix matrix4x4 = Matrix(row + 1, col + 1);


    matrixDefault.set(0 , 0, 1.0f);
    matrix4x4.set(vectored4x4);
    matrix3x3.set(vectored3x3);
    matrix2x2.set(vectored2x2);
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < col - 1 ; j++) {
            matrixSingular.set(i, j, 1.0f);
        }
    }


    std::vector<double> answers3x3 { { 1.0f, 1.0f, 1.0f } };
    std::vector<double> answers2x2 { { 1.0f, 10.f } };
    std::vector<double> answers1x1 { { 2.0f } };
    std::vector<double> answers4x1 { { 3.0f, 2.0f, 1.0f, 0.0f } };
    std::vector<double> results3x3 { { 1.0f, -31.0f, 22.0f } };
    std::vector<double> result4x1 { { 0.25f, 1.0f, -0.75f, 0.5f } };
    std::vector<double> result1x1 { { 2.0f } };


    Matrix nonSquared = Matrix(row - 1 , col);
    EXPECT_ANY_THROW(matrix2x2.solveEquation(answers3x3));
    EXPECT_ANY_THROW(nonSquared.solveEquation(answers3x3));
    EXPECT_ANY_THROW(matrixSingular.solveEquation(answers2x2));

    EXPECT_EQ(matrixDefault.solveEquation(answers1x1), result1x1);
    EXPECT_EQ(matrix4x4.solveEquation(answers4x1), result4x1);
    EXPECT_EQ(matrix3x3.solveEquation(answers3x3), results3x3);
}

TEST(Operations, Transpose) {
    int row = 3;
    int col = 3;
    std::vector<std::vector<double> > vectored2x2 { { 2.0f, 2.0f}, { 1.0f, 2.0f, } };
    std::vector<std::vector<double> > vectored2x2Trans { { 2.0f, 1.0f}, { 2.0f, 2.0f, } };

    Matrix matrixResult = Matrix(row - 1, col - 1);
    Matrix matrixDefault = Matrix();
    Matrix matrix2x2 = Matrix(row - 1, col - 1);

    matrixDefault.set(0 , 0, 1.0f);
    matrix2x2.set(vectored2x2);
    matrixResult.set(vectored2x2Trans);

    EXPECT_EQ(matrixDefault.transpose().get(0, 0), 1.0f);
    EXPECT_EQ(matrix2x2.transpose(), matrixResult);
}

TEST(Operations, Inverse) {
    int row = 3;
    int col = 3;
    std::vector<std::vector<double> > vectored3x3 { { 2.0f, 5.0f, 7.0f},
                                                    { 6.0f, 3.0f, 4.0f },
                                                    { 5.0f, -2.0f, -3.0f} };
    std::vector<std::vector<double> > vectored2x2 { { 2.0f, 2.0f}, { 1.0f, 2.0f, } };
    std::vector<std::vector<double> > result3x3{ {1.0f,   -1.0f,  1.0f},
                                                {-38.0f, 41.0f,  -34.0f},
                                                {27.0f,  -29.0f, 24.0f} };
    std::vector<std::vector<double> > result2x2{ {1.0f,  -1.0f},
                                                {-0.5f, 1.0f} };

    Matrix matrixDefault = Matrix();
    Matrix matrixSingular = Matrix(row - 1, col - 1);
    Matrix matrix2x2 = Matrix(row - 1, col - 1);
    Matrix matrix3x3 = Matrix(row, col);
    Matrix matrixResultDefault = Matrix();
    Matrix matrixResult2x2 = Matrix(row - 1, col - 1);
    Matrix matrixResult3x3 = Matrix(row, col);

    matrix3x3.set(vectored3x3);
    matrix2x2.set(vectored2x2);
    matrixResult3x3.set(result3x3);
    matrixResult2x2.set(result2x2);
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < col - 1 ; j++) {
            matrixSingular.set(i, j, 1.0f);
        }
    }

    EXPECT_ANY_THROW(matrixSingular.inverse());
    EXPECT_ANY_THROW(matrixDefault.inverse());
    EXPECT_EQ(matrix2x2.inverse(), matrixResult2x2);
    EXPECT_EQ(matrix3x3.inverse(), matrixResult3x3);
}

/*** Konec souboru white_box_tests.cpp ***/
