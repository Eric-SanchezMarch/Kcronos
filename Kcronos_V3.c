#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
HANDLE wHnd;

int temporitzador(char a);
void cronometro(char a, int thora, int tminuts,int tsegons);
void alarma(char a);
void accio(char a);

int main (){

	SetConsoleTitle("Kcronos V3.0");
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize = {0, 0, 30, 15};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    
	char a,i;
	system("color 0A");	
	system("cls");
	printf("##############################\n");
	printf("#        Kcronos V3.0        #\n");
	printf("##############################\n");
	printf("#    SELECT MODE:            #\n");
	printf("#                            #\n");
	printf("#    [1] PowerOff            #\n");
	printf("#    [2] Restart PC          #\n");
	printf("#    [3] Close Session       #\n");	
	printf("#    [4] Hibernate           #\n");
	printf("#                            #\n");
	printf("#                            #\n");
	printf("#                            #\n");
	printf("#                            #\n");
	printf("##############################\n");
		
	fflush(stdin);
	 i = getch();
	
	switch(i){
		case '1': a = 'A';break;
		case '2': a = 'B';break; 
		case '3': a = 'C';break;
		case '4': a = 'D';break;
		default:break;		
	}    
	
	temporitzador(a);
	return 0;
}

int temporitzador(char a){	
	int thora, tminuts, tsegons, maux;
	int x,i;
	char c;	
		
	thora = 0;									
	tminuts = 0;							
	tsegons = 0;
	
	HANDLE hOut;									//Controlarem els colors de la consola.
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	do{	
		system("cls");
		printf("Kcronos V3 \n\n");
		for (x=1; x<=5;x++){
			for (i=1; i<=30;i++){				
				if((x == 1)||(x ==3)||(x ==5)||(i == 1)||(i == 7)||(x == 12)){
					printf("#");
				}else if (x ==2 && i == 2){
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf(" [H] [M] [S]");
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf(" [R]");
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("   [i]");
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
					printf(" (P)  ");
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}else if ((x == 4)&&(i == 3)){
					SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf("        Timer:   %.2i:%.2i:%.2i   ", thora,tminuts,tsegons);
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}	
			}
		printf("\n");
		}
		
		c = toupper(getch());		// capturem un valor char i el pasem a majuscula. per seguir amb el codic.	
		
		if (c == 'I'){
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			printf("Info: \n  - Push H for hurs    \n  - Push M for min.   \n  - Push S for seg.  \n  - Push R for reset timer\n  - Push P for play \n  - Push ESC for exit \n");	
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			c = toupper(getch());
		}

		switch (c){	
			case 'H': 	printf("Hours  :  ");fflush(stdin);scanf("%i", & maux);thora += maux;break;
			case 'M': 	printf("Min.   :  ");fflush(stdin);scanf("%i", & maux);tminuts += maux;break;
			case 'S': 	printf("Seg.   :  ");fflush(stdin);scanf("%i", & maux);tsegons += maux;break;
						
			case 'R':	thora = 0; tminuts = 0; tsegons =  0;break;						
				
			case 'P': 	cronometro(a,thora,tminuts,tsegons);break;
						
			case 27 :   return 0;break;
			
			default :	break;	
							
		}
		
		if (tsegons >= 60){
			tminuts += tsegons / 60;
			tsegons = tsegons % 60;
		}
		if (tminuts >= 60){
			thora += tminuts / 60;
			tminuts = tminuts % 60;
		}

	}while(1);
	
}
void cronometro(char a, int thora, int tminuts,int tsegons){
	int hora,minuts,segons,x,i;

	
	HANDLE hOut;									//Controlarem els colors de la consola.
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	
	for( hora = 0; hora < 24; hora++){		
		for( minuts = 0; minuts < 60; minuts++){			
			for ( segons = 0; segons < 60; segons++){
				
				Sleep(1000);
				system("cls");
				printf("##############################\n#");
				
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("    Alarma:   %.2i:%.2i:%.2i      ", thora,tminuts,tsegons);
								
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("#\n##############################\n#");
								
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					printf("    Temps:    %.2i:%.2i:%.2i      ", hora,minuts,segons);
													
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					printf("#\n##############################\n");		
			
				if((thora == hora)&&(tminuts == minuts)&&(tsegons == segons))	{alarma(a);break;}				
				}							
			if((thora == hora)&&(tminuts == minuts)&&(tsegons == segons))	{alarma(a);break;}
			}			
		if((thora == hora)&&(tminuts == minuts)&&(tsegons == segons))	{alarma(a);break;}	
		}

}
void alarma(char a){	
	printf("ALARMA!\n");	
	Beep(880,75);// ALARMA sonora, pitara cada segon fins que pulsem un boto.
	accio(a);
}
void accio(char a){	
	if(a == 'A'){
		system("C:\\WINDOWS\\System32\\shutdown /s");
	}else if(a == 'B'){
		system("C:\\WINDOWS\\System32\\shutdown /r");
	}else if(a == 'C'){
		system("C:\\WINDOWS\\System32\\shutdown /l");
	}else if(a == 'D'){
		system("C:\\WINDOWS\\System32\\shutdown /h");
	}		
}




