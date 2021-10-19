// Problem Definition:

// Design a Ride sharing application where drivers can offer rides (origin, destination, no of seats), any rider
// can request rides (origin, destination, no of seats).
// There is an algo to choose to calculate Ride amount charged for a given ride based on distance and no of
// seats

// 1. When the ride closes, show the amount charged to the rider.
// 2. Ride amount if No of seats >= 2 : No of kilometers * No of seats * 0.75 * Amount Charged per KM
// 3. Ride amount if No of seats = 1 : No of kilometers * Amount Charged per KM

// The program should take as input two or more drivers and a set of riders requesting rides. Multiple rides
// can happen simultaneously.
// Assumptions :
// 1. Assume Amount charged per KM = 20
// 2. No of Kilometers = destination - origin
// 3. All values are Integer

// Test Case:
// A requesting for ride R1
// INPUT: A requests 50, 60, 1,
// OUTPUT: Ride Amount: 10 * 20 (Amount/Km) = 200
// A requesting for ride R1
// INPUT: A requests 50, 60, 2,
// OUTPUT: Ride Amount: 10 * 2 * 0.75 * 20 (Amount/Km) = 300


// Bonus:
// ● Upgrade the rider to a preferred rider if he has done in more than 10 rides.
// ● Preferred Rider amount if No of seats >= 2 : No of kilometers * No of seats * 0.5 * Amount
// Charged per KM
// ● Preferred Ride amount if No of seats = 1 : No of kilometers * Amount Charged per KM * 0.75
// Functionalities expected:
// ● Add Driver(name)
// ● Add Rider(name)
// ● Create Ride (id, origin, destination, no of seats)
// ● Create/Update Ride (id, origin, destination, no of seats)
// ● Withdraw Ride (id)
// ● Close ride and return ride amount charged


// Expectations:
// 1. Create the sample data yourself. You can put it into a file, test case or main driver program
// itself.
// 2. The code should be demo-able. Either by using the main driver program or test cases.
// 3. The code should be modular. The code should have the basic OO design. Please do not jam in
// the responsibilities of one class into another.
// 4. The code should be extensible. Wherever applicable, use interfaces and contracts between
// different methods. It should be easy to add/remove functionality without rewriting the entire
// codebase.
// 5. The code should handle edge cases properly and fail gracefully.
// 6. The code should be legible, readable and DRY.
// 7. Database integration is not required.


// Guidelines:
// 1. Please do not access the internet for anything EXCEPT syntax.
// 2. You are free to use the language and IDE of your choice.
// 3. The entire code should be your own


 #include<bits/stdc++.h>
 using namespace std;

enum RideStatus{IDLE,CREATED,WITHDRAWN,COMPLETED};

class Ride
{
private:
    int id;
    int dest;
    int origin;
    int seats;
    RideStatus rideStatus;

public:
    static const int AMT_PER_KM=20;

    Ride()
    {
        id=origin=dest=seats=0;
        rideStatus=RideStatus::IDLE;
    }
    int calculateFare(bool isPriorityRider)
    {
        int dist=dest-origin;
        if(seats<2)
            return dist*AMT_PER_KM*(isPriorityRider?0.75:1);
        return dist*AMT_PER_KM*(isPriorityRider?0.5:0.75)*seats;
    }
    int getID()
    {
        return id;
    }
    void setDest(int dest)
    {
        this->dest=dest;
    }
    void setID(int id)
    {
        this->id=id;
    }
    void setOrigin(int origin)
    {
        this->origin=origin;
    }
    RideStatus getRideStatus()
    {
        return this->rideStatus;
    }
    void setRideStatus(RideStatus rideStatus)
    {
        this->rideStatus=rideStatus;
    }
    void setSeats(int seats)
    {
        this->seats=seats;
    }

};

class Person
{
public:
    string name;
};

class Driver:private Person
{
public:
    Driver(string name)
    {
        this->name=name;
    }
};

class Rider:private Person
{
private:
    vector<Ride>allRides;
public:
    Rider(string name)
    {
        this->name=name;
    }
    void createRide(int id,int origin,int dest,int seats)
    {
        Ride currentRide;
        currentRide.setID(id);
        currentRide.setOrigin(origin);
        currentRide.setDest(dest);
        currentRide.setRideStatus(RideStatus::CREATED);
        currentRide.setSeats(seats);
        allRides.push_back(currentRide);
    }
    void updateRide(int id,int origin,int dest,int seats)
    {
        auto itr=allRides.rbegin();
        for(    ;itr!=allRides.rend();itr++)
        {
            if(itr->getID()==id)
                break;
        }
        if(itr->getRideStatus()!=RideStatus::CREATED)
        {
            cout<<"Cant update the ride, Ride not in progress\n";
            return;
        }
        itr->setOrigin(origin);
        itr->setDest(dest);
        itr->setSeats(seats);
    }
    void withdrawRide(int id)
    {
        auto itr=allRides.rbegin();
        for(    ;itr!=allRides.rend();itr++)
        {
            if(itr->getID()==id)
                break;
        }
        if(itr->getRideStatus()!=RideStatus::CREATED)
        {
            cout<<"Cant withdraw the ride, Ride not in progress\n";
            return;
        }
        itr->setRideStatus(RideStatus::WITHDRAWN);
        allRides.erase((itr+1).base());  //remove last element

    }
    int closeRide(int id)
    {
        auto itr=allRides.rbegin();
        for(    ;itr!=allRides.rend();itr++)
        {
            if(itr->getID()==id)
                break;
        }
        if(itr->getRideStatus()!=RideStatus::CREATED)
        {
            cout<<"Cant close the ride, Ride not in progress\n";
            return 0;
        }
        itr->setRideStatus(RideStatus::COMPLETED);
        return itr->calculateFare(allRides.size()>=10);
    }
};


 int main()
 {
    Rider r1("lucifer");
    Driver d1("sikanadar paaji");
    r1.createRide(1,50,60,1);
    cout<<r1.closeRide(1)<<"\n";
    r1.updateRide(1,50,60,2);
    cout<<r1.closeRide(1)<<"\n";
    cout<<"  =================\n";


    r1.createRide(1,50,60,1);
    r1.withdrawRide(1);
    r1.updateRide(1,50,60,2);
    cout<<r1.closeRide(1)<<"\n";
    cout<<"  =================\n";

    r1.createRide(1,50,60,1);
    r1.updateRide(1,50,60,2);
    cout<<r1.closeRide(1)<<"\n";
    cout<<"  =================\n";
 }