#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;
struct Enemy{
	int w;
	int n;
};

const int SizeI = 8, SizeJ = 8;//Global constant size's for massiv

void setcur(int x, int y){ //set cursor to x y position - Need for clean compiler.
COORD coord; 
coord.X = x; 
coord.Y = y; 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
Enemy W(Enemy m,char a[SizeI][SizeJ], int x, int y){
	bool check = false;
	int O = 0;
	
	for(int i = 0; i<SizeI; i++){
		if(m.n == y){
			if(m.w < x){
				m.w++;
				setcur(16,3);
				cout<<"Cought you w++"<<m.w<<"<"<<x<<"|"<<m.n<<"="<<y<<endl;
				setcur(0,0);
			}
			if(m.w > x){
				setcur(16,4);
				cout<<"Cought you n--"<<m.w<<">"<<x<<"|"<<m.n<<"="<<y<<endl;
				setcur(0,0);
				m.w--;
			}
			check = true;
			break;
		}
	}
	for(int i = 0; i<SizeJ; i++){
		if(m.w == x){
			if(m.n < y){
				setcur(16,1);
				cout<<"Cought you n++"<<m.w<<"="<<x<<"|"<<m.n<<"<"<<y<<endl;
				setcur(0,0);
				m.n++;
			}
			if(m.n > y){
				setcur(16,2);
				cout<<"Cought you n--"<<m.w<<"="<<x<<"|"<<m.n<<"<"<<y<<endl;
				setcur(0,0);
				m.n--;
			}
			check = true;
			break;
		}
	}
	setcur(16,7);
	cout<<"Rand: "<<check<<endl;
	setcur(0,0);
	if(check == false){
		O = 0+rand()%5;
		if(O == 1 ){
			m.n++;	
		}
		if(O == 2){
			m.w++;
		}
		if(O == 3 ){
			m.w--;
		}
		if(O == 4 ){
			m.n--;		
		}
	}
	return m;
}
int X(int x, int tab){ //X move
	if(tab == 119)
	x--;
	if(tab == 115)
	x++;
	return x;
}
int Y(int y, int tab){ //Y move
	if(tab == 100)
	y++;
	if(tab == 97)
	y--;
	
	return y;
}	
int move(int tab, int x, int y){
		while(true){	
		if(kbhit() == true){
			tab = getch();
			if(tab == 119){
				  setcur(0,0);
				  break;  	
			}
			if(tab == 100){
				  setcur(0,0);
				  break;  	
			}
			if(tab == 115){
				 setcur(0,0);
				 break;  	
			}
			if(tab == 97){
				setcur(0,0);
				break;  	
			}
		}else{
			tab = 0;
			break;	
		}
	
	}											
	return tab;
}
void Full(char a[SizeI][SizeJ], int Po, bool k){
	for(int i = 0; i<SizeI; i++){
		for(int j = 0; j<SizeJ; j++){
			if(a[i][j] == '+')//To stay point on map
				a[i][j] = '+';
			else//Else
			a[i][j] = ' ';//Stay enter
			
			if (i == 0 || i == 7) {//The border 1
		        a[i][j] = '#';
		    }
			if (j == 0 || j == 7) { //The border 2
		        a[i][j] = '#';
		    }
		    if(i == 3 and j < 4 and j != 2){ //Room.1
		    	a[i][j] = '#';
			}
			if(i > 3 and j == 3)//Room.2
			a[i][j] = '#';
			if(Po == 0 and k == true){//Door
				a[3][6] = ']';
				a[4][6] = ']';
			}else{//Unlocked door if not true
				a[3][6] = '|';
				a[4][6] = '|';	
			}
		}
	}
	//return a[SizeI][SizeJ]; // This function returning nothing - just too lazy to delite it
}

int you(int n){//Your symbol
	return n;
}
int enemy(){ //Enemy
	return 50.8+50.8+50.8+50.8+50.8;
}
void Win(){ // Got to exit - Win
	setcur(11,10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
	cout<<"You win!"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	system("pause");
	exit(0);
}
void Lose(){//If we die from enemy - Lose
	setcur(11,10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8903);
	cout<<endl<<"GAME OVER!"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	system("pause"); 
	exit(0);
}
int menu(){
	char a[3][5] {NULL};
	int n = 0;
	for(int i = 0; i<3; i++){
		for(int j = 0; j<5; j++){
			a[i][j] = ' ';
			if(i == 0 || i == 2)
			a[i][j] = '-';
			if(j == 0 || j == 4)
			a[i][j] = '|';
			if(i == 0 and j == 0 || i == 2 and j == 4 || i == 0 and j == 4 || i == 2 and j == 0)
			a[i][j] = '+';
		}
	}
	string code = "";
	string num = "";
	int three = 0;
	setcur(10,1);
	cout<<"Chose your skin. (Tab any letter to exit menu)";
	setcur(10,2);
	cout<<"253 - "<<(char)253<<" "<<"251 - "<<(char)251<<" "<<"252 - "<<(char)252;
	setcur(10,3); 
	cout<<"248 - "<<(char)248<<" "<<"178 - "<<(char)178<<" "<<"177 - "<<(char)177; 
	
	while(true){
	bool tab = false;
	if(kbhit()){
		n = getch();
		three++;
		num = n;	
		code = code + num;
		tab = true;
	}else
	n = 0;
	if(n > 'a' and n < 'z'){
		break;
	}
	for(int i = 0; i<3; i++){
		for(int j = 0; j<5; j++){
			if(a[i][j] == ' ' and tab){
				a[i][j] = n;
				break;
			}	
		}
		cout<<endl;
	}
	setcur(0,5);
	for(int i = 0; i<3; i++){
		for(int j = 0; j<5; j++){
			cout<<a[i][j]<<" ";	
		}
		cout<<endl;
	}
	if(three == 3)
	break;
	}
	if(code > "a" and code < "z"){
		return 64;
	}else
	n = stoi(code);
	setcur(0,0);
	if(n == 253 or n == 251 or n == 252 or n == 248 or n == 178 or n == 177){
		return n;
	}else
	return 64;
	
}
int secret(int x, int y){//Secret room yay
	char secr[8][8] {NULL};
	x++; y++;
	int FEnemy = 1; // First Enemy coord
	int SEnemy = 4; // Secon enmy coord
	bool FControl = false; //First Enemy control
	bool SControl = false; //Second Enemy control
	int Speed = 0;//Enemy speed
	
	int tab = 0; //kbhit
	
	setcur(16,0);
	cout<<"Sorry that secret room is on beta, so is that why here is so empty.."<<endl;
	setcur(0,0);
	
	int n = 64; //Our symbol number
	while(true){
	for(int i = 0; i<SizeI; i++){ //Fulling massiv with enters
		for(int j = 0; j<SizeJ; j++){
			secr[i][j] = ' ';
		}
	}
	for(int i = 0; i<5; i++){//Fulling map
		for(int j = 0; j<5; j++){
			if (i == 0 || i == 4) {
		        secr[i][j] = '#';
		    }
		    if(i == 0 and j == 3){
		    	secr[i][j] = 'X';
			}
			if (j == 0 || j == 4) {
		        secr[i][j] = '#';
		    }
		}
	}
	int PreX = x;
	int PreY = y;

	tab = move(tab,x,y);
	setcur(0,0);
	x = X(x,tab);
	y = Y(y,tab);
	
	if(x == 0 and y == 3){//Menu
		n = menu();
		system("cls");
		x = PreX;
		y = PreY;
	}
	
	Speed++;//Speed ++
	
	if(Speed == 30){//This is enemy speed
		Speed = 0;	
		if(FControl == false)//Enemy 1
		FEnemy++;
		else
		FEnemy--;
		
		if(FEnemy == 3){
		FControl = true;	
		}
		if(FEnemy == 1){
			FControl = false;
		}
		if(SControl == false)//Enemy 2
		SEnemy--;
		else
		SEnemy++;
		
		if(SEnemy == 1){
		SControl = true;	
		}
		if(SEnemy == 3){
			SControl = false;
		}
	}
	if(FEnemy == x and y == 3 or SEnemy == x and y == 2)//If we on enemy then we died
	Lose();
	
	secr[FEnemy][3] = '%';//First enemy
	secr[SEnemy][2] = '%';//Secon enemy
	
	if(x == 1 and y == 0){//If we on exit coord, then we leave
		return n;
	}
	if(secr[x][y] == '#'){
		x = PreX;
		y = PreY;
	}
	secr[x][y] = you(n); // You
		for(int i = 0; i<SizeI; i++){
			for(int j = 0; j<SizeJ; j++){
				if(i == 1 and j == 0 and secr[i][j] == '#')
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),135);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),527);
	
				cout<<secr[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	return n;
}
void color(char a[SizeI][SizeJ], int i,int j){
				if(a[i][j] == (char)254){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
				}
				if(a[i][j] == '@'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
				}
				if(a[i][j] == '#'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),527);
				}
				if(a[i][j] == '|'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
				}
				if(a[i][j] == ']'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				}
				if(a[i][j] == '='){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				}
				if(a[i][j] == '&'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				}
				if(a[i][j] == '+'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
				}
				if(a[i][j] == '0'){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
				}
}
void Blinking(){   //Func that remove cursor need to deleat the blink.
void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO structCursorInfo;
GetConsoleCursorInfo(handle,&structCursorInfo);
structCursorInfo.bVisible = FALSE;
SetConsoleCursorInfo( handle, &structCursorInfo );
}
int main() {
srand(time(0));

Blinking(); //Remove cursor 

char main[SizeI][SizeJ]; //Map
int tab = 0, x = 6, y = 2; //Tab for key that your press on your key
bool Point = false; //This need for one spawn points
bool EnemyOnPlus = false; // Enemy on Plus checker
bool win = false, lose = false;
bool MKey = false; //if we get a key.// This... uh... just thing to check if key on his position lol.
int p1 = 0,p2 = 0; //Key positions.
int PoiCounter = 0; //How much do you have points.
int pW = 0, pN = 0; //If enemy on plus.
Enemy m = {5,5}; //Enemy coordinates.

int intel = 0;//This thin need to slow down enemy
int OurSymbolNum = 64; //Our Symbol number

while(true){
	Full(main,PoiCounter,MKey); //Function need to full massiv.
	tab = move(tab,x,y); //Keyboard press
	
	int PreW = m.w; //Previous coordinates w - Enemy
	int PreN = m.n; //Previous coordinates n - Enemy
	int PreX = x; //Previous coordinates x - You
	int PreY = y; //Previous coordinates y - You
	

	x = X(x,tab);
	y = Y(y,tab);
	if(intel == 50){//Intel slow down
		m = W(m,main,x,y); 
		intel = 0;//That need to reset slow down value
	}else//else
	setcur(0,0);//Set cursor on 0 . 0 position
	
	intel++;//Slowing down ++

	if(x == 2 and y == 0){ // beta Secret room
		system("cls");
		OurSymbolNum = secret(x,y);
		system("cls");
	}
	
	if(main[x][y] == '+'){// if we on point we need to count it
		PoiCounter--;
	}
	if(main[m.w][m.n] == '#'){ //Your can't step on wall..
		m.w = PreW;
		m.n = PreN;
	}
	if(main[x][y] == '#'){ //And Enemy too..
		x = PreX;
		y = PreY;
	}
	if(m.w > SizeI or m.n > SizeJ){ //And you can't be bigger than map.. what? 
		m.w = PreW;
		m.n = PreN;
	}
	if(main[m.w][m.n] == '+'){//If enemy on plus we memorize coordinates
		pW = m.w;
		pN = m.n;
		EnemyOnPlus = true; //And say: "He was on plus".
	}
	if(x == 6 and y == 1){ //Gets main key
		MKey = true;
	}
	
	if(main[x][y] == ']')//Win 
	win = true;
	else//Or
	if(m.w == x and m.n == y)//Lose
	lose = true;
	
	main[x][y] = you(OurSymbolNum); // You
	main[m.w][m.n] = enemy(); //enemy
	
	cout <<"W: "<<m.w <<"N: "<<m.n << endl;
	cout<<"Points:"<<PoiCounter<<endl;
	
	for(int i = 0; i<SizeI; i++){ //Output all massiv
		for(int j = 0; j<SizeJ; j++){
			if(i == 6 and j == 1 and MKey == false){
				main[i][j] = '0';
			}
			if(Point == false){//Plus spawn random
				go:p1 = 1+rand()%8; //Return to label if we found an error.
				p2 = 1+rand()%8;
				if(main[p1][p2] == ' ' and main[p1][p2] != '#' and main[p1][p2] != '|' and main[p1][p2] != ']' and p1 != m.w and p2 != m.n and p1 != x and p1 != y){
					main[p1][p2] = '+';
					PoiCounter++;
				}else
				goto go;//This label need to generate new point, because of error. 
			}
			color(main,i,j); //Coloring map
			if(i == 2 and j == 0 and main[i][j] == '#'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			}
			cout<<main[i][j]<<" ";
		}
		Point = true;//Break Plus random spawner.
		cout<<endl;
	}
	if(EnemyOnPlus == true){ //Return plus symbol on map - if enemy was on plus
		EnemyOnPlus = false;
		main[pW][pN] = '+';
	}
	if(win == true){//Check what is happend Win or lose. If we don't win
		Win(); return 1;
	}
	else//Else we check lose
	if(lose == true){//If we not lose then nothing
		Lose(); return 1;
	}
}	
	return 0;
}
