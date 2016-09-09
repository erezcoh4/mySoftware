/**
 * \file nucleon.h
 *
 * \ingroup NucleiPackage
 * 
 * \brief Class def header for a class nucleon
 *
 * @author erezcohen
 */

/** \addtogroup NucleiPackage

    @{*/
#ifndef NUCLEON_H
#define NUCLEON_H

#include <iostream>
#include "myIncludes.h"
#include "TPlots.h"
#include "TCalculations.h"

/**
   \class nucleon
   this is my nucleon...
 */
class nucleon{

public:

    nucleon( Int_t fID = 0,
            TString fType =
            "proton" ,
            TVector3  fposition = TVector3() ,
            TLorentzVector fmomentum = TLorentzVector() );
    ~nucleon(){}
    
    void          SetID ( Int_t fID )       {ID = fID;};
    void     SetPDGcode ( Int_t _pdg )      {PDGcode = _pdg;};
    void        SetMass ( Float_t m )       {mass = m;};
    void    SetMomentum ( TLorentzVector p ){momentum = p;}
    void    SetPosition ( TVector3 v )      {position = v;}
    void        SetType ( TString ftype );
    
    
    void          Print ();
    
    
    Int_t           PDGcode , ID;
    
    
    Float_t         mass;
    
    TLorentzVector  momentum;
    
    TVector3        position;
    
    TString         type;

};

#endif
/** @} */ // end of doxygen group 

