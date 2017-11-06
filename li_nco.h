#ifndef li_NCO_H_INCLUDED
#define li_NCO_H_INCLUDED

#include "strategy.h"
extern int upcardArrFR[13];
extern int oppPlayedArrFR[13];
extern int lastRoundFR;

class li_nco : public strategy
{
public:
	li_nco();
	virtual ~li_nco();
	int nextPlay(int upCard, int round, int noOfRounds);
};

#endif // li_nco_H_INCLUDED
