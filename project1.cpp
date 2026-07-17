#include<iostream>
#include<ctime>
#include<string>

std::string getplayerinfo(){
    std::string name;
    std::cout<<"Enter your name: ";
    std::getline(std::cin,name);
    return name;
}

void displaystatus(int balance, int ownedBTC, int ownedAAPL){
    std::cout<<"Your balance is $"<<balance<<"\n";
    std::cout<<"You own "<<ownedBTC<<" BTC."<<"\n";
    std::cout<<"You own "<<ownedAAPL<<" shares of AAPL."<<"\n";
}

void displaymarket(int day, int btcPrice, int applePrice){
    std::cout<<"=========Day "<<day<<"!=========\n";
    std::cout<<"Today's Bitcoin (BTC) price is $"<<btcPrice<<"\n";
    std::cout<<"Today's Apple stock (AAPL) price is $"<<applePrice<<"\n";
    std::cout<<"=========================\n";
}

bool displayoptions(int &bankbalance, int &ownedBTC, int &ownedAAPL, int btcPrice, int applePrice);

void gotobuybtc(int &bankbalance, int &ownedBTC, int btcPrice){
    std::cout<<"You have chosen to buy Bitcoin (BTC). How many BTC would you like to buy? ";
    int amount;
    std::cin>>amount;
    if(bankbalance>=amount*btcPrice){
        std::cout<<"You have bought "<<amount<<" BTC.\n";
        bankbalance-=amount*btcPrice;
        ownedBTC+=amount;
    } else {
        std::cout<<"You do not have enough balance to buy "<<amount<<" BTC.\n";
    }
}

void gotobuyapple(int &bankbalance, int &ownedAAPL, int applePrice){
    std::cout<<"You have chosen to buy Apple stock (AAPL). How many shares would you like to buy? ";
    int amount;
    std::cin>>amount;
    if(bankbalance>=amount*applePrice){
        std::cout<<"You have bought "<<amount<<" shares of AAPL.\n";
        bankbalance-=amount*applePrice;
        ownedAAPL+=amount;
    } else {
        std::cout<<"You do not have enough balance to buy "<<amount<<" shares of AAPL.\n";
    }
}

void gotosellbtc(int &bankbalance, int &ownedBTC, int btcPrice){
    std::cout<<"You have chosen to sell Bitcoin (BTC). How many BTC would you like to sell? ";
    int amount;
    std::cin>>amount;
    if(amount<=ownedBTC){
        std::cout<<"You have sold "<<amount<<" BTC.\n";
        bankbalance+=amount*btcPrice;
        ownedBTC-=amount;
    } else {
        std::cout<<"You do not own enough BTC to sell "<<amount<<" BTC.\n";
    }
}

void gotosellapple(int &bankbalance, int &ownedAAPL, int applePrice){
    std::cout<<"You have chosen to sell Apple stock (AAPL). How many shares would you like to sell? ";
    int amount;
    std::cin>>amount;
    if(amount<=ownedAAPL){
        std::cout<<"You have sold "<<amount<<" shares of AAPL.\n";
        bankbalance+=amount*applePrice;
        ownedAAPL-=amount;
    } else {
        std::cout<<"You do not own enough shares of AAPL to sell "<<amount<<" shares.\n";
    }
}

bool displayoptions(int &bankbalance, int &ownedBTC, int &ownedAAPL, int btcPrice, int applePrice){
    std::cout<<"What would you like to do?\n";
    std::cout<<"1. Buy \n2. Sell \n3. See balance \n4. Skip to next day \n5. Exit game\n";
    int choice;
    std::cin>>choice;
    switch(choice){
        case 1:
         std::cout<<"Which asset would you like to buy? Enter 1 for BTC or 2 for AAPL: ";
         int assetChoice1;
         std::cin>>assetChoice1;
         if(assetChoice1==1){
            gotobuybtc(bankbalance, ownedBTC, btcPrice);
         } else if(assetChoice1==2){
            gotobuyapple(bankbalance, ownedAAPL, applePrice);
         } else {
            std::cout<<"Invalid choice. Please try again.\n";
            displayoptions(bankbalance, ownedBTC, ownedAAPL, btcPrice, applePrice);
            }
            return true;
        case 2:
         std::cout<<"Which asset would you like to sell? Enter 1 for BTC or 2 for AAPL: ";
         int assetChoice2;
         std::cin>>assetChoice2;
         if(assetChoice2==1){
            gotosellbtc(bankbalance, ownedBTC, btcPrice);
         } else if(assetChoice2==2){
            gotosellapple(bankbalance, ownedAAPL, applePrice);
         } else {
            std::cout<<"Invalid choice. Please try again.\n";
            displayoptions(bankbalance, ownedBTC, ownedAAPL, btcPrice, applePrice);
            }
            return true;
        case 3:
            displaystatus(bankbalance, ownedBTC, ownedAAPL);
            return true;
        case 4:
         std::cout<<"Skipping to next day...\n";
         return false;
        case 5:
         std::cout<<"Exiting game. Goodbye!\n";
         exit(0);
        default:
         std::cout<<"Invalid choice. Please try again.\n";
        return displayoptions(bankbalance, ownedBTC, ownedAAPL, btcPrice, applePrice);
    }
}

int main(){
    std::string playername=getplayerinfo();
    std::cout<<"Hi, "<<playername<<"! Welcome to the game!"<<std::endl;

    int bankbalance=10000;
    int ownedBTC=0;
    int ownedAAPL=0;
    int currentDay=1;
    int btcPrice=50000;
    int applePrice=150;

    while(true){
        displaystatus(bankbalance, ownedBTC, ownedAAPL);
        displaymarket(currentDay, btcPrice, applePrice);
        bool keepTradingToday=true;
        while(keepTradingToday){
            keepTradingToday=displayoptions(bankbalance, ownedBTC, ownedAAPL, btcPrice, applePrice);
        }
        currentDay++;
        btcPrice+=rand()%2000-1000;
        double btcfluctuation=1+((rand()%31)-15)/100.0;
        btcPrice*=btcfluctuation;
        double applfluctuation=1+((rand()%31)-15)/100.0;
        applePrice*=applfluctuation;
    }
    return 0;
}