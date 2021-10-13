class Point{

	int x;
	int y;
	char c;
public:
	Point(int a=0, int b=0, char ch=' '){
		x = a;
		y = b;
		c = ch;
	}
	int getX(){
		return x;
	}
	int getY(){
		return y;
	}
	char getC(){
		return c;
	}

	void setX(int a){
		x = a;
	}
	void setY(int a){
		y = a;
	}
	void setC(char a){
		c = a;
	}

};

class Enemy : public Point {

public:
	Enemy(int a=0, int b=0, char ch='X') : Point(a, b, ch){};
};

class Player : public Point{
public:
	Player(int a=0, int b=0, char ch='O') : Point(a,b,ch){};

};
