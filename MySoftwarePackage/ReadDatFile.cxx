#ifndef READDATFILE_CXX
#define READDATFILE_CXX

#include "ReadDatFile.h"
#include <fstream>
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ReadDatFile::ReadDatFile( std::string fInFileName
                         ,std::string fOutFileName
                         ,std::string fInFileType):
InFileName(fInFileName),
InFileType(fInFileType),
OutFileName(fOutFileName)
{
    Print();
    HeaderCSVfile();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ReadDatFile::Print() const{
    std::cout
    << "InFileName: \n" << InFileName << "\n"
    << "OutFileName: \n" << OutFileName
    << std::endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ReadDatFile::HeaderCSVfile(){
    outcsvfile.open( OutFileName );
    cout << "opened OutFile: \n"+OutFileName << endl;
    
    if (InFileType == "RealParticles_Final_ALL") {
        outcsvfile
        << "Ensemb" << "," << "Index" << "," << "Number" << ","
        << "ID" << "," << "IQ" << ","
        << "Anti" << "," << "mass" << ","
        << "E" << "," << "Px" << "," << "Py" << "," << "Pz" << ","
        << "X" << "," << "Y" << "," << "Z"
        << endl;
    }
    
    else if (InFileType == "DoHIA_pert") {
        outcsvfile
        << "ID" << "," << "charge" << ","
        << "parent_1" << "," << "parent_2" << ","
        << "mass" << "," << "indFree" << ","
        << "E" << "," << "Px" << "," << "Py" << "," << "Pz" << ","
        << "event"
        << endl;
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ReadDatFile::ReadDatFromFile( int Nlines
                                  , int debug
                                  , int NeventsToRead){
    std::ifstream InFile;
    InFile.open(InFileName);
    std::cout << "reading \n"<< InFileName << std::endl;
    std::string tmp;
    
    if (Nlines==-1) Nlines=1000000;
    if (NeventsToRead==-1) NeventsToRead=1000000;

    
    // read the file
    if (InFileType == "RealParticles_Final_ALL") {
        getline(InFile, tmp);
        std::cout << tmp << std::endl;
        for (int i = 0; i < Nlines; i++){
            InFile
            >> Ensemb[i]
            >> tmp // |
            >> Index[i]
            >> tmp // [
            >> Number[i]
            >> tmp // ]:
            >> ID[i] >> IQ[i] >> Anti[i] >> mass[i]
            >> tmp // |
            >> E[i] >> Px[i] >> Py[i] >> Pz[i]
            >> tmp // |
            >> X[i] >> Y[i] >> Z[i]
            >> tmp // |
            >> ScaleCS[i] >> firstEvent[i]
            >> tmp // [
            >> event_1[i] >> event_2[i]
            >> tmp // ]:
            >> perWeight[i]
            >> tmp // time:
            >> formationTime[i]
            >> productionTime[i]
            >> lastCollisionTime[i]
            >> in_Formation[i]
            >> tmp // parents:
            >> parents_1[i] >> parents_2[i] >> parents_3[i];
            
            if (InFile.eof() || (event_1[i] >= NeventsToRead)) break;
            
            if (debug>1) {
                SHOW3(Ensemb[i],Index[i],Number[i]);
                SHOW2(ID[i],IQ[i]);
                SHOW2(Anti[i], mass[i]);
                SHOW4(E[i] ,Px[i], Py[i] , Pz[i]);
                SHOW3( X[i] , Y[i] , Z[i] );
            }
            
            // Ensemb| Index[   Number]: ID IQ Anti mass | momentum(0:3) | position(1:3) | ScaleCS firstEvent [event] perWeight, max(-9.9d0,formationTime), productionTime,lastCollisionTime, in_Formation, parents
            //     1|     1[   100000]:  1  0 F   0.938 |  9.0225371E-01  1.7851833E-01 -1.2221472E-02 -4.9129979E-02|  1.298E+00 -2.045E-01 -1.445E+00| 1.000         0[        1        1]   0.000E+00 time:    0.000    0.000    0.000 F parents:   0   0   0
            //        Printf("point %i: (%.3f , %.3f)",i,X[i],Y[i]);
            outcsvfile
            << Ensemb[i] << "," << Index[i] << "," << Number[i] << ","
            << ID[i] << "," << IQ[i] << ","
            << Anti[i] << "," << mass[i] << ","
            << E[i] << "," << Px[i] << "," << Py[i] << "," << Pz[i] << ","
            << X[i] << "," << Y[i] << "," << Z[i]
            << endl;
        }
    }
    
    else if (InFileType == "DoHIA_pert") {
        for (int i = 0; i < Nlines; i++){
            
            InFile
            >> particle_id
            >> charge
            >> tmp_i // column 3, unimportant
            >> parent1
            >> parent2
            >> Mass
            >> indFree
            >> P0
            >> P1
            >> P2
            >> P3
            >> Weight
            >> event
            >> tmp
            >> tmp;
            
            if (InFile.eof() || (event > NeventsToRead)) break;
            
            if (debug>1) {
                SHOW3(particle_id,charge,Mass);
                SHOW(indFree);
                SHOW2(parent1,parent2);
                SHOW4(P0,P1,P2,P3);
                SHOW(event);
            }
            //    1  1       -999    0    0   0.93800 0    0.89568    0.11848    0.00190    0.00190  0.000000E+00     1    1  0.00
            //    1  0     100031    1    1   0.93800 0    0.92888    0.04261    0.01178    0.10742  0.000000E+00     1    1  0.00

            outcsvfile
            << particle_id << "," << charge << ","
            << parent1 << "," << parent2 << ","
            << Mass << "," << indFree << ","
            << P0 << "," << P1 << "," << P2 << "," << P3 << ","
            << event
            << endl;
            
        }
    }
    InFile.close();
}


    
#endif
