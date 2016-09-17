//HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//FUNCTION PROTOTYPES
void table(double (*pf)(double i, int m, double n), double a, int m, double n);
double md1(double i, int m, double n);
double md2(double i, int m, double n);
double md3(double i, int m, double n);


//VARIABLE DECLARATIONS
int m;			//NUMBER OF COMPOUNDING PERIODS PER YEAR
double n;		//NUMBER OF YEARS
double a;		//AMOUNT OF EACH MONTHLY PAYMENT
char freq;		//FREQUENCY OF COMPOUNDING INTEREST



main() 
{
	printf("FUTURE VALUE OF A SERIES OF MONTHLY DEPOSITS\n\n");

	//ACCEPT 'a' , 'n'
	printf("Please sit back and answer a few questions...\n\n");
	printf("Amount of each monthly payment: Rs. ");
	scanf("%lf", &a);
	
	printf("Number of years: ");
	scanf("%lf", &n);

	//ACCEPT FREQUENCY OF COMPOUNDING, REPEAT IF INCORRECT USING DO...WHILE()
	do 
	{
		printf("FREQUENCY OF COMPOUNDING INTEREST (A, S, Q, M, D, C): ");
		scanf("%1s", &freq);
		freq = toupper(freq);
		
		if (freq == 'A') {
			m = 1;
			printf("\nANNUAL COMPOUNDING SHIT\n");
		}	
		else if (freq == 'S') {
			m = 2;
			printf("\nSEMI-ANNUAL COMPOUNDING SHIT\n");
		}	
		else if (freq == 'Q') {
			m = 4;
			printf("\nQUARTERLY COMPOUNDING SHIT\n");
		}
		else if (freq == 'M') {
			m = 12;
			printf("\nMONTHLY COMPOUNDING SHIT\n");
		}
		else if (freq == 'D') {
			m = 360;
			printf("\nDAILY COMPOUNDING SHIT\n");
		}
		else if (freq == 'C') {
		//	m = 0;
			printf("\nCONTINUOUS COMPOUNDING SHIT\n");
		}
		else
			printf("\nERROR - PLEASE REPEAT THAT SHIT\n");

	} while (freq != 'A' && freq != 'S' && freq != 'Q' && 
			 freq != 'M' && freq != 'D' && freq != 'C');

		//CALCULATION SHIT
		if (freq == 'C')
			table(md3, a, m, n);		//CONTINUOUS COMPOUNDING SHITTY CALCULATIONS
		else if (freq == 'D')
			table(md2, a, m, n);		//DAILY COMPOUNDING SHITTY CALCULATIONS
		else
			table(md1, a, m, n);		//ANNUAL, SEMI-ANNUAL, QUATERLY, MONTHLY COMPOUNDING SHITTY CALCULATIONS
}



void table (double (*pf)(double i, int m, double n), double a, int m, double n)
//TABLE GENERATOR (THIS FUNCTION ACCEPTS A POINTER TO ANOTHER FUNCTION AS AN ARGUEMENT)
//i.e. double (*pf)(double i, int m, double n) is a POINTER TO FUNCTION md1, md2 or md3 DEPENDING UPON char freq
{
	int irate;
	double i;
	double f;
	
	printf("INTEREST RATE			FUTURE VALUE\n");
	
	for (irate = 1; irate <= 20; ++irate) 
	{
		i = 0.1 * irate;
		f = a * (*pf)(i, m, n);		//ACCESSES THE FUNCTION PASSED AS AN ARGUEMENT *pf (i, m, n)
		printf("%2d				%.2f\n", irate, f);
	}
	return;
}



double md1(double i, int a, double n)			//MONTHLY DEPOSITS, |A|S|Q|M| COMPOUNDING SHIT
{
	double factor, ratio;
	
	factor = 1 + i/m;
	ratio = 12 * (pow (factor, m*n) - 1) / i;
	return(ratio);
}



double md2(double i, int a, double n)			//MONTHLY DEPOSITS, DAILY COMPOUNDING SHIT
{
	double factor, ratio;
	
	factor = 1 + i/m;
	ratio = (pow (factor, m*n) - 1) / (pow (factor, m/12) - 1);
	return(ratio);
}



double md3(double i, int dummy, double n)		//MONTHLY DEPOSITS, CONTINUOUS COMPOUNDING SHIT
{
	double ratio;
	
	ratio = (exp(i*n) - 1) / (exp (i/12) - 1);
	return(ratio);
}
