#include<bits/stdc++.h>
using namespace std;

//pm->0,minister->1,mp->2
class Person
{
private:
    string name;
    bool isMP;
    bool isMinister;
    bool isPM;
    string constituency;
    int spendLimit;
public:
    Person(){}
    Person(string name,int role,int spendLimit,string constituency)
    {
        this->name=name;
        this->spendLimit=spendLimit;
        this->constituency=constituency;
        this->isMP=true;
        this->isMinister=false;
        this->isPM=false;
        if(role==0)
        {
            this->isMinister=true;
            this->isMP=true;
        }
        if(role==1)
        {
            this->isMinister=true;
        }
    }
    void spendMoney(int money)
    {
        int left=this->spendLimit - money;
        this->spendLimit =left;
    }
    string getName()
    {
        return this->name;
    }
    string getConstituencyName()
    {
        return this->constituency;
    }
    bool getIsMP()
    {
        return this->isMP;
    }
    bool getIsMinister()
    {
        return this->isMinister;
    }
    bool getIsPM()
    {
        return this->isPM;
    }
    int getSpendLimitLeft()
    {
        return this->spendLimit;
    }
};

class PoliticalSystem
{
private:
    vector<Person>persons;
    vector<int>spendLimit;
public:
    PoliticalSystem()
    {
        vector<Person>persons;
        this->persons=persons;
        vector<int>spendLimit;
        spendLimit.push_back(10000000);
        spendLimit.push_back(1000000);
        spendLimit.push_back(100000);
        this->spendLimit=spendLimit;
    }
    void addPersonToSystem(string name,int role,string constituency)
    {
        for(Person &p:persons)
        {
            if(p.getConstituencyName()==constituency)
            {
                cout<<"Sorry this constituency is already assigned on the name of "+p.getName()<<"\n";
                return;
            }
        }
        Person p=Person(name,role,spendLimit[role],constituency);
        persons.push_back(p);
        cout<<"Success! Constituency "<<constituency<<" assigned to "<<name<<"\n";
        return;
    }
    void spendMoney(int money,string name,string constituency)
    {
        for(Person &p:persons)
        {
            if(p.getName()==name && p.getConstituencyName()==constituency)
            {
                p.spendMoney(money);
                cout<<"Success! Money spent by "<<p.getName()<<"\n";
                return;
            }
        }
        cout<<"Invalid name or constituency name\n";
    }
    void isExceedExpense(string name,string constituency)
    {
        for(Person &p:persons)
        {
            if(p.getName()==name && p.getConstituencyName()==constituency)
            {
                if(p.getSpendLimitLeft()>=0)
                {
                    cout<<p.getName()<<" still has Rs "<<p.getSpendLimitLeft()<<"left in spend left.\n";
                    return;
                }
                if(p.getIsPM())
                {
                    cout<<p.getName()<<" has exceeded the expense by "<<p.getSpendLimitLeft()<<" but he cant be arrested as he is PM\n";
                    return;
                }
                if(p.getIsMinister())
                {
                    cout<<p.getName()<<" has exceeded the expense by "<<p.getSpendLimitLeft()<<" but he can be arrested only with the permission of PM\n";
                    return;
                }
                if(p.getIsMP())
                {
                    cout<<p.getName()<<" has exceeded the expense by "<<p.getSpendLimitLeft()<<"and hence he can be arrested by the commision\n";
                    return;
                }
            }
        }
    }
    
};


int main()
{
    PoliticalSystem system;
    system.addPersonToSystem("Ankit",1,"PatnaSahib");
    system.addPersonToSystem("Sparsh",0,"Haridwar");
    system.addPersonToSystem("Rohit",2,"Hyderabad");

    cout<<"******************************************************\n";


    system.addPersonToSystem("Amit",2,"Haridwar");
    cout<<"******************************************************\n";

    system.spendMoney(100000,"Ankit","PatnaSahib");
    system.isExceedExpense("Ankit","PatnaSahib");
   
    system.spendMoney(200000000,"Ankit","PatnaSahib");
    system.isExceedExpense("Ankit","PatnaSahib");
    cout<<"******************************************************\n";
    system.spendMoney(200000000,"Ankit","NewDelhi");


}

//output:
// Success! Constituency PatnaSahib assigned to Ankit
// Success! Constituency Haridwar assigned to Sparsh
// Success! Constituency Hyderabad assigned to Rohit
// ******************************************************        
// Sorry this constituency is already assigned on the name of Sparsh
// ******************************************************
// Success! Money spent by Ankit
// Ankit still has Rs 900000left in spend left.
// Success! Money spent by Ankit
// Ankit has exceeded the expense by -199100000 but he can be arrested only with the permission of PM
// ******************************************************
// Invalid name or constituency name