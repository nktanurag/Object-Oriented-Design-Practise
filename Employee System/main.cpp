#include<bits/stdc++.h>
using namespace std;

class Employee
{
private:
    int employeeId;
    string name;
    list<Employee>subordinates;
    int managerId;
public:
    Employee(string name)
    {
        this->name=name;
        this->employeeId=getUniqueId();
        this->managerId=0;
    }
    int getUniqueId()
    {
        static int id=1;
        return id++;
    }
    void addSubordinate(Employee &subord)
    {
        subordinates.push_back(subord);
    }
    void setManager(int managerId)
    {
        this->managerId=managerId;
    }
    string getName()
    {
        return this->name;
    }
    int getId()
    {
        return this->employeeId;
    }
    int getManagerId()
    {
        return this->managerId;
    }
    list<Employee>getSubordinates()
    {
        return this->subordinates;
    }
};

class EmployeeSystem
{
    list<Employee>Employees;
    unordered_map<int,Employee*>employeeMap;
public:
    EmployeeSystem(){}

    void registerEmployee(Employee& employee)
    {
        int employeeId=employee.getId();
        employeeMap[employeeId]=&employee;
        Employees.push_back(employee);
    }
    void registerManager(int empId,int managerId)
    {
        if(employeeMap.find(empId)==employeeMap.end() ||  employeeMap.find(managerId)==employeeMap.end())
        {
            cout<<"Employee or manager not registered\n";
            return;
        }
        employeeMap[empId]->setManager(managerId);
        employeeMap[managerId]->addSubordinate(*employeeMap[empId]);
    }
    void printDetails(int empId)
    {
        if(employeeMap.find(empId)==employeeMap.end())
        {
            cout<<"No such employee present\n";
            return;
        }
        cout<<"Employee Name -> "<<employeeMap[empId]->getName()<<"\n";
        cout<<"Employee ID -> "<< empId <<"\n";
        cout<<"Manager Name-> "<<employeeMap[employeeMap[empId]->getManagerId()]->getName() <<"\n";
    }
    void printDetails(string prefixName)
    {
        for(Employee e:Employees)
        {
            if(e.getName().substr(0,prefixName.length())==prefixName)
            {
                cout<<"Employee Name -> "<<e.getName()<<"\n";
                cout<<"Employee ID -> "<< e.getId()<<"\n";
                cout<<"Manager Name-> "<<employeeMap[e.getManagerId()]->getName()<<"\n";
                cout<<"\n\n\n";
            }
        }
    }
    list<Employee>getSubordinates(int empId)
    {
        if(employeeMap.find(empId)==employeeMap.end())
        {
            cout<<"No such employee present\n";
            list<Employee>dummy;
            return dummy;
        }
        return employeeMap[empId]->getSubordinates();
    }
    list<Employee>getSubordinates(string name)
    {
        for(Employee e:Employees)
        {
            if(e.getName()==name)
            {
                return e.getSubordinates();
            }
        }
        list<Employee>dummy;
        return dummy;
    }
};

int main()
{
    Employee e1("Ankit");
    Employee e2("Amit");
    Employee e3("Ashu");
    Employee e4("Rohit");
    Employee e5("Ag");

    EmployeeSystem system;
    system.registerEmployee(e1);
    system.registerEmployee(e2);
    system.registerEmployee(e3);
    system.registerEmployee(e4);
    system.registerEmployee(e5);

    system.registerManager(e1.getId(),e2.getId());
    system.registerManager(e3.getId(),e2.getId());
    system.registerManager(e5.getId(),e3.getId());
    system.registerManager(e4.getId(),e3.getId());

    system.printDetails("A");
    cout<<"\n\n\n\n";
    system.printDetails(e1.getId());
    cout<<"\n\n\n\n";
    for(Employee e:system.getSubordinates(e3.getId()))
    {
        cout<<e.getName()<<"\n";
    }
    cout<<"\n\n\n\n";

    for(Employee e:system.getSubordinates(e2.getName()))
    {
        cout<<e.getName()<<"\n";
    }
    cout<<"\n\n\n\n";
}