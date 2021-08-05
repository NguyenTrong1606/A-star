#include <iostream>
#include <fstream>
#include<stdio.h>
#define SL_MAX 50


using namespace std;



struct Node{
	int index;
	int g;
	int h;
	int f;
	int flag;
	int before;
};

Node p[SL_MAX];
Node Open[SL_MAX];
int a[SL_MAX][SL_MAX];
int b[SL_MAX];

void saveFile1(){
	fstream file1;
	int n;
	file1.open("input1.txt", ios :: out);
	if(file1.fail()){
		cout<<"LOI MO FILE!";
	}
	else{
		cout<<"nhap so luong dinh: ";
		cin>>n;
		file1 << n <<endl;
		cout<<"nhap gia tri tai cac dinh: "<<endl;
		
		for(int i = 1; i<= n; i++){
			int x;
			cout<<"nhap gia tri tai dinh "<<i<<" :";
			cin>>x;
			file1<<x<<"  ";
		}
		cout<<"Luu file thanh cong!";
	}
	file1.close();
}

void saveFile2(){
	fstream file1;
	file1.open("input1.txt");
	int n;
	file1 >> n;
	file1.close();
	fstream file2;
	file2.open("input2.txt", ios :: out);
	if(file2.fail()){
		cout<<"LOI MO FILE!";
	}
	else{
		cout<<"\n\nnhap ma tran gia tri g: "<<endl;
		for(int i=1; i<= n; i++){
			cout<<"nhap cac gia tri hang "<<i<<" :";
			for(int j=1; j <= n; j++){
				int x;
				cin>>x;
				file2 <<x<< "  ";
				
			}
			file2<<endl;
		}
		cout<<"Luu file thanh cong!";
	}
	file2.close();
}


void loadFile1(int *b, int &n){
	fstream file1;
	file1.open("input1.txt");
	if(file1.fail()){
		cout<<"LOI MO FILE!";
	}
	else{
		file1 >> n;
		for(int i= 1; i<=n; i++){
			file1>>b[i];
		}
	}
	file1.close();	
}


void loadFile2(int a[SL_MAX][SL_MAX], int n){
	fstream file2;
	file2.open("input2.txt");
	if(file2.fail()){
		cout<<"LOI MO FILE!";
	}
	else{
		for(int i=1; i<= n;i++){
			for(int j = 1; j <= n; j++){
				file2 >> a[i][j];
			}
		}
	}
	file2.close();		
}

void khoiTaoP(int &n, int *b){
	for(int i = 1; i<= n; i++){
		p[i].index = i;
		p[i].g = 0;
		p[i].h = b[i];
		p[i].f = p[i].h + p[i].g;
		p[i].flag = 0;
		p[i].before = 0;
	}
}



int count(int n, Node *Open){
	int count = 0;
	for(int i = 1; i <= n; i++){
		if(Open[i].flag == 1) count++;
	}
	return count;
}

int findIndexMin(int n, Node *Open){ //duyet open
	int min = 0, indexMin = 0;
	int i = 1;
	
	while(indexMin == 0){
		if(Open[i].flag == 1){
			min = Open[i].f;
			indexMin = i;
		}
		i++;
	};
	
	for(int j = 1; j <= n; j++){
		if(Open[j].f < min && Open[j].flag == 1){
			min = Open[j].f;
			indexMin = j;
		}
	}
	
	return indexMin;
}

int findIndex(int n, Node *Open, int vt){
	for(int i= 1; i<= n; i++){
		if(Open[i].index == vt) return i;
	}
	return -1;
}


void A_Star(int n, int start, int finish, int a[SL_MAX][SL_MAX],  int *b){
	int x = 1;
	Open[x] = p[start];
	Open[x].flag =1;
	p[start].flag = 1;
	Open[x].f = Open[x].h + Open[x].g;
	x++;
	
	while( count(x-1, Open) != 0){
		int indexMin = findIndexMin(x-1, Open);
		Open[indexMin].flag = 2;
		p[Open[indexMin].index].flag = 2;
		if(Open[indexMin].index == finish){
			cout << "Duong da di qua (tu dich den diem bat dau) la: "<<endl;
			cout<< finish << "   ";
			int y = finish;
			int z;
			while(y != start){
				z = findIndex(x-1, Open, y);
				y = Open[z].before;
				cout<<y<<"   ";
				
			}
			break;
			
		}
		else{
			for(int i = 1; i<= n; i++){
				if(a[Open[indexMin].index][i] != 0){ 
					if(p[i].flag == 0){ // chua duoc dua vao open
						Open[x] = p[i];
						Open[x].g = a[Open[indexMin].index][i] + Open[indexMin].g;
						Open[x].f = Open[x].h + Open[x].g;
						Open[x].before = Open[indexMin].index;
						Open[x].flag =1;
						p[i].flag= 1;
						x++;
						
					}
					else if(p[i].flag == 1){ //dang o trong Open
						int k = findIndex(x, Open, i);
						Node temp = p[i];
						temp.g = a[Open[indexMin].index][i] + Open[indexMin].g;
						temp.f = temp.h +temp.g;
						temp.before = Open[indexMin].index;
						temp.flag = 1;
						if(temp.f < Open[k].f) Open[k] = temp;
					}
					else{
						int k = findIndex(x, Open, i);
						Node temp = p[i];
						temp.g = a[Open[indexMin].index][i] + Open[indexMin].g;
						temp.f = temp.h +temp.g;
						temp.before = Open[indexMin].index;
						temp.flag = 1;
						if(temp.f < Open[k].f){
							Open[x] = temp;
							x++;
						}
					}
				}

			}
		}
	}
}



void menu(){
	int luachon = -1;
	int n, start, finish;
	do{
		system("cls");
		cout<<"\n======================menu======================";
		cout<<"\n1. Nhap du lieu. ";
		cout<<"\n2. Chon duong di. ";
		cout<<"\n0. Thoat";
		cout<<"\n================================================";
		cout<<"\n\nNhap lua chon: ";
		cin>>luachon;
		switch(luachon)
		{
			case 1:
				saveFile1();
				saveFile2();
				system("pause");
				break;
			
			case 2:
				loadFile1(b, n);
				loadFile2(a , n);
				khoiTaoP(n , b);
				cout<<"nhap dinh dau: ";
				cin>>start;
				cout<<"nhap dinh cuoi: ";
				cin >> finish;
				A_Star(n, start, finish, a, b);
				system("pause");
				break;
			
			case 0:
				break;
			
			default:
				cout<<"lua chon khong dung!";
				system("pause");
				break;
					
		}
	}while(luachon != 0);
}




int main(){
	menu();
	return 0;
	
}



