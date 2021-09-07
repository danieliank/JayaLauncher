#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//start of 2048 code
const int size=4;
int arr2048[128][128], maksNum;
unsigned int score;
bool play2048=1;

struct varPlayer{
	char name[128];
	int score;
};

varPlayer player[128];
int nOfPlayer=1;

void read(){
	FILE *fp = fopen("rank.txt","r");
	while(fscanf(fp, "%[^#]#%d\n", player[nOfPlayer].name, &player[nOfPlayer].score) != EOF) nOfPlayer++;
	fclose(fp);
}

void write(){
	FILE *fp = fopen("rank.txt","a");
	fprintf(fp, "%s#%d\n", player[nOfPlayer].name, player[nOfPlayer].score);
	fclose(fp);
}

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

int sqr2048(int x){
	int hasil=2;
	for(int a=1;a<x;a++){
		hasil*=2;
	}
	if(x==0)hasil=0;
	return hasil;
}


void print2048(){
	
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

bool move_2048(char dir){
//	printf("move_2048\n");
	if(dir=='w') return up_2048();
	else if(dir=='s') return down_2048();
	else if(dir=='d') return right_2048();
	else if(dir=='a') return left_2048();
	else return 0;
}

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

//jika player ingin bermain maka gameplay akan dijalankan untuk memulai game
void gamePlay2048(){
	
	memset(arr2048, 0, sizeof arr2048);
	play2048=1;
	maksNum = 2;
	score=0;
	bool check;
	check = randomPlacement();
	check = randomPlacement();
	
	char dir;
	print2048();
	while(play2048){
		//scanf doesn't work :")
		//cin>>dir;
		scanf("%c",&dir);
		printf("Your score : %d\n", score);
		if(move_2048(dir)){
//			printf("masuk : %c\n", dir);
			if(randomPlacement())print2048();
			else play2048=0;   
		}else if(howManyEmpty()>0 || !gameOver()){
			continue;
		}else play2048=0;
	}
	
	if(play2048==0){
		printf("      GAMEOVER\n");
		printf(" Your Score is : %d\n", score);
		puts("");
		printf("Thankyouu for playing\n");
		player[nOfPlayer].score=score;
		printf("Who is playing ?\n");
		scanf("%[^\n]",player[nOfPlayer].name);
//		printf("%s %d\n", player[nOfPlayer].name, player[nOfPlayer].score);
		write();
		nOfPlayer++;
		
		
		mergesort(1,nOfPlayer-1);
		//scoreboard;
		
		printf("\n    SCOREBOARD!!\n\n");
		for(int a=1;a<nOfPlayer;a++){
			printf("%s %d\n",player[a].name, player[a].score);
		}puts("");
		
		
		printf("if u want to play again press 1\n");
		printf("if not press 0\n");
		int tmp;
		printf("your choice : ");
		scanf("%d", &tmp);
		printf("\n");
		if (tmp==1)gamePlay2048();
		
	}
	
}

void setup2048(){
	play2048=1;
	while(play2048){
	
		puts("");
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
		printf("press w for swipe up\n");
		printf("press a for swipe left\n");
		printf("press s for swipe down\n");
		printf("press d for swipe right\n\n");
		printf("To play press 1\n");
		printf("To go back to Jaya Launcher press 0\n");		
		
		int tmp;
		scanf("%d", &tmp);
		play2048 = tmp;
		if(play2048){
			gamePlay2048();
		}
		
	}
}

//end of 2048 code


//start of Word Game


struct varWord{
	char word[128];
	int length;
	bool used;
};

struct varWordGame{
	char word[128];
	int length;
};

varWord words[128];
varWordGame playWord;
int randWord_index;

int usedWord=0,howManyWord=0;

void inputF(){
	FILE *fp = fopen("input.txt","r");
	while(fscanf(fp, "%s %d\n", words[howManyWord].word, &words[howManyWord].length) != EOF)howManyWord++;
	fclose(fp);
}

bool randomWord(){
	if(usedWord==howManyWord){
		return 0;
	}else{
		int unusedWord=howManyWord-usedWord;
		int randWord=rand()%unusedWord+1;
		int count=0;
	//	printf("howmany %d  used %d  unused %d  random %d\n", howManyWord, usedWord, unusedWord, randWord);
		for(int a=0;a<howManyWord;a++){
			if(!words[a].used){
				count++;
				if(randWord==count){
					randWord_index=a;
					strcpy(playWord.word,words[a].word);
					playWord.length=words[a].length;
					words[a].used=1;
					usedWord++;
					return 1;
				}
			}
		}
	}
	return 0;
}

bool lostOne(){
	bool check=randomWord();
	if(check){
		int x=rand() % playWord.length;
		char wordTmp[128];
			strcpy(wordTmp,playWord.word);
			wordTmp[x]='*';
			
			printf("\n%s\n", wordTmp);
			printf("\nGuess the missing letter!! (one letter only)\n");
			printf("(You got one chance :*)\n");
			scanf("\n%c", &wordTmp[x]);
			
			if(!strcmp(wordTmp,playWord.word))printf("\nYEY!!\n");
			else printf("\nBOOO!!!\nKamu cupu \n");
			printf("\nThe correct answer is: %s\n\n", playWord);
	}
	return check;
}


bool scrambler1(){
	bool check=randomWord();
	if(check){
		
		for(int a=1;a<=playWord.length;a++){
			int x=rand() % playWord.length, y=rand() % playWord.length;
					
	//		printf("%s  %d  %d\n", kata.word, x, y);
			char tmp=playWord.word[x];
			playWord.word[x]=playWord.word[y];
			playWord.word[y]=tmp;
		}
		char guess[128];
		printf("\n%s\n", playWord.word);
		printf("Guess the correct Word!!\n");
		for(int a=2;a>=0;a--){
			scanf("%s", guess);
			if(!strcmp(guess,words[randWord_index].word)){
				printf("\nYEY\n");
				break;
			}
			else if(a>0){
				printf("\nDon't worry mate, u still got %d more chance (UwU)\n", a);
			}else{
				printf("\nWell, I guess you're just suck. Sorry mate (o_o)\n");		
				printf("\nThe correct answer is: %s\n", words[randWord_index].word);

			}
		}
		
	}
	return check;	
}

bool scrambler2(){
	bool check=randomWord();
	if(check){
		for(int a=1;a<=playWord.length;a++){
			int pointer=rand()%playWord.length;
			char rev[128],tmp[128];
			memset(rev,0,sizeof(rev));
			memset(tmp,0,sizeof(tmp));
		
			strcpy(rev,playWord.word);
			strrev(rev);
			strncpy(tmp, rev, playWord.length-pointer);
			strncat(tmp, playWord.word, pointer);
			strcpy(playWord.word,tmp);	
		}
		
		char guess[128];
		printf("\n%s\n", playWord.word);
		printf("Guess the correct Word!!\n");
		for(int a=2;a>=0;a--){
			scanf("%s", guess);
			if(!strcmp(guess,words[randWord_index].word)){
				printf("\nYEY\n");
				break;
			}
			else if(a>0){
				printf("\nDon't worry mate, u still got %d more chance (UwU)\n", a);
			}else{
				printf("\nWell, I guess you're just suck. Sorry mate (o_o)\n");
				printf("\nThe correct answer is: %s\n", words[randWord_index].word);
			}
		}
	}
	return check;
}

void playWordGame(){
	int choice;
	inputF();
	do{
		puts("");
		puts("1. Lost One Letter <(0w0)>");
		puts("2. Scramble (-_-|||)");
		puts("0. Back to Jaya Launcher o_o");
		scanf("\n%d", &choice);
		switch(choice){
			case 1:{
				if(!lostOne()){
					puts("Sorry mate, out of word. Come back later");
					choice=0;
				}
				break;
			}
			case 2:{
				if(!scrambler2()){
					puts("Sorry mate, out of word. Come back later");
					choice=0;
				}
				break;
			}
			case 0:{
				break;
			}
		}
	}while(choice!=0);
}


//end of Word Game





void launcherSetup(){
	bool launch=1;
		read();
	do{
        puts("              _________           ");
        puts("             (=========)          ");
        puts("             |=========|          ");
        puts("             |====_====|          ");
        puts("             |== / \\ ==|          ");
        puts("             |= / _ \\ =|          ");
        puts("          _  |=| ( ) |=|  _       ");
        puts("         /=\\ |=|     |=| /=\\      ");
        puts("         |=| |=| INA |=| |=|      ");
        puts("         |=| |=|  _  |=| |=|      ");
        puts("         |=| |=| | | |=| |=|      ");
        puts("         |=| |=| | | |=| |=|      ");
        puts("         |=| |=| | | |=| |=|      ");
        puts("         |=| |/  | |  \\| |=|      ");
        puts("         |=|/    | |    \\|=|      ");
        puts("         |=/JAYA |_| JAYA\\=|      ");
        puts("         |(_____CODER_____)|      ");
        puts("         |=| |_|__|__|_| |=|      ");
        puts("         |=|   ( ) ( )   |=|      ");
        puts("        /===\\           /===\\     ");
        puts("       |||||||         |||||||    ");
        puts("       -------         -------    ");
        puts("        (~~~)           (~~~)     ");
        puts("                              ");
        puts("");
		printf("      Welcome to Jaya Launcher!!  \n");
		puts("");
		printf("   If you want to play 2048, press 1  \n ");
		printf("If you want to play word game, press 2  \n");
		printf("     If you want to quit, press 0   \n");
		int gameChoice;
		scanf("\n%d", &gameChoice);
		if(gameChoice==0)launch=0;
		else if(gameChoice==1)setup2048();
		else if(gameChoice==2){
			playWordGame();
		}
	
	}while(launch);
}

int main(){
	launcherSetup();	
}
