#include "Tollbooth.h"

int main()
{
    srand( time(NULL) ); // initialise random

    TollBooth* myTollBooth = new TollBooth();

    char pound = 156;

    unsigned go = 1;
    while (go == 1)
    {
        std::cout<<"Toll Booth Ready! What do? \n"
                "1. Take toll \n"
                "2. Open barrier \n"
                "3. Show traffic queue \n"
                "4. Show total earnings \n"
                "5. Quit"<<std::endl;

        std::cout<<"Protocol: ";
        unsigned choice;
        std::cin>>choice;

        switch ( choice )
        {
        case 1:
            myTollBooth->takeToll(); break;
        case 2:
            myTollBooth->moveOn(); break;
        case 3:
            myTollBooth->printQueue(); break;
        case 4:
            std::cout<<pound<<myTollBooth->getIncome()<<std::endl; break;
        case 5:
            go = 0;
        }
        std::cout<<"\n";
    }
}
