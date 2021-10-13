#include <iostream> //cout, cin
#include <windows.h> //cls, Sleep
#include <time.h> //czas do rng
#include <conio.h> //getch()
#include <stdlib.h> //exit()
#include "point.h" //wlasne klasy

//zmienne i tablice
const int x = 10;
const int y = 10;
const int enemyCount = 7;
char board [x][y];
Enemy e[enemyCount];
Point point;
Player p;
Player pNew;

//funkcje
void initBoard(char tab[][10], int ile);
void initEnemy(char tab[][10], Enemy *e, const int &enemyCounter);
Player initPlayer(char tab[][10], Player p);
int random(){ return (rand()%9)+1;}
bool isUsed(Enemy *en, int l, int ile, bool checkX);
void update(char tab[][10], Player p);
void move(Player &p, Point &point, char tab[][10]);
bool isBorder(int n);


int main(){

	srand(time(NULL));

	initBoard(board, x);
	initEnemy(board, e, enemyCount);
	p = initPlayer(board, p);

	while(true){
		update(board, p);
		move(p, point, board);
	}

	return 0;
}

void initBoard(char tab[][10], int ile){
	for(int i=0;i<ile;i++){
		for(int j=0;j<ile;j++){ //generowanie pustych znakow do template tabeli
			tab[i][j] = ' ';
		}
	}
}

Player initPlayer(char tab[][10], Player p){
	p.setX(0);
	p.setY(5);
	tab[p.getX()][p.getY()] = p.getC();

	return p;
}


void initEnemy(char tab[][10], Enemy *e, const int &enemyCount){
	for(int i=0;i<enemyCount;i++){ //generowanie wrogow poprzez ich obiekty

		for(int j=0; j<2; j++){
			if(j==0){
				do{
					 e[i].setX(random());
				}while(isUsed(e, e[i].getX(), i, true)); //sprawdzanie czy obiekt z takim parametrem x istnieje
			}
			else{
				do{
					 e[i].setY(random());
				}while(isUsed(e, e[i].getY(), i, false));
			}
		}

		tab[e[i].getX()][e[i].getY()] = 'X'; //enemies

	}

}
bool isUsed(Enemy *en, int l, int ile, bool checkX){

	if(checkX){
		for(int i=0;i<ile;i++){

			if(en[i].getX() == l) return true;
		}
		return false;
	}
	else{
		for(int i=0;i<ile;i++){

			if(en[i].getY() == l) return true;
		}
		return false;
	}

}
void update(char tab[][10], Player p){
	system("cls");

	tab[p.getX()][p.getY()] = p.getC();
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			std::cout<<tab[i][j];
		}
		std::cout<<std::endl;
	}

}

void move(Player &p, Point &point, char tab[][10]){
	int c;
	int x, y, n;
	bool charError;

	do{
		charError = false;
		c = getch();
		if(c==107 || c==27){
			exit(0);
		}
		else if(c==224){ //czy kliknieto strzalke
			x = p.getX();
			y = p.getY();
			c = getch();
			switch(c){
				case 77:
					// std::cout<<"arrow right";
					n = y+1;
					if(isBorder(n)){
						std::cout<<"End of the map"<<std::endl;
						Sleep(500);
					}
					else{
						if(tab[x][n]=='X'){
							std::cout<<"Game Over!";
							exit(0);
						}
						else{
							tab[x][y] = point.getC();
							p.setY(n);
						}
					}
					break;
				case 75:
					// std::cout<<"arrow left";
					n = y-1;
					if(isBorder(n)){
						std::cout<<"End of the map"<<std::endl;
						Sleep(500);
					}
					else{
						if(tab[x][n]=='X'){
							std::cout<<"Game Over!";
							exit(0);
						}
						else{
							tab[x][y] = point.getC();
							p.setY(n);
						}
					}
					break;
				case 72:
					// std::cout<<"arrow up";
					n = x-1;
					if(isBorder(n)){
						std::cout<<"End of the map"<<std::endl;
						Sleep(500);
					}
					else{
						if(tab[n][y]=='X'){
							std::cout<<"Game Over!";
							exit(0);
						}
						else{
							tab[x][y] = point.getC();
							p.setX(n);
						}
					}
					break;
				case 80:
					// std::cout<<"arrow down";
					n = x+1;
					if(isBorder(n)){
						std::cout<<"End of the map"<<std::endl;
						Sleep(500);
					}
					else{
						if(tab[n][y]=='X'){
							std::cout<<"Game Over!";
							exit(0);
						}
						else{
							tab[x][y] = point.getC();
							p.setX(n);
						}
					}
					break;
			}
		}
		else{
			std::cout<<"Wrong key: "<<c<<"!"<<std::endl;
			charError = true;
		}
	}while(charError);
	std::cout<<std::endl;
}

bool isBorder(int n){
	if(n<0 || n>=10) return true;
	else return false;
}
