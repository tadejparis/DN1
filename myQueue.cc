
#include "myQueue.h"

Define_Module(myQueue);		// makro, ki registrira modul

myQueue::myQueue() {
	currentJob = NULL;
	endServiceMsg = NULL;
}

myQueue::~myQueue() {
	delete currentJob;
	cancelAndDelete(endServiceMsg);
}

// inicializacijska metoda
void myQueue::initialize()
{
    endServiceMsg = new cMessage("end");	// sporocilo, ki ga bo modul posiljal samemu sebi - modul si ga interpretira kot konec procesiranja trenutnega opravila
    capacity = par("capacity");				// kapaciteta cakalne vrste
    serviceTime = par("serviceTime");		// cas procesiranje
    queue.setName("queue");					// opcijsko lahko cakalni vrsti dolocimo ime
    length = 0;								// na zacetku je cakalna vrsta prazna
}


// metoda, ki se klice ob sprejemu sporocila
// imamo dva tipa sporocil:
//   - sporocila, ki pridejo od zunaj in predstavljajo opravila, ki jih mora M/M/1 sistem sprocesirati
//   - sporocila, ki jih modul poslje samemu sebi in pomenijo konec procesiranja trenutnega opravila
void myQueue::handleMessage(cMessage *msg)
{
	// ali je prislo sporocilo o koncu procesiranja trenutnega opravila?
	if (msg==endServiceMsg)
    {
        send(currentJob, "out");	// trenutno opravilo je obdelano, zato ga posljemo skozi izhodna vrata naprej v omrezje
        if (queue.isEmpty())			// ce je cakalna vrsta prazna, potem v izvajanje ne moremo vzeti nobenega opravila
        {
            currentJob = NULL;
        }
        else						// ce cakalna vrsta ni prazna, v izvajajnje vzamemo naslednje opravilo v cakalni vrsti
        {
            // modul poslje sporocilo samemu sebi, ki ga bo obvestilo, da je izvajanja opravila konec
            // sporocilo bo prispelo cez cas, ki je dolocen s parametrom serviceTime
            scheduleAt( simTime()+serviceTime, endServiceMsg );
            currentJob = check_and_cast<cMessage *>(queue.pop());	// v spremenljivko currentJob shranimo trenutno opravilo
            EV << "Cakalni cas:" << simTime() - currentJob->getTimestamp() << " s";		// v konzolo izpisemo cas, ki ga je opravilo prezivelo v cakalni vrsti

            length--;				// cakalna vrsta se je skrajsala za 1
        }
    }
    // ali je skozi vhodna vrata prislo novo opravilo, ki ga mora M/M/1 sistem obdelati?
    else
    {
        cMessage *job = msg;

        // v primeru, da v obdelavi trenutno ni nobenega opravila, lahko zacnemo s procesiranja prispelega opravila
        if (currentJob == NULL)
        {
            scheduleAt( simTime()+serviceTime, endServiceMsg ); // modul poslje sporocilo samemu sebi, ki ga bo obvestilo, da je izvajanja opravila konec
            currentJob = job;									// v spremenljivko currentJob shranimo prispelo opravilo
        }
        // v primeru, da procesna enota ni prosta, opravilo poskusimo shraniti v cakalno vrsto
        else
        {
            // ali je cakalna vrsta presegla svojo kapaciteto?
            if (capacity >=0 && length >= capacity)
            {
                delete job;	// ce v cakalni vrsti ni prostora, opravilo zavrzemo
            }
            else
            {
                // sicer opravilo shranimo v cakalno vrsto
                job->setTimestamp();	// s pomocjo TimeStampa bomo lahko izmerili cas, ki ga je opravilo prezivelo v cakalni vrsti
                queue.insert( job );	// vstavljanje v vrsto
                length++;				// dolzina cakalne vrste se je povecala
            }
        }
    }
	updateDisplay(length);		// v graficni vmesnik simulacije izpisemo dolzino cakalne vrste
}

void myQueue::updateDisplay(int i)
{
    char buf[100];
    sprintf(buf, "Q_length :%ld", (long) i);
    getDisplayString().setTagArg("t",0,buf);
}

