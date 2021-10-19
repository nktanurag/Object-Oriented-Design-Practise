#include<bits/stdc++.h>
using namespace std;


class Booking
{
private:
    int start,end;
public:
    Booking(){};
    Booking(int start,int end)
    {
        this->start=start;
        this->end=end;
    }
    int getStart(){return this->start;}
    int getEnd(){return this->end;}
};

class Car
{
private:
    string model;
    int idCar;
    int price;
    vector<Booking*>Calendar;
public:
    Car(){};
    Car(string model,int price)
    {
        this->model=model;
        this->price=price;
        this->idCar=generateCarId();
        this->Calendar={};
    }
    bool bookCar(int start,int end)
    {
        for(auto b:Calendar)
        {
            if(b->getStart()>end || b->getEnd()<start)
                continue;
            else return false;
        }
        Booking b=Booking(start,end);
        Calendar.push_back(&b);
        return true;
    }
    string getModel(){return this->model;}
    int getIdCar(){return this->idCar;}
    int getPrice(){return this->price;}
    
    int generateCarId()
    {
        static int id=1;
        return id++;
    }
};

class Location
{
private:
    vector<Car*>Cars;
    string locationName;
    int locationId;
    int start,end;
public:
    Location(){};
    Location(string locationName,int start,int end)
    {
        this->start=start;
        this->end=end;
        this->locationName=locationName;
        this->locationId=generateLocationId();
        this->Cars={};
    };
    int addCar(string model,int price)
    {
        Car newCar=Car(model,price);
        Cars.push_back(&newCar);
        return newCar.getIdCar();
    }
    vector<int>carAvailable(int start,int end)
    {
        vector<int>availableCar;
        for(Car* c:this->Cars)
        {
            if(c->bookCar(start,end))
            {
                availableCar.push_back(c->getIdCar());
            }
        }
        return availableCar;
    }
    priority_queue<pair<int,int>>carAvailableByPrice(int start,int end)
    {
        priority_queue<pair<int,int>>carAvailableByPrice;
        for(Car* c:Cars)
        {
            if(c.bookCar(start,end))
            {
                carAvailableByPrice.push({c->getPrice(),c->getIdCar()});
            }
        }
        return carAvailableByPrice;
    }
    int generateLocationId()
    {
        static int id=0;
        return id++;
    }
    string getLocationName(){return this->locationName;}
    int getLocationId(){return this->locationId;}
    int getStart(){return this->start;}
    int getEnd(){return this->end;}
    vector<Car*> getCars(){return this->Cars;}
};
class UberRental
{
private:
    vector<Location*>Locations;
    // unordered_map<string,Location*>locationMap;
public:
    UberRental()
    {
        this->Locations={};
    };
    int addLocation(string locationName,int start,int end)//return loc id
    {
        // if(locationMap.find(locationName)==locationMap.end())return -1;//location name already present
        Location newLocation=Location(locationName,start,end);
        Locations.push_back(&newLocation);
        // locationMap[locationName]=&newLocation;
        return newLocation.getLocationId();
    }
    int addCar(string carModel,string carLocation,int price)//return car id
    {
        for(Location* l:Locations)
        {
            if(l->getLocationName()!=carLocation)continue;
            return l->addCar(carModel,price);
        }
        return -1;  //no location found
    }
    vector<int>searchCar(int start ,int end)
    {
        vector<int>carAvailable;
        for(Location* l:Locations)
        {
            if(!(l->getStart()<=start && l->getEnd()>=end))continue;
            vector<int>carAvailForLoc=l->carAvailable(start,end);
            for(auto carId:carAvailForLoc)
            {
                carAvailable.push_back(carId);
            }
        }
        return carAvailable;
    }
    vector<int>searchCarByPrice(int start,int end)
    {
        vector<int>carAvailable;
        priority_queue<pair<int,int>>carAvailableByPrice;
        for(Location* l:Locations)
        {
            priority_queue<pair<int,int>>carAvailableByPriceAtSingleLoc=l->carAvailableByPrice(start,end);
            while(!carAvailableByPriceAtSingleLoc.empty())
            {
                carAvailableByPrice.push(carAvailableByPriceAtSingleLoc.top());
                carAvailableByPriceAtSingleLoc.pop();
            }
        }
        while(!carAvailableByPrice.empty())
        {
            carAvailable.push_back(carAvailableByPrice.top().second);
            carAvailableByPrice.pop();
        }
        reverse(carAvailable.begin(),carAvailable.end());
        return carAvailable;
    }
};
int main()
{
    UberRental system=UberRental();
    int l1=system.addLocation("CV Raman Hostel",7,22);
    int l2=system.addLocation("APJ Hostel",5,21);
    int l3=system.addLocation("Asima Hostel",6,21);
    int l4=system.addLocation("Tut Block",9,20);
    
    cout<<l1<<" "<<l2<<" "<<l3<<" "<<l4<<"\n";
    
    int c1=system.addCar("Hero Razorback","APJ Hostel",50);
    int c2=system.addCar("Hero Sprint","Asima Hostel",55);
    int c3=system.addCar("WagonR","CV Raman Hostel",500);
    int c4=system.addCar("Hyundai Verna","Tut Block",1000);
    int c5=system.addCar("Hero Plus","APJ Hostel",150);
    int c6=system.addCar("IITP Bus","Asima Hostel",15);
    int c7=system.addCar("DirectorCar","CV Raman Hostel",0);
    int c8=system.addCar("ChoriWalaCycle","APJ Hostel",5);
    cout<<c1<<" "<<c2<<" "<<c3<<" "<<c4<<" "<<c5<<" "<<c6<<" "<<c7<<" "<<c8<<"\n";
    
    vector<int>carsAvail=system.searchCar(10,21);
    for(auto id:carsAvail)
        cout<<id<<" ";
    
}