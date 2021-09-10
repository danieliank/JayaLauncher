#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

//start of 2048 code
const int size=4;
int arr2048[128][128], maksNum, inputArrow;
unsigned int score;
bool play2048=1;

struct varPlayer{
	char name[128];
	int score;
};

varPlayer player[128];
int nOfPlayer=1;

//read rank.file
void read(){
	FILE *fp = fopen("rank.txt","r");
	while(fscanf(fp, "%[^#]#%d\n", player[nOfPlayer].name, &player[nOfPlayer].score) != EOF) nOfPlayer++;
	fclose(fp);
}

//write the newest player
void write(){
	FILE *fp = fopen("rank.txt","a");
	fprintf(fp, "%s#%d\n", player[nOfPlayer].name, player[nOfPlayer].score);
	fclose(fp);
}

// start of mergesort
void merge(int l, int m, int r){
	int juml=m-l+1, jumr=r-m;
	varPlayer L[juml],R[jumr];
	for(int a=0;a<juml;a++){
		strcpy(L[a].name,player[l+a].name);
		L[a].score=player[l+a].score;
	}
	
	for(int a=0;a<jumr;a++){
		strcpy(R[a].name,player[m+a+1].name);
		R[a].score=player[m+a+1].score;
	}
	
	int i=0,j=0,k=l;
	
	while(i<juml && j<jumr){
		if(L[i].score>=R[j].score){
			strcpy(player[k].name,L[i].name);
			player[k].score=L[i].score;
			i++;
		}else{
			strcpy(player[k].name,R[j].name);
			player[k].score=R[j].score;
			j++;
		}
		k++;
	}
	while(i<juml){
		strcpy(player[k].name,L[i].name);
		player[k].score=L[i].score;
		i++;
		k++;
	}
	while(j<jumr){
		strcpy(player[k].name,R[j].name);
		player[k].score=R[j].score;
		j++;
		k++;
	}
}

void mergesort(int l, int r){
//	for(int a=0;a<=nOfPlayer;a++){
//		printf("%s %d\n",player[a].name,player[a].score);
//	}
//	printf("%d %d\n", l, r);
	if(l<r){
		int m=(l+r-1)/2;
		
		mergesort(l,m);
		mergesort(m+1,r);
		merge(l,m,r);
	}
	
}
//end of mergesort


//return the real value of the array
int sqr2048(int x){
	int hasil=2;
	for(int a=1;a<x;a++){
		hasil*=2;
	}
	if(x==0)hasil=0;
	return hasil;
}

//print 2048 box and score 
void print2048(){
	
	system("cls");
//	printf("%d\n\n",inputArrow);
	printf("Your score : %d\n\n", score);
	for(int a=1;a<=size*5+1;a++){
		printf("_");
	}
	printf("\n");

	for(int a=1;a<=size;a++){
		if(arr2048[a][1]==0) printf("|    |");
		else if(sqr2048(arr2048[a][1])<10) printf("| %d  |", sqr2048(arr2048[a][1]));
		else if(sqr2048(arr2048[a][1])<100) printf("| %d |", sqr2048(arr2048[a][1]));
		else if(sqr2048(arr2048[a][1])<1000) printf("|%d |", sqr2048(arr2048[a][1]));
		else printf("|%d|", sqr2048(arr2048[a][1]));
		
		for(int b=2;b<=size;b++){
			if(arr2048[a][b]==0) printf("    |");
			else if(sqr2048(arr2048[a][b])<10) printf(" %d  |", sqr2048(arr2048[a][b]));
			else if(sqr2048(arr2048[a][b])<100) printf(" %d |", sqr2048(arr2048[a][b]));
			else if(sqr2048(arr2048[a][b])<1000) printf("%d |", sqr2048(arr2048[a][b]));
			else printf("%d|", sqr2048(arr2048[a][b]));
		
		}
		printf("\n");
	
		for(int a=1;a<=size*5+1;a++){
			if(a%5==1)printf("|");
			else printf("_");
		}
		printf("\n");	
	
	}
}


//swipe up
bool up_2048(){
	bool check=0;
	for(int a=2;a<=size;a++){
	 	for(int b=1;b<=size;b++){
	 		if(arr2048[a][b]!=0){
	 			int cnta=a-1;
	 			while(arr2048[cnta][b]==0 && cnta>0){
					check=1;
	 				cnta--;
				}
				if(arr2048[cnta][b]!=arr2048[a][b]){
//					printf("boll_up 1\n");
					arr2048[cnta+1][b]=arr2048[a][b];
					if(cnta+1!=a){
						arr2048[a][b]=0;
						check=1;
					}
				}else if(arr2048[cnta][b]==arr2048[a][b]){
//					printf("bool_up 2\n");
					score+=sqr2048(arr2048[cnta][b])*2;
					arr2048[cnta][b]++;
					arr2048[a][b]=0;
					check=1;
				}
//				print2048();
			}
		}
	}
	return check;
}


//swipe down
bool down_2048(){
	bool check=0;
	for(int a=size-1;a>=1;a--){
	 	for(int b=1;b<=size;b++){
	 		if(arr2048[a][b]!=0){
	 			int cnta=a+1;
	 			while(arr2048[cnta][b]==0 && cnta<=size){
					check=1;
	 				cnta++;
				}
				if(arr2048[cnta][b]!=arr2048[a][b]){
//					printf("boll_down 1\n");
					arr2048[cnta-1][b]=arr2048[a][b];
					if(cnta-1!=a){
						arr2048[a][b]=0;
						check=1;
					}
				}else if(arr2048[cnta][b]==arr2048[a][b]){
//					printf("bool_down 2\n");
					score+=sqr2048(arr2048[cnta][b])*2;
					arr2048[cnta][b]++;
					arr2048[a][b]=0;
					check=1;
				}
//				print2048();
			}
		}
	}
	return check;
}


//swipe right
bool right_2048(){
	bool check=0;
	for(int b=size-1;b>=1;b--){
	 	for(int a=1;a<=size;a++){
	 		if(arr2048[a][b]!=0){
	 			int cntb=b+1;
	 			while(arr2048[a][cntb]==0 && cntb<=size){
					check=1;
	 				cntb++;
				}
				if(arr2048[a][cntb]!=arr2048[a][b]){
//					printf("boll_right 1\n");
					arr2048[a][cntb-1]=arr2048[a][b];
					if(cntb-1!=b){
						arr2048[a][b]=0;
						check=1;
					}
				}else if(arr2048[a][cntb]==arr2048[a][b]){
//					printf("bool_right 2\n");
					score+=sqr2048(arr2048[a][cntb])*2;
					arr2048[a][cntb]++;
					arr2048[a][b]=0;
					check=1;
				}
//				print2048();
			}
		}
	}
	return check;
}


//swipe left
bool left_2048(){
	bool check=0;
	for(int b=2;b<=size;b++){
	 	for(int a=1;a<=size;a++){
	 		if(arr2048[a][b]!=0){
	 			int cntb=b-1;
	 			while(arr2048[a][cntb]==0 && cntb>0){
					check=1;
	 				cntb--;
				}
				if(arr2048[a][cntb]!=arr2048[a][b]){
//					printf("boll_left 1\n");
					arr2048[a][cntb+1]=arr2048[a][b];
					if(cntb+1!=b){
						arr2048[a][b]=0;
						check=1;
					}
				}else if(arr2048[a][cntb]==arr2048[a][b]){
//					printf("bool_left 2\n");
					score+=sqr2048(arr2048[a][cntb])*2;
					arr2048[a][cntb]++;
					arr2048[a][b]=0;
					check=1;
				}
//				print2048();
			}
		}
	}
	return check;
}

//check how many empty box in array
int howManyEmpty(){
	int empty=0;
	for(int a=1;a<=size;a++){
		for(int b=1;b<=size;b++){
			(arr2048[a][b]==0) ? empty++ : empty=empty;
		}
	}
//	printf("%d\n",empty);
	return empty;
}


//place a random number of 1 or 2 in a random empty box
bool randomPlacement(){
	
	int empty=howManyEmpty();
//	printf("empty : %d\n",empty);	
	if (empty>=1){
		int placement = (rand() % empty) + 1,cnt = 1;
		for(int a=1;a<=size;a++){
			for(int b=1;b<=size;b++){
				if(arr2048[a][b]==0){
					if(placement==cnt){
						arr2048[a][b]=rand()%maksNum + 1;
						return 1;
					}else cnt++;
				}
			}
		}
		
	}else return 0;
}

//check if the game is over(player cannot move anymore)
bool gameOver(){
	bool check=1;
	
	for(int a=1;a<=size;a++){
		for(int b=1;b<=size;b++){
			if(arr2048[a][b]==arr2048[a-1][b] || arr2048[a][b]==arr2048[a+1][b] || arr2048[a][b]==arr2048[a][b-1] || arr2048[a][b]==arr2048[a][b+1]){
				check=0;
			}
		}
	}
	return check;
}

//to start the game
bool gamePlay2048(){
	system("color f0");
	system("mode con: cols=21 lines=14");
	int cntGame=1;
	bool check;
	play2048=1;
	maksNum = 2;
	score=0;
	memset(arr2048, 0, sizeof arr2048);
	check = randomPlacement();
	check = randomPlacement();
	print2048();
//	printf("cntGame : %d\n",cntGame);
	while(play2048){
		check=1;
		inputArrow=0;
		inputArrow=getch();
		
		switch(inputArrow) {
		    case 72:{	// key up
		    	check = up_2048();
		        break;
			}case 80:{    // key down
		    	check = down_2048();
		        break;
		    }case 77:{    // key right
		    	check = right_2048();
		        break;
		    }case 75:{    // key left
		    	check = left_2048();
		        break;
		    }default:{
				check = 0;
				break;
			}
		}
		
		if(check){
//			printf("masuk : %c\n", dir);
			if(randomPlacement())print2048();
			else play2048=0;   
		}else if(howManyEmpty()>0 || !gameOver()){
			print2048();
			continue;
		}else play2048=0;
	}
	
	if(play2048==0){
		system("cls");
		system("color 8b");
		system("mode con: cols=22 lines=10");
		
		printf("       GAMEOVER\n");
		printf(" Your Score is : %d\n", score);
		puts("");
		printf("Thankyouu for playing\n");
		player[nOfPlayer].score=score;
		printf("Who is playing ?\n");
		scanf("\n");
		scanf("%[^\n]",player[nOfPlayer].name);
//		printf("%s %d\n", player[nOfPlayer].name, player[nOfPlayer].score);
		write();
		nOfPlayer++;
		
		
		mergesort(1,nOfPlayer-1);
		//scoreboard;
		
		system("cls");
		system("mode con: cols=32 lines=13");
		printf("         SCOREBOARD!!!\n");
		puts  ("             Top 5 \n");
		int min=6;
		if(nOfPlayer<min)min=nOfPlayer;
		for(int a=1;a<min;a++){
			printf("%d. %s %d\n", a, player[a].name, player[a].score);
		}puts("");
		
		
		printf("if u want to play again press 1\n");
		printf("if not press 0\n");
		int tmp;
		printf("your choice : ");
		scanf("%d", &tmp);
		printf("\n");
		if (tmp==1)return 1;
		else return 0;	
	}
	
}

void setup2048(){
	play2048=1;
	while(play2048){
		system("cls");
		system("color 09");
		system("mode con: cols=68 lines=40");
		puts("                       .,,uod8B8bou,,.");
		puts("              ..,uod8BBBBBBBBBBBBBBBBRPFT?l!i:.");
		puts("         ,=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||");
		puts("         !...:!TVBBBRPFT||||||||||!!^^""'     ||||");
		puts("         !.......:!?|||||!!^^""'              ||||");
		puts("         !.........||||                     ||||");
		puts("         !.........||||  Welcome            ||||");
		puts("         !.........||||         to          ||||");
		puts("         !.........||||            2048!!   ||||");
		puts("         !.........||||                     ||||");
		puts("         !.........||||                     ||||");
		puts("         `.........||||                    ,||||");
		puts("          .;.......||||               _.-!!|||||");
		puts("   .,uodWBBBBb.....||||       _.-!!|||||||||!:'");
		puts("!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....");
		puts("!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.");
		puts("!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.");
		puts("!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^""::::       `.");
		puts("!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         iBBbo.");
		puts("`..........YBRPFT?!::::::::::::::::::::::::;iof68bo.      WBBBBbo.");
		puts("  `..........:::::::::::::::::::::::;iof688888888888b.     `YBBBP^'");
		puts("    `........::::::::::::::::;iof688888888888888888888b.     `");
		puts("      `......:::::::::;iof688888888888888888888888888888b.");
		puts("        `....:::;iof688888888888888888888888888888888899fT!");
		puts("          `..::!8888888888888888888888888888888899fT|!^""");
		puts("            `' !!988888888888888888888888899fT|!^""");
		puts("                `!!8888888888888888899fT|!^""");
		puts("                  `!988888888899fT|!^""");
		puts("                    `!9899fT|!^""");
		puts("                      `!^""");

		
		for(int a=1;a<=size*5+1;a++)printf("_");
		printf("\n");
		printf("How to play 2048: \n");
		printf("press up arrow to swipe up\n");
		printf("press left arrow to swipe left\n");
		printf("press down arrow to swipe down\n");
		printf("press right arrow to swipe right\n\n");
		printf("To play press 1\n");
		printf("To go back to Jaya Launcher press 0\n");		
		
		int tmp;
		scanf("%d", &tmp);
		play2048 = tmp;
		if(play2048){
			while(gamePlay2048()){
				
			}
		}
		
	}
}


