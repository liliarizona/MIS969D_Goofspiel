#ifndef li_CO_H_INCLUDED
#define li_CO_H_INCLUDED

#include "strategy.h"
extern int upcardArrFR[13];
extern int oppPlayedArrFR[13];
extern int lastRoundFR;

class li_co : public strategy
{
public:
	li_co();
	virtual ~li_co();
	int nextPlay(int upCard, int round, int noOfRounds);
};

#endif // li_co_H_INCLUDED
