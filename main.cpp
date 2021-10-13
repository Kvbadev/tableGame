#include <iostream> //cout, cin
#include <windows.h> //cls, Sleep
#include <time.h> //czas do rng
#include <conio.h> //getch()
#include <stdlib.h> //exit()
#include "point.h" //wlasne klasy

//zmienne, tablice i obiekty
const int x = 10;
const int y = 10;
const int enemyCount = 7;
char board [x][y];
Enemy e[enemyCount];
Point point;
Player p(0,5,'O');
Gift g;

//funkcje
void initBoard(char tab[][10], int ile, const int &enemyCount, Enemy *e, Player p, Gift g);
void initEnemy(char tab[][10], Enemy *e, const int &enemyCounter);
void initGift(Gift &g, Enemy *e);
int random(){ return (rand()%9)+1;}
bool isUsed(Enemy *en, int l, int ile, bool checkX);
void update(char tab[][10], Player p, Gift g, int variant);
void move(Player &p, Point &point, char tab[][10], Enemy *e, const int &enemyCount);
bool isBorder(int n);
bool isEnemy(Player p, Enemy *e, const int &enemyCount);
void movement(int n, char tab[][10], Point point, Player &p, Enemy *e, bool isX);
void initGift(Gift &g, Enemy *e, const int &enemyCount);


int main(){

	srand(time(NULL));

	initEnemy(board, e, enemyCount);
	initGift(g, e, enemyCount);
	initBoard(board, x, enemyCount, e, p, g);
	std::cout<<"x: "<<g.getX()<<" y: "<<g.getY();

	while(true){
		update(board, p,g,0);
	  	move(p, point, board, e, enemyCount);
		// std::cout<<"Player: "<<p.getX()<<" "<<p.getY()<<std::endl;
		// std::cout<<"Gift: "<<g.getX()<<" "<<g.getY()<<std::endl;
	 }

	return 0;
}

void initBoard(char tab[][10], int ile, const int &enemyCount, Enemy *e, Player p, Gift g){
	for(int i=0;i<ile;i++){
		for(int j=0;j<ile;j++){ //generowanie pustych znakow do template tabeli
			tab[i][j] = ' ';
		}
	}
	tab[p.getX()][p.getY()] = p.getC();
	tab[g.getX()][g.getY()] = g.getC();
	for(int i=0;i<enemyCount;i++){
		tab[e[i].getX()][e[i].getY()] = e[i].getC();
	}
}

void initEnemy(char tab[][10], Enemy *e, const int &enemyCount){
	for(int i=0;i<enemyCount;i++){ //generowanie wrogow poprzez ich obiekty

		do{
			e[i].setX(random());
		}while(isUsed(e, e[i].getX(), i, true)); //sprawdzanie czy obiekt z takim parametrem x istnieje
		do{
			e[i].setY(random());
		}while(isUsed(e, e[i].getY(), i, false));
		tab[e[i].getX()][e[i].getY()] = e[i].getC(); //enemies
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
void update(char tab[][10], Player p, Gift g, int variant){
	system("cls");

	tab[p.getX()][p.getY()] = p.getC();
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if((variant==1) && (p.getX()==i && p.getY()==j)){
				printf("\033[31m");
				std::cout<<tab[i][j];
				printf("\033[37m");
			}
			else if((variant==2)&&(g.getX()==i && g.getY()==j)){
				printf("\u001b[32m");
				std::cout<<tab[i][j];
				printf("\033[37m");
			}
			else{
				std::cout<<tab[i][j];
			}
		}
		std::cout<<std::endl;
	}

}

void move(Player &p, Point &point, char tab[][10], Enemy *e, const int &enemyCount){
	int c;
	int x, y, n;
	Player *pWsk = &p;
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
					movement(n, tab, point, p, e, false);
					break;
				case 75:
					// std::cout<<"arrow left";
					n = y-1;
					movement(n, tab, point, p, e, false);
					break;
				case 72:
					// std::cout<<"arrow up";
					n = x-1;
					movement(n, tab, point, p, e, true);
					break;
				case 80:
					// std::cout<<"arrow down";
					n = x+1;
					movement(n, tab, point, p, e, true);
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

bool isEnemy(Player p, Enemy *e, const int &enemyCount){

	for(int i=0;i<enemyCount;i++){
		// std::cout<<p.getX()<<e->getX()<<p.getY()<<e->getY()<<std::endl;
		if((p.getX()==e->getX()) && (p.getY()==e->getY())){ //sprawdza czy coordy gracza i wroga sie pokrywaja
			e-=i;
			return true;
		}
		e++;
	}
	e-=enemyCount;
	return false;

}

bool isGift(Gift &g, Player &p){
	if(p.getX()==g.getX() && p.getY()==g.getY()) return true;
	else return false;
}

void movement(int n, char tab[][10], Point point, Player &p, Enemy *e, bool isX){

	if(isBorder(n)){
		std::cout<<"End of the map!"<<std::endl;
		Sleep(500);
	}
	else{
		tab[p.getX()][p.getY()] = point.getC();
		if(isX) p.setX(n);
		else 	p.setY(n);
		
		if(isEnemy(p, e, enemyCount)){
			update(tab,p,g,1);
			std::cout<<"Game Over!";
			Sleep(1000);
			exit(0);
		}
		else if(isGift(g, p)){
			update(tab,p,g,2);
			std::cout<<"You Win!";
			Sleep(1000);
			exit(0);
		}
	}
}

void initGift(Gift &g, Enemy *e, const int &enemyCount){

	for(int i=0; i<enemyCount; i++){
		do{
			g.setX(random());
		}while(isUsed(e, g.getX(),enemyCount,true) && g.getX()<=2);
		do{
			g.setY(random());
		}while(isUsed(e,g.getY(),enemyCount,false));
	}
}
