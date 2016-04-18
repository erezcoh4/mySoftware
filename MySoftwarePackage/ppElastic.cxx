#ifndef PPELASTIC_CXX
#define PPELASTIC_CXX

#include "ppElastic.h"










//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::pol ( vector<Double_t> par , Double_t x ){
    
    Double_t result = 0 , i = 0;
    
    for( auto const& a: par) {
        result += a * pow(x,i);
        i ++ ;
    }
    
    return result;
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a0(Double_t Ecm){
    vector<Double_t> pars;
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        return (exp(90.16161 - 42.54657*Ecm) + 250.6459 - 82.64069 * Ecm); // f0
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> {208.6132 , 85.75014 , 9.606524}; // f2
        factor = 1;
        return factor * pol(pars , Ecm);
    }
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a1(Double_t Ecm){
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        pars = vector<Double_t> {81.46621 , - 2.442514 }; // f1
        factor = 1;
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> {9014.328 , - 249.0616 , 26.35260 , 3.374141 }; // f3
        factor = 1e-2;
    }
    return factor * pol(pars , Ecm);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a2(Double_t Ecm){
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        pars = vector<Double_t> { - 1.613531 , - 1.424601 }; // f1
        factor = 1;
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> { 1.403383 , - 4.544666 }; // f1
        factor = 1e-1;
    }
    return factor * pol(pars , Ecm);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a3(Double_t Ecm){
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        pars = vector<Double_t> { 222.9465 , -125.6755 , -23.42175 , 15.85506 }; // f3
        factor = 1;
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> { 816000.1 , 1924544. , 1962241. , -1126850. ,  397754.5 , -88173.33 , 11948.51 , -896.5965 , 27.03873 , .1756284}; // f9
        factor = 1e-2;
    }
    return factor * pol(pars , Ecm);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a4(Double_t Ecm){
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        pars = vector<Double_t> { 1.675475 , -1.718991 , 0.4285591 , 15.85506 }; // f2
        factor = 1e-2;
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> { -535576.2 , 1179326. , -1056764. , 478358.4 ,  -100020.3 , -1995.474 , 5989.377 , -1358.871 , 135.3221 , -5.257673 }; // f9
        factor = 1e-5;
    }
    return factor * pol(pars , Ecm);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a5(Double_t Ecm){
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        pars = vector<Double_t> { -2.464428 , 2.413957 , -0.5908636  }; // f2
        factor = 1e-4;
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> { 6069.216 , -15344.59 , 15584.70 ,  8343.774 , 2567.415 , -458.0696 , 44.27438 , -1.805952 }; // f7
        factor = 1e-7;
    }
    return factor * pol(pars , Ecm);
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a6(Double_t Ecm){
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        pars = vector<Double_t> { 3.266005	, -3.199807	, 0.7833496  }; // f2
        factor = 1e-8;
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> { 4072.224	, -5742.969,	3032.050, 	-734.3411, 	78.63649,	-2.664602	 }; // f5
        factor = 1e-11;
    }
    return factor * pol(pars , Ecm);
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::a7(Double_t Ecm){
    if ( 1.9 < Ecm  && Ecm < 2.1) {
        pars = vector<Double_t> { 3.624606,	-3.551761,	0.8713306  }; // f2
        factor = 1e-1;
    }
    else if ( 2.1 < Ecm  && Ecm < 4.2) {
        pars = vector<Double_t> { 470.0798,	-1108.074,	924.0620,	-362.0080,	70.10400,	-5.363294 }; // f5
        factor = 1e-11;
    }
    return factor * pol(pars , Ecm);
}













//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::g_p(Double_t Ecm, Double_t Theta_cm){
    float e1 = pow((90 - Theta_cm - a1(Ecm))/a2(Ecm) , 2 );
    float e2 = pow((Theta_cm - 90 - a1(Ecm))/a2(Ecm) , 2 );
    return a0(Ecm)*( exp(-e1) + exp(-e2)  );
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::g_v(Double_t Ecm, Double_t Theta_cm){
    return a3(Ecm) + a4(Ecm)*pow( Theta_cm - 90. , 2 ) + a5(Ecm)*pow( Theta_cm - 90. , 4 ) + a6(Ecm)*pow( Theta_cm - 90. , 6 );
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::g_W(Double_t Ecm, Double_t Theta_cm){
    return exp( - pow( (Theta_cm - 90.)/78. , 20) );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::g_q(Double_t Ecm, Double_t Theta_cm){
    return a7(Ecm) * pow( Theta_cm - 90. , 2 );
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
Double_t ppElastic::f_Theta_cm(Double_t Ecm, Double_t Theta_cm){
    return (g_p(Ecm,Theta_cm) + g_W(Ecm,Theta_cm)*g_v(Ecm,Theta_cm) + g_q(Ecm,Theta_cm));
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ppElastic::ppElastic(){
    
    // build pp-eastic c.m. scattering angle following GSI ppElastic analysis [http://web-docs.gsi.de/~webhades/computing/pluto/NN/pp_elastic.html#ref*]
    // two invariant mass regions: 1.9 < Ecm < 2.1 GeV/c2, and 2.1 < Ecm < 4.2 GeV/c2
    TF2 *Xsec = new TF2("Xsec","f_Theta_cm(x,y)",1.9,4.2,0,180);
    plot.SetFrame(Xsec,"d#sigma/d#Omega","c.m. mass #sqrt{s} [GeV/c^{2}]","#theta [deg.]");
    TF1 *Xsec20GeV = new TF2("Xsec","f_Theta_cm(x,y)",1.9,4.2,0,180);
    plot.SetFrame(Xsec20GeV,"","#theta [deg.]");
    TF1 *Xsec24GeV = new TF2("Xsec","f_Theta_cm(x,y)",1.9,4.2,0,180);
    plot.SetFrame(Xsec24GeV,"","c.m. mass #sqrt{s} [GeV/c^{2}]","#theta [deg.]");
    TF1 *Xsec2GeV = new TF2("Xsec","f_Theta_cm(x,y)",1.9,4.2,0,180);
    
}


////....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//float ppElastic::ppElastic_angle(Double_t Ecm){
//    // choose c.m. scattering angle following GSI ppElastic analysis [http://web-docs.gsi.de/~webhades/computing/pluto/NN/pp_elastic.html#ref*]
////    SHOW(Ecm);
////    SHOW(Theta_cm);
////    
//    return Ecm;
//}

#endif
