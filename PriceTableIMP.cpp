#include "PriceTableIMP.h"
#include "readonly/ConstParams.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//=================================================================
// calculate the all pairs shortest patch and store the results
// in this->distTable
//=================================================================
void PriceTableIMP::calcAllPairsShortestPath(std::string mapFile){
    ifstream fin(mapFile);
    string placeA,placeB;
    int distance;

    int indexA,indexB;

    for(int i=0;i<12;i++){
    	for(int j=0;j<12;j++){
    		if(i==j)distTable.at(StationNames[i]).at(StationNames[j])=0;
    		else distTable.at(StationNames[i]).at(StationNames[j])=99999;
    	}
    }

    while(fin>>placeA){
    	fin>>placeB;
    	fin>>distance;
    	
    	for(int i=0;i<12;i++){
    		if(StationNames[i]==placeA)indexA=i;
    		if(StationNames[i]==placeB)indexB=i;
    	}

    	distTable.at(StationNames[indexB]).at(StationNames[indexA])=distance;
    	distTable.at(StationNames[indexA]).at(StationNames[indexB])=distance;
    }

    bool visited[12];
    int dist[12];

    for(int v=0;v<12;v++){
        for(int i=0;i<12;i++){
            visited[i]=false;
            dist[i]=distTable.at(StationNames[v]).at(StationNames[i]);
        }

        visited[v]=true;
        for(int i=0;i<11;i++){
            int MinDist=-1;
            int u;
            for(int j=0;j<12;j++){
                if(dist[j]==0||visited[j])continue;
                if(MinDist==-1||dist[j]<MinDist){
                    MinDist=dist[j];
                    u=j;
                }
            }
            visited[u]=true;
            for(int j=0;j<12;j++){
                if(visited[j])continue;
                if((dist[u]+distTable.at(StationNames[u]).at(StationNames[j]))<dist[j]){
                    dist[j]=dist[u]+distTable.at(StationNames[u]).at(StationNames[j]);
                }
            }
        }
        for(int i=0;i<12;i++){
            distTable.at(StationNames[v]).at(StationNames[i])=dist[i];
        }        
    }
}

//=================================================================
// calculate and return the rental when an ubike is returned
//=================================================================
int PriceTableIMP::calcPrice(int milageDiff, std::string bClass,
                  std::string from, std::string toStation){
	int shortDist=this->distTable.at(from).at(toStation);
	int price;
	if(milageDiff>shortDist){
		price = oriRates.find(bClass)->second;
		return milageDiff*price;
	}
	else{
		price = dscntRates.find(bClass)->second;
		return milageDiff*price;
	}

}
