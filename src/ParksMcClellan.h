//---------------------------------------------------------------------------

/*

From: http://www.iowahills.com/A7ExampleCodePage.html

The starting point for this file was the file from Wikipedia (at the very bottom of the article).
I checked my work against the scipy files on github .

http://en.wikipedia.org/wiki/Parks%E2%80%93McClellan_filter_design_algorithm
https://github.com/scipy/scipy/blob/master/scipy/signal/sigtoolsmodule.c

There were a few places where I eliminated some intermediate variables,
but I tried to keep the changes to a minimum. You should be able to
print out this file and the original from Wikipedia and do a side by side
comparison without much trouble.

Apparently, Fortran doesn't use global variables. Instead, they use something called
common memory space. e.g. COMMON PI2,AD,DEV,X,Y,GRID,DES,WT,ALPHA,IEXT,NFCNS,NGRID
I simply converted these to globals. It isn't pretty, but for this purpose, who cares?

The original Fortran code had 69 goto statements. This code has 56.
If you study this code a bit, you will learn very quickly why today, using
these statements is considered bad form. I am not sure they had much choice in 1972.

There are three noteworthy differences between this code and the SciPy code.
Search on SciPy in this file to find the difference comments.

You should also note that this code doesn't do much error checking. For example,
there are places where division by zero can and does occur for certain input
values.

This code is essentially straight c, and should compile without many changes.
I was using the array FirCoeff[] from my top level app to store the
coefficients. You will need to declare your own array. Also, this code uses ShowMessage()
which is part of Embarcadero's C++ Builder vcl.
*/


#ifndef ParksMcClellan2H
#define ParksMcClellan2H

void InitParksMcClellan(void);
void ParksMcClellan2(void);
double  EFF(double FREQ, double *FX, double *WTX, int LBAND, int JTYPE);
double WATE(double FREQ, double *FX, double *WTX, int LBAND, int JTYPE);
double D(int K, int N, int M);
double GEE(int K, int N);
void Remez(void);
void Ouch(int Count);


//#include "Main.h"  // defines FirCoeff[]
#include <math.h>
//#include <new.h>   // defines new
//#include <vcl.h>   // defines ShowMessage() used in InitParksMcClellan() and Ouch()
#define BIG 4096   // Used to define array sizes.
#define SMALL 256
#define M_2PI  6.28318530717958647692

int NFCNS, NGRID, *IEXT;
double DEV, *AD, *ALPHA, *X, *Y, *H, *EDGE, *FX, *WTX, *DES, *GRID, *WT;
bool InitDone = false;

void InitParksMcClellan(void)
{
 InitDone = true;

 // Using nothrow prevents an exception from being thrown. new will instead return NULL.
 // To free memory, use delete, not free. e.g. delete[] IEXT;
 // These array sizes are much larger than actually needed. See PARKS.FOR
 IEXT  = new int[SMALL];
 if(IEXT == NULL)InitDone = false;

 AD  = new double[SMALL];
 if(AD == NULL)InitDone = false;

 ALPHA    = new double[SMALL];
 if(ALPHA == NULL)InitDone = false;

 X  = new double[SMALL];
 if(X == NULL)InitDone = false;

 Y  = new double[SMALL];
 if(Y == NULL)InitDone = false;

 H  = new double[SMALL];
 if(H == NULL)InitDone = false;

 EDGE  = new double[SMALL];
 if(EDGE == NULL)InitDone = false;

 FX    = new double[SMALL];
 if(FX == NULL)InitDone = false;

 WTX  = new double[SMALL];
 if(WTX == NULL)InitDone = false;

 DES    = new double[BIG];
 if(DES == NULL)InitDone = false;

 GRID  = new double[BIG];
 if(GRID == NULL)InitDone = false;

 WT  = new double[BIG];
 if(WT == NULL)InitDone = false;

 if(!InitDone)printf("Memory not Allocated in InitParksMcClellan\n");

}


/* Input Values
  NFILT   FILTER LENGTH
  JTYPE   TYPE OF FILTER 1 = MULTIPLE PASSBAND/STOPBAND FILTER 2 = DIFFERENTIATOR 3 = HILBERT TRANSFORM FILTER
  NBANDS  NUMBER OF BANDS
  LGRID   GRID DENSITY, WILL BE SET TO 16 UNLESS SPECIFIED OTHERWISE BY A POSITIVE CONSTANT.
  EDGE[2*NBANDS] BANDEDGE ARRAY, LOWER AND UPPER EDGES FOR EACH BAND WITH A MAXIMUM OF 10 BANDS.
  FX[NBANDS]     DESIRED FUNCTION ARRAY (OR DESIRED SLOPE IF A DIFFERENTIATOR) FOR EACH BAND.
  WTX[NBANDS]    WEIGHT FUNCTION ARRAY IN EACH BAND.  FOR A DIFFERENTIATOR, THE WEIGHT FUNCTION IS INVERSELY PROPORTIONAL TO F.
*/
//---------------------------------------------------------------------------

void ParksMcClellan2(double *FirCoeff)
{
 if(!InitDone)
  {
   InitParksMcClellan();
   if(!InitDone)return;
  }

 int J, L, JTYPE, NBANDS, NFILT, LGRID, NEG, NODD, LBAND;
 int NM1, NZ;
 double DELF, FUP, TEMP, CHANGE, XT;

 // This example input will generate a 48 tap band pass filter.
 /*
 JTYPE = 1;   // 1 = MULTIPLE PASSBAND/STOPBAND FILTER 2 = DIFFERENTIATOR 3 = HILBERT TRANSFORM FILTER
 NBANDS = 3;  // Number of Bands
 NFILT = 48;  // Num Taps;
 LGRID = 16;  // Grid Density
 EDGE[1] = 0.0;
 EDGE[2] = 0.1;
 EDGE[3] = 0.2;
 EDGE[4] = 0.35;
 EDGE[5] = 0.425;
 EDGE[6] = 0.5;
 FX[1]   = 0.0;
 FX[2]   = 1.0;
 FX[3]   = 0.0;
 WTX[1] = 10.0;
 WTX[2] = 1.0;
 WTX[3] = 10.0;*/


  // This example input will generate a 32 tap low pass filter.
 JTYPE = 1;   // 1 = MULTIPLE PASSBAND/STOPBAND FILTER 2 = DIFFERENTIATOR 3 = HILBERT TRANSFORM FILTER
 NBANDS = 2;  // Number of Bands
 NFILT = 63;  // Num Taps;
 LGRID = 16;  // Grid Density
 EDGE[1] = 0.0;
 EDGE[2] = 0.2;
 EDGE[3] = 0.25;
 EDGE[4] = 0.5;
 FX[1]   = 1.0;
 FX[2]   = 0.0;
 WTX[1] = 1.0;
 //WTX[2] = 10.0;
 WTX[2] = 1.0;



 if(JTYPE == 1) NEG = 0;   // Lowpass, Bandpass, Highpass, and Notch
 else NEG = 1;             // Hilberts and Differentiators
 NODD = NFILT % 2;
 NFCNS = NFILT/2;
 if(NODD == 1 && NEG == 0) NFCNS = NFCNS + 1;

// From here on down, the code is essentially a simple Fortran to C conversion.
//  SET UP THE DENSE GRID.  THE NUMBER OF POINTS IN THE GRID IS (FILTER LENGTH + 1)*GRID DENSITY/2

	  GRID[1] = EDGE[1];
	  DELF = LGRID * NFCNS;
	  DELF = 0.5 / DELF;
	  if(NEG == 0) goto L135;
	  if(EDGE[1] < DELF) GRID[1] = DELF;
L135: J = 1;
	  L = 1;
	  LBAND = 1;
L140: FUP = EDGE[L+1];
L145: TEMP = GRID[J];

// CALCULATE THE DESIRED MAGNITUDE RESPONSE AND THE WEIGHT FUNCTION ON THE GRID

	  DES[J] = EFF(TEMP,FX,WTX,LBAND,JTYPE);
	  WT[J] = WATE(TEMP,FX,WTX,LBAND,JTYPE);
	  J=J+1;
	  GRID[J] = TEMP + DELF;
	  if(GRID[J] > FUP) goto L150;
	  goto L145;
L150: GRID[J-1] = FUP;
	  DES[J-1] = EFF(FUP,FX,WTX,LBAND,JTYPE);
	  WT[J-1] = WATE(FUP,FX,WTX,LBAND,JTYPE);
	  LBAND = LBAND + 1;
	  L = L + 2;
	  if(LBAND > NBANDS) goto L160;
	  GRID[J] = EDGE[L];
	  goto L140;
L160: NGRID = J-1;
	  if(NEG != NODD) goto L165;
	  if(GRID[NGRID] > (0.5-DELF)) NGRID = NGRID-1;


//SET UP A NEW APPROXIMATION PROBLEM WHICH IS EQUIVALENT TO THE ORIGINAL PROBLEM

L165: if(NEG <= 0)
	   {
		if(NODD == 1) goto L200;
		for(J=1; J<=NGRID; J++)
		 {
		  CHANGE = cos(M_PI * GRID[J] );
		  DES[J] = DES[J] / CHANGE;
		  WT[J] = WT[J] * CHANGE;
		 }
		goto L200;
	   }
	  if(NODD == 1) goto L190;
	  for(J=1; J<=NGRID; J++)
	   {
		CHANGE = sin(M_PI * GRID[J]);
		DES[J] = DES[J] / CHANGE;
		WT[J] = WT[J] * CHANGE;
	   }
	  goto L200;
L190: for(J=1; J<=NGRID; J++)
	   {
		CHANGE = sin( M_2PI * GRID[J] );
		DES[J] = DES[J] / CHANGE;
		WT[J] = WT[J] * CHANGE;
	   }

// INITIAL GUESS FOR THE EXTREMAL FREQUENCIES--EQUALLY SPACED ALONG THE GRID

L200: TEMP = (double)(NGRID-1)/(double)NFCNS;
	  for(J=1; J<=NFCNS; J++)
	   {
		XT = J-1;
		IEXT[J] = XT * TEMP + 1.0;
	   }
	  IEXT[NFCNS+1] = NGRID;
	  NM1 = NFCNS-1;
	  NZ = NFCNS+1;

	  // CALL THE REMEZ EXCHANGE ALGORITHM TO DO THE APPROXIMATION PROBLEM
	  Remez();

	  // CALCULATE THE IMPULSE RESPONSE.
	  if(NEG > 0)goto L320;  // NEG = 1 for Hilberts and Differentiators

	  if(NODD == 0) goto L310;
	  for(J=1; J<=NM1; J++) // NEG=0 and NODD=0 for bandpass even length filter nfcns=nfilt/2
	   {
		H[J] = 0.5 * ALPHA[NZ-J];
	   }
	  H[NFCNS] = ALPHA[1];
	  goto L350;

L310: H[1] = 0.25 * ALPHA[NFCNS]; // NEG=0 and NODD=1 for bandpass odd length filter nfcns=nfilt/2 + 1
	  for(J=2; J<=NM1; J++)
	   {
		H[J] = 0.25 * (ALPHA[NZ-J] + ALPHA[NFCNS+2-J]);
	   }
	  H[NFCNS] = 0.5 * ALPHA[1] + 0.25 * ALPHA[2];
	  goto L350;


L320: if(NODD == 0) goto L330;  // NEG=1 and NODD=0 for even length Hilberts and Differentiators
	  H[1] = 0.25 * ALPHA[NFCNS];
	  H[2] = 0.25 * ALPHA[NM1];
	  for(J=3; J<=NM1; J++)
	   {
		H[J] = 0.25 * (ALPHA[NZ-J] - ALPHA[NFCNS+3-J] );
	   }
	  H[NFCNS] = 0.5 * ALPHA[1] - 0.25 * ALPHA[3];
	  H[NZ] =0.0;
	  goto L350;
L330: H[1] = 0.25 * ALPHA[NFCNS]; // NEG=1 and NODD=1 for odd length Hilberts and Differentiators
	  for(J=2; J<=NM1; J++)
	   {
		H[J] = 0.25 * (ALPHA[NZ-J] - ALPHA[NFCNS+2-J] );
	   }
	  H[NFCNS] = 0.5 * ALPHA[1] - 0.25 * ALPHA[2];




L350: // Output section. Code for the Hilberts and Differentiators was omitted.
      // Note that the Fortran arrays started at 1, but my FirCoeff array starts at 0.
	  // Write the first half of the response
	  for(J=1; J<=NFCNS; J++)
	   {
		FirCoeff[J-1] = H[J];
	   }
	  // NEG=0 and NODD=0 for bandpass even length filter nfcns=nfilt/2
	  if(NEG == 0 && NODD == 0)
	  for(J=1; J<=NFCNS; J++)
	   {
		FirCoeff[NFCNS+J-1] = H[NFCNS-J+1];
	   }
	  // NEG=0 and NODD=1 for bandpass odd length filter nfcns=nfilt/2 + 1
	  if(NEG == 0 && NODD == 1)
	  for(J=1; J<NFCNS; J++)
	   {
		FirCoeff[NFCNS+J-1] = H[NFCNS-J];
	   }

}

/*
FUNCTION TO CALCULATE THE DESIRED MAGNITUDE RESPONSE AS A FUNCTION OF FREQUENCY. AN ARBITRARY
FUNCTION OF FREQUENCY CAN BE APPROXIMATED if THE USER REPLACES THIS FUNCTION WITH THE
APPROPRIATE CODE TO EVALUATE THE IDEAL MAGNITUDE.  NOTE THAT THE PARAMETER FREQ IS THE
VALUE OF NORMALIZED FREQUENCY NEEDED FOR EVALUATION.
*/


double EFF(double FREQ, double *FX, double *WTX, int LBAND, int JTYPE)
{
 if(JTYPE == 2)  return( FX[LBAND] * FREQ );
 else return( FX[LBAND] );
}


//FUNCTION TO CALCULATE THE WEIGHT FUNCTION AS A FUNCTION OF FREQUENCY.  SIMILAR TO THE FUNCTION
//EFF, THIS FUNCTION CAN BE REPLACED BY A USER-WRITTEN ROUTINE TO CALCULATE ANY DESIRED WEIGHTING FUNCTION.

double WATE(double FREQ, double *FX, double *WTX, int LBAND, int JTYPE)
{
 if(JTYPE == 1 || JTYPE == 3) return(WTX[LBAND]); // JTYPE=1 Bandpass JTYPE=3 for Hilberts
 if(FX[LBAND] < 0.0001) return(WTX[LBAND]);       // JTYPE=2 for Differentiators
 return(WTX[LBAND] / FREQ);
}


/*
THIS SUBROUTINE IMPLEMENTS THE REMEZ EXCHANGE ALGORITHM FOR THE WEIGHTED CHEBYSHEV
APPROXIMATION OF A CONTINUOUS FUNCTION WITH A SUM OF COSINES.  INPUTS TO THE SUBROUTINE
ARE A DENSE GRID WHICH REPLACES THE FREQUENCY AXIS, THE DESIRED FUNCTION ON THIS GRID,
THE WEIGHT FUNCTION ON THE GRID, THE NUMBER OF COSINES, AND AN INITIAL GUESS OF THE EXTREMAL
FREQUENCIES. THE PROGRAM MINIMIZES THE CHEBYSHEV ERROR BY DETERMINING THE BEST LOCATION OF
THE EXTREMAL FREQUENCIES (POINTS OF MAXIMUM ERROR) AND THEN CALCULATES THE COEFFICIENTS OF
THE BEST APPROXIMATION.
*/

void Remez(void)
{
 int J, ITRMAX, NZ, NZZ, JET, K, L, NU, JCHNGE, K1, KNZ, KLOW, NUT, KUP;
 int NUT1, LUCK, KN, NM1, KKK, JM1, JP1, NITER;
 double A[SMALL], P[SMALL], Q[SMALL];
 double DNUM, DDEN, DTEMP, FT, XT, XT1, XE;
 double FSH, GTEMP, CN, DELF, AA, BB;  // SciPy declares CN as an int, which is probably inconsequential the way CN is used.
 double DEVL, COMP, YNZ, Y1, ERR;


	  ITRMAX = 40;      // MAXIMUM NUMBER OF ITERATIONS This was 25. It was changed by Parks in a later file.
	  DEVL = -1.0;
	  NZ = NFCNS + 1;
	  NZZ = NFCNS + 2;
	  NITER = 0;
L100: IEXT[NZZ] = NGRID + 1;
	  NITER = NITER + 1;
	  if(NITER > ITRMAX) goto L400; // L400 is where the coeff calc starts
	  for(J=1; J<=NZ; J++)
	   {
		DTEMP = GRID[ IEXT[J] ];
		X[J] = cos(DTEMP * M_2PI);
	   }

	  JET = (NFCNS-1)/15 + 1;
	  for(J=1; J<=NZ; J++)
	   {
		AD[J] = D(J,NZ,JET);
	   }

	  DNUM = 0.0;
	  DDEN = 0.0;
	  K = 1;
	  for(J=1; J<=NZ; J++)
	   {
		L = IEXT[J];
		DNUM += AD[J] * DES[L];
		DDEN += (double)K * AD[J]/WT[L];
		K = -K;
	   }
	  DEV = DNUM / DDEN;

//      WRITE(IOUT,131) DEV
//  131 FORMAT(1X,12HDEVIATION = ,F12.9)

	  NU = 1;
	  if(DEV > 0.0) NU = -1;
	  DEV = -(double)NU * DEV;
	  K = NU;
	  for(J=1; J<=NZ; J++)
	   {
		L = IEXT[J];
		DTEMP = (double)K * DEV/WT[L];
		Y[J] = DES[L] + DTEMP;
		K = -K;
	   }
	  if(DEV <= DEVL)
	   {
		Ouch(NITER);
		goto L400;
	   }
	  DEVL = DEV;
	  JCHNGE = 0;
	  K1 = IEXT[1];
	  KNZ = IEXT[NZ];
	  KLOW = 0;
	  NUT = -NU;
	  J = 1;

//SEARCH FOR THE EXTREMAL FREQUENCIES OF THE BEST APPROXIMATION

L200: if(J == NZZ) YNZ = COMP;
	  if(J >= NZZ) goto L300;
	  KUP = IEXT[J+1];
	  L = IEXT[J] + 1;
	  NUT = -NUT;
	  if(J == 2) Y1 = COMP;
	  COMP = DEV;
	  if(L >= KUP) goto L220;
	  ERR = GEE(L,NZ);
	  ERR = (ERR - DES[L]) * WT[L];
	  DTEMP = (double)NUT * ERR - COMP;
	  if(DTEMP <= 0.0) goto L220;
	  COMP = (double)NUT * ERR;
L210: L = L + 1;
	  if(L >= KUP) goto L215;
	  ERR = GEE(L,NZ);
	  ERR = (ERR - DES[L]) * WT[L];
	  DTEMP = (double)NUT * ERR - COMP;
	  if(DTEMP <= 0.0) goto L215;
	  COMP = (double)NUT * ERR;
	  goto L210;
L215: IEXT[J] = L-1;
	  J = J + 1;
	  KLOW = L - 1;
	  JCHNGE = JCHNGE+1;
	  goto L200;
L220: L = L - 1;
L225: L = L - 1;
	  if(L <= KLOW) goto L250;
	  ERR = GEE(L,NZ);
	  ERR = (ERR - DES[L]) * WT[L];
	  DTEMP = (double)NUT * ERR - COMP;
	  if(DTEMP > 0.0) goto L230;
	  if(JCHNGE <= 0) goto L225;
	  goto L260;
L230: COMP = (double)NUT * ERR;
L235: L = L - 1;
	  if(L <= KLOW) goto L240;
	  ERR = GEE(L,NZ);
	  ERR = (ERR - DES[L]) * WT[L];
	  DTEMP = (double)NUT * ERR - COMP;
	  if(DTEMP <= 0.0) goto L240;
	  COMP = (double)NUT * ERR;
	  goto L235;
L240: KLOW = IEXT[J];
	  IEXT[J] = L + 1;
	  J = J + 1;
	  JCHNGE = JCHNGE + 1;
	  goto L200;
L250: L = IEXT[J] + 1;
	  if(JCHNGE > 0) goto L215;
L255: L = L + 1;
	  if(L >= KUP) goto L260;
	  ERR = GEE(L,NZ);
	  ERR = ( ERR - DES[L] ) * WT[L];
	  DTEMP = (double)NUT * ERR - COMP;
	  if(DTEMP <= 0.0) goto L255;
	  COMP = (double)NUT * ERR;
	  goto L210;
L260: KLOW = IEXT[J];
	  J = J + 1;
	  goto L200;

L300: if(J > NZZ) goto L320;
	  if(K1 > IEXT[1]) K1 = IEXT[1];
	  if(KNZ < IEXT[NZ]) KNZ = IEXT[NZ];
	  NUT1 = NUT;
	  NUT = -NU;
	  L = 0 ;
	  KUP = K1;
	  COMP = YNZ * (1.00001);
	  LUCK = 1;
L310: L = L + 1;
	  if(L >= KUP) goto L315;
	  ERR = GEE(L,NZ);
	  ERR = (ERR - DES[L]) * WT[L];
	  DTEMP = (double)NUT * ERR - COMP;
	  if(DTEMP <= 0.0) goto L310;
	  COMP = (double)NUT * ERR;
	  J = NZZ;
	  goto L210;
L315: LUCK = 6;
	  goto L325;
L320: if(LUCK > 9) goto L350;
	  if(COMP > Y1) Y1 = COMP;
	  K1 = IEXT[NZZ];
L325: L = NGRID + 1;
	  KLOW = KNZ;
	  NUT = -NUT1;
	  COMP = Y1 * 1.00001;
L330: L = L-1;
	  if(L <= KLOW) goto L340;
	  ERR = GEE(L,NZ);
	  ERR = (ERR - DES[L]) * WT[L];
	  DTEMP = (double)NUT * ERR - COMP;
	  if(DTEMP <= 0.0) goto L330;
	  J = NZZ;
	  COMP = (double)NUT * ERR;
	  LUCK = LUCK + 10;
	  goto L235;
L340: if(LUCK == 6) goto L370;
	  for(J=1; J<=NFCNS; J++)
	   {
		IEXT[NZZ - J] = IEXT[NZ - J];
	   }
	  IEXT[1] = K1;
	  goto L100;
L350: KN = IEXT[NZZ];
	  for(J=1; J<=NFCNS; J++)
	   {
		IEXT[J] = IEXT[J+1];
	   }
	  IEXT[NZ] = KN;
	  goto L100;
L370: if(JCHNGE > 0) goto L100;

//CALCULATION OF THE COEFFICIENTS OF THE BEST APPROXIMATION USING THE INVERSE DISCRETE FOURIER TRANSFORM

L400: NM1 = NFCNS - 1;
	  FSH = 1.0E-06;
	  GTEMP = GRID[1];
	  X[NZZ] = -2.0;
	  CN = 2 * NFCNS - 1;
	  DELF = 1.0/CN;
	  L = 1;
	  KKK = 0;

	  // Different than the SciPy code. You may find that that this condition always tests the same way.
	  if(GRID[1] < 0.01 && GRID[NGRID] > 0.49) KKK = 1;
	  // if (edge[1] == 0.0 && edge[2*nbands] == 0.5) kkk = 1;  // the SciPy code

	  if(NFCNS <= 3) KKK = 1;
	  if(KKK == 1) goto L405;
	  DTEMP = cos(M_2PI * GRID[1]);
	  DNUM = cos(M_2PI * GRID[NGRID] );
	  AA = 2.0/(DTEMP-DNUM);
	  BB = -(DTEMP+DNUM)/(DTEMP-DNUM);
L405: for(J=1; J<=NFCNS; J++)
	   {
		FT = J-1;
		FT = FT * DELF;
		XT = cos(M_2PI * FT);
		if(KKK == 1) goto L410;
		XT = (XT-BB)/AA;
		XT1 = sqrt(1.0 - XT*XT);
		FT = atan2(XT1,XT)/M_2PI;   // Different than the SciPy code
		// ft = acos(xt)/TWOPI;     // the SciPy code which was embedded in a #if .. #endif  It appears to be debug that wasn't removed.
L410:   XE = X[L];
		if(XT > XE) goto L420;
		if((XE-XT) < FSH) goto L415;
		L = L + 1;
		goto L410;
L415:   A[J] = Y[L];
		goto L425;
L420:   if((XT-XE) < FSH) goto L415;
		GRID[1] = FT;
		A[J] = GEE(1,NZ);
L425:   if(L > 1) L = L-1;
	   }
	  GRID[1] = GTEMP;
	  DDEN = M_2PI / CN;
	  for(J=1; J<=NFCNS; J++)
	   {
		DTEMP = 0.0;
		DNUM = (double)(J-1) * DDEN;
		//if(NM1 >= 1) This orig piece of code is redundant.
		for(K=1; K<=NM1; K++)
		 {
		  DTEMP += A[K+1] * cos(DNUM * (double)K);
		 }
		DTEMP = 2.0 * DTEMP + A[1];
		ALPHA[J] = DTEMP;
	   }

	  for(J=2; J<=NFCNS; J++)
	   {
		ALPHA[J] = 2.0 * ALPHA[J]/CN;
	   }
	  ALPHA[1] = ALPHA[1]/CN;
	  if(KKK == 1) goto L545;
	  P[1] = 2.0 * ALPHA[NFCNS]*BB + ALPHA[NM1];
	  P[2] = 2.0 * AA * ALPHA[NFCNS];
	  Q[1] = ALPHA[NFCNS-2] - ALPHA[NFCNS];
	  for(J=2; J<=NM1; J++)
	   {
		if(J < NM1) goto L515;
		AA = 0.5 * AA;
		BB = 0.5 * BB;
L515:   P[J+1] = 0.0;
		for(K=1; K<=J; K++)
		 {
		  A[K] = P[K];
		  P[K] = 2.0 * BB * A[K];
		 }
		P[2] += A[1] * 2.0 * AA;
		JM1 = J-1;
		for(K=1; K<=JM1; K++)
		 {
		  P[K] += Q[K] + AA * A[K+1];
		 }
		JP1 = J + 1;
		for(K=3; K<=JP1; K++)
		 {
		  P[K] += AA * A[K-1];
		 }
		if(J == NM1) goto L540;
		for(K=1; K<=J; K++)
		 {
		  Q[K] = -A[K];
		 }
		Q[1] += ALPHA[NFCNS-1-J];
	  }
L540: for(J=1; J<=NFCNS; J++)
	   {
		ALPHA[J] = P[J];
	   }
L545: if(NFCNS <= 3)
	   {
		ALPHA[NFCNS+1] = 0.0;
		ALPHA[NFCNS+2] = 0.0;
	   }
}

//-----------------------------------------------------------------------
// FUNCTION TO CALCULATE THE LAGRANGE INTERPOLATION COEFFICIENTS FOR USE IN THE FUNCTION GEE.
double D(int K, int N, int M)
{
 int J, L;
 double Dee, Q;
 Dee = 1.0;
 Q = X[K];
 for(L=1; L<=M; L++)
 for(J=L; J<=N; J+=M)
  {
   if(J != K)Dee = 2.0 * Dee * (Q - X[J]);
  }
 return(1.0/Dee); // Dee can and will go to zero.
}

//-----------------------------------------------------------------------
// FUNCTION TO EVALUATE THE FREQUENCY RESPONSE USING THE LAGRANGE INTERPOLATION FORMULA
// IN THE BARYCENTRIC FORM
double GEE(int K, int N)
{
 int j;
 double P,C,D,XF;
 P = 0.0;
 XF = GRID[K];
 XF = cos(M_2PI * XF);
 D = 0.0;
 for(j=1; j<=N; j++)
  {
   C = XF - X[j];
   C = AD[j] / C;   // C can and will go to zero.
   D = D + C;
   P = P + C*Y[j];
  }
 return(P/D);  // D can and will go to zero.
}

/*
Note:
In the 3 places noted above regarding divide by zero.
Using code similar to this helps this algorithm converge.

 #define MIN_TEST_VAL 1.0E-6
 if(fabs(C) < MIN_TEST_VAL )
  {
   if(C < 0.0)C = -MIN_TEST_VAL;
   else       C =  MIN_TEST_VAL;
  }
*/

//-----------------------------------------------------------------------
/*
WRITES AN ERROR MESSAGE WHEN THE ALGORITHM FAILS TO CONVERGE. THERE SEEM TO BE TWO CONDITIONS
UNDER WHICH THE ALGORITHM FAILS TO CONVERGE: (1) THE INITIAL GUESS FOR THE EXTREMAL FREQUENCIES
IS SO POOR THAT THE EXCHANGE ITERATION CANNOT GET STARTED, OR (2) NEAR THE TERMINATION OF A
CORRECT DESIGN, THE DEVIATION DECREASES DUE TO ROUNDING ERRORS AND THE PROGRAM STOPS. IN THIS LATTER
CASE THE FILTER DESIGN IS PROBABLY ACCEPTABLE, BUT SHOULD BE CHECKED BY COMPUTING A FREQUENCY RESPONSE.
*/

void Ouch(int Count)
{/*
  UnicodeString US;
  US =  "Failure to Coverge. \n";
  US += "The probable cause is rounding errors. \n";
  US += "Number of iterations = " + UnicodeString(Count) + "\n";
  US += "If the number of iterations exceeds 3, \n";
  US += "the design may be correct, but should be verified.";
  ShowMessage(US);*/
  printf("Failed to converge\n");
}

#endif
