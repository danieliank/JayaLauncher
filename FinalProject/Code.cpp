#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include"2048.h"
#include"Word Game.h"
#include"TicTacToe.h"

void launcherSetup(){
	bool launch=1;
		read();
	do{
		system("cls");
/*
	0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White
*/
		system("color b4");
		system("mode con: cols=43 lines=32");
        puts("                _________           ");
        puts("               (=========)          ");
        puts("               |=========|          ");
        puts("               |====_====|          ");
        puts("               |== / \\ ==|          ");
        puts("               |= / _ \\ =|          ");
        puts("            _  |=| ( ) |=|  _       ");
        puts("           /=\\ |=|     |=| /=\\      ");
        puts("           |=| |=| INA |=| |=|      ");
        puts("           |=| |=|  _  |=| |=|      ");
        puts("           |=| |=| | | |=| |=|      ");
        puts("           |=| |=| | | |=| |=|      ");
        puts("           |=| |=| | | |=| |=|      ");
        puts("           |=| |/  | |  \\| |=|      ");
        puts("           |=|/    | |    \\|=|      ");
        puts("           |=/JAYA |_| JAYA\\=|      ");
        puts("           |(_____CODER_____)|      ");
        puts("           |=| |_|__|__|_| |=|      ");
        puts("           |=|   ( ) ( )   |=|      ");
        puts("          /===\\           /===\\     ");
        puts("         |||||||         |||||||    ");
        puts("         -------         -------    ");
        puts("          (~~~)           (~~~)     ");
        puts("                              ");
        puts("");
		printf("        Welcome to Jaya Launcher!!  \n");
		puts("");
		printf("    If you want to play 2048, press 1  \n ");
		printf("If you want to play word game, press 2\n");
		printf("If you want to play Tic Tac Toe, press 3  \n");
		printf("     If you want to quit, press 0   \n");
		int gameChoice;
		scanf("\n%d", &gameChoice);
		if(gameChoice==0)launch=0;
		else if(gameChoice==1)setup2048();
		else if(gameChoice==2)playWordGame();
		else if(gameChoice==3)playXO();

	}while(launch);
}

int main(){
	
	launcherSetup();	
}
