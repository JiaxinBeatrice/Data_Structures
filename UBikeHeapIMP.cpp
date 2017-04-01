#include "UBikeHeapIMP.h"

// Add your code here

#include <iostream>
void UBikeHeapIMP::addUBikePtr(UBike* ubptr)
{
    this->number++;
    currNum=this->number;
    while(currNum != 1 && (*this)[currNum/2]->mileage > ubptr->mileage){
            (*this)[currNum] = (*this)[currNum/2];
            (*this)[currNum]->heapIndex = currNum;
            currNum = currNum/2;
    }
    (*this)[currNum] = ubptr;
    (*this)[currNum]->heapIndex = currNum;
}

UBike* UBikeHeapIMP::removeUBikePtr(int heapIndex)
{
    int currIndex = heapIndex;

    if(heapIndex>this->number)return NULL;

    UBike *removed_One = (*this)[heapIndex];
    if(heapIndex==this->number){
        (*this)[this->number] = NULL;
        this->number--;
        return removed_One;
    }

    (*this)[this->number]->heapIndex = heapIndex;
    (*this)[heapIndex] = (*this)[this->number];
    (*this)[number] = NULL;
    this->number--;

    int tmp;
    UBike* toSwap;

    //bubble down
    while(true){
        int left = currIndex*2;
        int right = currIndex*2+1;

        if(right<=this->number){
            if((*this)[left]->mileage <(*this)[right]->mileage)tmp = left;
            else tmp = right;
        }
        else if (right == this->number-1)tmp = left;
        else break;

        if((*this)[tmp]->mileage < (*this)[currIndex]->mileage){
            (*this)[tmp]->heapIndex = currIndex;
            (*this)[currIndex]->heapIndex = tmp;

            toSwap = (*this)[tmp];
            (*this)[tmp] = (*this)[currIndex];
            (*this)[currIndex] = toSwap;

            currIndex = tmp;
        }
        else break;
    }

    //bubble up
    while(true){
        if(currIndex == 1)break;
        tmp = currIndex/2;
        if((*this)[tmp]->mileage > (*this)[currIndex]){
            (*this)[tmp]->heapIndex = currIndex;
            (*this)[currIndex]->heapIndex = tmp;

            toSwap = (*this)[tmp];
            (*this)[tmp] = (*this)[currIndex];
            (*this)[currIndex] = toSwap;

            currIndex = tmp;
        }
        else break;
    }

    return removed_One;
}
