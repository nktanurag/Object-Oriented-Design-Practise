#include<bits/stdc++.h>
using namespace std;

enum ParkingType
{
    Cycle,Compact,Large
};
enum VehicleType
{
    Motorcycle,Car,Bus
};



class Vehicle
{
private:
    string vehicleNo;
    VehicleType vehicleType;
    string ownerName;
public:
    Vehicle(){}
    Vehicle(string vehicleNo,VehicleType vehicleType,string ownerName)
    {
        this->vehicleNo=vehicleNo;
        this->ownerName=ownerName;
        this->vehicleType=vehicleType;
    }
    string getVehicleNo()
    {
        return this->vehicleNo;
    }
    VehicleType getVehicleType()
    {
        return this->vehicleType;
    }
    string getOwnerName()
    {
        return this->ownerName;
    }
};
class ParkingSpot
{
private:
    int levelId,rowId,spotId;
    Vehicle vehicle;
    ParkingType parkingType;
    bool isAvailable;
public:
    ParkingSpot(){};
    ParkingSpot(int levelId,int rowId,int spotId,ParkingType parkingType)
    {
        Vehicle vehicle;
        this->vehicle=vehicle; 
        this->levelId=levelId;
        this->rowId=rowId;
        this->spotId=spotId;
        this->parkingType=parkingType;
        this->isAvailable=true;
    }
    int getLevelId()
    {
        return this->levelId;
    }
    int getRowId()
    {
        return this->rowId;
    }
    int getSpotId()
    {
        return this->spotId;
    }
    bool getIsAvailable()
    {
        return this->isAvailable;
    }
    Vehicle getVehicleBooked()
    {
        return this->vehicle;
    }
    void bookSpot(Vehicle &vehicle)
    {
        this->vehicle=vehicle;
        this->isAvailable=false;
    }
    void unbookSpot(Vehicle &vehicle)
    {
        Vehicle newVehicle;
        this->vehicle=newVehicle;
        this->isAvailable=true;
    }
    ParkingType getParkingType()
    {
        return this->parkingType;
    }
};
class ParkingLotSystem
{
private:
    int level,row,spots;
    vector<vector<vector<ParkingSpot>>>parkingSpots;
public:
    ParkingLotSystem(){}
    ParkingLotSystem(vector<vector<vector<int>>>spotsId)
    {
        this->level=spotsId.size();
        this->row=spotsId[level-1].size();
        this->spots=spotsId[level-1][row-1].size();
        vector<vector<vector<ParkingSpot>>>parkingSpots(level,vector<vector<ParkingSpot>>(row,vector<ParkingSpot>(spots)));
        for(int i=0;i<level;i++)
        {
            for(int j=0;j<row;j++)
            {
                for(int k=0;k<spots;k++)
                {
                    if(spotsId[i][j][k]==0)
                    {
                        ParkingSpot newSpot=ParkingSpot(i+1,j+1,k+1,Cycle);
                        parkingSpots[i][j][k]=newSpot;
                    }
                    else if(spotsId[i][j][k]==1)
                    {
                        ParkingSpot newSpot=ParkingSpot(i+1,j+1,k+1,Compact);
                        parkingSpots[i][j][k]=newSpot;
                    }
                    else
                    {
                        ParkingSpot newSpot=ParkingSpot(i+1,j+1,k+1,Large);
                        parkingSpots[i][j][k]=newSpot;
                    }
                        
                }
            }
        }
        this->parkingSpots=parkingSpots;
    }
    
    void bookVehicle(string vehicleNo,VehicleType vehicleType,string ownerName)
    {
        for(int i=0;i<level;i++)
        {
            for(int j=0;j<row;j++)
            {
                vector<ParkingSpot*>existingAvailable;
                for(int k=0;k<spots;k++)
                {
                    string vehicleno;
                    if(parkingSpots[i][j][k].getParkingType()==Cycle || parkingSpots[i][j][k].getParkingType()==Compact  || parkingSpots[i][j][k].getIsAvailable()==false)
                    {
                        existingAvailable={};
                        vehicleno="";
                    } 
                    else if(existingAvailable.size()==0 || vehicleno==parkingSpots[i][j][k].getVehicleBooked().getVehicleNo())
                    {
                        existingAvailable.push_back(&parkingSpots[i][j][k]);
                        vehicleno=parkingSpots[i][j][k].getVehicleBooked().getVehicleNo();
                    }
                    else
                    {
                        existingAvailable={};
                        vehicleno="";
                    }
                        
        
                    if(vehicleType==Motorcycle && parkingSpots[i][j][k].getIsAvailable())
                    {
                        Vehicle newVehicle=Vehicle(vehicleNo,vehicleType,ownerName);
                        parkingSpots[i][j][k].bookSpot(newVehicle);
                        cout<<"Booking successful at: Level: "<<parkingSpots[i][j][k].getLevelId()<<" Row: "<<parkingSpots[i][j][k].getRowId()<<" Spot: "<<parkingSpots[i][j][k].getSpotId()<<"\n";
                        return;
                    }
                    else if(vehicleType==Car && parkingSpots[i][j][k].getIsAvailable() && (parkingSpots[i][j][k].getParkingType()==Compact || parkingSpots[i][j][k].getParkingType()==Large))
                    {
                        Vehicle newVehicle=Vehicle(vehicleNo,vehicleType,ownerName);
                        parkingSpots[i][j][k].bookSpot(newVehicle);
                        cout<<"Booking successful at: Level: "<<parkingSpots[i][j][k].getLevelId()<<" Row: "<<parkingSpots[i][j][k].getRowId()<<" Spot: "<<parkingSpots[i][j][k].getSpotId()<<"\n";
                        return;
                    }
                    else if(vehicleType==Bus && existingAvailable.size()==5)
                    {
                        Vehicle newVehicle=Vehicle(vehicleNo,vehicleType,ownerName);
                        for(auto &s:existingAvailable)
                        {
                            s->bookSpot(newVehicle);
                        }
                        cout<<"Booking successful at: Level: "<<parkingSpots[i][j][k].getLevelId()<<" Row: "<<parkingSpots[i][j][k].getRowId()<<" Spot: "<<parkingSpots[i][j][k].getSpotId()-4<<"\n";
                        return;
                    }
                }
            }
        }
        cout<<"Booking Unsuccessful\n";
        return;
    }
    void unbookVehicle(int level,int row,int spot)
    {
        if(parkingSpots[level-1][row-1][spot-1].getIsAvailable())
        {
            cout<<"Parking Spot already empty\n";
            return;
        }
        if(parkingSpots[level-1][row-1][spot-1].getVehicleBooked().getVehicleType()!=Bus)
        {
            string vehicleno=parkingSpots[level-1][row-1][spot-1].getVehicleBooked().getVehicleNo();
            Vehicle v=parkingSpots[level-1][row-1][spot-1].getVehicleBooked();
            parkingSpots[level-1][row-1][spot-1].unbookSpot(v);
            cout<<"Success!, Vehicle No: "<<vehicleno<<"unbooked successfully "<< "Level-Row-Slot: "<<level<<"-"<<row<<"-"<<spot<<" unbooked Unsuccessfully\n"; 
        }
        else
        {
            //assume user provide starting point of spot and not in middle
            string vehicleno=parkingSpots[level-1][row-1][spot-1].getVehicleBooked().getVehicleNo();
            for(int i=0;i<5;i++)
            {
                if(spot-1+i >= this->spots || parkingSpots[level-1][row-1][spot-1+i].getIsAvailable() || parkingSpots[level-1][row-1][spot-1+i].getVehicleBooked().getVehicleNo()!=vehicleno)
                {
                    cout<<"Invalid Input, Please Try Again\n";
                }
            }
            for(int i=0;i<5;i++)
            {
                Vehicle v=parkingSpots[level-1][row-1][spot-1+i].getVehicleBooked();
                parkingSpots[level-1][row-1][spot-1+i].unbookSpot(v);
            }
            cout<<"Success!, Vehicle No: "<<vehicleno<<"unbooked successfully "<<" Level-Row-Slot: "<<level<<"-"<<row<<"-"<<spot<<" unbooked Unsuccessfully\n"; 
        }
    }
    void getStatusSlot(int level,int row,int spot)
    {
        if(parkingSpots[level-1][row-1][spot-1].getIsAvailable())
        {
            cout<<"Success, Level-Row-Slot:"<<level<<"-"<<row<<"-"<<spot<<" is availble to be booked"<<"\n";
        }
        else
        {
            cout<<"Oops! Sorry, Level-Row-Slot:"<<level<<"-"<<row<<"-"<<spot<<" is not availble to be booked\n";
           
            Vehicle v=parkingSpots[level-1][row-1][spot-1].getVehicleBooked();
            cout<<"Info about given slot: Vehicle No: "<<v.getVehicleNo()<<" Vehcile Type: "<<v.getVehicleType()<<" Owner Name: "<<v.getOwnerName()<<" \n";
        }
    }
};


int main()
{
    vector<vector<vector<int>>>spotsId={
        {
            {0,0,1,1,1,0,2},
            {1,0,2,1,2,2,1},
            {1,0,2,0,2,1,0}
        },
        {
            {2,2,2,2,2,1,2},
            {1,0,2,2,2,2,0},
            {1,0,1,2,2,2,0}
        }
    };
    vector<VehicleType>vehicles={Motorcycle,Car,Bus};
    ParkingLotSystem system=ParkingLotSystem(spotsId);
    // system.bookVehicle("BR12",Motorcycle,"Ankit");
    // system.getStatusSlot(1,1,1);
    cout<<"Press 1 to book Vehicle \n";
    cout<<"Press 2 to unbook Vehicle \n";
    cout<<"Press 3 to get status of a slot \n";
    cout<<"Press 4 to stop \n\n";
    int choice;
    while(2)
    {
        cout<<"Enter choice\n";
        cin>>choice;
        if(choice==1)
        {
            string vehicleNo,ownerName;
            int vehicleType;
            cout<<"Enter vehicle no,vehicleType,ownerName\n";
            cin>>vehicleNo>>vehicleType>>ownerName;
            system.bookVehicle(vehicleNo,vehicles[vehicleType],ownerName);
            cout<<"*********************************************************\n";
        }
        else if(choice==2)
        {
            int level,row,spot;
            cout<<"Enter level,row,spot\n";
            cin>>level>>row>>spot;
            system.unbookVehicle(level,row,spot);
            cout<<"*********************************************************\n";
        }
        else if(choice==3)
        {
            int level,row,spot;
            cout<<"Enter level,row,spot\n";
            cin>>level>>row>>spot;
            system.getStatusSlot(level,row,spot);
            cout<<"***********************************************************\n";
        }
        else if(choice==4)
        {
            exit(0);
        }
        else 
        {
            cout<<"Wrong Input, Try Again!\n";
        }

    }
    

}










