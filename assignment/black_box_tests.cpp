//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Tomas Bartu <xbartu11@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Tomas Bartu
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test {
protected:
    BinaryTree queue;
};

class NonEmptyTree : public ::testing::Test {
protected:
    virtual void SetUp() {
        int values[] = { 4, 8, 15, 16, 23, 42 };

        for (int value : values) {
            queue.InsertNode(value);
        }
    }
    BinaryTree queue;
};

class TreeAxioms : public ::testing::Test {
protected:
    virtual void SetUp() {
        int values[] = { 4, 8, 15, 16, 23, 42 };

        for (int value : values) {
            queue.InsertNode(value);
        }
    }
    BinaryTree queue;
};

TEST_F(EmptyTree, InsertNode) {
    EXPECT_TRUE(queue.GetRoot() == nullptr);

    queue.InsertNode(815);
    ASSERT_TRUE(queue.GetRoot() != nullptr);
    EXPECT_EQ(queue.GetRoot()->key, 815);

    EXPECT_TRUE(queue.InsertNode(815).first == false);
    EXPECT_EQ(queue.InsertNode(815).second, queue.GetRoot());
}

TEST_F(EmptyTree, DeleteNode) {
    EXPECT_FALSE(queue.DeleteNode(815));
}

TEST_F(EmptyTree, FindNode) {
    EXPECT_TRUE(queue.FindNode(815) == nullptr);
}

TEST_F(NonEmptyTree, InsertNode) {
    int values[] = { 4, 8, 15, 16, 23, 42 };

    EXPECT_TRUE(queue.GetRoot() != nullptr);

    for (int value : values) {
        EXPECT_FALSE(queue.InsertNode(value).first);
        EXPECT_TRUE(queue.InsertNode(value).second != nullptr);
    }

    std::pair<bool, Node_t *> res = queue.InsertNode(815);
    EXPECT_TRUE(res.first);
    EXPECT_EQ(res.second, queue.InsertNode(815).second);
}

TEST_F(NonEmptyTree, DeleteNode) {
    int values[] = { 4, 8, 15, 16, 23, 42 };

    EXPECT_TRUE(queue.GetRoot() != nullptr);

    for (int value : values) {
        queue.DeleteNode(value);
    }
    EXPECT_TRUE(queue.GetRoot() == nullptr);

}

TEST_F(NonEmptyTree, FindNode) {
    int values[] = { 4, 8, 15, 16, 23, 42 };

    EXPECT_TRUE(queue.GetRoot() != nullptr);
    EXPECT_TRUE(queue.FindNode(815) == nullptr);

    for (int value : values) {
        BinaryTree::Node_t *pElement = queue.FindNode(value);
        ASSERT_TRUE(pElement != nullptr);
        EXPECT_EQ(pElement->key, value);
    }
}

TEST_F(TreeAxioms, Axiom1) {
    std::vector<Node_t *> vectored {};
    queue.GetLeafNodes(vectored);

    for (auto value : vectored) {
        EXPECT_EQ(value->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2) {
    std::vector<Node_t *> vectored {};
    queue.GetNonLeafNodes(vectored);

    for (auto value : vectored) {
        if (value->color == RED) {
            EXPECT_EQ(value->pLeft->color, BLACK);
            EXPECT_EQ(value->pRight->color, BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3) {
    std::vector<Node_t *> vectored {};
    queue.GetAllNodes(vectored);

    bool first = true;
    int result = 0;

    for (auto value : vectored) {
        if (value->pLeft == nullptr && value->pRight == nullptr) {
            Node_t * pNext = value->pParent;
            int count = 0;

            while(queue.GetRoot() != pNext) {
                if (pNext->color == BLACK) {
                    count++;
                }
                pNext = pNext->pParent;
            }

            if (first) {
                first = false;
                result = count;
            }
            EXPECT_EQ(result, count);
        }
    }
}

/*** Konec souboru black_box_tests.cpp ***/
