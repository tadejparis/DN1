

#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <omnetpp.h>

using namespace omnetpp;

class myQueue : public cSimpleModule{
private:
	cQueue queue;					// objekt, ki predstavlja cakalno vrsto
	cMessage *currentJob;			// opravilo, ki se trenutno procesira
    cMessage *endServiceMsg;		// sporocilo, ki ga modul posilja samemu sebi
	int capacity, length;			// capacity = kapaciteta cakalne vrste (parameter), length = trenutna dolzina cakalne vrste
	simtime_t serviceTime;			// cas procesiranja (parameter)

public:
	myQueue();
	virtual ~myQueue();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay(int i);
};
#endif /* MYQUEUE_H_ */
