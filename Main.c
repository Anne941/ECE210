//*****************************************************************************
// TITLE:			LAB 8
// 
// NAME:		    <Your Name Here>
// LAB SECTION:		<301, 302, 303, 304, 305, or 306>
// LAB DAY:			<Lab Day>
//
// CLASS:			ECE 210
// DATE: 			FALL 2014
// 
// DESCRIPTION:		<Insert a short description of what you are working on in 
//                   in this lab>
//*****************************************************************************
/* Initialization Functions */
void	LEDBARInit(void);
void 	DIPSWInit(void);
void	PBSwInit(void);	
void 	RGB_LEDInit(void);
void 	sysTickInit(void);
int rand(void);
/* Inputs, outputs, and wait timers */			
int 	read_PBSwitchNum(int SwitchNumber);
int		read_Switches(void);
void    LEDBAROutput(int value);
void 	turnOn(char color);
void 	turnOff(char color);
void  potentiometersInit(void);
int   readPotentiometer0(void);
int   readPotentiometer1(void);
int   readPotentiometer2(void);
void    sysTickWait1mS(int waitTime);
void	RIT128x96x4Init(int freq);
void    RIT128x96x4Clear(void); 
void    RIT128x96x4StringDraw(const char* letter, int xx, int yy, int intensity);
char* 	convert(int baudotCode);
//*****************************************************************************
//
// Main Program:
//
//*****************************************************************************
int
main(void)
{
	//Initializing the variables used in the lab.
	int turnItCodes[10];
	int correctcode[10];
	int pushItCodes[10];
	
	int ii;   					//for counter variable
	int xx;							//x axis string position
	int yy;							//y axis string position
	
	int turnIt;		//holds 'Turn It' message
	int correct;	// holds 'Correct' message
	int pushIt;	//  holds 'Push it" message
	
	// used to read current values
	int potenValue0 = 0;
	int pushButton1 = 1;
	
	int isInput = 0;
	int inputRequested = 0;
	int inputSelected = 0;
	int ATWCCW = 1; // 0 = false, 1 = true
	
								
	//Initializing the LEDBAR, RGB LED, DIPSwitches and Pushbuttons, and a wait timer
	LEDBARInit();
	DIPSWInit();
	PBSwInit();
	RGB_LEDInit();
	sysTickInit();
	potentiometersInit();
	RIT128x96x4Init(1000000);
	 
	/* Main Part of the Program starts here */
	
	// code for 'Turn It'
  turnItCodes[0] = 16;	// T
	turnItCodes[1] = 7;	// U
	turnItCodes[2] = 10;	// R
	turnItCodes[3] = 12;	// N
	turnItCodes[4] = 4;	// 
	turnItCodes[5] = 6;	// I
	turnItCodes[6] = 16;	// T
	
	// code for 'Correct'
	correctcode[0] = 14;	// C
	correctcode[1] = 24;	// O
	correctcode[2] = 10;	// R
	correctcode[3] = 10;	// R
	correctcode[4] = 1;	// E
	correctcode[5] = 14;	// C
	correctcode[6] = 16;	// T 
	
	// code for 'Push It'
	pushItCodes[0] = 22;	// P
	pushItCodes[1] = 7;	// U
	pushItCodes[2] = 5;	// S
	pushItCodes[3] = 20;	// H
	pushItCodes[4] = 4;	// 
	pushItCodes[5] = 6;	// I
	pushItCodes[6] = 16;	// T 	
	
	//Flash to say we are getting ready to go!
	turnOn('B');
	sysTickWait1mS(250);
	turnOff('B');

	//Clear messages on the screen
	RIT128x96x4Clear();
	
	//Start at the upper left hand corner of the screen!
	xx = 0;
	yy = 0;
	
  while(1){
		
		// Assign inputRequest - 1: button,  2: switch, 3: knob 
		int randomNum = rand() % 3;	// generates a number between 0-3
		
		if (randomNum <= 1)
		{
			inputRequested = 1;	// button
		}
		/*
		else if (1 < randomNum <= 2)
		{
			inputRequested = 2;	// switch
		} 
		*/
		else if (1 < randomNum <= 3)
		{
			inputRequested = 3;	// knob
		}
		
		if (inputRequested == 1)
		{
			//Display 'Push it'
			for(ii = 0; ii < 7;ii++)
			{
				pushIt = pushItCodes[ii];
				RIT128x96x4StringDraw(convert(pushIt), xx + 6*ii,yy,15);
			}
		} else if (inputRequested == 2)
		{
			
		} else if (inputRequested == 3)
		{
			//Display 'Turn it'
			for(ii = 0; ii < 7;ii++)
			{
				turnIt = turnItCodes[ii];
				RIT128x96x4StringDraw(convert(turnIt), xx + 6*ii,yy,15);
			}
		}
		
      
			while (isInput == 0)	// loop until an input is detected
			{

				// record values of inputs here
				potenValue0 = readPotentiometer0();				  // knob value
				pushButton1 = read_PBSwitchNum(1);		// push button
																								  	// switch

				// Did the knob change?
				if (ATWCCW == 1)
				{
					if (potenValue0 >= 500)
					{
						inputSelected = 3;
						ATWCCW = 0;
						isInput = 1;
					}
				}
				else	//ATWCW
				{
					if (potenValue0 <= 500)
					{
						isInput = 1;
						inputSelected = 3;
						ATWCCW = 1;
					}
				}
				
				//Did a switch change?
				
				//Was a button pushed?
				if (pushButton1 == 0)
				{
					inputSelected = 1;
					isInput = 1;
				}
				
			}//end while(no input)
			
			
			// Was the input correct?
			if (inputSelected == inputRequested)
			{
					//Flash to confirm correct input!
					turnOn('G');
					sysTickWait1mS(250);
					turnOff('G');
				
					// Display 'correct'
					//Letters are displayed left to right
					for(ii = 0; ii < 7;ii++)
					{
						correct = correctcode[ii];
						RIT128x96x4StringDraw(convert(correct), xx + 6*ii,yy,15);
					}
				sysTickWait1mS(1000);
			}
			else
			{
					//Flash to confirm incorrect input!
					turnOn('R');
					sysTickWait1mS(250);
					turnOff('R');
			}
					
			//RESET VALUES
			isInput = 0;
			inputSelected = 0;
		
			}//end while(1)
		
	}
	

/* The convert() function maps 5 bit Baudot codes to the output needed for 
   for the LCD Display */

char* convert(int baudotCode)
{
	switch(baudotCode)
	{
		case(1): return "E";
		case(3): return "A";
		case(4): return " ";
		case(5): return "S";
		case(6): return "I";
		case(7): return "U";
		case(9): return "D";
		case(10): return "R";
		case(11): return "J";
		case(12): return "N";		 
		case(13): return "F";					 	
		case(14): return "C";
		case(15): return "K";
		case(16): return "T";
		case(17): return "Z";
		case(18): return "L";
		case(19): return "W";
		case(20): return "H";			 					 
		case(21): return "Y";
		case(22): return "P";
		case(23): return "Q";
		case(24): return "O";
		case(25): return "B";
		case(26): return "G";
		case(28): return "M";
		case(29): return "X";
		case(31): return "V";
	}
	return " ";
}
