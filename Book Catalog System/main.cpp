#include <bits/stdc++.h>
using namespace std;


enum Category
{
    Science,Engineering,History,Fiction,Sci_fi,Mythology
};

class Book
{
private:
    string name;
    string author;
    string publisher;
    int publishYear;
    Category category;
    double price;
    int countSold;
public:
    Book(string name,string author,string publisher,int publishYear,Category category,double price,int countSold)
    {
        this->name=name;
        this->author=author;
        this->publisher=publisher;
        this->publishYear=publishYear;
        this->category=category;
        this->price=price;
        this->countSold=countSold;
    }
    string getName()
    {
        return this->name;
    }
    string getAuthor()
    {
        return this->author;
    }
    string getPublisher()
    {
        return this->publisher;
    }
    int getPublishYear()
    {
        return this->publishYear;
    }
    Category getCategory()
    {
        return this->category;
    }
    double getPrice()
    {
        return this->price;
    }
    int getCountSold()
    {
        return this->countSold;
    }
};
class CatalogueSystem
{
public:
    list<Book>Books;
    // priority_queue<pair<int,Book*>,vector<pair<int,Book*>>>countQueue;
    CatalogueSystem(){};
    void addBookToCatalogue(Book book)
    {
        Books.push_back(book);
    }
    vector<Book>searchBookByAuthor(string prefixAuthorName)
    {
        vector<Book>bookByAuthor;
        for(auto b:Books)
        {
            if(b.getAuthor().substr(0,prefixAuthorName.length())==prefixAuthorName)
            {
                bookByAuthor.push_back(b);
            }
        }
        return bookByAuthor;
    }
    vector<Book>searchBookByName(string prefixName)
    {
        vector<Book>bookByName;
        for(auto b:Books)
        {
            if(b.getName().substr(0,prefixName.length())==prefixName)
            {
                bookByName.push_back(b);
            }
        }
        return bookByName;
    }
    vector<Book>getMostSoldBook(string author,int limit)
    {
        vector<Book>mostSold;
        if(limit<=0)return mostSold;

        priority_queue<pair<int,Book*>>countQueue;
        for(auto &b:Books)
        {
            if(b.getAuthor()==author)
            {
                countQueue.push({b.getCountSold(),&b});
                if(countQueue.size()>limit)
                    countQueue.pop();
            }
        }
        while(!countQueue.empty())
        {
            mostSold.push_back(*countQueue.top().second);
            countQueue.pop();
        }
        return mostSold;
    }
};

int main()
{
    Book b1("Fault in our starts","John Green","Dutton Books",2012,Fiction,250.5,5);
    Book b2("Concept of Physics1","HC Verma","Bharti Bhawan",2001,Science,400,125);
    Book b3("Concept of Physics2","HC Verma","Bharti Bhawan",2001,Science,400,1250);
    Book b4("Concept of Physics3","HC Verma","Bharti Bhawan",2001,Science,800,1215);
    Book b5("Concept of Physics4","HC Verma","Bharti Bhawan",2001,Science,1000,14025);
    Book b6("Concept of Physics5","HC Verma","Bharti Bhawan",2001,Science,4000,1025);
    Book b7("Concept of Physics6","HC Verma","Bharti Bhawan",2001,Science,480,1225);
    Book b8("Concept of Physics7","HC Verma","Bharti Bhawan",2001,Science,1400,12545);
    Book b9("Concept of Physics8","HC Verma","Bharti Bhawan",2001,Science,4100,1258);
    Book b10("Physics9","HC Pandit","Bharti Bhawan",2001,Science,4100,258);
    CatalogueSystem system;
    system.addBookToCatalogue(b1);
    system.addBookToCatalogue(b2);
    system.addBookToCatalogue(b3);
    system.addBookToCatalogue(b4);
    system.addBookToCatalogue(b5);
    system.addBookToCatalogue(b6);
    system.addBookToCatalogue(b7);
    system.addBookToCatalogue(b8);
    system.addBookToCatalogue(b9);
    system.addBookToCatalogue(b10);

    cout<<"******************************************\n";
    cout<<"searchBookByName= "<<"Concept of Phy\n";
    cout<<"Book Name      "<<" "<<"Author Name    "<<" "<<"Publisher Name   "<<" "<<"PublishYear"<<" "<<"Category  "<<" "<<"Price"<<" "<<"CountSold"<<"\n";
    for(auto b:system.searchBookByName("Concept of Phy"))
    {
        cout<<b.getName()<<" "<<b.getAuthor()<<" "<<b.getPublisher()<<" "<<b.getPublishYear()<<" "<<b.getCategory()<<" "<<b.getPrice()<<" "<<b.getCountSold()<<"\n";
    }


    cout<<"\n\n******************************************\n";
     cout<<"searchBookByAuthor= "<<"HC\n";
    cout<<"Book Name      "<<" "<<"Author Name    "<<" "<<"Publisher Name   "<<" "<<"PublishYear"<<" "<<"Category  "<<" "<<"Price"<<" "<<"CountSold"<<"\n";
    for(auto b:system.searchBookByAuthor("HC"))
    {
        cout<<b.getName()<<" "<<b.getAuthor()<<" "<<b.getPublisher()<<" "<<b.getPublishYear()<<" "<<b.getCategory()<<" "<<b.getPrice()<<" "<<b.getCountSold()<<"\n";
    }

    cout<<"\n\n******************************************\n";
    cout<<"Book Name      "<<" "<<"Author Name    "<<" "<<"Publisher Name   "<<" "<<"PublishYear"<<" "<<"Category  "<<" "<<"Price"<<" "<<"CountSold"<<"\n";
    for(auto b:system.getMostSoldBook("HC Verma",8))
    {
        cout<<b.getName()<<" "<<b.getAuthor()<<" "<<b.getPublisher()<<" "<<b.getPublishYear()<<" "<<b.getCategory()<<" "<<b.getPrice()<<" "<<b.getCountSold()<<"\n";
    }
    cout<<"\n\n******************************************\n";
}