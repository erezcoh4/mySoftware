#ifndef READDATFILE_CXX
#define READDATFILE_CXX

#include "ReadDatFile.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
ReadDatFile::ReadDatFile( std::string fInFileName
                   , std::string fOutFileName):
InFileName(fInFileName),
OutFileName(fOutFileName)
{
    Print();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ReadDatFile::Print() const{
    std::cout
    << "InFileName: " << InFileName << ", "
    << "OutFileName: " << OutFileName
    << std::endl;
}


#endif
