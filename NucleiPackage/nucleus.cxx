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
void nucleus::AddNucleon ( nucleon N ) {
    nucleons.push_back(N);
    if (N.type=="proton") {
        protons.push_back(N);
    }
    else if (N.type=="neutron") {
        neutrons.push_back(N);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nucleus::ClearNucleons(){
    if (!nucleons.empty())  nucleons.clear();
    if (!protons.empty())   protons.clear();
    if (!neutrons.empty())  neutrons.clear();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nucleus::Print(){
    SHOW3( Name , A , mass );
    SHOW2( protons.size() , neutrons.size() );
    for (auto nucleon : nucleons) {
        nucleon.Print();
    }
    PrintXLine();
}


// service (not working with THIS nucleus' nucleons.... )
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
std::vector<Float_t> nucleus::GetDistancesBetweenNucleons( std::vector<nucleon> nucs ){
    std::vector<Float_t> NNdistances;
    for ( auto n1 : nucs ){
        for ( auto n2 : nucs ){
            if ( n1.ID != n2.ID ) {
                NNdistances.push_back( ( n1.position - n2.position ).Mag() );
            }
        }
    }
    return NNdistances;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
std::vector<Float_t> nucleus::GetDistancesBetweenNucleons(std::vector<nucleon> nucs1,
                                                          std::vector<nucleon> nucs2 ){
    std::vector<Float_t> NNdistances;
    for ( auto n1 : nucs1 ){
        for ( auto n2 : nucs2 ){
            if ( n1.ID != n2.ID ) {
                NNdistances.push_back( ( n1.position - n2.position ).Mag() );
            }
        }
    }
    return NNdistances;
}


#endif
