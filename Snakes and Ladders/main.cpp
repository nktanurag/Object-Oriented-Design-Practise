
#include<bits/stdc++.h>
using namespace std;

class Snake
{
private:
    int start;
    int end;
public:
    Snake(int start,int end)
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
class Ladder
{
private:
    int start;
    int end;
public:
    Ladder(int start,int end)
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
class Player
{
private:
    int id;
    string name;
    int position;
public:
    Player(string name)
    {
        this->id=generateId();
        this->name=name;
        this->position=0;
    }
    void setPosition(int pos)
    {
        this->position=pos;
    }
    int generateId()
    {
        static int id=1;
        return id++;
    }
    string getName()
    {
        return this->name;
    }
    int getId()
    {
        return this->id;
    }
    int getCurrentPosition()
    {
        return this->position;
    }
};
class Game
{
private:
    vector<Player*>Players;
    int currTurn;
    unordered_map<int,int>snakeAndLadders;
    Player* winner;
    void nextPlayerTurn()
    {
        this->currTurn=((1+this->currTurn)%Players.size());
    }
public:
    Game(vector<Player>&player,vector<Snake>&snakes,vector<Ladder>&ladders)
    {
        vector<Player*>Players;
        for(auto &p:player)
        {
            Players.push_back(&p);
        }
        this->Players=Players;
        for(auto s:snakes)
        {
            snakeAndLadders[s.getStart()]=s.getEnd();
        }
        for(auto l:ladders)
        {
            snakeAndLadders[l.getStart()]=l.getEnd();
        }
        this->currTurn=0;
        this->winner=NULL;
    }
    bool rollDice(Player &player,int diceValue)
    {
        if(diceValue<1 || diceValue>6 || winner!=NULL )
            return false;
        int destination=player.getCurrentPosition() + diceValue;
        if(destination<=100)
        {
            if(snakeAndLadders.find(destination)!=snakeAndLadders.end())
            {
                destination=snakeAndLadders[destination];
            }
            
            player.setPosition(destination);
        }
        if(destination==100)
            this->winner=Players.at(this->currTurn);
        nextPlayerTurn();
        return true;
    }
    Player* getWinner()
    {
        return this->winner;
    }
    Player* getCurrTurn()
    {
        return Players[this->currTurn];
    }
};
int main()
{
    std::srand(time(NULL));
    
    Player p1("Ankit");
    Player p2("Anurag");
    Player p3("Shiv");
    
    Snake s1(34,1);
    Snake s2(25,5);
    Snake s3(47,19);
    Snake s4(65,52);
    Snake s5(87,57);
    Snake s6(99,6);
    Snake s7(91,61);
    
    Ladder l1(3,51);
    Ladder l2(6,27);
    Ladder l3(20,70);
    Ladder l4(36,55);
    Ladder l5(63,95);
    Ladder l6(68,98);
    
    vector<Player>Players={p1,p2,p3};
    vector<Snake>Snakes={s1,s2,s3,s4,s5,s6,s7};
    vector<Ladder>Ladders={l1,l2,l3,l4,l5,l6};
    
    Game system=Game(Players,Snakes,Ladders);
    
    int move=0;
    while(system.getWinner()==NULL)
    {
        cout<<"*********************************************\nMove No="<<++move<<"\n";
        Player* currTurnPlayer=system.getCurrTurn();
        bool rightMove=false;
        while(!rightMove)
        {
            int diceValue=(rand()%6)+1;
            cout<<currTurnPlayer->getName()<<" "<<"Id->"<<currTurnPlayer->getId()<<" Dicevalue "<<diceValue<<"\n";
            // cin>>diceValue;
            rightMove=system.rollDice(*currTurnPlayer,diceValue);
            for(auto p:Players)
            {
                cout<<p.getName()<<" at position "<<p.getCurrentPosition()<<"\n";
            }
        }
    }
    cout<<"*********************************************\n";
    cout<<system.getWinner()->getName()<<" with id="<<system.getWinner()->getId()<<" is a winner\n";
}

           