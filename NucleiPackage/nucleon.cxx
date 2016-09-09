#ifndef NUCLEON_CXX
#define NUCLEON_CXX

#include "nucleon.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nucleon::nucleon( Int_t fID, TString ftype , TVector3 fposition , TLorentzVector fmomentum ){
    SetID(fID);
    SetType(ftype);
    SetPosition(fposition);
    SetMomentum(fmomentum);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nucleon::SetType ( TString ftype )
{
    type = ftype;
    if (type=="proton") {
        PDGcode = 2212;
        mass = Mp;
    }
    else if (type=="neutron") {
        PDGcode = 2112;
        mass = Mn;
    }
    else mass = 0;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nucleon::Print (){
    SHOW3( type , PDGcode , ID );
    SHOWTVector3( position );
    SHOWTLorentzVector( momentum );
    PrintLine();
}

#endif
