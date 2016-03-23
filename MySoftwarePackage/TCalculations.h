//
//  TCalculations.h
//
//
//  Created by Erez Cohen on 5/15/15.
//
//
#include "TPlots.h"
#include "TAnalysis.h"



// leptons
#define Me 0.000511
#define Mmu 0.1056


// mesons
#define Mpi 0.1395

// nucleons
#define Mp 0.938
#define Mp2 0.938*0.938
#define Mn 0.939


// nuclei
#define AMU2GeV 0.931494
#define Md      2.0141018 * AMU2GeV // deuteron
#define mC12    12 * AMU2GeV        // Carbon 12
#define mCl38   37.968011 * AMU2GeV // Chlorine 38
#define mAr40   39.962383 * AMU2GeV // Argon 40


// globals
#define SpeedOfLight  30.     // [cm/ns]
#define RAD2DEG TMath::RadToDeg()





#ifndef __TCalculations_H__
#define __TCalculations_H__



#ifdef __CINT__
#pragma link C++ class std::vector<TVector3>+;
#pragma link C++ class std::vector<TLorentzVector>+;
#endif


class TCalculations{
    
    
private:
    
    
    
public:
    
    TPlots * plot;
    
    // constructor
    TCalculations                   (){};
    
    // destructor
    ~TCalculations                  (){};
//    
//    // momentum corrections: energy loss and Coulomb corrections
//    TVector3 EnergyLossCorrrection  ( TVector3 );
//    TVector3 CoulombCorrection      ( TVector3 , Float_t );
//    
//    // Missing mass
//    Double_t MmissNpNn              (TLorentzVector , TVector3 , int , int);
//    Double_t ppMmissHe3             (TLorentzVector , TVector3 , TVector3);
//    TString TargetAsString          (int);
//    void    TargetMassAndDeltaE     (int , float * , float *);
   
    
    Float_t DistanceFromPointToLine (Double_t , Double_t , Double_t , Double_t );
    Float_t Chi2FitStraightLine     (const int ,Double_t* ,Double_t* ,Double_t* ,Double_t* ,Double_t* );
    Double_t Sum                    (const int , Double_t*, Double_t, Double_t* , Double_t);
    Double_t Distance               (TVector3 , TVector3 , bool print=false);
    float RadiationLength           (int, int, float);
    
    
    // unit conversions
    float InversefmToInverseGeV     (float x) {return x * 0.1972;}; // 1 / fm = 0.1972 1 / GeV
    float fmToGeV                   (float x) {return x * 5.070 ;}; // 1 fm = 5.070 GeV/c, 1 / fm = 0.1972 / GeV
    float TwoIdenticalSpheresOverlapVolume(float R, float d);

};


#endif
