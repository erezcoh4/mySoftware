#ifndef NUCLEUS_CXX
#define NUCLEUS_CXX

#include "nucleus.h"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nucleus::nucleus( TString fShortName , Int_t fA ){
    
    ShortName = fShortName;
    A = fA;
    Name = Form("%d%s",A,ShortName.Data());
    label = Form("^{%d}%s",A,ShortName.Data());
    
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nucleus::Print(){
    SHOW3( Name , A , mass );
    for (auto nucleon : nucleons) {
        nucleon.Print();
    }
    PrintLine();
}

#endif
