#include "UBikeSystemIMP.h"

//=================================================================
// read the map and initialize this->priceTable
//=================================================================
void UBikeSystemIMP::InitDistTable
  (std::string MapFile){
  	priceTable.calcAllPairsShortestPath(MapFile);
  	net=0;
}
    
//=================================================================
// add a new bike to the system
//=================================================================
void UBikeSystemIMP::NewBike
(std::string classType, std::string license,
  int mile, std::string station){
	UBike* bike = new UBike;
    bike -> isRented = false;
    bike -> classType = classType;
    bike-> license = license;
    bike -> mileage = mile;
    bike-> station = station;
    ubHashTable.addUBikePtr(bike);  //add hashTable
    std::map< std::string, UBStation >::iterator tempStation;  //ubStation
    tempStation = ubStations.find(station);
    if(tempStation == ubStations.end())  //station not exist
    {
        UBStation newStation;
        UBikeHeapIMP newHeap;
        newHeap.addUBikePtr(bike);  //add heap
        newStation[classType] = newHeap;
        ubStations[station] = newStation;
    }
    else  //station exist
    {
        UBStation::iterator tempType;
        tempType = (tempStation -> second).find(classType);
        if(tempType == (tempStation->second).end())  //classType not exist
        {
            UBikeHeapIMP newHeap;
        	newHeap.addUBikePtr(bike);  //add heap
            (tempStation -> second)[classType] = newHeap;
        }
        else  //classType exist
        {
        	(tempType->second).addUBikePtr(bike);  //add heap
        }
    }
}
   
//=================================================================
// remove the bike license
//=================================================================
void UBikeSystemIMP::JunkIt
  (std::string license){
  	UBike *bike;
    bike = ubHashTable.findUBikePtr(license,false);
    std::map< std::string, UBStation >::iterator tempStation;//Ubstation
    if(bike != NULL)  //bike exist
    {
	    tempStation = ubStations.find(bike -> station);
	    if(tempStation != ubStations.end())  //station exist
	    {
	        UBStation::iterator tempType;
	        tempType = (tempStation -> second).find(bike -> classType);
	        if(tempType != (tempStation->second).end())  //classType exist
	        {
	            bike = (tempType -> second).removeUBikePtr(bike -> heapIndex);  // delete heap
				bike = ubHashTable.findUBikePtr(license, true);  //delete hashTable;
	        }
	    }
    }
}
    
//=================================================================
// rent a bike
//=================================================================
void UBikeSystemIMP::Rent
  (std::string classType, std::string station){
  	std::map< std::string, UBStation >::iterator tempStation;  //ubStation
    tempStation = ubStations.find(station);
    UBike* bike;
    if(tempStation != ubStations.end())  //station exist 
    {
        UBStation::iterator tempType;
        UBStation::iterator rentType;
        tempType = (tempStation -> second).find(classType);
        rentType = (tempStation -> second).find("Rented");
        if(tempType != (tempStation ->second).end())  //classType exist
        {
            bike = (tempType -> second).removeUBikePtr(1);  //delete heap
            if(bike == NULL)  //the type has no bike
            {
                return;
            }
            bike -> isRented = true;
            if(rentType == (tempStation->second).end())  //rented not exist
            {
                UBikeHeapIMP newHeap;
                newHeap.addUBikePtr(bike);  //add rented heap
                (tempStation -> second)["Rented"] = newHeap;
            }
            else  //rented exist
            {
                (rentType -> second).addUBikePtr(bike);  //add rented heap
            }
        }

    }
}
    
//=================================================================
// return the bike
//=================================================================
void UBikeSystemIMP::Return
  (std::string station, std::string license, int returnMile){
  	UBike *bike;
    int price;
    std::map< std::string, UBStation >::iterator tempStation;
    bike = ubHashTable.findUBikePtr(license, false);
    if(bike != NULL)  //bike exist
    {
	    int iniMile = bike -> mileage; //initial
	    if(bike -> isRented == true)
	    {
		    tempStation = ubStations.find(bike->station);
		    bike -> mileage = returnMile;
		    if(tempStation != ubStations.end())  //station exist
		    {
		        UBStation::iterator rentType;
		        rentType = (tempStation -> second).find("Rented");
		        if(rentType != (tempStation->second).end())  //rentType exist
		        {
		            bike = (rentType -> second).removeUBikePtr(bike -> heapIndex);
		        }

		        UBStation::iterator tempType;
		        tempType = (tempStation -> second).find(bike -> classType);
		        if(tempType == (tempStation -> second).end())  //classType not exist
		        {
		            UBikeHeapIMP newHeap;
		            newHeap.addUBikePtr(bike);  //add heap
		            (tempStation ->second)[bike -> classType] = newHeap;
		        }
		        else  //classType exist
		        {
		            (tempType -> second).addUBikePtr(bike);
		        }
		    }
		    
		    price = priceTable.calcPrice(returnMile - iniMile, bike -> classType, bike -> station, station);
		    bike -> isRented = false;
		    net += price;
	    }
	}
}
    
//=================================================================
// move the ubike license to another station
//=================================================================
void UBikeSystemIMP::Trans
  (std::string station, std::string license){
  	UBike *bike;
    bike = ubHashTable.findUBikePtr(license,false);
    if(bike != NULL)
    {
        if(bike -> isRented == false)
        {
            std::map< std::string, UBStation >::iterator tempStation;
            tempStation = ubStations.find(bike -> station);
            if(tempStation != ubStations.end())  //station exist
            {
                UBStation::iterator tempType;
                tempType = (tempStation -> second).find(bike -> classType);
                if(tempType != (tempStation -> second).end())//find classtype
                {
                    bike = (tempType->second).removeUBikePtr(bike -> heapIndex);
                }
            }
            tempStation = ubStations.find(station);
            if(tempStation == ubStations.end())  //station not exist
            {
            	UBStation newStation;
        		UBikeHeapIMP newHeap;
        		newHeap.addUBikePtr(bike);  //add heap
        		newStation[bike -> classType] = newHeap;
        		ubStations[station] = newStation;
            }
            else  //station exist
            {
                UBStation::iterator tempType2;
		        tempType2 = (tempStation -> second).find(bike -> classType);
		        if(tempType2 == (tempStation -> second).end())  //classType not exist
		        {
		            UBikeHeapIMP newHeap;
		            newHeap.addUBikePtr(bike);  //add heap
		            (tempStation ->second)[bike -> classType] = newHeap;
		        }
		        else  //classType exist
		        {
		            (tempType2 -> second).addUBikePtr(bike);
		        }
            }
            
        	bike -> station = station;
        }
    }
}
    
//=================================================================
// clear all the allocated memories for ubikes
//=================================================================
void UBikeSystemIMP::ShutDown(){
	for(int i=0;i<256;i++)
    {
        ubHashTable[i].clear();
    }
}