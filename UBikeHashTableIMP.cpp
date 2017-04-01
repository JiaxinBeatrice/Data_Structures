#include "UBikeHashTableIMP.h"

//=================================================================
// add the ubike pointer to the hash table
//=================================================================
void UBikeHashTableIMP::addUBikePtr(UBike* ubptr){
    char x[5];
    int s=0;
    int address;
    for(int i=0;i<5;i++){
    	x[i]=ubptr->license[i];
    	s=s*29;
    	if(x[i]-'0'>=0 && x[i]-'9'<=0)s+=x[i]-'0';
    	else s+=x[i]-'A'+10;
    }
    address = (s%8192)/32;
    (*this)[address].push_front(ubptr);
}
    
//=================================================================
// find the ubike pointer in the hash table given ubike license
// if toRemove is true, remove the the pointer from the hash table
// return the ubike pointer that points to the ubike "license"
//=================================================================
UBike* UBikeHashTableIMP::findUBikePtr(std::string license, bool toRemove){
    char x[5];
    int s=0;
    int address;
    UBike* bike;
    for(int i=0;i<5;i++){
    	x[i]=license[i];
    	s=s*29;
    	if(x[i]-'0'>=0 && x[i]-'9'<=0)s+=x[i]-'0';
    	else s+=x[i]-'A'+10;
    }
    address = (s%8192)/32;

    UBikePtrList::iterator x;
    for(x=(*this)[address].begin();x!=(*this)[address].end();x++){
        if((*x)->license == license){
            bike = (*x);
            if(toRemove){
                (*this)[address].remove(*x);              
            }
            break;
        }
    }
    return bike;
}
