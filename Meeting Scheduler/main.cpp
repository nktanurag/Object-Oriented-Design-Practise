#include<bits/stdc++.h>
using namespace std;

class Meeting
{
private:
    int start,end;
public:
    Meeting(){};
    Meeting(int start,int end)
    {
        this->start=start;
        this->end=end;
    }
    int getStart()
    {
        return this->start;
    }
    int getEnd()
    {
        return this->end;
    }
};
class Room
{
private:
    string name;
    vector<Meeting> calendar;
public:
    Room(){};
    Room(string name)
    {
        this->name=name;
        this->calendar={};
    }
    string getRoomName()
    {
        return this->name;
    }
    bool book(int start,int end)
    {
        for(Meeting m:calendar)
        {
            if(m.getStart()>end || m.getEnd()<start)
                continue;
            else
                return false;
        }
        Meeting m=Meeting(start,end);
        calendar.push_back(m);
        return true;
    }
    
};
class Scheduler
{
private:
    vector<Room*>Rooms;
public:
    Scheduler(){};
    Scheduler(vector<Room>&rooms)
    {
        vector<Room*>Rooms;
        for(auto &r:rooms)
        {
            Rooms.push_back(&r);
        }
        this->Rooms=Rooms;
    }

    bool bookMeet(int start,int end)
    {
        for(auto &room:Rooms)
        {
            if(room->book(start,end))
            {
                cout<<"Room Meeting scheduled from "<<start<<" to "<<end<<" in room name "<<room->getRoomName()<<"\n";
                return true;
            }
        }
        cout<<"No Meeting Room Available at given time\n";
        return false;
    }
};

int main()
{
    Room r1("Room1");
    Room r2("Room2");
    Room r3("Room3");
    Room r4("Room4");
    Room r5("Room5");
    
    vector<Room>Rooms={r1,r2,r3,r4,r5};
    
    Scheduler system=Scheduler(Rooms);

    int start,end;
    while(2)
    {
        cout<<"************************************************\n";
        cout<<"Enter Room Starting and Ending Time\n";
        cin>>start>>end;
        if(start==-1 && end==-1)exit(0);
        system.bookMeet(start,end);
        
    }
}
