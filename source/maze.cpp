#include <iostream>
#include<stdlib.h>
#include <fstream>
#include <string.h>
#define MAX_STACK_SIZE 900
using namespace std;

class element {  

	public:
		int enable;
		int gezildi;
		int satir;
		int sutun;
		int yon[8];
		element(){}//constructor
};  

class stack{
	element yigit[MAX_STACK_SIZE];
	
public:
	int top;
	stack();
	void yigit_ekle(element item);
	element yigit_al();
	void yigit_dolu();
	void yigit_bos();
};
 

//Initialize stack
stack::stack(){top=0;} 

void stack :: yigit_dolu(){  
    printf("Yigit dolu!!!\n"); exit(-1);  
}  
 
void stack :: yigit_bos(){  
    printf("Yigit bos!!!\\n"); exit(-2);  
}  
 
void stack :: yigit_ekle(element item ){  
    if( top >= MAX_STACK_SIZE-1 ) // Yeni eleman için yer var mý?  
        yigit_dolu();              // Yýðýt dolu uyarýsý ver ve çýk  
    yigit[++top] = item;          // önce göstergeyi artýr  
    // sonra yýðýtta iþaret edilen konuma yeni elemaný aktar  
}  
 
element stack :: yigit_al(  ){  
    if( top < 0 )    yigit_bos(); // Yýðýt boþsa uyarý ver ve çýk  
    return yigit[(top)--];        // Yýðýt elemanýný döndür, sonra göstergeyi azalt  
}

void findRoad(int satir,int sutun)
{
	stack yigit;
	stack yigit2;
	stack yigit3;

	char line[30];
	int k=0;
	element dizi[30][30];
	ifstream infile;
	infile.open("maze.txt");
	while (!infile.eof()) 
	{
		infile.getline(line,254);
		for(int j=0;j<sutun;j++)
		{
			element e;
			if(line[j]!='\0')//transfer the datas to element's array
			{
				e.satir=k; e.sutun=j; 	//assign the coordinate values of element
				for(int h=0;h<8;h++)
					e.yon[h]=0;
				if(line[j]-48==0)
				{
					e.enable=0; e.gezildi=0;//assign the bool values of element
					dizi[k][j]=e;
				}
				else if(line[j]-48==1)
				{
					e.enable=1; e.gezildi=1;//assign the bool values of element
					dizi[k][j]=e;
				}
			}
		}
		k++;
	}
	
	int solution[satir][sutun];
	int solution_counter=1;
	ofstream outfile("path.txt");
	int i=0,j=0,control=0;//control=0,sa 1.yýgýta,control=1 se 2.yýgýtada ekle
	int i_tut=0,j_tut=0;

	if(dizi[0][0].enable==0)//baslangýc yerini aldý
	{
		dizi[0][0].gezildi=1;
		dizi[0][0].satir=0;
		dizi[0][0].sutun=0;
		//yigit_ekle(&top , dizi[0][0]);
	}
	
	while(yigit.top!=-1){
		if(i==satir-1&&j==sutun-1)//çýkýþa geldikmi
		{
			int u=0;
			int hold[8];
			element y;
			int sayac=0;
			while(yigit.top!=-1)//temp stacke aktarma
			{	
				sayac++;
				y=yigit.yigit_al();
				solution[y.satir][y.sutun]=1;
				yigit3.yigit_ekle(y);
			}
			for(int h=0;h<sayac;h++)//temp staký geri al
				yigit.yigit_ekle(yigit3.yigit_al());
			
			element other_way=yigit2.yigit_al();
			element way=yigit.yigit_al();
			dizi[way.satir][way.sutun].gezildi=0;
			
			while(u==0)
			{
				if(way.satir==other_way.satir && way.sutun==other_way.sutun)
					break;
				way=yigit.yigit_al();
				for(int h=0;h<8;h++)
					hold[h]=dizi[way.satir][way.sutun].yon[h];
				for(int h=0;h<8;h++)//cikarilan elemanlarýn yon býlgýlerý sýfýrlanýyor
					dizi[way.satir][way.sutun].yon[h]=0;
				dizi[way.satir][way.sutun].gezildi=0;
				
			}
		
			for(int h=0;h<8;h++)//stacke tekrar girecegi icin yon bilgisini tekrar alýyor 
					dizi[way.satir][way.sutun].yon[h]=hold[h];
			yigit.yigit_ekle(way);
			dizi[way.satir][way.sutun].gezildi=1;
			i=way.satir;//bu kordinat degerleriyle kaldýgý yerden devam et
			j=way.sutun;
			
			outfile<<"Solution"<<solution_counter<<"\n";
			for(int h=0;h<satir;h++){//solution yazdýrýlýyor
				for(int g=0;g<sutun;g++){
					if(solution[h][g]==1)
						outfile<<"#";
					else
						outfile<<".";
				}
				outfile<<"\n";
			}
			for(int h=0;h<satir;h++)//solution dizisini sýfýrla
				for(int g=0;g<sutun;g++)
					solution[h][g]=0;
			outfile<<"\n\n";
			solution_counter++;
		}
		
		for(int k=i-1;k<i+2;k++){
			for(int l=j-1;l<j+2;l++){
				if(k==i && l==j)
					continue;
			
				if(k>=0 && l>=0 && k<satir && l<sutun )
				{
					if(dizi[k][l].enable == 0 && control==0 && dizi[k][l].gezildi == 0)
					{
							
							if(k<i && l<j){//gidilen yoldan bi daha gitmemesi için deðeriyon deðeri atanýyor
								if(dizi[i][j].yon[0]==1)
									continue;
								else
									dizi[i][j].yon[0]=1;}
							else if(k<i && l==j){
								if(dizi[i][j].yon[1]==1)
									continue;
								else
									dizi[i][j].yon[1]=1;}
							else if(k<i && l>j){
								if(dizi[i][j].yon[2]==1)
									continue;
								else
									dizi[i][j].yon[2]=1;}
							else if(k==i && l<j){
								if(dizi[i][j].yon[3]==1)
									continue;
								else
									dizi[i][j].yon[3]=1;}
							else if(k==i && l>j){
								if(dizi[i][j].yon[4]==1)
									continue;
								else
									dizi[i][j].yon[4]=1;}
							else if(k>i && l<j){
								if(dizi[i][j].yon[5]==1)
									continue;
								else
									dizi[i][j].yon[5]=1;}
							else if(k>i && l==j){
								if(dizi[i][j].yon[6]==1)
									continue;
								else
									dizi[i][j].yon[6]=1;}
							else if(k>i && l>j){
								if(dizi[i][j].yon[7]==1)
									continue;
								else
									dizi[i][j].yon[7]=1;}
							
							
							dizi[k][l].gezildi=1;
							dizi[k][l].satir=k;
							dizi[k][l].sutun=l;
							control=1;
							i_tut=k; j_tut=l;
							yigit.yigit_ekle(dizi[k][l]);
					}
					else if(dizi[k][l].enable == 0 && control==1 && dizi[k][l].gezildi==0)
					{
							control=2;
							yigit2.yigit_ekle(dizi[i][j]);
							break;
					}
				}
			}//satir
			if(control==2)
				break;
			
		}//sutun
		if(control==0)
		{
			int u=0;
			int hold[8];
			if(dizi[i][j].satir==0 && dizi[i][j].sutun==0)
				return;
			element temp2=yigit2.yigit_al();
			element temp=yigit.yigit_al();
			dizi[temp.satir][temp.sutun].gezildi=0;
			
			for(int h=0;h<8;h++)
				hold[h]=dizi[temp.satir][temp.sutun].yon[h];
			
			for(int h=0;h<8;h++)//stackten cikarilan elemanýn yon býlgýlerý sýfýrlanýyor
				dizi[temp.satir][temp.sutun].yon[h]=0;
		
			while(u==0)
			{
				if(temp.satir==temp2.satir && temp.sutun==temp2.sutun)
					break;
				temp=yigit.yigit_al();
				dizi[temp.satir][temp.sutun].gezildi=0;
				for(int h=0;h<8;h++)
					hold[h]=dizi[temp.satir][temp.sutun].yon[h];
				for(int h=0;h<8;h++)//stackten cikarilan elemanýn yon býlgýlerý sýfýrlanýyor
					dizi[temp.satir][temp.sutun].yon[h]=0;
			}
			dizi[temp.satir][temp.sutun].gezildi=1;
			for(int h=0;h<8;h++)
				dizi[temp.satir][temp.sutun].yon[h]=hold[h];
			yigit.yigit_ekle(dizi[temp.satir][temp.sutun]);
			i=temp.satir;
			j=temp.sutun;
			continue;
		}
		control=0;
		i=i_tut;
		j=j_tut;
	}
}

int  sutun_hesapla()
{
	char line[30];
	ifstream read;
	read.open("maze.txt");
	read.getline(line,254);
	read.close();
	return strlen(line);//return the column size
}	

int satir_hesapla()
{
	char line[30];
	int satir=0;
	ifstream read;
	read.open("maze.txt");
	
	while (!read.eof()) //find the number of lines
	{
		read.getline(line,30);
		satir++;
	}
	return satir;
	read.close();
}
	
void loadData()
{
	int sutun=sutun_hesapla();
	int satir=satir_hesapla();
	findRoad(satir,sutun);
}

int main()
{
	loadData();
	return 0;
}