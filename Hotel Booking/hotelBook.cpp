#include <bits/stdc++.h>
using namespace std;

//class for hotel data
class Hotel
{
    public:
        string name;
        int roomAvl;
        string location;
        int rating;
        int pricePr;
};

//class for user data
class User : public Hotel
{
    public:
        string uname;
        int uId;
        int cost;
};

bool sortByName(Hotel &A, Hotel &B)
{
    return A.name>B.name;
}
 
bool sortByRating(Hotel &A,Hotel &B)
{
    return A.rating>B.rating;
}

bool sortByRoomAvailabilty(Hotel &A,Hotel &B)
{
    return A.roomAvl < B.roomAvl;
}

//print hotel details
void printHotelData(vector<Hotel>&hotels)
{
    cout<<"                  BookMyHotel     \n";
    cout<<"Hotels       "
        <<"Room      "
        <<"Location     "
        <<"Rating       "
        <<"Price per Room       "
        <<"\n";
    
    for(int i=0;i<hotels.size();i++)
    {
        cout<<hotels[i].name<<"       ";
        cout<<hotels[i].roomAvl<<"        ";
        cout<<hotels[i].location<<"        ";
        cout<<hotels[i].rating<<"             ";
        cout<<hotels[i].pricePr<<"        ";
        cout<<"\n";
    }
}

//sort hotels date by name
void SortHotelsByName(vector<Hotel>&hotels)
{
    sort(hotels.begin(),hotels.end(),sortByName);
    cout<<"Hotels Data By Name:\n\n";
    printHotelData(hotels);
}

//sort hotels data by rating
void SortHotelsByRating(vector<Hotel>&hotels)
{
    sort(hotels.begin(),hotels.end(),sortByRating);
    cout<<"Hotels Data By Rating:\n\n";
    printHotelData(hotels);
}

//sort hotels data by location
void SortHotelByLocation(string loc,vector<Hotel>&hotels)
{
    cout<<"     BookMyHotel     \n";
    cout<<"Hotel Name       "
        <<"Room Availabilty     "
        <<"Location     "
        <<"Rating       "
        <<"Price per Room       "
        <<"\n";
    
    for(int i=0;i<hotels.size();i++)
    {
        if(hotels[i].location!=loc)continue;
        cout<<hotels[i].name<<"     ";
        cout<<hotels[i].roomAvl<<"      ";
        cout<<hotels[i].location<<"     ";
        cout<<hotels[i].pricePr<<"      ";
        cout<<"\n";
    }
}

//sort hotels data by roomAvailabilty
void SortHotelByRoomAvailability(vector<Hotel>&hotels)
{
    sort(hotels.begin(),hotels.end(),sortByRoomAvailabilty);
    printHotelData(hotels);
}

//add user
void addUser(string userName,int userId,int bookingCost,vector<User>&users)
{
    User u;
    u.uname=userName;
    u.uId=userId;
    u.cost=bookingCost;
    users.push_back(u);
    cout<<"User "<<u.uname<<" added\n";
}

//add hotels
void addHotel(string hotelName,int hotelRoomAvail,string hotelLoc,int hotelRating,int hotelPrice,vector<Hotel>&hotels)
{
    Hotel h;
    h.name=hotelName;
    h.roomAvl=hotelRoomAvail;
    h.location=hotelLoc;
    h.rating=hotelRating;
    h.pricePr=hotelPrice;
    hotels.push_back(h);

    cout<<"Hotel "<<h.name<<" added\n"; 
}

//print user data
void PrintUserData(int userId,vector<User>&users)
{
    for(int i=0;i<users.size();i++)
    {
        if(users[i].uId==userId)
        {
            cout<<"User Name: "<<users[i].uname<<"\n";
            cout<<"User Id: "<<users[i].uId<<"\n";
            cout<<"Booking Price: "<<users[i].cost<<"\n";
            return;
        }
    }
    cout<<"User Id Invalid\n";

}

int main()
{
    cout<<"Enter 1 for Adding hotels";
    cout<<"Enter 2 for Adding Users";
    
    //adding hotels
    vector<Hotel>hotels;
    addHotel("Samrat",25,"Patna",4,51000,hotels);
    addHotel("Maurya",15,"Patna",5,15000,hotels);
    addHotel("Ashoka",25,"Patna",4,41000,hotels);
    addHotel("TajMah",15,"Patna",5,53000,hotels);
    
    printHotelData(hotels);
}
