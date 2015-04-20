#include "AdaptiveStaircase.h"
#include <stdlib.h>
#include "stdio.h"
#include <iostream>
#include <algorithm>

using namespace std;




void AdaptiveStaircase::updateSeq(int seq, answer ans){
    tracker &tr = myTracker.at(seq); // get Tracker for that sequence
    // ***** Evaluate answer and increment the corresponding counter *****
    if(isCorrect(seq,ans)){
        tr.nCorrectAns++;
    }else{
        tr.nFalseAns++;
    }
    // ***** Determine moving direction of stimu (up, down, stay?) *****
    if(tr.nFalseAns >= nUp){ // Increase stimu level(UP) + reset answers
        tr.dir = up;
        tr.nFalseAns = 0;
        tr.nCorrectAns = 0;
    } else if(tr.nCorrectAns >= nDown){ // Decrease stimu level (DOWN) + reset answers
        tr.dir = down;
        tr.nFalseAns = 0;
        tr.nCorrectAns = 0;
    } else{ // If not enough correct/false answers, STAY at this stimu lvl + do NOT reset answers
        tr.dir = stay;
    }

    // Increment reversal counter
    if (tr.dir != stay){ // reversal
        tr.nReversal++;
    }
    // ***** determine the stepSize (adaptive) *****
    if (tr.nReversal <= qualSteps.size() - 1){ //Check whether index is in boundary
        tr.stepSize = qualSteps.at(tr.nReversal);
    } else { //If Index greater than number of elements in qualSteps, take the last one! This is the smallest step.
        tr.stepSize = qualSteps.at(qualSteps.size()-1);
    }

    // ***** put in the new quality *****
    tr.quality = tr.quality + tr.dir*tr.stepSize;

    // ***** Check for "impossible" quality values (staircase reaches one of both endpoints) --> keep inside boundary *****
    if (tr.quality <= 0){
        tr.quality = qualSteps.at(qualSteps.size()-1); //last element of qualSteps = minimum qual level
    }
    if (tr.quality > 100){
        tr.quality = 100;
    }
}


// This function shall always be called, when next sequence shall be played. This function needs as argument,
// the answer from the current sequence to process it.
seqQual AdaptiveStaircase::nextSeqQual(answer prevAns){
    if(!this->isFinished()){
        this->addToHistory(currSQ);
        this->updateSeq(currSQ.sequence, prevAns);
        this->updateRemainingSet();
        this->currSQ.sequence = genRandomSeq();
        this->currSQ.quality = myTracker.at(currSQ.sequence).quality;
        return currSQ;
    } else{
        return endSignal;
    }
}

// If a sequence has reached nMaxReversal reversals, then delete it from remaining set
// --> Random generator will not generate this sequence again
void AdaptiveStaircase::updateRemainingSet(){
    for(int i = 0; i < myTracker.size(); i++){
        auto pos = std::find(remainingSeq.begin(), remainingSeq.end(), i);
        if(pos!=remainingSeq.end() && myTracker.at(i).nReversal >= nMaxReversal){
            remainingSeq.erase(pos);
        }
    }
}

// The whole procedure is finished, if every sequence has at least nMaxReversal reversals
int AdaptiveStaircase::isFinished(){
    for(int i = 0; i < myTracker.size(); i++){
        if(myTracker.at(i).nReversal < nMinReversal){return false;} // Some more reversals needed! Not finished
    }
    return true;
}

// Generate a random sequence from the remaining set
int AdaptiveStaircase::genRandomSeq()
{
    return remainingSeq.at(rand()%remainingSeq.size());
}

void AdaptiveStaircase::addToHistory(seqQual sq)
{
    historySQ.push_back(sq);
}

// This function should return whether the given answer ans to sequence seq was correct or false to the sequence
int AdaptiveStaircase::isCorrect(int seq, answer ans)
{
    return seqAnswers.at(seq) == ans;
}

AdaptiveStaircase::~AdaptiveStaircase(){

}


AdaptiveStaircase::AdaptiveStaircase(int nDown, direction startFrom, int nMaxReversal, int nMinReversal, int startQual,
        std::vector<int> qualSteps, std::vector<answer> seqAnswers)
{
    this->nDown = nDown;
    this->startFrom = startFrom;
    this->nMaxReversal = nMaxReversal;
    this->nMinReversal = nMinReversal;
    this->qualSteps = qualSteps;
    this->seqAnswers = seqAnswers;

    tracker temp_tracker = {0,0,0,stay,qualSteps.at(0),startQual};
    for(int i=0;i<seqAnswers.size();i++){
        myTracker.push_back(temp_tracker);
        remainingSeq.push_back(i);
    }

    this->currSQ.sequence = this->currSQ.sequence = genRandomSeq();
    this->currSQ.quality = startQual;

// use qualSteps somehow like this.. only specify until the last step size, subsequent sequences will use last entry.
/*
    this->qualSteps.push_back(20); // 0. - 1. reversal
    this->qualSteps.push_back(20); // 1. - 2. reversal
    this->qualSteps.push_back(10);
    this->qualSteps.push_back(10);
    this->qualSteps.push_back(5); // 5. - n. reversal
*/
}
