/*

###############################################################################
#                                                                             #
#            Ladder Operator Vibrational Configuration Interaction            #
#                              By: Eric G. Kratz                              #
#                                                                             #
###############################################################################

 Headers, libraries, and data structures for LOVCI

*/

//Make including safe
#ifndef VCI_HEADERS
#define VCI_HEADERS

//Header Files
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <complex>
#include <cmath>
#include <fstream>
#include <vector>
#include <map>
#include <sys/stat.h>
#include <algorithm>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/LU>
#include <Eigen/QR>
#include <Eigen/SVD>
#include <Eigen/Eigenvalues>
#include <Eigen/StdList>
#include <Eigen/Eigen>
#include <Eigen/StdVector>

//Set namespaces for common libraries
using namespace Eigen;
using namespace std;

//Global exact constants
const double pi = 4*atan(1); //Pi
const double rt2pi = sqrt(2*pi); //Needed for Gaussian broadening

//Global measured constants (NIST, CODATA 2010)
const double cs = 2.99792458e-10; //Speed of light (cm)
const double k = 0.69503476; //Boltzmann constant (cm^-1)

//Global derived constants
const double h = 2*pi; //Planck constant (cm^-1)

//Custom classes
class HOFunc
{
  //Class for harmonic oscillator basis functions
  public:
    double Freq; //Frequency
    int Quanta; //Number of quanta in the mode
    double ModeInt; //Intensity
};

class WaveFunction
{
  //Class for storing a VCI wavefunction
  public:
    int M; //Number of modes
    vector<HOFunc> Modes; //Functions
};

class FConst
{
  //Class for anharmonic force constants
  public:
    //Note: fc should include the permutation term
    double fc; //Value of the force constant
    vector<int> fcpow; //Modes and powers for the force constant
};

struct ProgramState {
  bool GauBroad; //Use Gaussian broadening instead of Lorentzian
  int Ncpus; //Number of CPUs for the calculations
  double LorentzWid; //Width of the peaks in the final spectrum
  double DeltaFreq; //Spectrum resolution
  double FreqCut; //Cutoff for the spectrum
  vector<WaveFunction> BasisSet; //Full basis set
  vector<HOFunc> SpectModes; //List of spectator modes
  vector<FConst> AnharmFC; //List of force constants
  int StartTime; //Time the calculation starts
  int EndTime; //Time the calculation ends
};

//Function declarations (alphabetical)
void AnharmHam(MatrixXd& H, const vector<WaveFunction> &BasisSet, const vector<FConst> &AnharmFC);

double AnharmPot(int n, int m, const FConst& fc, const vector<WaveFunction> &BasisSet);

void AnnihilationLO(double&,int&);

bool CheckFile(const string&);

void CreationLO(double&,int&);

double Fact(int);

int FindMaxThreads();

double GBroaden(double,double,double);

double LBroaden(double,double,double);

void PrintFancyTitle();

void PrintSpectrum(VectorXd& Freqs, MatrixXd& Psi, fstream& outfile, double LorentzWid, double FreqCut, int Ncpus, const vector<HOFunc> &SpectModes, bool GauBroad, const vector<WaveFunction> &BasisSet, double DeltaFreq);

void ReadCIArgs(int argc, char* argv[], fstream& vcidata, fstream& spectfile, ProgramState &ps);

void ReadCIInput(MatrixXd& VCIHam, fstream& vcidata, ProgramState &ps);

void ScaleFC(vector<FConst> &AnharmFC);

bool ScreenState(int n, int m, const FConst& fc, const vector<WaveFunction> &BasisSet);

void VCIDiagonalize(MatrixXd&,MatrixXd&,VectorXd&);

void ZerothHam(MatrixXd& H, const vector<WaveFunction> &BasisSet, const vector<HOFunc> &SpectModes);

#endif // VCI_HEADERS
