//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Tomas Bartu <xbartu11@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Tomas Bartu
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = nullptr;
}

PriorityQueue::~PriorityQueue()
{
    Element_t *pNext = nullptr;
    for (Element_t *pIteration { m_pHead }; pIteration != nullptr; pIteration = pNext) {
        pNext = pIteration->pNext;
        delete pIteration;
    }
    delete pNext;
}

void PriorityQueue::Insert(int value)
{
    // adding only one element
    Element_t *pElement { new Element_t() };
    pElement->value = value;
    pElement->pNext = nullptr;

    // add to empty queue
    if (m_pHead == nullptr) {
        m_pHead = pElement;
        return;
    }

    // add to begin of queue
    if (value >= m_pHead->value) {
        pElement->pNext = m_pHead;
        m_pHead = pElement;
        return;
    }

    for (Element_t *pIteration { m_pHead }; pIteration != nullptr; pIteration = pIteration->pNext) {
        if (value <= pIteration->value) {
            // add to end of queue
            if (pIteration->pNext == nullptr) {
                pIteration->pNext = pElement;
                break;
            }
            // add somewhere else
            if (pIteration->pNext->value < value) {
                pElement->pNext = pIteration->pNext;
                pIteration->pNext = pElement;
                break;
            }
        }
    }
}

bool PriorityQueue::Remove(int value)
{
    Element_t *pPrevious { nullptr };
    for (Element_t *pIteration { m_pHead }; pIteration != nullptr; pIteration = pIteration->pNext) {
        if (pIteration->value == value) {
            if (pIteration == m_pHead) {
                // remove from begin of queue
                m_pHead = pIteration->pNext;
                pIteration->pNext = nullptr;
                delete pIteration;
            } else {
                // remove from somewhere else
                pPrevious->pNext = pIteration->pNext;
                pPrevious->pNext = nullptr;
                pIteration->pNext = nullptr;
                delete pIteration;
            }
            return true;
        }
        pPrevious = pIteration;
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    Element_t *pPrevious { m_pHead };
    for (Element_t *pIteration { m_pHead }; pIteration != nullptr; pIteration = pIteration->pNext) {
        if (pIteration->value == value) {
            return pPrevious;
        }
        pPrevious = pIteration->pNext;
    }
    return nullptr;
}

size_t PriorityQueue::Length()
{
    size_t count { 0 };
    for (Element_t *pIteration { m_pHead }; pIteration != nullptr; pIteration = pIteration->pNext) {
        count++;
    }
	return count;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
