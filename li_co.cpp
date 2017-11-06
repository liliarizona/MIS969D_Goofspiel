#include <iostream>
#include <algorithm>
#include "strategy.h"
#include "li_co.h"

#include "strategy.h"

using namespace std;
int upcardArrFR[13]={0};
int oppPlayedArrFR[13]={0};
int lastRoundFR=0;


li_co::li_co()
{

}

li_co::~li_co()
{

}

int li_co::nextPlay(int upCard, int round, int noOfRounds) {
	cout << "Calling li_co" << endl;

    int i=0;
    if(round!=lastRoundFR)
    {
       for(i=0;i<13;i++)
       {
           upcardArrFR[i]=0;
           oppPlayedArrFR[i]=0;
       }
        lastRoundFR=round;
    }

    int j=0;
    int cardCounter=0;
    int numberPerSuit=13;
    int iPlayed[13]={0};
    int iPlayedIndex=0;
    int iDidntPlayed[13]={0};
    int iDidntPlayedIndex=0;
    int oppPlayedTemp[13]={0};
    int oppPlayedTempIndex=0;
    int oppDidntPlayed[13]={0};
    int oppDidntPlayedIndex=0;

    int flag;

    for(i=1;i<=numberPerSuit;i++)
    {
        if(playedCard(round,i))
        {
            cardCounter++;
            iPlayed[iPlayedIndex]=i;
            iPlayedIndex++;
        }
        else
        {
            iDidntPlayed[iDidntPlayedIndex]=i;
            iDidntPlayedIndex++;
        }
    }

//    cout<<"card : "<<cardCounter<<"\n";
    //deck[round].display();
    upcardArrFR[cardCounter]=upCard;
///////////////////////////////////////////////////////////////////////////////
// refine part starts

    int counter;
    int counter2;

	int markermy,markerop;
	int myPreHands[13]={0};
    int opPrevHands[13]={0};
    int myFutHands[13]={0};
    int opFutHands[13]={0};
    int myFutIndex=0;
    int opFutIndex=0;
    int myPreIndex=0;
    int opPreIndex=0;
    // get current hands status. what cards have been played and what cards are left.
	for(counter=1;counter<=numberPerSuit;counter++)
        {
            markermy=playedCard(round,counter);
            markerop=opponentPlayedCard(round,counter);
            if(markermy)
            {
                myPreHands[myPreIndex]=counter;
                myPreIndex++;
            //    cout<<counter<<"\t";
            }
                else
                {
                    myFutHands[myFutIndex]=counter;
                    myFutIndex++;
                }
            if(markerop)
            {
                opPrevHands[opPreIndex]=counter;
                opPreIndex++;
            }
                else
                {
                    opFutHands[opFutIndex]=counter;
                    opFutIndex++;
                }
        }
   // cout<<"\n";
    sort(myFutHands,myFutHands+numberPerSuit);
    sort(opFutHands,opFutHands+numberPerSuit);


    int preDeck[13]={0};
    int futDeck[13]={0};
    int preDeckIndex=0;
    int futDeckIndex=0;

    for(counter=0;counter<numberPerSuit;counter++)
    {
        flag=1;
        for(counter2=0;counter2<=cardCounter;counter2++)
        {
            if(upcardArrFR[counter2]==counter)
            {
                flag=0;
            }
        }
        if(flag)
        {
            futDeck[futDeckIndex]=counter;
            futDeckIndex++;
        }
        else
        {
            preDeck[preDeckIndex]=counter;
            preDeckIndex++;
        }
    }
    sort(futDeck,futDeck+numberPerSuit);
    sort(preDeck,preDeck+numberPerSuit);

    if(upCard>futDeck[numberPerSuit-1])
    {
        if(myFutHands[numberPerSuit-1]>=opFutHands[numberPerSuit-1])
        {
            return myFutHands[numberPerSuit-1];
        }
    }

    for(i=1;i<=numberPerSuit;i++)
    {
        if(opponentPlayedCard(round,i) && oppPlayedTempIndex<cardCounter)
        {
            oppPlayedTemp[oppPlayedTempIndex]=i;
            oppPlayedTempIndex++;
        }
        else
        {
            oppDidntPlayed[oppDidntPlayedIndex]=i;
            oppDidntPlayedIndex++;
        }
    }

    for(i=0;i<cardCounter;i++)
    {
        flag=1;
        for(j=0;j<cardCounter-1;j++)
        {
            if(oppPlayedTemp[i]==oppPlayedArrFR[j])
            {
                flag=0;
            }

        }
        if(flag)
        {
            oppPlayedArrFR[cardCounter-1]=oppPlayedTemp[i];
        }
    }

    sort(futDeck,futDeck+numberPerSuit);
    sort(preDeck,preDeck+numberPerSuit);
//cout<<"this upcard: "<<upCard<<"\n";
//cout<<"largest further deck: "<<futDeck[numberPerSuit-1]<<"\n";
    if(upCard>futDeck[numberPerSuit-1])
    {
        if(myFutHands[numberPerSuit-1]>=opFutHands[numberPerSuit-1])
        {
            return myFutHands[numberPerSuit-1];
        }
    }
// refine part ends
/////////////////////////////////////////////////////////////////////////////


    if(cardCounter+1>3)
    {
        //int myoppPlayedWithOrderSize=12;
        int correlation[13]={0};

        for(i=0;i<cardCounter+1;i++)
        {
            //cout<<"deck: "<<mydeck.getCard(i+1).get_value()<<"\t";
            correlation[i]=oppPlayedArrFR[i]%upcardArrFR[i];
            //cout<<"correlation: "<<correlation[i]<<"\n";
        }

        int modvalue=100;
        int myreturn=0;
        if(correlation[0] == correlation[1] && correlation[1]== correlation[2])
        {
            modvalue=correlation[0];
        }

        if(modvalue==100)
        {
            myreturn=upCard;
        }
        else
        {
            if((upCard+modvalue+1)==13)
            {
                myreturn=13;
            }
            else
            {
                myreturn=(upCard+modvalue+1)%13;
            }
        }


        if(playedCard(round,myreturn))
        {
            for(i=1;i<10;i++)
            {
                if((myreturn+i)==13)
                {
                        if(!playedCard(round,myreturn+i))
                        {
                            return myreturn+i;
                        }
                }
                else
                {
                    if(!playedCard(round,(myreturn+i)%13))
                       {
                            return (myreturn+i)%13;
                       }
                }
            }
        }
        else
        {
            return myreturn;
        }

    }
    else
    {
        return cardCounter+1;
    }

    return unusedRandomCard(round);
}

