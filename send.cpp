#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <bitset>
#include "RCSwitch.h"

//using std::string;
using namespace std;

/*
Errorcodes:
0.) Anzeigen der Hilfe, wie die Eingabe richtig auszusehen habe.
1.) Ung�ltige Anzahl an Parametern. Zahl der Parameter ist ungerade.
2.) Ung�ltige Eingabe. Der Housecode muss mind. 1 Zeichen lang sein und darf nicht l�nger als 5 Zeichen lang sein.
3.) Ung�ltige Eingabe. Der Housecode ist keine Bin�rzahl.
4.) Ung�ltige Eingabe. Der Schaltparameter am Ende darf nur 0 oder 1 sein.
*/

int main(int argc, char** argv)
{
	//Check variable for the number of parameters in the input.
	int intUngueltigeEingabe = argc % 2;

	//Checking if there is an invalid input. In case of that the number of parameters is uneven, the process will be terminated
	if (intUngueltigeEingabe != 0)
	{
		cout << "1 Falsche Eingabe";
		return 1;
	}
	//Checking if the user wants to display the help, if yes, there will be a text shown, which explains how the function call should look like.
	else if (argv[0] == "Send" && argv[1] == "-h")
	{
		cout << "0 Die richtige Eingabe erfolgt durch: Send {Housecode Devicecode HC DC usw} {Parameter Ob Ein- bzw Ausgeschaltet werden soll 1 = Ein 0 = Aus} Bsp: Send 001 2 0";
		return 1;
	}


	else
	{
		//Initialization of required variables
		int intAnzahlDerZuSchaltendenAktoren = (argc - 2) / 2;
		bool boolEingabeIstEineBinaerZahl = true;

		//Loop for checking input errors. The range of validity for the housecodes and devicecodes is between 1 and 31.
		for (int i = 1; i < argc - 1; i+=2)
		{
			//Checking if the input is longer than five numbers or an empty input occured 
			int intLaengeDerEingabe = strlen(argv[i]);

			if (intLaengeDerEingabe == 0 || intLaengeDerEingabe >5)
				cout << "2 Ungueltige Eingabe. Der Housecode ist entweder 0 Zeichen lang oder l�nger als 5 Zeichen.";
			else
			{
				//Checking if the input is composed of the numbers 1 and 0. If the input contains other numbers or characters the process will be terminated
				string strUeberpruefen = argv[i];
				unsigned int intAbbruchBedingungForSchleife = strUeberpruefen.length();
				
				for (int x = 0; x < intAbbruchBedingungForSchleife; x++)
				{
					if (strUeberpruefen[x] != '0' & strUeberpruefen[x] != '1')
					{
						cout << "3 Eingabe ist keine Binärzahl.";
						boolEingabeIstEineBinaerZahl = false;
						return 1;
					}
				}
			}
		}

		//Checking if the last number is an 1 or 0. If not the process will be terminated
		bool boolSchalten;
		bool boolEingabeGueltig = true;
		
		int command = atoi(argv[argc-1]);
		if (command == 1)
			boolSchalten = true;
		else if ( command  == 0)
		{
			boolSchalten = false;
		}
		else
		{
			cout << "4 Ungueltige Eingabe des Schaltparameters.";
			return 1;
		}

		//If input is binary and the last parameter valid, the initialization of RCSwitch and other steps will be initiated
		if (boolEingabeIstEineBinaerZahl & boolEingabeGueltig & wiringPiSetup() != -1)
		{
			piHiPri(20);
			RCSwitch switchPI;

			switchPI.setPulseLength(300);
			switchPI.enableTransmit(0);

			//Switching the actuators. If the last number is an 1 they will switched on, else off
			if (boolSchalten)
			{
				int x = 1; //Required variable to find the right positions of the argv[] array

				//Loop for turn on the actuators with the corresponding house- and devicecode
				for (int i = 0; i < intAnzahlDerZuSchaltendenAktoren; i++)
				{
					switchPI.switchOnBinary(argv[x], atoi(argv[x + 1]));
					x += 2;
				}
			}
			else
			{
				int x = 1; //Required variable to find the right positions of the argv[] array

				//Loop for turn off the actuators with the corresponding house- and devicecode
				for (int i = 0; i < intAnzahlDerZuSchaltendenAktoren; i++)
				{
					switchPI.switchOffBinary(argv[x], atoi(argv[x + 1]));
					x += 2;
				}
			}
		}
	}
return 0;
}

