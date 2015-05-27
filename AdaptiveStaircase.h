/*
 * AdaptiveStaircase.h
 *
 *  Created on: 18.04.2015
 *      Author: richi-ubuntu
 */

#ifndef ADAPTIVESTAIRCASE_H_
#define ADAPTIVESTAIRCASE_H_
#include <vector>
#include "testexecution.h"




enum direction {down = -1, stay, up};

typedef struct{
    int nFalseAns; //number of False Answers. Reset to 0, when max number of false answers reached
    int nCorrectAns; // number of correctAnswers
    int nReversal; //number of invertations of the direction, when max number reached, this sequence is finished
    direction dir;
    direction lastdir = up;
    int stepSize;
    int quality;
}tracker;



class AdaptiveStaircase {
private:
    //*****************************************
    // REMARK: We want the 50% mark, which is the threshold for guessing. So we want a 1-up,1-down method!
    const int nUp = 1; //To my knowledge there is no method other than 1-up n-down.
    int nDown;
    int nMaxReversal;
    int nMinReversal;
    direction startFrom;
    std::vector<int> qualSteps; //adaptive qual Steps, one value for each reversal, until minimum step. subsequent will be minimum
    //*****************************************
    std::vector<tracker>myTracker;
    std::vector<int> remainingSeq;
    std::vector<decision> seqAnswers;
    //*****************************************
    std::vector<seqQual> historySQ;

    seqQual currSQ;
    const seqQual endSignal = {-1,-1};


public:
    AdaptiveStaircase(int nDown, direction startFrom, int nMaxReversal, int nMinReversal,
            int startQual, std::vector<int> qualSteps, std::vector<decision> seqAnswers);
    virtual ~AdaptiveStaircase();
    std::vector<seqQual> getHistory(){return historySQ;}
    int genRandomSeq();
    int isCorrect(int seq, decision ans);
    int isFinished();


    void addToHistory(seqQual sq);
    void finishSequence(int seq);
    seqQual nextSeqQual(decision prevAns);
    void updateSeq(int seq, decision ans);
    void updateRemainingSet();

    seqQual getCurrSQ(){return currSQ;}
};

#endif /* ADAPTIVESTAIRCASE_H_ */
