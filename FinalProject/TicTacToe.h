//TicTacToe
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

int board[4][4];
int sizeXO=3;
bool endGame=0;
int playerTurn=-1;


void printXO(){
	for(int a=0;a<=sizeXO*4;a++){
		printf("%c",char(219));
	}
	puts("");
	for(int a=1;a<=sizeXO;a++){
		printf("%c",char(219));
		for(int b=1;b<=sizeXO;b++){
			if(board[a][b]==1)printf("\\_/%c",char(219));
			else if(board[a][b]==-1) printf("%c%c%c%c", char(201), char(205), char(187), char(219));
			else printf(" %d %c", (a-1)*3+b, char(219));
		}
		printf("\n%c",char(219));
		for(int b=1;b<=sizeXO;b++){
			if(board[a][b]==1)printf("/ \\%c",char(219));
			else if(board[a][b]==-1) printf("%c%c%c%c", char(200), char(205), char(188), char(219));
			else printf("   %c",char(219));
		}
		printf("\n");
		for(int a=0;a<=sizeXO*4;a++){
			printf("%c",char(219));
			//if(a==0 || a==sizeXO*3)printf("|");
			//else printf("_");
		}
		puts("");
	
	}
}

int emptyBoard(){
	int empty=0;
	for(int a=1;a<=3;a++){
		for(int b=1;b<=3;b++){
			if(board[a][b]==0)empty++;
		}
	}
	return empty;
}

bool equals(int a, int b, int c){
	if(a==b && b==c && a!=0)return 1;
	else return 0;
}

int checkWinner(){
// 1=x
//-1=o
// 0=draw
// 2=no winner yet	
	
	int winner=2;
	
	//vertical
	for(int a=1;a<=3;a++){
		if(equals(board[1][a],board[2][a],board[3][a])){
			winner=board[1][a];
		}
	}
	//horizontal
	for(int a=1;a<=3;a++){
		if(equals(board[a][1],board[a][2],board[a][3])){
			winner=board[a][1];
		}
	}
	//diagonal
	if(equals(board[1][1],board[2][2],board[3][3])){
		winner=board[1][1];
	}
	if(equals(board[1][3],board[2][2],board[3][1])){
		winner=board[1][3];
	}
	//if full and no winner
	if(emptyBoard()==0 && winner==2){
		winner=0;
	}
	return winner;
}

int min(int a, int b){
	return(a<b) ? a : b;
}

int max(int a, int b){
	return(a>b) ? a : b;
}

int minimax(int depth, bool isMax){
	int result=checkWinner();
	if(result!=2){
		return result;
	}
	
	if(isMax){
		int bestScore=-1e9;
		for(int a=1;a<=3;a++){
			for(int b=1;b<=3;b++){
				if(board[a][b]==0){
					board[a][b]=playerTurn*-1;
					int score=minimax(depth+1, false);
				//	printXO();
					board[a][b]=0;
					bestScore=max(bestScore,score);
				//	printf(" score : %d maxscore : %d\n",score, bestScore);
				}
			}
		}
		return bestScore;
	}else{
		int bestScore=1e9;
		for(int a=1;a<=3;a++){
			for(int b=1;b<=3;b++){
				if(board[a][b]==0){
					board[a][b]=playerTurn;
					int score=minimax(depth+1, true);
				//	printXO();
					board[a][b]=0;
					bestScore=min(bestScore,score);
				//	printf(" score : %d maxscore : %d\n",score, bestScore);
				}
			}
		}
		return bestScore;
	}
}

void goodMove(){
	int bestScore=-1e9;
	int move[1];
	for(int a=1;a<=3;a++){
		for(int b=1;b<=3;b++){
			if(board[a][b]==0){
				board[a][b]=playerTurn*-1;
				int score=minimax(0, false);
				board[a][b]=0;
				if(score>bestScore){
					bestScore=score;
					move[0]=a;
					move[1]=b; 
				}
			}	
		}
	}
	board[move[0]][move[1]]=playerTurn*-1;
	playerTurn*=-1;
	
}

void badMove(){
	int bestScore=1e9;
	int move[1];
	for(int a=1;a<=3;a++){
		for(int b=1;b<=3;b++){
			if(board[a][b]==0){
				board[a][b]=playerTurn*-1;
				int score=minimax(0, false);
				board[a][b]=0;
				if(score<bestScore){
					bestScore=score;
					move[0]=a;
					move[1]=b; 
				}
			}	
		}
	}
	board[move[0]][move[1]]=playerTurn*-1;
	playerTurn*=-1;
}

void solo(){
	endGame=0;
	playerTurn=-1;
	system("cls");
	printf("1. Baby Mode\n");
	printf("2. Mental Break Dance Mode\n");
	printf("0. Exit\n");
	int choice;
	printf("\nMau yang mana hayoo?\n");
	scanf("%d", &choice);
	
	for(int a=1;a<=5;a++){
		//printf("endGame : %d\n", endGame);
		if(endGame)break;
		system("cls");
		if(choice==0){
			puts("Press enter pliss:)");
			break;
		}
		else if(choice==1)badMove();
		else goodMove();
		printXO();
		
		switch(checkWinner()){
			case 0:{
				system("cls");
				printXO();
				printf("Sesama Bot harus Damai :)\n");
				endGame=1;
				break;
			}
			case 1:{
				system("cls");
				printXO();
				printf("Udah jomblo, kalah lagi :'(\n");
				endGame=1;
				break;
			}
			case -1:{
				system("cls");
				printXO();
				printf("Selamat yah mbloo\n");
				endGame=1;
				break;
			}
			case 2:{
				break;
			}
		}
		if(endGame)break;
		
		playerTurn*=-1;
		printf("Jomblo's Turn\n");
		
		int input;
		bool valid=0;
		while(!valid){
			scanf("%d",&input);
			if((input>0 && input<10) && (board[((input-1)/3)+1][((input-1)%3)+1]==0)){
				board[((input-1)/3)+1][((input-1)%3)+1]=playerTurn;
				valid=1;
			}
			else printf("\ninvalid pak!\n");
		}	
		
		
		switch(checkWinner()){
			case 0:{
				system("cls");
				printXO();
				printf("Sesama Bot harus Damai :)\n");
				endGame=1;
				break;
			}
			case 1:{
				system("cls");
				printXO();
				printf("Udah jomblo, kalah lagi :'(\n");
				endGame=1;
				break;
			}
			case -1:{
				system("cls");
				printXO();
				printf("Selamat yah mbloo\n");
				endGame=1;
				break;
			}
			case 2:{
				break;
			}
		}
	}
}

void duo(){
	endGame=0;
	for(int a=1;a<=9;a++){
		if(endGame)break;
		system("cls");
		printXO();
		playerTurn*=-1;
		
		if(playerTurn==1)puts("Your Turn");
		else puts("Mantan's Turn");
		
		int input;
		bool valid=0;
		while(!valid){
			scanf("%d",&input);
			if((input>0 && input<10) && (board[((input-1)/3)+1][((input-1)%3)+1]==0)){
				board[((input-1)/3)+1][((input-1)%3)+1]=playerTurn;
				valid=1;
			}
			else printf("\ninvalid pak!\n");
		}	
		
		switch(checkWinner()){
			case 0:{
				system("cls");
				printXO();
				printf("Sesama Mantan harus Damai :)\n");
				endGame=1;
				break;
			}
			case 1:{
				system("cls");
				printXO();
				printf("Selamat, Mantan anda Kalah\n");
				endGame=1;
				break;
			}
			case -1:{
				system("cls");
				printXO();
				printf("Selamat kepada Mantan\n");
				endGame=1;
				break;
			}
			case 2:{
				break;
			}
		}
	}
	getch();
}

void playXO(){
	int choice;
	do{
		for(int a=0;a<=4;a++){
			for(int b=0;b<=4;b++){
				board[a][b]=-1;
			}
		}
		for(int a=1;a<=3;a++){
			for(int b=1;b<=3;b++){
				board[a][b]=0;
			}
		}
		
		system("cls");
		system("color b");
		system("mode con: cols=33 lines=16");
		
		printf("Welcome to TicTacToe!!\n\n");
		printf("How to Play\n");
		puts("_____________");
		puts("| 1 | 2 | 3 |");
		puts("|___|___|___|");
		puts("| 4 | 5 | 6 |");
		puts("|___|___|___|");
		puts("| 7 | 8 | 9 |");
		puts("|___|___|___|");
		printf("press the number and press enter\n\n");
		
		printf("1. Jomblo(1 player)\n");
		printf("2. Bersama Mantan(2 player)\n");
		printf("0. Back to Jaya\n");
		scanf("%d",&choice);
		switch(choice){
			case 0:{
				break;
			}
			case 1:{
				solo();
				getch();
				break;
			}
			case 2:{
				duo();
				getch();
				break;
			}
			default:{
				printf("ngisinya yang bener dong :(\n");
				getch();
				break;
			}
		}	
	}while(choice!=0);
}

