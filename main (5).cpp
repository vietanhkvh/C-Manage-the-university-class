#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <iomanip>

//Khai bao cac struct
#include "ListClasses.h"
#include "ListRegisters.h"
#include "ListStudents.h"
#include "ListSubjects.h"

#define STACKSIZE 500

#define MAXLIST 300
#define MAXTICKET 300
#define SOLUONGMOITRANG 15
#define SOLUONGMOITRANG1 100
#define SOLUONGMOITRANG2 6


// giao dien
#define X_a 132
#define Y_a 6

#define X_ThongBao 120
#define Y_ThongBao 40

#define X_DISPLAY 5
#define Y_DISPLAY 4
#define Y_DISPLAY1 45

#define X_MENU_TICKET 20
#define Y_MENU_TICKET 4

#define X_PAGE 20
#define Y_PAGE 40

#define X_TITLE 60
#define Y_TITLE 1

#define Y_MENU2 10
#define Y_MAIN 15

// key
#define SPACE  32
#define ESC  27
#define ENTER 13
#define BACKSPACE 8
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F10 68
#define PAGE_DOWN 81
#define PAGE_UP 73

#define MAX_LENGTH 15
#define MAX_CMND 12

//color
#define GREY 7
#define GREEN 6
#define PURPLE 5

int currposAirplane = 0;
int currposPrecAirplane = 0;
int trangHienTaiMB = 1;
int tongsoTrangMB = 0;

int vitriHienTaiTK = 1;
int vitriTruocDoTK = 1;

int vitriHienTaiCB = 0;

int vitriHienTaiCB1 = 10;

int vitriTruocDoCB = 0;
int vitriTruocDoCB1 = 10;

int trangHientaiCB = 1;
int tongsoTrangSVLopHoc = 0;

int vitriHienTaiCBDel = 0;
int vitriTruocDoCBDel = 0;
int trangHientaiCBDel = 1;
int tongsoTrangCBDel = 0;

int vitriHienTaiHK = 0;
int vitriTruocDoHK = 0;
int trangHientaiHK = 1;
int tongsoTrangHK = 0;

int vitriHienTaiMenu = 0;
int vitriTruocDoMenu = 0;

unsigned int arrIdLop[500];
//
using namespace std;

//======================================GiaoDien======================================================//
void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void TextColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void Normal (){
	TextColor(11);
	SetBGColor(0);
}

void setColor(int textColor, int BackColor){
	// converts the textColor and BackColor to one
	int color = textColor + (BackColor * 16);

	// creates the handle we need to use
	HANDLE Console_Handle;

	// grab the handle so we can use it
	Console_Handle= GetStdHandle(STD_OUTPUT_HANDLE);

	// sets the color desired
	SetConsoleTextAttribute(Console_Handle, color);
}
//============================Xoa man Hinh====================================
void XoaManHinh()
{
	for (int i =3;i<29;i++)
	{
		gotoxy(2,i);
		cout<<"                                                                                     ";
	}
}
void XoaManHinhAddMH()
{
	for (int i =3;i<29;i++)
	{
		gotoxy(2,i);
		cout<<"                                               ";
	}
}

void XoamanhinhF()
{
	int toadoy=12;
	for (int i = 0; i < 15;i++)
	{
		gotoxy(16, toadoy); cout << "                ";
		gotoxy(34, toadoy); cout << "                     ";
		gotoxy(60, toadoy); cout << "                 ";
		gotoxy(81, toadoy); cout << "                ";
		gotoxy(105, toadoy);cout << "    ";
		toadoy++;
	}
}

void XoamanhinhH()
{
	int toadoy = 12;
	for (int i = 0; i < 15; i++)
	{
		gotoxy(25,toadoy); cout<<"        ";
		gotoxy(62,toadoy); cout<<"        ";
		toadoy++;
	}
}

//Ve khung hinh chu nhat
void VeKhungCH(int x, int y, int width, int height, bool draw) 
{
	if (draw)
	{	
		TextColor(11);
		gotoxy(x, y);
		cout << char(218);
		gotoxy(x + width, y);
		cout << char(191);
		gotoxy(x, y + height);
		cout << char(192);
		gotoxy(x + width, y + height);
		cout << char(217);
		for (int i = y + 1; i < (y + height); i++)
		{
			gotoxy(x, i);
			cout << char(179);
			gotoxy(x+width, i);
			cout << char(179);
		}
		
		for (int i = x + 1; i < (x + width); i++)
		{
			gotoxy(i, y);
			cout << char(196);
			gotoxy(i, y+height);
			cout << char(196);
		}
		
	}
	else 
	{
		for (int i = x; i <= (x + width); i++)
		{
			gotoxy(i, y);
			cout << " ";
			gotoxy(i, y + height);
			cout << " ";
		}
		for (int i = y + 1; i < (y + height); i++)
		{
			gotoxy(x, i);
			cout << " ";
			gotoxy(x + width, i);
			cout << " ";
		}
	}
	Normal();
}

// Di chuyen khung chon
int KhungChon(int x,int y, int wide ,int numberchoices)
{
	//y=2
	int i=1;
	int n=y;
	int keyboard;
	
	do 
	{
		if ((i > numberchoices) || (i<1) ) 
			{
			n=y;
			i=1;
			}
		TextColor(4);
		VeKhungCH(x-1,n-1, wide,2,1);
			
		keyboard = getch();
		if (keyboard == 0) keyboard = getch();
			{
			if (keyboard == KEY_DOWN)
				{
					SetBGColor(0);
					VeKhungCH(x-1,n-1,wide,2,0);
					n+=2;
					i++;
				}
			if (keyboard == KEY_UP)
				{
					SetBGColor(0);
					VeKhungCH(x-1,n-1,wide,2,0);
					n-=2;
					i--;
				}
			}
		
	}
	while ((keyboard != ENTER) && (keyboard != ESC));
	if (keyboard == ENTER) 
	{ 
		
		VeKhungCH(x-1,n-1,wide,2,0);
		TextColor(11);
		return i;
	}
	if (keyboard == ESC) 
	{ 
		VeKhungCH(x-1,n-1,wide,2,0);
		TextColor(11);
		return 5;
	}
}
// Nen chay
void RunningColor(int x, int y)
{
	gotoxy(x,y);
	setColor(11, 0);
}

string tpMenuChinh[8] = {	" QUAN LY LOP TIN CHI ",
							" DANH SACH SV DA DANG KY ",
							" CAP NHAT SINH VIEN LOP HOC ",
							" QUAN LY MON HOC ",
							" DANG KY LOP TIN CHI ",
							" NHAP DIEM ",
							" IN BANG DIEM MON HOC ",
							" IN DIEM TRUNG BINH CUA LOP "};
int taodoxMenuChinh[5];

//logo
void Intro(){
	string a;
	ifstream file("C:\\Users\\Admin\\Desktop\\chuyenbay\\lammau.txt");
	while(!file.eof()){
		getline(file, a);		
		cout << a << endl;
	}
}
//tao khung co chu ben trong
void CreatBox(int x, int y, string text, int lenght){
	
	gotoxy(x - 2, y - 1);
	cout << char(218) << setw(lenght) << setfill(char(196)) << char(196) << char(191);
	if (lenght != 20){
		gotoxy(x - 2, y);
		TextColor(14);
		cout << char(179) << text << setw(lenght - text.length() + 1) << setfill(' ') << char(179);
		TextColor(11);
	}
	else {
		gotoxy(x - 2, y);
		cout << char(179);
		gotoxy(x + 4, y);
		cout << text << setw(lenght - text.length() - 4) << setfill(' ') << char(179);
	}
	gotoxy(x- 2, y + 1);
	cout << char(192) << setw(lenght) << setfill(char(196)) << char(196) << char(217);
}

void ChuyenMauMenu(string key[], int vitri)
{
	gotoxy(taodoxMenuChinh[vitri] - 3, Y_MAIN + vitri * 2); cout << char(175);
	gotoxy(taodoxMenuChinh[vitri] + 2 + tpMenuChinh[vitri].length(), Y_MAIN + vitri * 2); cout << char(174);
	gotoxy(taodoxMenuChinh[vitri], Y_MAIN + vitri * 2);
	setColor(0, 14);
	cout << key[vitri];

	gotoxy(taodoxMenuChinh[vitriTruocDoMenu], Y_MAIN + vitriTruocDoMenu * 2);
	setColor(11, 0);
	cout << key[vitriTruocDoMenu];
	//getch();
	//gotoxy(taodoxMenuChinh[vitriTruocDoMenu] - 3, Y_MAIN + vitri * 2); cout << char(0);
	//gotoxy(taodoxMenuChinh[vitriTruocDoMenu] + 2 + tpMenuChinh[vitri].length(), Y_MAIN + vitri * 2); cout << char(0);
	
	vitriTruocDoMenu = vitri;
}

void ChangeColorItemMainMenu(string key, int index, int newColor, int oldColor)
{
	gotoxy(taodoxMenuChinh[index] , Y_MAIN);
	setColor(0, newColor);
	cout << key;
	setColor(11, oldColor);
}
//hien thi thanh phan cua menu
void MainMenu(string key[], int nKey)
{
	int center;
	system("color 0B");
	gotoxy(108 - 7, Y_MAIN); cout << char(175); // 2 dau lon hon
	gotoxy(108 + 7, Y_MAIN); cout << char(174); // 2 dau be hon
	center = 110 - (tpMenuChinh[0].length() / 2);
	taodoxMenuChinh[0] = center;
	gotoxy(center, Y_MAIN + 0 * 2);
	cout << " " << tpMenuChinh[0] << " ";
	for (int i = 1; i < nKey; i++)
	{
		center = 108 - (tpMenuChinh[i].length() / 2);
		taodoxMenuChinh[i] = center;
		gotoxy(center, Y_MAIN + i * 2);
		cout << " " << tpMenuChinh[i] << " ";
	}
	ChangeColorItemMainMenu(key[0], 3, 14, 0);
}


string tpGiaodienMB[3] = { "SO HIEU MAY BAY", "LOAI MAY BAY", "SO CHO" };
string tpGiaodienCB[6] = { "SO HIEU MB", "MA CHUYEN BAY", "NGAY GIO","SAN BAY DEN","TRANG THAI","SO VE" };
string tpGiaodienHK[4] = { "CMND", "HO", "TEN", "PHAI" };
string tpGiaodienThongTinVe[2] = { "CHUYEN BAY", "THONG TIN CHUYEN BAY"};
string tpGiaodienHK1CB[5] = { "STT", "SO VE", "SO CMND", "HO TEN", "PHAI"};

string tpGiaodienlopTC[7]={"MA LOP TC", "MA MON HOC", "NIEN KHOA", "HOC KY", "NHOM", "SO SV TOI DA", "SO SV TOI THIEU"};
string tpGiaodienlopTCDK[2]={"MA LOP TC", "MA MON HOC"};
string tpGiaodienthemlopTC[6]={"MA MON HOC", "NIEN KHOA", "HOC KY", "NHOM", "SO SV TOI DA", "SO SV TOI THIEU"};
string tpGiaodienSV[7]={"MSSV" , "HO", "TEN", "PHAI", "SDT", "MA LOP HOC", "NAM NHAP HOC"};
string tpGiaodienSVDK[7]={"STT","MSSV" ,"HO","TEN" ,"DIEM"};
string tpGiaodienMH[4]={"MA MON HOC", "TEN MON HOC", "SO TIN CHI LY THUYET", "SO TIN CHI THUC HANH"};
string tpGiaoDienB1DKLopTC[3]={"Ma so sinh vien","Nien khoa lop tin chi","Hoc ky cua lop tin chi"};
string tpGiaoDienXuatDSDK[4]={"Ma mon hoc", "Nien khoa", "Hoc ky", "Nhom"};

string tpMucLucSV[2] = { " F2:Them   F3:Huy   F4:Hieu Chinh   F5:Xoa   F10:Save ", " QUAN LY DANH SACH SINH VIEN LOP HOC" };
string tpMucLucLop[2] = { " F2:Them   F3:Xoa   F4:Hieu Chinh   F10:Save ", " QUAN LY LOP TIN CHI " };
string tpMucLucMH[2] = { " F2:Them   F3:Xoa   F4:Hieu Chinh   F10:Save ", " QUAN LY MON HOC " };
string tpMucLucDK[2] = { " F5:Chinh sua lop dang ky      F3: Luu lop tin chi da chon", " QUAN LY LOP DANG KY" };

int toadoxGiaoDien[9] = { 11,31,56,77,96,111,131,151,171 }; // lop tin chi, mon hoc
int toadoxGiaoDien1[8] = { 17,30,50,66,76,90,105,125 };//
int toadoxGiaoDien2[3] = { 20, 50, 94 }; // dung cho huy ve
int toadoxGiaoDien3[6] = { 40,48,58,72,90,99 }; // dung cho thong ke hanh khach 1 chuyen bay
void GiaoDienChinhSua(string key[], int nKey, int lenght){
	int yA = Y_a;
	for (int i = 0; i < nKey; i++){
		CreatBox(X_a + 20, yA, key[i], lenght);
		yA += 3;
	}
}
void GiaoDienB1DKLopTC(string key[], int nKey, int lenght){
	int yA = Y_a;

	for (int i = 0; i < nKey; i++){
		CreatBox(30, yA, key[i], lenght);
		yA += 3;
	}
}
void GiaoDienThemLop(string key[], int nKey, int lenght){
		int yA = Y_a;
	for (int i = 0; i < nKey; i++){
		CreatBox(X_a + 20, yA, key[i], lenght);
		yA += 3;
	}
}
void TitleBangChon(string key[]){
	gotoxy(toadoxGiaoDien[0] + 20, Y_DISPLAY + 39);
	setColor(15, 6);
	cout <<  key[0];
	gotoxy(X_TITLE, Y_TITLE); cout << key[1];
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3);
	cout << "ESC : Thoat";
	setColor(11, 0);
}
void TitleBangChon1(string key[]){
	gotoxy(toadoxGiaoDien[0] + 30, Y_DISPLAY + 35);
	setColor(15, 6);
	cout <<  key[0];
	gotoxy(X_TITLE, Y_TITLE); cout << key[1];
	gotoxy(toadoxGiaoDien[0] + 100, Y_DISPLAY + 35);
	cout << "ESC: Tiep tuc chon lop tin chi";
	setColor(11, 0);
}

void DeleteMenuAdd()
{
	//system("color 5A");
	for (int i = 0; i < 20; i++)
	{
		gotoxy(X_a + 18, Y_a + i - 1);
		cout << setw(60) << setfill(' ') << " ";
	}
}

void DeleteOldData(int nKey, int locate)
{
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(toadoxGiaoDien[i] + 1, Y_DISPLAY + 3 + locate);
		cout << setw(toadoxGiaoDien[i] - toadoxGiaoDien[i]-2) << setfill(' ') << " ";		
	}
}

void DeleteNote(int nColumn)
{
	gotoxy(toadoxGiaoDien[0] + 1, Y_DISPLAY + 40);
	cout << setw(toadoxGiaoDien[nColumn] - toadoxGiaoDien[0] - 1) << " " << setfill(' ');
}

void DeleteNotify()
{
	gotoxy(X_ThongBao, Y_ThongBao);
	cout << setw(35) << setfill(' ') << " ";
	gotoxy(X_ThongBao - 5, Y_ThongBao + 1);
	cout << setw(40) << setfill(' ') << " ";
	gotoxy(X_ThongBao - 5, Y_ThongBao + 2);
	cout << setw(40) << setfill(' ') << " ";
	gotoxy(X_ThongBao - 5, Y_ThongBao + 3);
	cout << setw(33) << setfill(' ') << " ";
}

void Display0(string key[], int nKey, int range)
{
	int arrTemp[9];
	if (nKey != 5){
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien[i];
		}
	}
	else {
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien3[i];
		}
	}
	
	TextColor(14);
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(arrTemp[i], Y_DISPLAY+ 1);
		cout << key[i];
	}
	TextColor(11);
	
	for (int j = Y_DISPLAY; j <= Y_DISPLAY + range; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoxy(arrTemp[i] - 3, j);
			cout << char(179); // cot thang
		}
	}

	for (int i = arrTemp[0]; i <= arrTemp[nKey]; i++)
	{
		gotoxy(i - 3, Y_DISPLAY);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i == arrTemp[6])
		{
			cout << char(194);
		}
		else if (i == arrTemp[0])
		{
			cout << char(218); //moc phai
		}	
		else if (i == arrTemp[nKey])
		{
			cout << char(191);//moc trai
		}  
		else
		{
			cout << char(196); //duong thang ngang
		}
		
		gotoxy(i - 3, Y_DISPLAY + 2);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i == arrTemp[6])
			cout << char(197); //nga 4
		else if (i == arrTemp[0])
		{
			cout << char(195); //nga 3 sang phai
		}
		else if (i == arrTemp[nKey])
		{
			cout << char(180);//nga 3 sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i -3, Y_DISPLAY1 + range+1);
		if (i == arrTemp[nKey])
		{
			cout << char(217); //nga 3 sang trai
		}
		else if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i== arrTemp[6])
			cout << char(193);
		else if (i == arrTemp[0])
			cout << char(192); //nga 3 sang phai
		else
		{
			cout << char(196); //duong thang ngang
		}
	}
	
	if (nKey == 4)
	{
		gotoxy(arrTemp[4] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[4] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
	if (nKey == 5)
	{
		gotoxy(arrTemp[5] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[5] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
}

void Display(string key[], int nKey)
{
	int arrTemp[9];
	if (nKey != 5){
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien[i];
		}
	}
	else {
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien3[i];
		}
	}
	
	TextColor(14);
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(arrTemp[i], Y_DISPLAY+ 1);
		cout << key[i];
	}
	TextColor(11);
	
	for (int j = Y_DISPLAY; j <= Y_DISPLAY + 32; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoxy(arrTemp[i] - 3, j);
			cout << char(179); // cot thang
		}
	}

	for (int i = arrTemp[0]; i <= arrTemp[nKey]; i++)
	{
		gotoxy(i - 3, Y_DISPLAY);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i == arrTemp[6])
		{
			cout << char(194);
		}
		else if (i == arrTemp[0])
		{
			cout << char(218); //moc phai
		}	
		else if (i == arrTemp[nKey])
		{
			cout << char(191);//moc trai
		}  
		else
		{
			cout << char(196); //duong thang ngang
		}
		
		gotoxy(i - 3, Y_DISPLAY + 2);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i == arrTemp[6])
			cout << char(197); //nga 4
		else if (i == arrTemp[0])
		{
			cout << char(195); //nga 3 sang phai
		}
		else if (i == arrTemp[nKey])
		{
			cout << char(180);//nga 3 sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i -3, Y_DISPLAY + 33);
		if (i == arrTemp[nKey])
		{
			cout << char(217); //nga 3 sang trai
		}
		else if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i== arrTemp[6])
			cout << char(193);
		else if (i == arrTemp[0])
			cout << char(192); //nga 3 sang phai
		else
		{
			cout << char(196); //duong thang ngang
		}
	}
	
	if (nKey == 4)
	{
		gotoxy(arrTemp[4] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[4] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
	if (nKey == 5)
	{
		gotoxy(arrTemp[5] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[5] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
}

void Display1(string key[], int nKey)
{
	int arrTemp[8];
	if (nKey != 5){
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien1[i];
		}
	}
	else {
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien3[i];
		}
	}
	
	TextColor(14);
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(arrTemp[i], Y_DISPLAY+ 1);
		cout << key[i];
	}
	TextColor(11);
	
	for (int j = Y_DISPLAY; j <= Y_DISPLAY + 32; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoxy(arrTemp[i] - 3, j);
			cout << char(179); // cot thang
		}
	}

	for (int i = arrTemp[0]; i <= arrTemp[nKey]; i++)
	{
		gotoxy(i - 3, Y_DISPLAY);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i == arrTemp[6] )
		{
			cout << char(194);
		}
		else if (i == arrTemp[0])
		{
			cout << char(218); //moc phai
		}	
		else if (i == arrTemp[nKey])
		{
			cout << char(191);//moc trai
		}  
		else
		{
			cout << char(196); //duong thang ngang
		}
		
		gotoxy(i - 3, Y_DISPLAY + 2);
		if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i == arrTemp[6])
			cout << char(197); //nga 4
		else if (i == arrTemp[0])
		{
			cout << char(195); //nga 3 sang phai
		}
		else if (i == arrTemp[nKey])
		{
			cout << char(180);//nga 3 sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i -3, Y_DISPLAY + 33);
		if (i == arrTemp[nKey])
		{
			cout << char(217); //nga 3 sang trai
		}
		else if (i == arrTemp[1] || i == arrTemp[2] || i == arrTemp[3] || i == arrTemp[4] || i == arrTemp[5] || i== arrTemp[6] || i == arrTemp[7])
			cout << char(193);
		else if (i == arrTemp[0])
			cout << char(192); //nga 3 sang phai
		else
		{
			cout << char(196); //duong thang ngang
		}
	}
	
	if (nKey == 4)
	{
		gotoxy(arrTemp[4] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[4] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
	if (nKey == 5)
	{
		gotoxy(arrTemp[5] - 3, Y_DISPLAY);
		cout << char(191);
		gotoxy(arrTemp[5] - 3, Y_DISPLAY + 2);
		cout << char(180);
	}
	
}

void Display2(string key[], string key2[], int nKey)
{
	TextColor(14);
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(toadoxGiaoDien2[i], Y_DISPLAY + 6);
		cout << key[i];
	}
	TextColor(11);
	
	for (int j = Y_DISPLAY + 5; j <= Y_DISPLAY + 20; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoxy(toadoxGiaoDien2[i] - 3, j);
			cout << char(179); // cot thang
		}
	}
	
	TextColor(14);
	gotoxy(toadoxGiaoDien2[1], Y_DISPLAY + 8); cout << "SO HIEU MB";
	for (int i = 1; i < 6; i++)
	{
		gotoxy(toadoxGiaoDien2[1], Y_DISPLAY + 8 + i * 2);
		if (i == 5) 
			cout << "SO GHE TREN MB";
		else 
			cout << key2[i + 1];
	}
	TextColor(11);
	
	for (int i = toadoxGiaoDien2[0]; i <= toadoxGiaoDien2[nKey]; i++)
	{
		gotoxy(i - 3, Y_DISPLAY + 5);
		if (i == toadoxGiaoDien2[1])
			cout << char(194);//nga 3
		else if (i == toadoxGiaoDien2[0])
		{
			cout << char(218); //moc phai
		}
		else if (i == toadoxGiaoDien2[nKey])
		{
			cout << char(191);//moc trai
		}  
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i - 3, Y_DISPLAY + 7);
		if (i == toadoxGiaoDien2[1])
			cout << char(197); //nga 4
		else if (i == toadoxGiaoDien2[0])
		{
			cout << char(195); //nga 3 sang phai
		}
		else if (i == toadoxGiaoDien2[nKey])
		{
			cout << char(180);//nga 3 sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i - 3, Y_DISPLAY + 20);
		if (i == toadoxGiaoDien2[0])
		{
			cout << char(192); //queo sang phai
		}
		else if (i == toadoxGiaoDien2[1])
		{
			cout << char(193);
		}
		else if (i == toadoxGiaoDien2[nKey])
		{
			cout << char(217); //queo sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}
	}
}

void Display3(){
	TextColor(11);
	gotoxy(25, 14); cout << char(218); // moc phai
	for (int i = 0; i < 15; i++){
		gotoxy(26 + i, 14); cout << char(196); // thang ngang
	}
	cout << "THONG TIN";
	for (int i = 24; i < 39; i++){
		gotoxy(26 + i, 14); cout << char(196);
	}
	cout << char(191); // moc trai
	
	for (int i = 1; i < 12; i++){
		gotoxy(25, 14 + i); cout << char(179); // cot thang
		gotoxy(65, 14 + i); cout << char(179); // cot thang
	}
	
	TextColor(14);
	gotoxy(32, 17); cout << "VU HOANG VIET ANH";
	gotoxy(32, 19); cout << "N17DCCN006";
	gotoxy(45, 19); cout << "D17CQCN01 - N";
	TextColor(11);

	gotoxy(25, 26); cout << char(192);
	for (int i = 1; i < 40; i++){
		gotoxy(25 + i, 26); cout << char(196);
	}
	cout << char(217);
	
	TextColor(14);
	SetBGColor(3);
	gotoxy(30, 38); cout << "         ";
	gotoxy(30, 39); cout << "  ENTER  ";
	gotoxy(30, 40); cout << "         ";
	gotoxy(132, 38); cout << "         ";
	gotoxy(132, 39); cout << "   ECS   ";
	gotoxy(132, 40); cout << "         ";
	TextColor(11);
	SetBGColor(0);
}

void Display4(string key[], int nKey, int rangerow)
{
	int arrTemp[8];
	if (nKey != 5){
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien2[i];
		}
	}
	else {
		for (int i = 0; i <= nKey; i++){
			arrTemp[i] = toadoxGiaoDien3[i];
		}
	}
	
	TextColor(14);
	for (int i = 0; i < nKey; i++)
	{
		gotoxy(arrTemp[i], Y_DISPLAY1+ 1);
		cout << key[i];
	}
	TextColor(11);
	
	for (int j = Y_DISPLAY1; j <= Y_DISPLAY1 + rangerow; j++)
	{
		for (int i = 0; i < nKey + 1; i++)
		{
			gotoxy(arrTemp[i] - 3, j);
			cout << char(179); // cot thang
		}
	}

	for (int i = arrTemp[0]; i <= arrTemp[nKey]; i++)
	{
		gotoxy(i - 3, Y_DISPLAY1);
		if (i == arrTemp[1] )
		{
			cout << char(194);
		}
		else if (i == arrTemp[0])
		{
			cout << char(218); //moc phai
		}	
		else if (i == arrTemp[nKey])
		{
			cout << char(191);//moc trai
		}  
		else
		{
			cout << char(196); //duong thang ngang
		}
		
		gotoxy(i - 3, Y_DISPLAY1 + 2);
		if (i == arrTemp[1] )
			cout << char(197); //nga 4
		else if (i == arrTemp[0])
		{
			cout << char(195); //nga 3 sang phai
		}
		else if (i == arrTemp[nKey])
		{
			cout << char(180);//nga 3 sang trai
		}
		else
		{
			cout << char(196); //duong thang ngang
		}

		gotoxy(i -3, Y_DISPLAY1 + rangerow +1);
		if (i == arrTemp[nKey])
		{
			cout << char(217); //nga 3 sang trai
		}
		else if (i == arrTemp[1])
			cout << char(193);
		else if (i == arrTemp[0])
			cout << char(192); //nga 3 sang phai
		else
		{
			cout << char(196); //duong thang ngang
		}
	}
	
	if (nKey == 4)
	{
		gotoxy(arrTemp[4] - 3, Y_DISPLAY1);
		cout << char(191);
		gotoxy(arrTemp[4] - 3, Y_DISPLAY1 + 2);
		cout << char(180);
	}
	
	if (nKey == 5)
	{
		gotoxy(arrTemp[5] - 3, Y_DISPLAY1);
		cout << char(191);
		gotoxy(arrTemp[5] - 3, Y_DISPLAY1 + 2);
		cout << char(180);
	}
	
}

int ChooseMenu(string key[], int nKey)
{
	ShowCur(false);
	vitriHienTaiMenu = 0;
	vitriTruocDoMenu = 0;
	int keyboard = 0;
	while (true)
	{
		keyboard = getch();
		if (keyboard == 0)
			keyboard = getch();

		switch (keyboard)
		{
		case KEY_UP:
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] - 3, Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] + 2 + tpMenuChinh[vitriHienTaiMenu].length(), Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			if (vitriHienTaiMenu > 0)
				vitriHienTaiMenu = vitriHienTaiMenu - 1;
			else
				vitriHienTaiMenu = nKey - 1;
			ChuyenMauMenu(key, vitriHienTaiMenu);
			break;
		case KEY_DOWN:
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] - 3, Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			gotoxy(taodoxMenuChinh[vitriTruocDoMenu] + 2 + tpMenuChinh[vitriHienTaiMenu].length(), Y_MAIN + vitriHienTaiMenu * 2); cout << char(0);
			if (vitriHienTaiMenu < nKey - 1)
				vitriHienTaiMenu = vitriHienTaiMenu + 1;
			else
				vitriHienTaiMenu = 0;
			ChuyenMauMenu(key, vitriHienTaiMenu);
			break;
		case ESC:
			return -1;
			break;
		case ENTER:
			ShowCur(true);
			return vitriHienTaiMenu;
			break;
		}
	}
}
//=============================================================================//

//===================================Dinh dang=================================//
void Trim(char *s)
{
	int i = strlen(s) - 1;
	char *p = s;
	while (*p == ' ') p++;
	if (p != s) strcpy(s, p);
	while (s[i] == ' '  && i>0)
		i--;
	s[i + 1] = 0;
}
//=============================================================================//


//===================================Chuc nang==================================//

//=========================DOC/GHI FILE========================================//
//Mon hoc
void SaveMonHoc(ListSubject DSMH){
	fstream fileOut1("monhoc.txt", ios::out | ios::binary);
	for (int i = 0; i < DSMH.n; i++)
		fileOut1.write(reinterpret_cast<const char*>(DSMH.nodes[i]), sizeof(SUBJECT));

	fileOut1.close();
}
void LoadMonHoc(ListSubject &DSMH){
	fstream fileIn1("monhoc.txt", ios::in | ios::binary);
	while (!fileIn1.eof()) {
		DSMH.nodes[++DSMH.n] = new SUBJECT;
		fileIn1.read(reinterpret_cast<char*>(DSMH.nodes[DSMH.n]), sizeof(SUBJECT));
	}
	delete DSMH.nodes[DSMH.n];
	fileIn1.close();
}


//==============================================================================//



//===================================Lop tin chi======================================//
int SoLop;

//Khai bao ds lop
void Initialize(TREECLASS &root) { // khoi tao cay hanh khach
	SoLop = -1;
	root = NULL;
}
//
unsigned int SinhIDClass() {
	unsigned int r;
	srand((unsigned int)time(0));
	r = rand();
	return r;
}
//Tham lop hoc
void Insert_Lop(TREECLASS &t, Class lop) {
	if (t == NULL) { // cay rong
		NodeClass *point = new NodeClass; // khoi tao 1 node de them vao cay
		point->clAss = lop;
		point->left= NULL;
		point->right = NULL;
		t = point; // node point chinh la nut goc
		arrIdLop[++SoLop] = lop.idClass;
//		cout<<"themsfsdfsdf";
	}
	else { // cay co ton tai phan tu
		if (lop.idClass < t->clAss.idClass)
			Insert_Lop(t->left, lop);
		else if (lop.idClass > t->clAss.idClass)
			Insert_Lop(t->right, lop);
	}
}
//Search lop
NodeClass* FindClass(TREECLASS root, unsigned int idClass)
{
	if (root != NULL)
	{
		NodeClass* p = root;
		while (p != NULL)
		{
			if (p->clAss.idClass == idClass)
				return p;
			else if (p->clAss.idClass > idClass)
				p = p->left;
			else
				p = p->right;
		}
	}
	return NULL;
}


void TimNodeTheMang(TREECLASS &x, TREECLASS &y){
	if (y->left != NULL)
		TimNodeTheMang(x, y->left);// tìm node cuc trai cua cay y(t->right)
	else {//tim duôc node cuc trai thì cho node can xoa tro den node cuc trai, roi lien ket sao cho dung thu tu
		x->clAss = y->clAss;
		x = y; // cho node x tro den y de sau nay xoa
		y = y->right;
	}
}

bool Delete_Class(TREECLASS &t, Class lop){
	if (t == NULL) return false;
	else {
		if (lop.idClass > t->clAss.idClass)	
			Delete_Class(t->right, lop);
		else if (lop.idClass < t->clAss.idClass)
			Delete_Class(t->left, lop);
		else {
			NodeClass *temp = t;
			if (t->left == NULL)//th chi có cây con bên phai
				t = t->right;
			else if (t->right == NULL)//th chi co cây con bên trai
				t = t->left;
			else {//node co cay con o ca 2 phia
				TimNodeTheMang(temp, t->right);
			}
			delete temp;
			return true;
		}
	}
}
void Quick_Sort(int head, int tail, unsigned int a[]){
	int temp;
	int x = a[(head + tail) / 2];
	int i = head, j = tail;
	do {
		while (a[i] < x) i++;
		while (a[j] > x) j--;
		if(i <= j){
			if (i < j) {
				temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
			i++; j--;
		}
	} while(i <= j);
	if (head < j) Quick_Sort(head, j, a);
	if (tail > i) Quick_Sort(i, tail, a);
}
void XuatLop(Class lop, int locate){
	DeleteOldData(sizeof(tpGiaodienlopTC) / sizeof(string), locate);
	gotoxy(toadoxGiaoDien[0] + 1, Y_DISPLAY + 3 + locate); cout << lop.idClass;
	gotoxy(toadoxGiaoDien[1] + 1, Y_DISPLAY + 3 + locate); cout << lop.idSubject;
	gotoxy(toadoxGiaoDien[2] + 1, Y_DISPLAY + 3 + locate); cout << lop.schoolYear;
	gotoxy(toadoxGiaoDien[3] + 1, Y_DISPLAY + 3 + locate); cout << lop.numberSemester;
	gotoxy(toadoxGiaoDien[4] + 1, Y_DISPLAY + 3 + locate); cout << lop.idGroup;
	gotoxy(toadoxGiaoDien[5] + 1, Y_DISPLAY + 3 + locate); cout << lop.maxNumStudents;
	gotoxy(toadoxGiaoDien[6] + 1, Y_DISPLAY + 3 + locate); cout << lop.minNumStudents;
}
void XuatListClassTheoTungTrang(TREECLASS t, int thutuBatDau)
{
	for (int i = 0; i + thutuBatDau <= SoLop && i < SOLUONGMOITRANG; i++)
	{
		NodeClass* p = FindClass(t, arrIdLop[i + thutuBatDau]);
		XuatLop(p->clAss, i * 2);
	}
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "Trang " << trangHientaiHK << "/" << tongsoTrangHK;
}
void ThietLapMauChoTungDongLop(Class hk, int ThuTu)
{
	SetBGColor(7);
	XuatLop(hk, ThuTu % SOLUONGMOITRANG);
	SetBGColor(0);
}
void ChuyenDoiTungDongLop(int ThuTu, Class LopMoi, Class LopCu)
{
	int current = ThuTu;
	SetBGColor(7);
	XuatLop(LopMoi, (current % SOLUONGMOITRANG) * 2);
	SetBGColor(0);
	XuatLop(LopCu, (vitriTruocDoHK % SOLUONGMOITRANG) * 2);
	vitriTruocDoHK = current;
}

void ChuyenTrangLop(TREECLASS t)
{
	vitriHienTaiHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	vitriTruocDoHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	system("cls");
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY LOP TIN CHI ";
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
	Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
	DeleteNote(sizeof(tpGiaodienlopTC) / sizeof(string));
}

NodeClass* ChooseClass(TREECLASS &t)
{
	if (t == NULL) return NULL;
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	int PASS = 1;
	Quick_Sort(0, SoLop, arrIdLop);
	Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
	trangHientaiHK = 1;
	vitriHienTaiHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	vitriTruocDoHK = (trangHientaiHK - 1) * SOLUONGMOITRANG;
	NodeClass* newClass = FindClass(t, arrIdLop[0]);
	XuatListClassTheoTungTrang(t, 0);
	ThietLapMauChoTungDongLop(newClass->clAss, vitriHienTaiHK);
	NodeClass* oldClass = NULL;
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "trang " << trangHientaiHK << "/" << tongsoTrangHK;
	setColor(15, 6); 
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
	while (PASS)
	{
		keyboard_read = getch();
		if (keyboard_read == 0)
			keyboard_read = getch();
		switch (keyboard_read){
		case KEY_UP:
			if (vitriHienTaiHK % SOLUONGMOITRANG > 0)
			{
				vitriHienTaiHK = vitriHienTaiHK - 1;
				oldClass = newClass;
				newClass = FindClass(t, arrIdLop[vitriHienTaiHK]);
				ChuyenDoiTungDongLop(vitriHienTaiHK, newClass->clAss, oldClass->clAss);
			}
			break;
		case KEY_DOWN:
			if (vitriHienTaiHK % SOLUONGMOITRANG < SOLUONGMOITRANG - 1 && vitriHienTaiHK < SoLop)
			{
				vitriHienTaiHK = vitriHienTaiHK + 1;
				oldClass = newClass;
				newClass = FindClass(t, arrIdLop[vitriHienTaiHK]);
				ChuyenDoiTungDongLop(vitriHienTaiHK, newClass->clAss, oldClass->clAss);
			}
			break;
		case KEY_RIGHT:
			if (trangHientaiHK < tongsoTrangHK)
			{
				trangHientaiHK++;
				ChuyenTrangLop(t);
				newClass = FindClass(t, arrIdLop[vitriHienTaiHK]);
				oldClass = newClass;
				XuatListClassTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
				ThietLapMauChoTungDongLop(newClass->clAss, vitriHienTaiHK);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiHK > 1)
			{
				trangHientaiHK--;
				ChuyenTrangLop(t);
				newClass= FindClass(t, arrIdLop[vitriHienTaiHK]);
				oldClass = newClass;
				XuatListClassTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
				ThietLapMauChoTungDongLop(newClass->clAss, vitriHienTaiHK);
			}
			break;
		case ENTER:  //enter
			PASS = 0;
			ShowCur(true);
			return newClass;
			break;
		case ESC:
			ShowCur(true);
			return NULL;
			break;
		}
	}
}

void NhapHoacEditSo(int &result, bool &isMove, int &ordinal, bool &isSave, int doDaiChuoi, int condition)
{
	int length;
	if (result != 0)
		length = (int)log10(result) + 1;
	else length = 0;
	gotoxy(X_a + 20 + doDaiChuoi, ordinal * 3 + Y_a);
	if (result != 0)
	cout << result;
	int count = length;
	while (true)
	{
		while (kbhit())
		{
			int key = getch();
			if (key != 224 && key != SPACE && key != 0 )
			{
				if (key >= 48 && key <= 57)
				{
					int f = key - 48;
					if (count == 0 && key == 48)
						continue;
					else
						if (result * 10 + (f) <= condition)
						{
							cout << f;
							result = result * 10 + (f);
							count++;
						}
				}
				else if (key == ENTER)
				{
					if (result > condition)
						continue;
					return;
					
				}
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;
				}
			}
			else if (key == 224)
			{
				key = getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//while tru

}

void NhapHoacEditString(string &result, bool &isMove, int &ordinal, bool &isSave, int doDaiChuoi)
{
	int length = result.length();
	gotoxy(X_a + 20 + doDaiChuoi, ordinal * 3 + Y_a);
	cout << result;
	int count = length;
	bool isSpaced = false;
	while (true)
	{
		while (kbhit())
		{
			int key = getch();	
			if (key != 224  && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == SPACE || key >= 48 && key <= 57 || key == 45)
				{
					if (count < MAX_LENGTH)
					{
						count++;
						cout << (char)key;
						result += (char)key;
						isSpaced = false;
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1, 1);
					count--;
				}
			}
			else if (key == 224)
			{
				key = getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//true
}

// Tim kiem ma mon hoc
int SearchMH(ListSubject dsmh, char mamh[11])
{
	int vitri = -1;
	Trim(mamh);
	for (int i = 0; i <= dsmh.n; i++)
		if (strcmp(dsmh.nodes[i]->idSubject, mamh) == 0) vitri = i;
	return vitri;
}

//giao dien + thuat toan them lop hoc
void InputClass(TREECLASS &t, Class &lop , ListSubject &dsmh, bool daChinhSua = false){
	ShowCur(true);
	int TrinhTu = 0;
	bool isMoveUp = false;
	bool isSave = false;
	 int check=0;
	
	 int idClass = 0;
	char idSubject[11];
	string idSubjectSTR="";
	char schoolYear[10];
	string schoolYearSTR="";
	 int numberSemester=0;
	 int idGroup=0;
	 int maxNumStudents=0;
	 int minNumStudents=0;
	listRegister ListRegisters;
	bool DaCoID = false;
	gotoxy(X_ThongBao, Y_ThongBao + 1); cout << "F10. Luu";
	if (daChinhSua){
		idClass = lop.idClass;
		strcpy(idSubject,lop.idSubject);
		idSubjectSTR= lop.idSubject;
		strcpy(schoolYear,lop.schoolYear);
        schoolYearSTR=lop.schoolYear;
		numberSemester=lop.numberSemester;
		idGroup=lop.idGroup;
		maxNumStudents=lop.maxNumStudents;
		minNumStudents=lop.minNumStudents;
		
//		for(int i=0;i<sizeof(schoolYear);i++) cout << schoolYear[i];
		
		gotoxy(X_a + 40, 0 * 3 + Y_a); cout << idClass;
		gotoxy(X_a + 40, 1 * 3 + Y_a); cout << idSubjectSTR;	
		gotoxy(X_a + 40, 2 * 3 + Y_a); cout << schoolYearSTR;
		gotoxy(X_a + 40, 3 * 3 + Y_a); cout << numberSemester;
		gotoxy(X_a + 40, 4 * 3 + Y_a); cout << idGroup;
		gotoxy(X_a + 40, 5 * 3 + Y_a); cout << maxNumStudents;
		gotoxy(X_a + 40, 6 * 3 + Y_a); cout << minNumStudents;
	}
		
	if(!daChinhSua){
	idClass=SinhIDClass();
    gotoxy(X_a + 40, 0 * 3 + Y_a); cout << idClass;
	}						
	else {
	gotoxy(X_a + 40, 0 * 3 + Y_a); cout << idClass;	
	}
	
	while(true){
		switch(TrinhTu){
			case 0: {
				if (daChinhSua) break;
//				NhapHoacEditSo(idClass, isMoveUp, TrinhTu, isSave, 10, 10);
                if(FindClass(t, idClass) == NULL){
					DaCoID = false;
					break;
				}
				DaCoID = true;
				break;
			}
			case 1: {
				NhapHoacEditString(idSubjectSTR, isMoveUp, TrinhTu, isSave, 20);
				strcpy(idSubject,idSubjectSTR.c_str());
				check=SearchMH(dsmh,idSubject);				
				break;
			}
			case 2: {
				NhapHoacEditString(schoolYearSTR, isMoveUp, TrinhTu, isSave, 20);
				break;
			}
			case 3: {
				NhapHoacEditSo(numberSemester, isMoveUp, TrinhTu, isSave, 20, 3);
				break;
			}
			case 4: {
				NhapHoacEditSo(idGroup, isMoveUp, TrinhTu, isSave,20, 100);
				break;
			}
			case 5: {
				NhapHoacEditSo(maxNumStudents, isMoveUp, TrinhTu, isSave, 20, 1000);
				break;
			}
			case 6: {
				NhapHoacEditSo(minNumStudents, isMoveUp, TrinhTu, isSave, 20, 1);
				break;
			}
		}
			if (isMoveUp){
				if (TrinhTu == 0)
					isMoveUp = false;
				TrinhTu--;
			}
			else {
				if (TrinhTu == 6)
					isMoveUp = true;
				TrinhTu++;
			}
			if (isSave){
//				strcpy(idSubject,idSubjectSTR.c_str());
//				check=SearchMH(dsmh,idSubject);
//				if(check!=-1){
//			        gotoxy(X_ThongBao, Y_ThongBao);
//					cout<<"Ma mon hoc khong ton tai";
//				}
				
				gotoxy(X_ThongBao, Y_ThongBao); cout << setw(50) << setfill(' ') << " ";
				if (idSubjectSTR.empty() || schoolYearSTR.empty() || (int)log10(idClass) + 1 == 0 || (int)log10(idGroup) + 1 == 0 || (int)log10(numberSemester) + 1 == 0 ||
				   (int)log10(maxNumStudents) + 1 == 0 || (int)log10(minNumStudents) + 1 == 0) {
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "Phai dien day du thong tin. Khong duoc de trong !";
				}
				else if (DaCoID){
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "Ma lop hoc khong duoc trung!";
				}
				else if(check==-1){
			        gotoxy(X_ThongBao, Y_ThongBao);
					cout<<"Ma mon hoc khong ton tai";
				}
				else {
					lop.idClass=idClass;
					strcpy(lop.idSubject, idSubjectSTR.c_str());
					strcpy(lop.schoolYear, schoolYearSTR.c_str());
					lop.numberSemester = numberSemester;
					lop.idGroup = idGroup;
					lop.maxNumStudents = maxNumStudents;
					lop.minNumStudents = minNumStudents;
					
					if (daChinhSua) {
						NodeClass* p = FindClass(t, idClass);
						p->clAss = lop;
					}
					else
						Insert_Lop(t, lop);

					DeleteMenuAdd();
					gotoxy(X_ThongBao, Y_ThongBao + 1);
					cout << "						";
					return;
				}
				isSave = false;
		}
		else isSave = false;
	}
	ShowCur(false);
}


void GhiLopVaoFile(TREECLASS p, fstream &fileOut3, int size) {
	if (p != NULL) {
		fileOut3.write(reinterpret_cast<const char*>(&p->clAss), size);
		fileOut3.write(reinterpret_cast<const char*>(&p->clAss.listRegisters.n),sizeof(int));
		for(NODE_REGISTER *q=p->clAss.listRegisters.Head;q!=NULL;q=q->Next){
			int s=sizeof(q->IFRegister);
			fileOut3.write(reinterpret_cast<const char*>(&q->IFRegister),s);
		}
		GhiLopVaoFile(p->left, fileOut3, size);
		GhiLopVaoFile(p->right, fileOut3, size);
	}
}

void demSoLop(TREECLASS p,int &sl){
	if(p!=NULL){
		sl++;
		demSoLop(p->left,sl);
		demSoLop(p->right,sl);
	}
}

void SaveLopTC(TREECLASS point) {
	int sl=0;
	demSoLop(point,sl);
	fstream fileOut3("loptinchi.txt", ios::out | ios::binary);
	fileOut3.write(reinterpret_cast<const char*>(&sl), sizeof(int));

	int size = sizeof(Class);
	TREECLASS p = point;
	GhiLopVaoFile(p, fileOut3, size);
	fileOut3.close();
}

void Insert_after_dk(listRegister &dsdk, Register sv);
void ThemVaoDauListDK(listRegister &dsdk, Register data) ;

void Insert_First(listRegister &ds, Register sv)
{	
   NODE_REGISTER *p;
   p = new NODE_REGISTER;
   p->IFRegister = sv;
   p->Next = ds.Head;
   ds.Head = p;
//   ++ds.n;
}

void LoadLopTC(TREECLASS &t) {
	fstream fileIn3("loptinchi.txt", ios::in | ios::binary);
	int SoLH;
	Class lop;
	fileIn3.read(reinterpret_cast<char*>(&SoLH), sizeof(int));
//	cout<<SoLH;
	//fileIn3 >> SoHanhKhach;
	int size = sizeof(Class);
	for (int i = 0; i < SoLH; i++)
	{
		fileIn3.read(reinterpret_cast<char*>(&lop), size);
//		lop.listRegisters=new listRegister;
		
		fileIn3.read(reinterpret_cast<char*>(&lop.listRegisters.n), 4);
		
//		cout<<endl<<lop.listRegisters.n<<endl;
		
		
//		cout<<"debug3";
		lop.listRegisters.Head=NULL;
		for(int j=0;j<lop.listRegisters.n;j++){
			int s=sizeof(Register);
			Register r;
			fileIn3.read(reinterpret_cast<char*>(&r),s);
//			cout<<"debug1";
			Insert_First(lop.listRegisters,r);
//			cout<<"debug2";
		}
		Insert_Lop(t, lop);
	}
}



//Menu lop tin chi
void MenuDSLop(TREECLASS &t , ListSubject &dsmh)
{
    ShowCur(false);
backMenu: 
	tongsoTrangHK = SoLop / SOLUONGMOITRANG + 1;
	trangHientaiHK = 1;
	Quick_Sort(0, SoLop, arrIdLop);
	
	XuatListClassTheoTungTrang(t, 0);
	Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
	setColor(15, 6);
	gotoxy(toadoxGiaoDien[0] + 20, Y_DISPLAY + 39);
	cout << " F2: Them F3: Huy F4: Hieu Chinh";
	gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY LOP TIN CHI ";
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
	int key;
	while(true){
		while(kbhit()){
			gotoxy(X_PAGE, Y_PAGE - 2);
			cout << "Trang " << trangHientaiHK << "/" << tongsoTrangHK;
			key = getch();
			if (key == 0 || key == 224)
			{
				key = getch();
				gotoxy(X_ThongBao, Y_ThongBao);
				cout << setw(35) << setfill(' ') << " ";
				if (key == KEY_F2) //f2
				{
					Class lop;
					gotoxy(20, Y_DISPLAY + 39); cout << setw(150) << " ";
					GiaoDienChinhSua(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string), 35);
					InputClass(t, lop, dsmh, false);
					tongsoTrangHK = SoLop / SOLUONGMOITRANG + 1;
					trangHientaiHK = 1;
					system("cls");
					Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
					XuatListClassTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "Them thanh cong !";
					TitleBangChon(tpMucLucLop);
				}
				else if (key == KEY_F3) {// F3
					system("cls");
					setColor(15, 6);
					gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY LOP TIN CHI ";
					setColor(11, 0);
					NodeClass* b = ChooseClass(t);
					if (b == NULL) goto backMenu;
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Enter neu chac chan xoa !";
					key = getch();
					if (key == ENTER){
						system("cls");
						Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
						int idClass= b->clAss.idClass;
						for (int i = 0; i <= SoLop; i++)
						{
							if (arrIdLop[i] == idClass)
							{
								for (int j = i; j < SoLop; j++)
									arrIdLop[j] = arrIdLop[j + 1];
								SoLop--;
								break;
							}
						}
						if (Delete_Class(t, b->clAss)){
							XuatListClassTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
							gotoxy(X_ThongBao, Y_ThongBao);
							cout << "Xoa thanh cong !";
							TitleBangChon(tpMucLucLop);
						}
					}
					else goto backMenu;
				}
				else if (key == KEY_F4){
					gotoxy(20, Y_DISPLAY + 39); cout << setw(150) << " ";
					NodeClass* b = ChooseClass(t);
					if (b == NULL) goto backMenu;
					GiaoDienChinhSua(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string), 35);
					InputClass(t, b->clAss, dsmh, true);
					system("cls");
					XuatListClassTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Sua thanh cong !";
					TitleBangChon(tpMucLucLop);
				}
				else if (key == KEY_RIGHT && trangHientaiHK < tongsoTrangHK)
				{
					system("cls");
					trangHientaiHK++;
					XuatListClassTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
					TitleBangChon(tpMucLucLop);
				}
				else if (key == KEY_LEFT && trangHientaiHK > 1)
				{
					system("cls");
					trangHientaiHK--;
					XuatListClassTheoTungTrang(t, (trangHientaiHK - 1) * SOLUONGMOITRANG);
					Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
					TitleBangChon(tpMucLucLop);
				}
			}
			else if (key == ESC)
//			    SaveLopTC(t);
				return;
		}
	}
}
//==========================Sinh vien lop hoc=============================//

NODE_STUDENT* taoNodeStudent(Student data) {
	NODE_STUDENT *p = new nodeStudent;
	if (p == NULL) return NULL;	
	p->IFStudent = data; // gan gia tri cho node
	p->Next = NULL; // cho next tro toi NULL (init danh sach lien ket)
	return p;
}

void InitListStudent(listStudent &sv) {
	sv.Head = sv.Tail = NULL;
}

bool ListStudent_Empty(listStudent sv) { // kiem tra ds sinh vien co rong hay khong
	return sv.Head == NULL;
}

void ThemVaoDauList(listStudent &sv, Student data) {
	NODE_STUDENT *p = taoNodeStudent(data);//d
	
	if (sv.Head == NULL)
		sv.Head = sv.Tail = p; // nut dau cung la nut cuoi
	else{
	    p->Next = sv.Head;
	    sv.Head = p;
    }
	++sv.n;
}

void ThemVaoCuoiList(listStudent &dssv, Student data) {
	NODE_STUDENT *p = taoNodeStudent(data);
//	if (dssv.Head == NULL)
//		dssv.Head = dssv.Tail = p; // nut dau cung la nut cuoi
//	else {
		dssv.Tail->Next = p;
		dssv.Tail = p;
//	}
	++dssv.n;
}


void Insert_after(listStudent &dssv, Student sv)
{
    NODE_STUDENT *p=taoNodeStudent(sv);
    if(dssv.n==0){
       dssv.Head=dssv.Tail=p;
	}
	else{
		for(NODE_STUDENT *k=dssv.Tail; ;k=k->Next){
			if(k->Next==NULL){
				k->Next=p;
				break;
			}
		}
	}
	++dssv.n;
}

void ThemSauNode(listStudent &dssv,NODE_STUDENT *p ,Student sv){
	NODE_STUDENT *q;
   if(p == NULL)
		printf("khong them sinh vien vao danh sach duoc");
   else
   {
      q = taoNodeStudent(sv);
      for(NODE_STUDENT *k=dssv.Head;k!=NULL;k=k->Next){
      	if(strcmp(k->IFStudent.idStudent,p->IFStudent.idStudent)==0 && strcmp(k->IFStudent.idClass,p->IFStudent.idClass)==0){
      		q->Next=k->Next;
      		k->Next=q;
      		++dssv.n;
      		break;
		}
	  }
   }

}

void Insert_Order(listStudent &dssv, Student sv)
{
   NODE_STUDENT *p, *q;  // q la nut truoc, p la nut sau
   q = NULL;
   char mlsv[29]="";
   char mlsv1[29]="";strcat(mlsv1,sv.idClass); strcat(mlsv1,sv.idStudent);
	p=dssv.Head;
	while(p!=NULL){
		strcat(mlsv,p->IFStudent.idClass); strcat(mlsv,p->IFStudent.idStudent); 		
		if(strcmp(mlsv1,mlsv)>0){
		   	q = p;
		}
		p=p->Next;
		strcpy(mlsv,"");
	}
    if(q == NULL)  // them nut vao dau danh sach lien ket
    {	
	  ThemVaoDauList(dssv, sv);
	}
    else           // them nut vao sau nut q
    {	
	  ThemSauNode(dssv, q, sv);
	}
}

//void Clearlist(NODE_STUDENT &First)
//{  
//   NODE_STUDENT p;  
//  while(First != NULL)
//   {
//      p = First;
//      First = First->next;
//      delete p;
//   }
//}


NODE_STUDENT* FindStudent (listStudent sv, char *id){
	if (sv.Head == NULL) return NULL;
	for (NODE_STUDENT* p = sv.Head; p != NULL; p = p->Next)
		if (stricmp(p->IFStudent.idStudent, id) == 0)
			return p;
	return NULL;
}

int arrSTTSinhVien[20];
int arrSoVe[20];
int SoSV;


void XuatStudent(Student sv, int locate){
    gotoxy(toadoxGiaoDien1[0] -1, Y_DISPLAY + 3 + locate); cout << sv.idStudent;
	gotoxy(toadoxGiaoDien1[1] , Y_DISPLAY + 3 + locate); cout << sv.lastName;
	gotoxy(toadoxGiaoDien1[2] , Y_DISPLAY + 3 + locate); cout<< sv.firstName; 
	
	gotoxy(toadoxGiaoDien1[3] +1, Y_DISPLAY + 3 + locate);
		switch(sv.gender){
		case 1: 
		    cout << "Nam";
			break;
		case 2: cout << "Nu";
			break;
		default:
			break;
	}
	gotoxy(toadoxGiaoDien1[4], Y_DISPLAY + 3 + locate); cout<<sv.numberPhone;
	gotoxy(toadoxGiaoDien1[5] -1, Y_DISPLAY + 3 + locate); cout<<sv.idClass;
	gotoxy(toadoxGiaoDien1[6]+5 , Y_DISPLAY + 3 + locate); cout<<sv.yearStudy;
}

void XuatListSVTheoTungTrang(listStudent sv, int firstOrdinal){
	if (sv.Head == NULL && sv.Tail == NULL) return;
	int count = -1;
	for (NODE_STUDENT* p = sv.Head; p != NULL; p = p->Next){
		count++;
		if (count == firstOrdinal){
			int i = -1;
			while (p != NULL && i < SOLUONGMOITRANG - 1){
				XuatStudent(p->IFStudent, (++i) * 2);
				p = p->Next;
			}
			break;
		}
	}
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "Trang" << trangHientaiCB << "/" << tongsoTrangSVLopHoc;
	return;
}

bool Delete_Head(listStudent &sv){
	if (ListStudent_Empty(sv)) return false;
	NODE_STUDENT* p = sv.Head;
	sv.Head = p->Next;
	delete p;
	--sv.n;
	return true;
}

bool Delete_Tail(listStudent &sv)
{
		if (ListStudent_Empty(sv)) return false;
		for (NODE_STUDENT *p = sv.Head; p != NULL; p = p->Next)
		{
			if (p->Next == sv.Tail)
			{
				delete sv.Tail;
				p->Next = NULL;
				sv.Tail = p;
				--sv.n;
				return true;
			}
		}
}

bool Delete_After(listStudent &sv, NODE_STUDENT* p)
{
	if (p == NULL || p->Next == NULL) return false;
	NODE_STUDENT* q = p->Next;
	p->Next = q->Next;
	delete q;
	--sv.n;
	return true;
}

bool DeleteStudent_Id(listStudent &sv, Student data)
{
	NODE_STUDENT* p = FindStudent(sv, data.idStudent);
	if (p == NULL) return false;
	if (p == sv.Head) return Delete_Head(sv);
	if (p == sv.Tail) return Delete_Tail(sv);
	else
	{
		NODE_STUDENT* q = sv.Head;
		while (q->Next != p)
			q = q->Next;
		return Delete_After(sv, q);
	}
}

int SV_Empty(listStudent dssv)
{
	int result=0;
   if(dssv.n == 0)
   {
		result=1;
   }
   return result;
}


NODE_STUDENT* FindStudentTheoThuTu(listStudent sv, int ThuTu){
	if (sv.Head == NULL) return NULL;
	if (sv.n - 1 < ThuTu) return NULL;
	if (sv.n - 1 == ThuTu) return sv.Tail;
	if (ThuTu == 0) return sv.Head;
	NODE_STUDENT *p = sv.Head;
	int count = 0;
	while (count != ThuTu){
		p = p->Next;
		count++;
	}
	return p;
}

void XuatIDSV(listStudent sv, int firstOrdinal){
	int temp = -1;
	for (int i = firstOrdinal; i < SoSV; i++){ // gia tri cua SoSV co duoc sau khi goi ham FindFlightTheoCMND
		temp++;
		if (temp < SOLUONGMOITRANG2) {
			NODE_STUDENT* p = FindStudentTheoThuTu(sv, arrSTTSinhVien[i]);
			gotoxy(toadoxGiaoDien2[0] + 1, Y_DISPLAY + 8 + temp * 2);
			cout << p->IFStudent.idStudent;
		}
	}
}



void ThietLapMauChoTungDong(Student sv, int ThuTu) // thiet lap thanh sáng màu cho tung` dong` cua dssv
{
	SetBGColor(7);
	XuatStudent(sv, (ThuTu % SOLUONGMOITRANG) * 2);
	SetBGColor(0);
}

void ChuyenDoiTungDongSV(int ThuTu, Student SVMoi, Student SVCu) // chuyen thanh sáng lên hay xuông' 
{
	int current = ThuTu;
	ThietLapMauChoTungDong(SVMoi, current);
	XuatStudent(SVCu, (vitriTruocDoCB % SOLUONGMOITRANG) * 2);
	vitriTruocDoCB = current;
}

void ChuyenTrangChonSV(listStudent dssv)
{
	system("cls");
	Display1(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string));
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	TitleBangChon(tpMucLucSV);
}

NODE_STUDENT* ChooseStudent(listStudent dssv)
{
	int keyboard_read = 0;
	ShowCur(false);
	trangHientaiCB = 1;
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	tongsoTrangSVLopHoc = ((dssv.n - 1) / SOLUONGMOITRANG) + 1;
	
	NODE_STUDENT* newNodeStudent = FindStudentTheoThuTu(dssv, vitriHienTaiCB);
	NODE_STUDENT* oldNodeStudent = NULL;
	
	XuatListSVTheoTungTrang(dssv, (trangHientaiCB - 1) * SOLUONGMOITRANG);
	ThietLapMauChoTungDong(newNodeStudent->IFStudent, vitriHienTaiCB);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (vitriHienTaiCB % SOLUONGMOITRANG > 0)
			{
				vitriHienTaiCB = vitriHienTaiCB - 1;
				oldNodeStudent = newNodeStudent;
				for (newNodeStudent = dssv.Head; newNodeStudent->Next != oldNodeStudent; newNodeStudent = newNodeStudent->Next);
				ChuyenDoiTungDongSV(vitriHienTaiCB, newNodeStudent->IFStudent, oldNodeStudent->IFStudent);
			}
			break;
		case KEY_DOWN:
			if (vitriHienTaiCB % SOLUONGMOITRANG < SOLUONGMOITRANG - 1 && newNodeStudent->Next != NULL) 
			{
				vitriHienTaiCB = vitriHienTaiCB + 1;
				oldNodeStudent = newNodeStudent;
				newNodeStudent = newNodeStudent->Next;
				ChuyenDoiTungDongSV(vitriHienTaiCB, newNodeStudent->IFStudent, oldNodeStudent->IFStudent);
			}
			break;
		
		case KEY_RIGHT:
			if (trangHientaiCB < tongsoTrangSVLopHoc)
			{
				trangHientaiCB++;
				ChuyenTrangChonSV(dssv);
				XuatListSVTheoTungTrang(dssv, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeStudent = FindStudentTheoThuTu(dssv, vitriHienTaiCB);
				ThietLapMauChoTungDong(newNodeStudent->IFStudent, vitriHienTaiCB);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiCB > 1)
			{
				trangHientaiCB--;	
				ChuyenTrangChonSV(dssv);
				XuatListSVTheoTungTrang(dssv, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeStudent = FindStudentTheoThuTu(dssv, vitriHienTaiCB);
				ThietLapMauChoTungDong(newNodeStudent->IFStudent, vitriHienTaiCB);
			}
			break;
		case ENTER:  //enter
			ShowCur(true);
			return newNodeStudent;
			break;
		case ESC: 
			return NULL; 
			break;
		}//end switch  read key
	}
}

void InputSV(listStudent &dssv, Student &sv, char malh[16], bool IsNewClass, bool ChinhSua = false){
	ShowCur(true);
	int TrinhTu = 0;
	bool isMoveUp = false;
	bool isSave = false;
	 int check=0;
	
	char idStudent[13];
	string idStudentSTR="";
	 string lastName="";
	 string firstName="";
	int gender;
	int numberPhone;
	char idClass[16];
	strcpy(idClass,malh);
	string idClassSTR="";
	int yearStudy;
	
	bool DaTrungID = false;
	gotoxy(X_ThongBao, Y_ThongBao + 1); cout << "F10. Luu";
	
	if (ChinhSua){
		strcpy(idStudent,sv.idStudent);
	    lastName=sv.lastName;
	    firstName=sv.firstName;
		gender=sv.gender;
		numberPhone=sv.numberPhone;
		strcpy(idClass,sv.idClass);
		yearStudy=sv.yearStudy;
		
		
		gotoxy(X_a + 40, 0 * 3 + Y_a); cout << idStudent;
		gotoxy(X_a + 40, 1 * 3 + Y_a); cout << lastName;	
		gotoxy(X_a + 40, 2 * 3 + Y_a); cout << firstName;
		gotoxy(X_a + 40, 3 * 3 + Y_a); cout << gender;
		gotoxy(X_a + 40, 4 * 3 + Y_a); cout << numberPhone;
		gotoxy(X_a + 40, 5 * 3 + Y_a); cout << idClass;
		gotoxy(X_a + 40, 6 * 3 + Y_a); cout << yearStudy;
	}		
	else {
		gotoxy(X_a + 40, 5 * 3 + Y_a); cout << idClass;
	}
	while(true){
		switch(TrinhTu){
			case 0: {
				idStudentSTR=sv.idStudent;
				NhapHoacEditString(idStudentSTR, isMoveUp, TrinhTu, isSave, 20);
//				strcpy(idStudent,idStudentSTR.c_str());
				
				if(idStudentSTR.empty() && IsNewClass == false){
					return;
				}
                if( FindStudent(dssv, (char*)idStudentSTR.c_str()) == NULL){
					DaTrungID = false;
					break;
				}
				else if( ChinhSua && FindStudent(dssv, (char*)idStudentSTR.c_str()) != NULL){
					DaTrungID = false;
				}
				else {
					DaTrungID=true;
				}
				break;
			}
			case 1: {
				NhapHoacEditString(lastName, isMoveUp, TrinhTu, isSave, 20);
				break;
			}
			case 2: {
				NhapHoacEditString(firstName, isMoveUp, TrinhTu, isSave, 20);
				break;
			}
			case 3: {
				NhapHoacEditSo(gender, isMoveUp, TrinhTu, isSave, 20, 2);
				break;
			}
			case 4: {
				NhapHoacEditSo(numberPhone, isMoveUp, TrinhTu, isSave,20, 9999999999);
				break;
			}
//			case 5: {
////				gotoxy(X_a + 40, 5 * 3 + Y_a); cout << idClass;
/////				NhapHoacEditString(idClassSTR, isMoveUp, TrinhTu, isSave, 20, 1000);
//				break;
//			}
			case 6: {
				NhapHoacEditSo(yearStudy, isMoveUp, TrinhTu, isSave, 20, 9999);
				break;
			}
		}
		
			if (isMoveUp){
				if (TrinhTu == 0)
					isMoveUp = false;
				TrinhTu--;
			}
			else {
				if (TrinhTu == 6)
					isMoveUp = true;
				TrinhTu++;
			}
		
			if (isSave){			
				gotoxy(X_ThongBao, Y_ThongBao); cout << setw(50) << setfill(' ') << " ";			
				if ( lastName.empty() || firstName.empty() ||(int)log10(gender) + 1 == 0 || (int)log10(numberPhone) + 1 == 0 || (int)log10(yearStudy) + 1 == 0 )
				{
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "Phai dien day du thong tin. Khong duoc de trong!";
				}
				else if (DaTrungID){
					gotoxy(X_ThongBao, Y_ThongBao);
					cout << "Ma sinh vien khong duoc trung!";
				}
				else {					
					if (ChinhSua) {// thong tin chinh sua vao node giong node damh chinh sua
						if(strcmp(idStudentSTR.c_str(),idStudent)==0){//truong hop khong sua id sv
							strcpy(sv.idStudent, idStudentSTR.c_str());												
							sv.lastName=lastName;
							sv.firstName=firstName;
							sv.gender=gender;
							sv.numberPhone=numberPhone;
							strcpy(sv.idClass,malh);
							sv.yearStudy=yearStudy;
							NODE_STUDENT* p = FindStudent(dssv, idStudent);
							p->IFStudent = sv;
						}
						else{	//truong hop sua id sv
							strcpy(sv.idStudent, idStudent);//Copy id sv cu vao bien "sv" 										
							if(DeleteStudent_Id(dssv, sv)){ // xoa sv co id cu
								strcpy(sv.idStudent, idStudentSTR.c_str());	//copy cac tt cua sv moi vao bien "sv" 											
								sv.lastName=lastName;
								sv.firstName=firstName;
								sv.gender=gender;
								sv.numberPhone=numberPhone;
								strcpy(sv.idClass,malh);
								sv.yearStudy=yearStudy;
								
								//Them sv vao dssv giu nguyen thu tu
								Insert_Order(dssv,sv);
							}							
						}
					}
					else 
					{
//					    ThemSVThuTu(dssv,sv);
//						ThemSVCoThuTu(dssv,sv);
					    Insert_Order(dssv,sv);//them co thu tu
                    }						
					tongsoTrangSVLopHoc = ((dssv.n - 1) / SOLUONGMOITRANG) + 1;
				    DeleteMenuAdd();
					return;
				}
				isSave = false;
		}
		else isSave = false;
	}
	ShowCur(false);
}

void SaveSinhVien(listStudent dssv) {
	int sizeStudent = sizeof(Student);
	fstream fileOut2("sinhvien.txt", ios::out | ios::binary);
	fileOut2.write(reinterpret_cast<const char*>(&dssv.n), sizeof(int));
	NODE_STUDENT* p = dssv.Head;
	while(p != NULL){
		fileOut2.write(reinterpret_cast<const char*>(&p->IFStudent), sizeStudent);
		p = p->Next;
	}
	fileOut2.close();
}

void LoadSinhVien(listStudent &dssv) {
	int sizeStudent = sizeof(Student);
	int SoSinhVien;
	fstream fileIn2("sinhvien.txt", ios::in | ios::binary);
	InitListStudent(dssv);
	fileIn2.read(reinterpret_cast<char*>(&SoSinhVien), sizeof(int));
	Student p;
	for (int i = 0; i < SoSinhVien; ++i) {
		fileIn2.read(reinterpret_cast<char*>(&p), sizeStudent);
//		ThemVaoDauList(dssv, p);
//        ThemVaoCuoiList(dssv, p);
    Insert_after(dssv,p);
	}
	fileIn2.close();
}

void LoadSV(listStudent &dssv){
	ifstream infile;
	string data;
	int n;
	Student sv;
	infile.open("sinhvien1.txt",ios::in);
	if(!infile) {
		gotoxy(X_ThongBao,Y_ThongBao);
		cout<<"Khong mo duoc file";
		return;
	}
	infile>>n;
	for(int i=0;i<n;i++){
		infile>>data; strcpy(sv.idStudent,data.c_str());
		infile>>sv.lastName;
		infile>>sv.firstName;
		infile>>sv.gender;
		infile>>sv.numberPhone;
		infile>>data; strcpy(sv.idClass,data.c_str());
		infile>>sv.yearStudy;
		//		ThemVaoDauList(dssv,sv);
//		ThemVaoCuoiList(dssv, sv);
	    Insert_after(dssv,sv);	
//		ThemSVCoThuTu(dssv,sv);
//		Insert_Order(dssv,sv);
		infile.ignore();
	}
	infile.close();
}

void SaveSV(listStudent &dssv){
	ofstream outFile;
	outFile.open("sinhvien1.txt",ios::out);
	outFile<<dssv.n<<endl;
	for(NODE_STUDENT *k=dssv.Head; k!=NULL; k=k->Next){
		outFile<<k->IFStudent.idStudent<<endl;
		outFile<<k->IFStudent.lastName<<endl;
		outFile<<k->IFStudent.firstName<<endl;
		outFile<<k->IFStudent.gender<<endl;
		outFile<<k->IFStudent.numberPhone<<endl;
		outFile<<k->IFStudent.idClass<<endl;
		outFile<<k->IFStudent.yearStudy<<endl;	
//		ThemVaoDauList(dssv,sv);
//		ThemVaoCuoiList(dssv, sv);
//	    Insert_after(dssv,sv);
	}	
	outFile.close();
}

void ChuyenTrangQLySV(listStudent dssv){
	system("cls");
	setColor(15, 3);
	gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY SINH VIEN LOP HOC";
	setColor(11, 0);
	XuatListSVTheoTungTrang(dssv, (trangHientaiCB - 1) * SOLUONGMOITRANG);
	Display1(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string));
	TitleBangChon(tpMucLucSV);
}
listStudent CapNhatDSSVHienThi(listStudent &dssv, char malh[16]){
		//Khai bao danh sach sinh vien tam
	listStudent dssvTemp;
	//Quet dssv chinh, dua pt co idclass giong da nhap va dssv tam
	for(NODE_STUDENT *k=dssv.Head;k!=NULL;k=k->Next){
		if(strcmp(k->IFStudent.idClass,malh)==0){
			Insert_after(dssvTemp,k->IFStudent);
		}
	}
	return dssvTemp;
}

void ThemSVLopHoc(listStudent &dssv, char malh[16], bool IsNewClass){
	ShowCur(false);
backMenu:
	system("cls");	  									
	gotoxy(X_TITLE+10, Y_TITLE); cout << "DANH SACH SINH VIEN";
	setColor(14, 0);
	Display1(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string));	
				
	gotoxy(toadoxGiaoDien[0] + 20, Y_DISPLAY + 39);
	setColor(15, 6);
	cout <<  " F2: Them F3: Huy F4: Hieu Chinh F5: Xoa F10: Save ";
	gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "ESC : thoat";
	setColor(11, 0);
		
	trangHientaiCB = 1;
//	tongsoTrangSVLopHoc = ((dssvTemp.n - 1) / SOLUONGMOITRANG) + 1;
//	XuatListSVTheoTungTrang(dssvTemp, 0);

	tongsoTrangSVLopHoc = ((CapNhatDSSVHienThi(dssv,malh).n - 1) / SOLUONGMOITRANG) + 1;
	if(!IsNewClass){
		XuatListSVTheoTungTrang(CapNhatDSSVHienThi(dssv,malh), 0);
	}
	setColor(11, 0);
	int key;
	while(true){
		while(kbhit()){
			key = getch();
			if (key == 0 || key == 224){
				key = getch();
				if (key == KEY_F2){  // F2
					Student sv;
					strcpy(sv.idStudent,"");
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					GiaoDienChinhSua(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string), 35);
					gotoxy(X_ThongBao + 30, Y_ThongBao + 3); cout << "           ";
					InputSV(dssv,sv,malh,IsNewClass,false);
//					tongsoTrangSVLopHoc = ((dssvTemp.n - 1) / SOLUONGMOITRANG) + 1;//luu y
//					ChuyenTrangQLySV(dssvTemp);//luu y
					
					tongsoTrangSVLopHoc = ((CapNhatDSSVHienThi(dssv,malh).n - 1) / SOLUONGMOITRANG) + 1;//luu y
					ChuyenTrangQLySV(CapNhatDSSVHienThi(dssv,malh));//luu y
					
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Them thanh cong !";
					DeleteNotify();
					ShowCur(false);
					system("pause");								
				}
				
				else if (key == KEY_F3){ // F3: huy. dieu kien xoa mot hoc sinh la khi khong dang ky mot mon hoc nao

				}
				
				else if (key == KEY_F4){
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					NODE_STUDENT* nsv=ChooseStudent(CapNhatDSSVHienThi(dssv,malh));
					GiaoDienChinhSua(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string), 35);
					InputSV(dssv,nsv->IFStudent,malh,IsNewClass,true);
					system("cls");
					Display1(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string));
					
					
					XuatListSVTheoTungTrang(CapNhatDSSVHienThi(dssv,malh), (trangHientaiCB - 1) * SOLUONGMOITRANG);//luu y
					
					TitleBangChon(tpMucLucSV);
					DeleteNotify();
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Sua thanh cong !";
				}
				
				else if (key == KEY_F5){ // F5:xoa
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					NODE_STUDENT* nsv = ChooseStudent(CapNhatDSSVHienThi(dssv,malh));
					if (nsv == NULL) goto backMenu;
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Enter neu chac chan xoa !";
					key = getch();
					if (key == ENTER){
						if (DeleteStudent_Id(dssv, nsv->IFStudent)){
							tongsoTrangSVLopHoc = ((CapNhatDSSVHienThi(dssv,malh).n - 1) / SOLUONGMOITRANG) + 1;
							if (CapNhatDSSVHienThi(dssv,malh).n % SOLUONGMOITRANG == 0) trangHientaiCB--;
							ChuyenTrangQLySV(CapNhatDSSVHienThi(dssv,malh));
							TitleBangChon(tpMucLucSV);
							gotoxy(X_ThongBao, Y_ThongBao); cout << "Xoa thanh cong !";
							DeleteNotify();
						}
					}
					else goto backMenu;
				}
				
				else if (key == KEY_RIGHT && trangHientaiCB < tongsoTrangSVLopHoc){
					trangHientaiCB++;
//					ChuyenTrangQLySV(dssvTemp);//luu y
					
					ChuyenTrangQLySV(CapNhatDSSVHienThi(dssv,malh));//luu y
					
				}
				
				else if (key == KEY_LEFT && trangHientaiCB > 1){
					trangHientaiCB--;
					ChuyenTrangQLySV(CapNhatDSSVHienThi(dssv,malh));//luu y
				}
			}
			else if (key == ESC)
					return;
		}
	}
}

void XemDSSVLopHoc(listStudent &dssv, char malh[16]){
	ShowCur(false);
	system("cls");	  									
	gotoxy(X_TITLE+10, Y_TITLE); cout << "DANH SACH SINH VIEN";
	setColor(14, 0);
	Display1(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string));	
				
		
	trangHientaiCB = 1;
	tongsoTrangSVLopHoc = ((CapNhatDSSVHienThi(dssv,malh).n - 1) / SOLUONGMOITRANG) + 1;
	XuatListSVTheoTungTrang(CapNhatDSSVHienThi(dssv,malh), 0);

	int key;
	while(true){
		while(kbhit()){
			key = getch();
			if (key == 0 || key == 224){
				if (key == KEY_RIGHT && trangHientaiCB < tongsoTrangSVLopHoc){
					trangHientaiCB++;
					ChuyenTrangQLySV(CapNhatDSSVHienThi(dssv,malh));
				}
					
				else if (key == KEY_LEFT && trangHientaiCB > 1){
					trangHientaiCB--;
					ChuyenTrangQLySV(CapNhatDSSVHienThi(dssv,malh));
				}
			}
			else if (key == ESC)
					return;
		}
	}
}

int CheckOldIdclass(listStudent dssv, char malh[16]){
	int result=1;
	NODE_STUDENT* k=dssv.Head;
	while(k!=NULL)
	{
//		MALHSTR=k->IFStudent.idClass;
		if(strcmp(k->IFStudent.idClass,malh)==0){
			result=2;
			break;
		}
		k=k->Next;
	}
	return result;
}

void MenuThemSinhVien(listStudent &dssv, string malhSTR, bool IsNewClass){
	char malh[16];
	strcpy(malh,malhSTR.c_str());
    ShowCur(false);
	int flag = 0;
	do
	{
	system("cls");
	VeKhungCH(20,0,70,15,1);
	gotoxy(35,1);
	setColor(6,0);
	cout<<"============ CHUC NANG ===========";
	
	gotoxy (30,6);
	setColor(2,0);
	cout<<"1. Quan ly sinh vien lop "+malhSTR;
	gotoxy(30,8);
	cout<<"2. Xem danh sach sinh vien lop "+malhSTR;
	gotoxy(30,10);
	cout<<"3. Thoat";
		
//	gotoxy(30,18);	
//	if(SV_Empty(dssv)==1)cout<<"DSSV rong";
	
	setColor(3,0);
		int a = KhungChon(30,6,50,3);
		switch (a)
		{
			case 1:
			{
				ThemSVLopHoc(dssv, malh, IsNewClass);
//				SaveSinhVien(dssv);
				SaveSV(dssv);
				break;
			}
			case 2:
			{
				XemDSSVLopHoc(dssv,malh);
				break;
			}
			case 3:
			{
				SaveSV(dssv);
				flag = 1;
				break;
			}
		}
	int key=getch();
	if(key==ESC) return;
	}
	while (flag == 0);
}

void MenuQlySinhVien(listStudent &dssv){	
	
	char malh[16];
	string malhSTR, MALHSTR;				
	int flag = 0;	
	do
	{
	system("cls");
	VeKhungCH(20,0,70,15,1);
	gotoxy(25,1);
	setColor(6,0);
	cout<<"============ CHUC NANG QUAN LY SINH VIEN LOP HOC ===========";
	
	gotoxy (30,6);
	setColor(2,0);
	cout<<"1. Them danh sach sinh vien vao lop hoc moi";
	gotoxy(30,8);
	cout<<"2. Quan ly danh sach sinh vien lop hoc da ton tai";
	gotoxy(30,10);
	cout<<"3. Xem danh sach sinh vien toan truong";
	gotoxy(30,12);
	cout<<"4. Thoat";
	
	setColor(6, 0);
	gotoxy(30,4);
	cout<<"NHAP MA LOP HOC: ";
	ShowCur(true);
	cin.getline(malh,16);	

	malhSTR=malh;
//	cout<<malh<<endl;
		
	
	ShowCur(false);
	setColor(3,0);
		int a = KhungChon(30,6,49,4);
		switch (a)
		{
			case 1:
			{
//				Funtion kiem tra co nhap dung ma lop
				if(CheckOldIdclass(dssv,malh) == 2){
					gotoxy(100,5);
					cout<<"CAN PHAI LA MA LOP HOC MOI"<<endl;
					gotoxy(100,6);
					system("pause");
				}
				else if(CheckOldIdclass(dssv,malh) == 1){
					MenuThemSinhVien(dssv,malh,true);
				}
				break;
			}
			case 2:
			{ 	
				if(CheckOldIdclass(dssv,malh) == 2){
					MenuThemSinhVien(dssv,malh,false);
				}
				else if(CheckOldIdclass(dssv,malh) == 1){
					gotoxy(100,5);
					cout<<"CAN PHAI LA MA LOP HOC DA TON TAI"<<endl;
					gotoxy(100,6);
					system("pause");
				}
				break;
			}
			case 3:
			{
				ShowCur(false);
				system("cls");	  									
				gotoxy(X_TITLE+10, Y_TITLE); cout << "DANH SACH SINH VIEN";
				setColor(14, 0);
				Display1(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string));	
							
					
				trangHientaiCB = 1;
				tongsoTrangSVLopHoc = ((dssv.n - 1) / SOLUONGMOITRANG) + 1;
				XuatListSVTheoTungTrang(dssv, 0);
				
				int key;
				while(true){
					while(kbhit()){
						key = getch();
						if (key == 0 || key == 224){
							if (key == KEY_RIGHT && trangHientaiCB < tongsoTrangSVLopHoc){
								trangHientaiCB++;
								ChuyenTrangQLySV(dssv);
							}
								
							else if (key == KEY_LEFT && trangHientaiCB > 1){
								trangHientaiCB--;
								ChuyenTrangQLySV(dssv);
							}
						}
						else if (key == ESC)
								return;
					}
				}
				break;
			}
			case 4:
			{				
				flag = 1;
				break;
			}
		}
	int key=getch();
	if(key==ESC) return;
	}while (flag == 0);	
		
	ShowCur(true);
}

//==================================================================//

//==============================Mon hoc==============================//


bool SearchMH2(ListSubject dsmh, char mamh[11])
{
	int vitri = -1;
	Trim(mamh);
	for (int i = 0; i <= dsmh.n; i++)
		if (stricmp(dsmh.nodes[i]->idSubject, mamh) == 0) vitri = i;
	return vitri>=0;
}
//
//Xuat mon hoc
void XuatMH(ListSubject MH, int vitri, int toadoy)
{
	TextColor(11);
	gotoxy(9,toadoy) ; cout<<vitri+1;
	gotoxy(16,toadoy); cout<<MH.nodes[vitri]->idSubject;
	gotoxy(27,toadoy); cout<<MH.nodes[vitri]->nameSubject;
	gotoxy(56,toadoy); cout<<MH.nodes[vitri]->numTheoryCredits;
	gotoxy(72,toadoy); cout<<MH.nodes[vitri]->numPracticeCredits;
}
//xuat mon hoc kieu gioi han trang
void XuatDSMHB(ListSubject mh, int vitriDautien)//vtdt=0
{
	int temp = -1, SOLUONGMOITRANGMB = 20;
	for (int i = vitriDautien; i < mh.n; i++)
	{
		temp++;
		if (temp < SOLUONGMOITRANGMB)
			XuatMH(mh, i, 5 + temp);
	}
}
//Ve bang mon hoc
void KhungXuatMH()
{
	TextColor(6);
	gotoxy(20,1);
	cout<<"<============ DANH SACH MON HOC ============>";
	TextColor(9);
	gotoxy(7,3);
	cout<<"STT";
	gotoxy(13,3);
	cout<<"MA MON HOC";
	gotoxy(30,3);
	cout<<"TEN MON HOC";
	gotoxy(50,3);
	cout<<"SO TC LY THUYET";
	gotoxy(66,3);
	cout<<"SO TC THUC HANH";
	
	VeKhungCH(5,2,77,23,1);
	for (int i = 3;i<26;i++)
	{
		gotoxy(11,i);
		cout<<char (179);
		gotoxy(25,i);
		cout<<char (179);
		gotoxy(49,i);
		cout<<char (179);
		gotoxy(65,i);
		cout<<char (179);
	}
	gotoxy(6,4);
	for (int i = 1; i< 77;i++)
	cout<<char(196);
	
	//nga ba huong xuong
	gotoxy(11,2);	cout<<char (194);
	gotoxy(25,2);	cout<<char (194);
	gotoxy(49,2);	cout<<char (194);
	gotoxy(65,2);	cout<<char (194);
	//nga tu
	gotoxy(11,4);	cout<<char (197);
	gotoxy(25,4);	cout<<char (197);
	gotoxy(49,4);	cout<<char (197);
	gotoxy(65,4);	cout<<char (197);
	//nga ba huong len
	gotoxy(11,25);	cout<<char (193);
	gotoxy(25,25);	cout<<char (193);
	gotoxy(49,25);	cout<<char (193);
	gotoxy(65,25);	cout<<char (193);
	
	gotoxy(5,4);
	cout<<char (195);
	gotoxy(82,4);
	cout<<char (180); //nga ba sang trai
	Normal();
}
//
//Chon + thanh sang mon hoc
int PickMH(ListSubject dsmh)
{
	system("cls");
	TextColor(11);
	int vitriHienTai = 0; // dieu kien de khoi bi sai moi khi UP hay DOWN
	int trangHienTai = 1;
	int keyboard;
	int choice = 0;
	int k = 0;
	int toadoy = 5;
	int SOLUONGMOITRANGMH = 20;
	int tongsoTrang;
	KhungXuatMH();
	TextColor(11);
//	gotoxy(80,26); cout<<"ESC: thoat";
	Normal();
	XuatDSMHB(dsmh, vitriHienTai);
	SetBGColor(8);
	XuatMH(dsmh,0,toadoy);
	SetBGColor(0);
	VeKhungCH(89,19,35,6,1);
	setColor(3,0);
	gotoxy(90,21); cout<<" RIGHT/LEFT de sang trang KE/SAU ";
	gotoxy(90,22); cout<<" ENTER de chon                   ";
	gotoxy(90,23); cout<<" ESC de thoat                    ";
	Normal();
	while (true) {
	//	while(kbhit()){
			tongsoTrang = ((dsmh.n - 1) / SOLUONGMOITRANGMH) + 1;
			keyboard = getch();
			if (keyboard == 0) keyboard = getch();
			switch (keyboard) 
			{
				case KEY_UP: 
				{
					if (vitriHienTai > 0)
					{
						SetBGColor(0);
				    	XuatMH(dsmh,choice,toadoy);
				    	vitriHienTai--; choice--; toadoy--;
						SetBGColor(8);
						XuatMH(dsmh,choice,toadoy);
				    	SetBGColor(0);
				    }
				    break;
			    }
			    case KEY_DOWN: 
				{
					if (vitriHienTai < SOLUONGMOITRANGMH - 1 && (choice < dsmh.n-1) ) // dieu kien thu 2 de ngan khong cho xuong hang
					{
						SetBGColor(0);																	
					    XuatMH(dsmh,choice,toadoy);
					    vitriHienTai++; choice++; toadoy++;
					    SetBGColor(8);
						XuatMH(dsmh,choice,toadoy);
						SetBGColor(0);
					}
					break;
				}
				case KEY_RIGHT:
				{
				if (trangHienTai < tongsoTrang)
					{
						XoaManHinh();
						KhungXuatMH();
						trangHienTai++;
						vitriHienTai = 0;
						toadoy = 5;
						choice = (trangHienTai - 1) * SOLUONGMOITRANGMH;
						XuatDSMHB(dsmh, choice);
						SetBGColor(8);
						XuatMH(dsmh,choice,toadoy);
						SetBGColor(0);
					}
					break;
				}
				case KEY_LEFT: 
				{
					if (trangHienTai > 1)
						{
							XoaManHinh();
							KhungXuatMH();
							trangHienTai--;
							vitriHienTai = 0;
							toadoy = 5;
							choice = (trangHienTai - 1) * SOLUONGMOITRANGMH;
							XuatDSMHB(dsmh, choice);
							SetBGColor(8);
							XuatMH(dsmh,choice,toadoy);
							SetBGColor(0);
						}
					break;
				}
				case ENTER: 
				{
					SetBGColor(0);
				    XuatMH(dsmh,choice,toadoy);
				    VeKhungCH(89,19,35,6,0);
					gotoxy(90,21); cout<<"                                  ";
					gotoxy(90,22); cout<<"                                  ";
					gotoxy(90,23); cout<<"                                  ";
					Normal();
					return choice;
					break;
				}
				
				case ESC: 
				{
				SetBGColor(0);
				XuatMH(dsmh,choice,toadoy);
				VeKhungCH(89,19,35,6,0);
				gotoxy(90,21); cout<<"                                  ";
				gotoxy(90,22); cout<<"                                  ";
				gotoxy(90,23); cout<<"                                  ";
				Normal();
				return -1;
				break;
				}
			}
		}
//	}
}
//

//1.Them mon hoc
void AddDSMH(ListSubject &DSMH)
{	
	char keyboard;
	do
	{
		XoaManHinhAddMH();
		TextColor(11);
	//Nhap ma mon hoc
		gotoxy(2,3);
		cout<<"1.Nhap ma mon hoc: ";
		DSMH.nodes[DSMH.n] = new SUBJECT;
		fflush(stdin);
		
		
		char mamh[11];
		cin.getline(mamh,11);
		Trim(mamh);
		int Check;
			do
			{
				Check = SearchMH(DSMH,mamh);
				if (Check != -1)
				{
					VeKhungCH(89,19,27,3,1);
					setColor(14,0);			
					gotoxy(90,20); cout<<"MA MON HOC DA DUOC SU DUNG";
					gotoxy(90,21); cout<<"       Moi dat lai      ";
					gotoxy(21,3);cout<<"                 ";
					gotoxy(21,3);ShowCur(1);
					cin.getline(mamh,11);
					VeKhungCH(89,19,27,4,0);
					gotoxy(90,20); cout<<"                             ";
					gotoxy(90,21); cout<<"                             ";
					gotoxy(90,22); cout<<"                             ";
					Normal();
				}	
			}while (Check != -1);
		strcpy(DSMH.nodes[DSMH.n]->idSubject,mamh);
	
	//Nhap ten mh
		char tenmh[100];
		gotoxy(2,5);
		cout<<"2.Nhap ten mon hoc: ";
		cin.getline(tenmh,100);
		strcpy(DSMH.nodes[DSMH.n]->nameSubject,tenmh);
		
	//Nhap so tin chi ly thuyet
		float stclt ;
		gotoxy(2,7);
		cout<<"3.Nhap so tin chi ly thuyet: ";
		cin>>stclt;
		while (stclt<0)
		{
			gotoxy(17,27);
			cout<<"So cho tin chi lon hon 0";
			gotoxy(17,28);
			cout<<"Nhan phim bat ky der tiep tuc";
			keyboard=getch();
			gotoxy(17,27);
			cout<<"                                        ";
			gotoxy(17,28);
			cout<<"                              ";
			gotoxy(15,4);
			cout<<"    ";
			gotoxy(15,4);
			cin>>stclt;
		}
		DSMH.nodes[DSMH.n]->numTheoryCredits=stclt;
		
	//Nhap so tin chi thuc hanh
		float stcth ;
		gotoxy(2,9);
		cout<<"4.Nhap so tin chi thuc hanh: ";
		cin>>stcth;
		while (stcth<0)
		{
			gotoxy(17,27);
			cout<<"So cho tin chi lon hon 0";
			gotoxy(17,28);
			cout<<"Nhan phim bat ky de tiep tuc";
			keyboard=getch();
			gotoxy(17,27);
			cout<<"                                        ";
			gotoxy(17,28);
			cout<<"                              ";
			gotoxy(15,4);
			cout<<"    ";
			gotoxy(15,4);
			cin>>stclt;
		}
		DSMH.nodes[DSMH.n]->numPracticeCredits=stcth;

		DSMH.n++;
		gotoxy(20,27);
		cout<<"Thanh cong!! Nhan phim bat ky de tiep tuc";
		gotoxy(20,28);
		cout<<"Nhan ESC de thoat";
		keyboard=getch();
	}
	while (keyboard != ESC);
}
//2.Xoa mon hoc
void DeleteMH(ListSubject &dsmh){
	int keyboard;
	int trangHienTai = 1;
	int SOLUONGMOITRANGMB = 20;
	do
	{
		fflush(stdin);
		int k = PickMH(dsmh);
		if (k != -1)
		{
		int flag = 1;
			if (flag == 1)
			{
				setColor(239,77);
				gotoxy(79,12); cout <<"Ban co muon xoa mon hoc nay?"; 
				gotoxy(98,15); cout <<"Enter de xac nhan"; 
				setColor(3,0);
				int getkytu;
				getkytu = getch();
				gotoxy(79,12); cout <<"                                                           "; 
				gotoxy(98,15); cout <<"                "; 
				if (getkytu == ENTER)
				{ 
					for (int i = k; i < dsmh.n; i++)
					{
						dsmh.nodes[i]=dsmh.nodes[i+1];
					}
					dsmh.n--;
					
					system("cls");
					KhungXuatMH();
					XuatDSMHB(dsmh, (trangHienTai - 1) * SOLUONGMOITRANGMB);
					setColor(3,0);
					gotoxy(79,22); cout <<" Xoa thanh cong !!! ";
					gotoxy(79,23); cout <<" Nhan phim bat ky de tiep tuc "; 
					gotoxy(79,24); cout <<" ESC de thoat       ";  
					Normal();
					keyboard = getch();
				}
			}
//			else 
//			{
//				gotoxy(79,22); cout <<"May bay dang co chuyen bay ";
//				gotoxy(79,23); cout <<"      Khong the xoa"; 
//				getch();
//			}
		}
		else (keyboard = ESC);
	}
	while (keyboard != ESC);
	
	
}
//
//3.Hieu chinh
void EditDSMH (ListSubject &dsmh) //
{	
	int keyboard,Temp;	
	int SOLUONGMOITRANGMB = 20;
	int tongsoTrang = ((dsmh.n - 1) / SOLUONGMOITRANGMB) + 1;
	int toadox[5] = {9,16,27,56,72};
	int toadoy;
	int k;
	do
	{
			int flag=0;
			int chonlua=1;
			k = PickMH(dsmh);
			if (k != -1)
			{
				TextColor(14);
				gotoxy(80,26); cout<<"ESC: thoat";
				Normal();	
				int trangHienTai = (k/SOLUONGMOITRANGMB)+1;
				if (trangHienTai >=2) toadoy = (k - ((trangHienTai*2 - 2)*10)) + 5;
				else toadoy = k+5;
				SetBGColor(8);
				gotoxy(toadox[chonlua],toadoy);
				cout<<dsmh.nodes[k]->idSubject;
				SetBGColor(0);
				do
				{
					keyboard = getch();
					VeKhungCH(89,19,25,3,0);
					gotoxy(91,20); cout<<"                    ";	
					gotoxy(91,21); cout<<"                    ";
					if (keyboard == 0) keyboard = getch();
					switch (keyboard) 
					{
					case KEY_RIGHT:	if ( chonlua < 4)
					{
							if (chonlua == 1)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->idSubject;
								chonlua++;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->nameSubject;
								Normal();
								
							}
							else if ( chonlua == 2)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->nameSubject;
								chonlua++;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->numTheoryCredits;
								Normal();
							}
							else if ( chonlua == 3)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->numTheoryCredits;
								chonlua++;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->numPracticeCredits;
								Normal();
							}
					}
					break;
					case KEY_LEFT:if ( chonlua > 1)
					{
							if ( chonlua == 2)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->nameSubject;
								chonlua--;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->idSubject;
								Normal();
							}
							else if ( chonlua == 3)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->numTheoryCredits;
								chonlua--;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->nameSubject;
								Normal();
							}
							else if ( chonlua == 4)
							{
								SetBGColor(0);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->numPracticeCredits;
								chonlua--;
								SetBGColor(8);
								gotoxy(toadox[chonlua],toadoy);
								cout<<dsmh.nodes[k]->numTheoryCredits;
								Normal();
							}
					}
					break;
					case ENTER:
					{							
						switch(chonlua)
						{
						case 1:
						{
							char Temp[11];
							char b[11];
							fflush(stdin);
							strcpy(Temp,dsmh.nodes[k]->idSubject);
							gotoxy(toadox[chonlua],toadoy);
							cout<<"       ";
							gotoxy(toadox[chonlua],toadoy);
							cin.getline(b,11);
							Trim(b);
							int Check;
							do
							{
								Check = SearchMH(dsmh,b);
								if (Check != -1)
								{
									VeKhungCH(89,19,25,3,1);
									setColor(14,0);			
									gotoxy(90,20); cout<<"MA MON HOC DA DUOC SU DUNG ";
									gotoxy(90,21); cout<<"       Moi dat lai      ";
									Normal();
									gotoxy(toadox[chonlua],toadoy);
									cout<<"       ";
									gotoxy(toadox[chonlua],toadoy);
									ShowCur(1);
									cin.getline(b,15);
									VeKhungCH(89,19,25,4,0);
									ShowCur(0);
									gotoxy(90,21); cout<<"                             ";
									gotoxy(90,22); cout<<"                             ";
									gotoxy(90,23); cout<<"                             ";
									Normal();
								}	
							}
							while (Check != -1);
							strcpy(dsmh.nodes[k]->idSubject,b);	
							VeKhungCH(89,19,31,3,1);
							gotoxy(90,20); cout<<" Chinh sua thanh cong   ";	
							gotoxy(90,21); cout<<" Nhan phim bat ky de tiep tuc sua";
							break;
						}
						case 2:
						{
							
							char b[100];
							fflush(stdin);
							gotoxy(toadox[chonlua],toadoy);
							cout<<"              ";
							gotoxy(toadox[chonlua],toadoy);
							ShowCur(1);
							cin.getline(b,100);
							strcpy(dsmh.nodes[k]->nameSubject,b);	
							VeKhungCH(89,19,31,3,1);
							ShowCur(0);
							gotoxy(90,20); cout<<" Chinh sua thanh cong   ";	
							gotoxy(90,21); cout<<" Nhan phim bat ky de tiep tuc";
							break;
							
								
						}
						case 3:
						{
						int flag = 0;
						if (flag == 1)
						{
							float a;
							gotoxy(toadox[chonlua],toadoy);
							cout<<"      ";
							gotoxy(toadox[chonlua],toadoy);
							cin>>a;
							while (a<0)
							{
								VeKhungCH(89,19,25,3,1);
								setColor(14,0);			
								gotoxy(90,20); cout<<" SO TC PHAI LON HON 0 ";
								Normal();
								gotoxy(toadox[chonlua],toadoy);
								cout<<"     ";
								gotoxy(toadox[chonlua],toadoy);
								cin>>a;
								VeKhungCH(89,19,25,3,0);
								gotoxy(90,21); cout<<"                         ";
								Normal();
							}
							dsmh.nodes[k]->numTheoryCredits=a;							
							VeKhungCH(89,19,25,3,1);
							gotoxy(90,20); cout<<" Chinh sua thanh cong   ";	
							gotoxy(90,21); cout<<" Nhan phim bat ky de tiep tuc ";
							break;
						}
						}
						
						case 4:
							{
								float a;
							gotoxy(toadox[chonlua],toadoy);
							cout<<"      ";
							gotoxy(toadox[chonlua],toadoy);
							cin>>a;
							while (a<0)
							{
								VeKhungCH(89,19,25,3,1);
								setColor(14,0);			
								gotoxy(90,20); cout<<" SO TC PHAI LON HON 0 ";
								Normal();
								gotoxy(toadox[chonlua],toadoy);
								cout<<"     ";
								gotoxy(toadox[chonlua],toadoy);
								cin>>a;
								VeKhungCH(89,19,25,3,0);
								gotoxy(90,21); cout<<"                              ";
								Normal();
							}
							dsmh.nodes[k]->numPracticeCredits=a;							
							VeKhungCH(89,19,25,3,1);
							gotoxy(90,20); cout<<" Chinh sua thanh cong   ";	
							gotoxy(90,21); cout<<" Nhan phim bat ky de tiep tuc ";
							break;
							}
						
						
						break;
						}
					break;
			    	}
					case ESC: 
						flag=1;
						break;
					}
				}while (flag == 0);
		}
	}
	while (k != -1);
}
//
// Sap xep mon hoc theo ten
ListSubject SortMH(ListSubject dsmh, ListSubject temp){	
	for(int i=0;i<dsmh.n-1;i++){
		for(int j=i+1;j<dsmh.n;j++){
			if(strcmp(dsmh.nodes[i]->nameSubject,dsmh.nodes[j]->nameSubject)>0){
				SUBJECT *tam=dsmh.nodes[i];
				dsmh.nodes[i]=dsmh.nodes[j];
				dsmh.nodes[j]=tam;
			}	
		}			
	}
	temp=dsmh;
	return temp;
}
//
//4.Xem danh sach mon hoc theo thu tu ten mon hoc
void XuatDSMH(ListSubject dsmh)
{
	ShowCur(false);
	system("cls");
	TextColor(11);
	int vitriHienTai = 0; // dieu kien de khoi bi sai moi khi UP hay DOWN
	int trangHienTai = 1;
	int keyboard;
	int choice = 0;
	int SOLUONGMOITRANGMB = 20;
	int tongsoTrang;
	KhungXuatMH();
	TextColor(11);
	Normal();
	ListSubject temp;
	dsmh=SortMH(dsmh,temp);
	XuatDSMHB(dsmh, vitriHienTai);
	VeKhungCH(89,20,35,5,1);
	setColor(3,0);
	gotoxy(90,22); cout<<" RIGHT/LEFT de sang trang KE/TRUOC";
	gotoxy(90,23); cout<<" ESC de thoat                     ";
	Normal();
	while (true) { // lap vo tan
		while(kbhit()){
			tongsoTrang = ((dsmh.n - 1) / SOLUONGMOITRANGMB) + 1;
			keyboard = getch();
			if (keyboard == 0) keyboard = getch();
			switch (keyboard) 
			{
				case KEY_RIGHT:
				{
				if (trangHienTai < tongsoTrang)
					{
						XoaManHinh();
						KhungXuatMH();
						trangHienTai++;
						vitriHienTai = 0;
						choice = (trangHienTai - 1) * SOLUONGMOITRANGMB;
						XuatDSMHB(dsmh, choice);
					}
					break;
				}
				case KEY_LEFT: 
				{
					if (trangHienTai > 1)
						{
							XoaManHinh();
							KhungXuatMH();
							trangHienTai--;
							vitriHienTai = 0;
							choice = (trangHienTai - 1) * SOLUONGMOITRANGMB;
							XuatDSMHB(dsmh, choice);
						}
					break;
				}
				case ESC: 
				{
				gotoxy(90,21); cout<<"                                  ";
				gotoxy(90,22); cout<<"                                  ";
				gotoxy(90,23); cout<<"                                  ";
				Normal();
				return ;
				break;
				}
			}
		}
	}
	ShowCur(true);
}
//
//Xoa toan bo mon hoc
void clearMH(ListSubject &dsmh){
	dsmh.n=0;
}
//
//Menu mon hoc
void MenuMonHoc(ListSubject &dsmh){
ShowCur(false);
	int flag = 0;
	do
	{
	system("cls");
	VeKhungCH(0,0,61,29,1);
	gotoxy(10,1);
	setColor(6,0);
	cout<<"============ DANH SACH MON HOC ===========";
	
	gotoxy (85,0);
	cout <<"MENU";
	gotoxy (70,2);
	setColor(2,0);
	cout<<"1. Them mon hoc vao danh sach";
	gotoxy(70,4);
	cout<<"2. Xoa mon hoc khoi danh sach";
	gotoxy(70,6);
	cout<<"3. Hieu chinh thong tin mon hoc";
	gotoxy(70,8);
	cout<<"4. Xem danh sach mon hoc";
	gotoxy(70,10);
	cout<<"5. Thoat";
//	gotoxy(70,12);
//	cout<<"6. Xoa toan bo danh sach";
	setColor(3,0);
		int a = KhungChon(70,2,35,5);
		switch (a)
		{
			case 1:
			{
				AddDSMH(dsmh);
				SaveMonHoc(dsmh);
				break;
			}
			case 2:
			{
				DeleteMH(dsmh);
				SaveMonHoc(dsmh);
				break;
			}
			case 3:
			{
				EditDSMH(dsmh);
                SaveMonHoc(dsmh);
				break;	
			}
			case 4:
			{
				
				XuatDSMH(dsmh);
				TextColor(14);
				break;
			}
			case 5:
			{
				SaveMonHoc(dsmh);
				flag = 1;
				break;
			}
		}
	}
	while (flag == 0);
	ShowCur(true);
}
//======================================================================================//

//============================Dang ky lop tin chi=======================================//


//===========================DSSV dang ky============================//
NODE_REGISTER* taoNodeRegister(Register data) {
	NODE_REGISTER *p = new NODE_REGISTER;
	if (p == NULL) return NULL;	
	p->IFRegister = data; // gan gia tri cho node
	p->Next = NULL; // cho next tro toi NULL (init danh sach lien ket)
	return p;
}

void InitListRegister(listRegister &dsdk) {
	dsdk.Head = dsdk.Tail = NULL;
}

bool ListRegister_Empty(listRegister dsdk) { // kiem tra ds sinh vien dk co rong hay khong
	return dsdk.Head == NULL;
}

void ThemVaoDauListDK(listRegister &dsdk, Register data) {
	
	NODE_REGISTER *p = taoNodeRegister(data);
	
	if (dsdk.Head == NULL)
		dsdk.Head = dsdk.Tail = p; // nut dau cung la nut cuoi
	else{
	    p->Next = dsdk.Head;
	    dsdk.Head = p;
    }
    
	++dsdk.n;
}

void ThemVaoCuoiListDK(listRegister &dsdk, Register data) {
	NODE_REGISTER *p = taoNodeRegister(data);
		dsdk.Tail->Next = p;
		dsdk.Tail = p;
	++dsdk.n;
}

	int z=10;
void Insert_after_dk(listRegister &dsdk, Register sv)
{
    NODE_REGISTER *p=taoNodeRegister(sv);
    if(dsdk.n==0){
       dsdk.Head=dsdk.Tail=p;
	}
	else{
		for(NODE_REGISTER *k=dsdk.Tail; ;k=k->Next){
			if(k->Next==NULL){
				k->Next=p;
				dsdk.Tail=p;
				break;
			}
		}
	}
	++dsdk.n;

//	gotoxy(X_ThongBao, Y_ThongBao+(z++)); cout<<"Them thanh cong";
//	cout<<z<<endl;
//	system("pause");
}



void ThemSauNodeDK(listRegister &dsdk, NODE_REGISTER *p, Register sv){
	NODE_REGISTER *q;
   if(p == NULL)
		printf("khong them sinh vien vao danh sach duoc");
   else
   {
      q = taoNodeRegister(sv);
      for(NODE_REGISTER *k=dsdk.Head;k!=NULL;k=k->Next){
      	if(strcmp(k->IFRegister.idStudent, p->IFRegister.idStudent)==0){
      		q->Next=k->Next;
      		k->Next=q;
      		++dsdk.n;
      		break;
		}
	  }
   }

}

void Insert_Order_DK(listRegister &dsdk, Register sv)
{
   NODE_REGISTER *p, *q;  // q la nut truoc, p la nut sau
   q = NULL;
	p=dsdk.Head;
	while(p!=NULL){ 		
		if(strcmp(sv.idStudent,p->IFRegister.idStudent)>0){
		   	q = p;
		}
		p=p->Next;
	}
    if(q == NULL)  // them nut vao dau danh sach lien ket
    {	
	  ThemVaoDauListDK(dsdk, sv);
	  int i=10;
	  gotoxy(X_ThongBao, Y_ThongBao+(i++));cout<<"                     ";
	  gotoxy(X_ThongBao, Y_ThongBao+(i++));cout<<"Them dau thanh cong";
	}
    else           // them nut vao sau nut q
    {	
	  ThemSauNodeDK(dsdk, q, sv);
	  int i=10;
	  gotoxy(X_ThongBao, Y_ThongBao+(i++));cout<<"                     ";
	  gotoxy(X_ThongBao, Y_ThongBao+(i++));cout<<"Them order thanh cong";
	}
}

NODE_REGISTER* FindStudentDK(listRegister sv, char *id){
	if (sv.Head == NULL) return NULL;
	for (NODE_REGISTER* p = sv.Head; p != NULL; p = p->Next)
		if (stricmp(p->IFRegister.idStudent, id) == 0)
			return p;
	return NULL;
}

int arrSTTSinhVienDK[20];
int SoSVDK;


void XuatStudentDK(Register sv, int locate){
    gotoxy(toadoxGiaoDien1[0] -1, Y_DISPLAY + 3 + locate); cout << sv.idStudent;
	gotoxy(toadoxGiaoDien1[1] , Y_DISPLAY + 3 + locate); cout << sv.point;
}

void XuatStudentDK1(Register sv, Student s,int locate, int count){
    gotoxy(toadoxGiaoDien1[0] -1, Y_DISPLAY + 3 + locate); cout<<count;
    gotoxy(toadoxGiaoDien1[1], Y_DISPLAY + 3 + locate);cout << sv.idStudent;
    gotoxy(toadoxGiaoDien1[2], Y_DISPLAY + 3 + locate);cout << s.lastName;
    gotoxy(toadoxGiaoDien1[3], Y_DISPLAY + 3 + locate);cout << s.firstName;
	gotoxy(toadoxGiaoDien1[4] , Y_DISPLAY + 3 + locate); cout << sv.point;
}

void XuatListSVDKTheoTungTrang(listRegister sv, int firstOrdinal){
	if (sv.Head == NULL && sv.Tail == NULL) return;
	int count = -1;
	for (NODE_REGISTER* p = sv.Head; p != NULL; p = p->Next){
		count++;
		if (count == firstOrdinal){
			int i = -1;
			while (p != NULL && i < SOLUONGMOITRANG - 1){
				XuatStudentDK(p->IFRegister, (++i) * 2);
				p = p->Next;
			}
			break;
		}
	}
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "Trang" << trangHientaiCB << "/" << tongsoTrangSVLopHoc;
	return;
}

void XuatListSVDKTheoTungTrang1(listRegister sv, listStudent s, int firstOrdinal){
	if (sv.Head == NULL && sv.Tail == NULL) return;
	int count = 0;int i = -1;
	
	for (NODE_REGISTER* p = sv.Head; p != NULL; p = p->Next){
		++count;		
		for(NODE_STUDENT* k = s.Head; k !=NULL; k= k->Next){			
			if (/*count == firstOrdinal &&*/ strcmp(p->IFRegister.idStudent,k->IFStudent.idStudent)==0){
				
//				while (p != NULL && i < SOLUONGMOITRANG - 1){
					XuatStudentDK1(p->IFRegister,k->IFStudent ,(++i) * 2, count);
//					p = p->Next;
					k = k->Next;
//				}
//				break;
			}
		}
	}
	gotoxy(X_PAGE, Y_PAGE - 2);
	cout << "Trang" << trangHientaiCB << "/" << tongsoTrangSVLopHoc;
	return;
}

void ThietLapMauChoTungDongDK(Register sv, Student s, int ThuTu) // thiet lap thanh sáng màu cho tung` dong` cua dssv
{
	SetBGColor(17);
	XuatStudentDK1(sv,s,(ThuTu % SOLUONGMOITRANG) * 2, ThuTu+1);
	SetBGColor(0);
}

void ChuyenTrangQLySVDK(listRegister dssv, listStudent s){
	system("cls");
	setColor(15, 3);
	gotoxy(X_TITLE, Y_TITLE); cout << "DANH SACH SINH VIEN DANG KY";
	setColor(11, 0);
	XuatListSVDKTheoTungTrang1(dssv,s,(trangHientaiCB - 1) * SOLUONGMOITRANG);
	Display1(tpGiaodienSVDK, sizeof(tpGiaodienSVDK) / sizeof(string));
}

NODE_REGISTER* FindStudentDKTheoThuTu(listRegister sv, int ThuTu){
	if (sv.Head == NULL) return NULL;
	if (sv.n - 1 < ThuTu) return NULL;
	if (sv.n - 1 == ThuTu) return sv.Tail;
	if (ThuTu == 0) return sv.Head;
	NODE_REGISTER *p = sv.Head;
	int count = 0;
	while (count != ThuTu){
		p = p->Next;
		count++;
	}
	return p;
}

void ChuyenDoiTungDongSVDK(int ThuTu, Register SVMoi, Register SVCu,Student sNew, Student sOld);
void ChuyenTrangChonSVDK(listRegister dssv);
NODE_REGISTER* ChooseStudentDK(listRegister dssv,listStudent sv)
{
	int keyboard_read = 0;
	ShowCur(false);
	trangHientaiCB = 1;
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	tongsoTrangSVLopHoc = ((dssv.n - 1) / SOLUONGMOITRANG) + 1;
	
	NODE_REGISTER* newNodeStudentDK = FindStudentDKTheoThuTu(dssv, vitriHienTaiCB);
	NODE_REGISTER* oldNodeStudentDK = NULL;
	
	Student sNew;Student sOld;
	for(NODE_STUDENT *p=sv.Head;p!=NULL;p=p->Next){
		if(strcmp(p->IFStudent.idStudent,newNodeStudentDK->IFRegister.idStudent)==0){
			sNew=p->IFStudent;
			break;
		}	
	}
	
	XuatListSVDKTheoTungTrang1(dssv,sv ,(trangHientaiCB - 1) * SOLUONGMOITRANG);
	ThietLapMauChoTungDongDK(newNodeStudentDK->IFRegister,sNew,vitriHienTaiCB);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (vitriHienTaiCB % SOLUONGMOITRANG > 0)
			{
				vitriHienTaiCB = vitriHienTaiCB - 1;
				oldNodeStudentDK = newNodeStudentDK;
				for(NODE_STUDENT *p=sv.Head;p!=NULL ;p=p->Next){
					if(strcmp(p->IFStudent.idStudent,oldNodeStudentDK->IFRegister.idStudent)==0){
						sOld=p->IFStudent;
						break;
					}	
				}
				for (newNodeStudentDK = dssv.Head; newNodeStudentDK->Next != oldNodeStudentDK; newNodeStudentDK = newNodeStudentDK->Next);
				for(NODE_STUDENT *p=sv.Head;p!=NULL;p=p->Next){
					if(strcmp(p->IFStudent.idStudent,newNodeStudentDK->IFRegister.idStudent)==0){
						sNew=p->IFStudent;
						break;
					}	
				}
				ChuyenDoiTungDongSVDK(vitriHienTaiCB, newNodeStudentDK->IFRegister, oldNodeStudentDK->IFRegister,sNew,sOld);
			}
			break;

		case KEY_DOWN:
			if (vitriHienTaiCB % SOLUONGMOITRANG < SOLUONGMOITRANG - 1 && newNodeStudentDK->Next != NULL) 
			{
				vitriHienTaiCB = vitriHienTaiCB + 1;
				oldNodeStudentDK = newNodeStudentDK;
				for(NODE_STUDENT *p=sv.Head;p!=NULL;p=p->Next){
					if(strcmp(p->IFStudent.idStudent,oldNodeStudentDK->IFRegister.idStudent)==0){
						sOld=p->IFStudent;
						break;
					}
				}
				newNodeStudentDK = newNodeStudentDK->Next;
				for(NODE_STUDENT *p=sv.Head;p!=NULL;p=p->Next){
					if(strcmp(p->IFStudent.idStudent,newNodeStudentDK->IFRegister.idStudent)==0){
						sNew=p->IFStudent;
						break;
					}
				}
				ChuyenDoiTungDongSVDK(vitriHienTaiCB, newNodeStudentDK->IFRegister, oldNodeStudentDK->IFRegister,sNew, sOld);
			}
			break;
		
		case KEY_RIGHT:
			if (trangHientaiCB < tongsoTrangSVLopHoc)
			{
				trangHientaiCB++;
				ChuyenTrangChonSVDK(dssv);
				XuatListSVDKTheoTungTrang(dssv, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeStudentDK = FindStudentDKTheoThuTu(dssv, vitriHienTaiCB);
				ThietLapMauChoTungDongDK(newNodeStudentDK->IFRegister,sNew, vitriHienTaiCB);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiCB > 1)
			{
				trangHientaiCB--;	
				ChuyenTrangChonSVDK(dssv);
				XuatListSVDKTheoTungTrang(dssv, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeStudentDK = FindStudentDKTheoThuTu(dssv, vitriHienTaiCB);
				ThietLapMauChoTungDongDK(newNodeStudentDK->IFRegister,sNew, vitriHienTaiCB);
			}
			break;
		case ENTER:  //enter
			ShowCur(true);
			return newNodeStudentDK;
			break;
		case ESC: 
			return NULL; 
			break;
		}//end switch  read key
	}
}

bool Delete_Head_DK(listRegister &sv){
	if (ListRegister_Empty(sv)) return false;
	NODE_REGISTER* p = sv.Head;
	sv.Head = p->Next;
	delete p;
	--sv.n;
	return true;
}

bool Delete_Tail_DK(listRegister &sv)
{
		if (ListRegister_Empty(sv)) return false;
		for (NODE_REGISTER *p = sv.Head; p != NULL; p = p->Next)
		{
			if (p->Next == sv.Tail)
			{
				delete sv.Tail;
				p->Next = NULL;
				sv.Tail = p;
				--sv.n;
				return true;
			}
		}
}

bool Delete_After_DK(listRegister &sv, NODE_REGISTER* p)
{
	if (p == NULL || p->Next == NULL) return false;
	NODE_REGISTER* q = p->Next;
	p->Next = q->Next;
	delete q;
	--sv.n;
	return true;
}

bool DeleteStudentDK_Id(listRegister &sv, Register data)
{
	NODE_REGISTER* p = FindStudentDK(sv, data.idStudent);
	if (p == NULL) return false;
	if (p == sv.Head) return Delete_Head_DK(sv);
	if (p == sv.Tail) return Delete_Tail_DK(sv);
	else
	{
		NODE_REGISTER* q = sv.Head;
		while (q->Next != p)
			q = q->Next;
		return Delete_After_DK(sv, q);
	}
}

//NODE_REGISTER* FindStudentDKTheoThuTu(listRegister sv, int ThuTu){
//	if (sv.Head == NULL) return NULL;
//	if (sv.n - 1 < ThuTu) return NULL;
//	if (sv.n - 1 == ThuTu) return sv.Tail;
//	if (ThuTu == 0) return sv.Head;
//	NODE_REGISTER *p = sv.Head;
//	int count = 0;
//	while (count != ThuTu){
//		p = p->Next;
//		count++;
//	}
//	return p;
//}

void XuatIDSVDK(listRegister sv, int firstOrdinal){
	int temp = -1;
	for (int i = firstOrdinal; i < SoSVDK; i++){ // gia tri cua SoSV co duoc sau khi goi ham FindFlightTheoCMND
		temp++;
		if (temp < SOLUONGMOITRANG2) {
			NODE_REGISTER* p = FindStudentDKTheoThuTu(sv, arrSTTSinhVienDK[i]);
			gotoxy(toadoxGiaoDien2[0] + 1, Y_DISPLAY + 8 + temp * 2);
			cout << p->IFRegister.idStudent;
		}
	}
}

void ChuyenDoiTungDongSVDK(int ThuTu, Register SVMoi, Register SVCu, Student sNew, Student sOld) // chuyen thanh sáng lên hay xuông' 
{
	int current = ThuTu;
	ThietLapMauChoTungDongDK(SVMoi, sNew,current);
	XuatStudentDK1(SVCu, sOld, (vitriTruocDoCB % SOLUONGMOITRANG) * 2, current);
	vitriTruocDoCB = current;
}

void ChuyenTrangChonSVDK(listRegister dssv)
{
	system("cls");
	Display1(tpGiaodienSV, sizeof(tpGiaodienSV) / sizeof(string));
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	TitleBangChon(tpMucLucSV);
}

//=============================================================================================//

//1.Sao chep cay nhi phan thanh mang con tro lop tin chi
nodeClass* taoNodeClass(CLASS data) {
	NODE_CLASS *p = new nodeClass;
	if (p == NULL) return NULL;	
	p->IFCLASS = data; // gan gia tri cho node
	p->Next = NULL; // cho next tro toi NULL (init danh sach lien ket)
	return p;
}

void InitListClass(listClassLK &dsl) {
	dsl.Head = dsl.Tail = NULL;
}
void Insert_after_Class(listClassLK &dsl, CLASS lop)
{
    NODE_CLASS *p=taoNodeClass(lop);
    if(dsl.n==0){
       dsl.Head=dsl.Tail=p;
	}
	else{
		for(NODE_CLASS *k=dsl.Head; ;k=k->Next){
			if(k->Next==NULL){
				k->Next=p;
				break;
			}
		}
	}
	++dsl.n;
}

void XuatClass(CLASS lop, int locate){
    gotoxy(toadoxGiaoDien[0] -1, Y_DISPLAY + 3 + locate); cout << lop.idClass;
	gotoxy(toadoxGiaoDien[1] , Y_DISPLAY + 3 + locate); cout << lop.idSubject;
	gotoxy(toadoxGiaoDien[2] , Y_DISPLAY + 3 + locate); cout<< lop.schoolYear; 	
	gotoxy(toadoxGiaoDien[3] +1, Y_DISPLAY + 3 + locate); cout<<lop.numberSemester;
	gotoxy(toadoxGiaoDien[4], Y_DISPLAY + 3 + locate); cout<<lop.idGroup;
	gotoxy(toadoxGiaoDien[5] -1, Y_DISPLAY + 3 + locate); cout<<lop.maxNumStudents;
	gotoxy(toadoxGiaoDien[6]+5 , Y_DISPLAY + 3 + locate); cout<<lop.minNumStudents;
}

void XuatListLopTheoTungTrang(listClassLK dsl, int firstOrdinal){
	gotoxy(X_ThongBao, Y_ThongBao); cout << setw(50) << setfill(' ') << " ";
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout << "CHON LOP TIN CHI MUON DANG KY";
	setColor(14, 0);
	Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
	if (dsl.Head == NULL && dsl.Tail == NULL) return;
	int count = -1;
	for (NODE_CLASS* p = dsl.Head; p != NULL; p = p->Next){
		count++;
		if (count == firstOrdinal){
			int i = -1;
			while (p != NULL && i < SOLUONGMOITRANG - 1){
				XuatClass(p->IFCLASS, (++i) * 2);
				p = p->Next;
			}
			break;
		}
	}
//	gotoxy(X_PAGE, Y_PAGE - 2);
//	cout << "Trang" << trangHientaiCB << "/" << tongsoTrangSVLopHoc;

}

void XuatClassDK(CLASS lop, int locate){
    gotoxy(toadoxGiaoDien2[0] -1, Y_DISPLAY1 + 3 + locate); cout << lop.idClass;
	gotoxy(toadoxGiaoDien2[1] , Y_DISPLAY1 + 3 + locate); cout << lop.idSubject;
	
//	gotoxy(toadoxGiaoDien2[0] -1, Y_DISPLAY1 + 3 + locate); cout << lop.idClass;
//	gotoxy(toadoxGiaoDien2[1] , Y_DISPLAY1 + 3 + locate); cout << lop.idSubject;
	
//	gotoxy(toadoxGiaoDien[2] , Y_DISPLAY + 3 + locate); cout<< lop.schoolYear; 	
//	gotoxy(toadoxGiaoDien[3] +1, Y_DISPLAY + 3 + locate); cout<<lop.numberSemester;
//	gotoxy(toadoxGiaoDien[4], Y_DISPLAY + 3 + locate); cout<<lop.idGroup;
//	gotoxy(toadoxGiaoDien[5] -1, Y_DISPLAY + 3 + locate); cout<<lop.maxNumStudents;
//	gotoxy(toadoxGiaoDien[6]+5 , Y_DISPLAY + 3 + locate); cout<<lop.minNumStudents;
}

void XuatListLopDK(listClassLK dsl, int firstOrdinal, int rangerow){
	setColor(15, 3);
	gotoxy(30, 42); cout << "DANH SACH LOP TIN CHI DA CHON";
	setColor(11, 0);
	Display4(tpGiaodienlopTCDK, sizeof(tpGiaodienlopTCDK) / sizeof(string), rangerow);
	TitleBangChon1(tpMucLucDK);
	
	if (dsl.Head == NULL && dsl.Tail == NULL) return;

	int count = -1;
	for (NODE_CLASS* p = dsl.Head; p != NULL; p = p->Next){
		count++;
		if (count == firstOrdinal){
			int i = -1;
			while (p != NULL){
				XuatClassDK(p->IFCLASS, (++i) * 2);
				p = p->Next;
			}
			break;
		}
	}

}


void ChuyenTrangQLyLop(listClassLK dsl, listClassLK dsl1){
	system("cls");
	XuatListLopDK(dsl, (trangHientaiCB - 1) * SOLUONGMOITRANG, 4);	
	XuatListLopTheoTungTrang(dsl1, (trangHientaiCB - 1) * SOLUONGMOITRANG);
}

NODE_CLASS* FindClassTheoThuTu(listClassLK sv, int ThuTu){
	if (sv.Head == NULL) return NULL;
	if (sv.n - 1 < ThuTu) return NULL;
	if (sv.n - 1 == ThuTu) return sv.Tail;
	if (ThuTu == 0) return sv.Head;
	NODE_CLASS *p = sv.Head;
	int count = 0;
	while (count != ThuTu){
		p = p->Next;
		count++;
	}
	return p;
}

NODE_CLASS* FindClassLK (listClassLK dsl, char schoolYear[10], int numberSemester){
	if (dsl.Head == NULL) return NULL;
	for (NODE_CLASS* p = dsl.Head; p != NULL; p = p->Next)
		if (stricmp(p->IFCLASS.schoolYear, schoolYear) == 0 && p->IFCLASS.numberSemester==numberSemester)
			return p;
	return NULL;
}

void ThietLapMauChoTungDongLTC(CLASS sv, int ThuTu) // thiet lap thanh sáng màu cho tung` dong` cua dsl
{
	SetBGColor(7);
	XuatClass(sv, (ThuTu % SOLUONGMOITRANG) * 2);
	SetBGColor(0);
}

void ThietLapMauChoTungDongLTC1(CLASS sv, int ThuTu) // thiet lap thanh sáng màu cho tung` dong` cua dsl
{
	SetBGColor(7);
	XuatClassDK(sv, (ThuTu % SOLUONGMOITRANG) * 2);
	SetBGColor(0);
}

void ChuyenTrangChonLTC(listClassLK dssv)
{
	system("cls");
	Display(tpGiaodienlopTC, sizeof(tpGiaodienlopTC) / sizeof(string));
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
}
void ChuyenDoiTungDongLTC(int ThuTu, CLASS SVMoi, CLASS SVCu) // chuyen thanh sáng lên hay xuông' 
{
	int current = ThuTu;
	ThietLapMauChoTungDongLTC(SVMoi, current);
	XuatClass(SVCu, (vitriTruocDoCB % SOLUONGMOITRANG) * 2);
	vitriTruocDoCB = current;
}
void ChuyenDoiTungDongLTC1(int ThuTu, CLASS SVMoi, CLASS SVCu) // chuyen thanh sáng lên hay xuông' 
{
	int current = ThuTu;
	ThietLapMauChoTungDongLTC1(SVMoi, current);
	XuatClassDK(SVCu, (vitriTruocDoCB % SOLUONGMOITRANG) * 2);
	vitriTruocDoCB = current;
}

bool CheckDK2Lan(listClassLK dsl, unsigned int idClass){
	for(NODE_CLASS* p=dsl.Head; p!=NULL; p=p->Next){
		if(p->IFCLASS.idClass==idClass){
			return true;	
		}
	}
	return false;
}

NODE_CLASS* ChonLop(listClassLK dsl, listClassLK &dslTemp, int choice)
{
	int keyboard_read = 0, rangerow=4;
	ShowCur(false);
	trangHientaiCB = 1;
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	tongsoTrangSVLopHoc = ((dsl.n - 1) / SOLUONGMOITRANG) + 1;
	
	NODE_CLASS* newNodeClass = FindClassTheoThuTu(dsl, vitriHienTaiCB);
	NODE_CLASS* oldNodeClass = NULL;
	
	XuatListLopTheoTungTrang(dsl, (trangHientaiCB - 1) * SOLUONGMOITRANG);
	ThietLapMauChoTungDongLTC(newNodeClass->IFCLASS, vitriHienTaiCB);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (vitriHienTaiCB % SOLUONGMOITRANG > 0)
			{
				vitriHienTaiCB = vitriHienTaiCB - 1;
				oldNodeClass = newNodeClass;
				for (newNodeClass = dsl.Head; newNodeClass->Next != oldNodeClass; newNodeClass = newNodeClass->Next);
				ChuyenDoiTungDongLTC(vitriHienTaiCB, newNodeClass->IFCLASS, oldNodeClass->IFCLASS);
			}
			break;
		case KEY_DOWN:
			if (vitriHienTaiCB % SOLUONGMOITRANG < SOLUONGMOITRANG - 1 && newNodeClass->Next != NULL) 
			{
				vitriHienTaiCB = vitriHienTaiCB + 1;
				oldNodeClass = newNodeClass;
				newNodeClass = newNodeClass->Next;
				ChuyenDoiTungDongLTC(vitriHienTaiCB, newNodeClass->IFCLASS, oldNodeClass->IFCLASS);
			}
			break;
		case ENTER:  //enter
			if(choice == 1)
			{
				//Kiem tra xem co chon mot lop tin chi 2 lan de dang ky
				if(CheckDK2Lan(dslTemp, newNodeClass->IFCLASS.idClass))
				{
					gotoxy(X_ThongBao, Y_ThongBao);
					cout<<"Lop tin chi nay da chon!";
					system("pause");
				}
				else{
					
					Insert_after_Class(dslTemp,newNodeClass->IFCLASS);
					
					rangerow+=2;
					
					
					XuatListLopDK(dslTemp,(trangHientaiCB - 1) * SOLUONGMOITRANG, rangerow);
					
					
					return newNodeClass;
				}
			}
			else if(choice == 2){
				return newNodeClass;
			}
			break;	
			
		case KEY_RIGHT:
			if (trangHientaiCB < tongsoTrangSVLopHoc && choice ==1)
			{
				trangHientaiCB++;
				ChuyenTrangChonLTC(dsl);
//				XuatListLopDK(dslTemp,(trangHientaiCB - 1) * SOLUONGMOITRANG, rangerow);
				XuatListLopTheoTungTrang(dsl, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeClass = FindClassTheoThuTu(dsl, vitriHienTaiCB);
				ThietLapMauChoTungDongLTC(newNodeClass->IFCLASS, vitriHienTaiCB);
			}
			break;
		case KEY_LEFT:
			if (trangHientaiCB > 1 && choice ==1)
			{
				trangHientaiCB--;	
				ChuyenTrangChonLTC(dsl);
//				XuatListLopDK(dslTemp,(trangHientaiCB - 1) * SOLUONGMOITRANG, rangerow);
				XuatListLopTheoTungTrang(dsl, (trangHientaiCB - 1) * SOLUONGMOITRANG);
				newNodeClass = FindClassTheoThuTu(dsl, vitriHienTaiCB);
				ThietLapMauChoTungDongLTC(newNodeClass->IFCLASS, vitriHienTaiCB);
			}
			break;
		
		case ESC: 
			return NULL; 
			break;
		}//end switch  read key
	}
}

NODE_CLASS* ChonLop2(listClassLK &dsl)
{
	int keyboard_read = 0, rangerow=4;
	ShowCur(false);
	trangHientaiCB = 1;
	vitriHienTaiCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	vitriTruocDoCB = (trangHientaiCB - 1) * SOLUONGMOITRANG;
	tongsoTrangSVLopHoc = ((dsl.n - 1) / SOLUONGMOITRANG) + 1;
	
	NODE_CLASS* newNodeClass = FindClassTheoThuTu(dsl, vitriHienTaiCB);
	NODE_CLASS* oldNodeClass = NULL;
	
	XuatListLopDK(dsl, (trangHientaiCB - 1) * SOLUONGMOITRANG, rangerow);
	ThietLapMauChoTungDongLTC1(newNodeClass->IFCLASS, vitriHienTaiCB);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (vitriHienTaiCB % SOLUONGMOITRANG > 0)
			{
				vitriHienTaiCB = vitriHienTaiCB - 1;
				oldNodeClass = newNodeClass;
				for (newNodeClass = dsl.Head; newNodeClass->Next != oldNodeClass; newNodeClass = newNodeClass->Next);
				ChuyenDoiTungDongLTC1(vitriHienTaiCB, newNodeClass->IFCLASS, oldNodeClass->IFCLASS);
			}
			break;
		case KEY_DOWN:
			if (vitriHienTaiCB % SOLUONGMOITRANG < SOLUONGMOITRANG - 1 && newNodeClass->Next != NULL) 
			{
				vitriHienTaiCB = vitriHienTaiCB + 1;
				oldNodeClass = newNodeClass;
				newNodeClass = newNodeClass->Next;
				ChuyenDoiTungDongLTC1(vitriHienTaiCB, newNodeClass->IFCLASS, oldNodeClass->IFCLASS);
			}
			break;
		case ENTER:  //enter

			return newNodeClass;
			break;
						
		case ESC: 
			return NULL; 
			break;
		}//end switch  read key
	}
}


void CopyToListClass(TREECLASS &t, listClassLK &dsl)
{
	for (int i = 0; i <= SoLop; i++)
	{
		NodeClass* p = FindClass(t, arrIdLop[i]);	
        Insert_after_Class(dsl,p->clAss);
	}
}

listClassLK CapNhatDSLHienThi(listClassLK &dsl, char schoolYear[10], int numberSemester){
	//Khai bao danh sach sinh vien tam
	listClassLK dslTemp;
	
	//Quet dsl chinh, dua pt co nien khoa va ky hoc giong da nhap va dsl tam
	for(NODE_CLASS *k=dsl.Head;k!=NULL;k=k->Next){
		if(strcmp(k->IFCLASS.schoolYear,schoolYear)==0 && k->IFCLASS.numberSemester==numberSemester){
			Insert_after_Class(dslTemp,k->IFCLASS);
		}
	}
	return dslTemp;
}

//Search lop theo nien khoa va hoc ky
NodeClass* FindClass2(TREECLASS root, char schoolYear[10], int numberSemester)
{
	if (root != NULL)
	{
		NodeClass* p = root;
		while (p != NULL)
		{
			if (p->clAss.numberSemester == numberSemester && strcmp(p->clAss.schoolYear,schoolYear)==0)
				return p;
			if (p->left->clAss.numberSemester == numberSemester && strcmp(p->left->clAss.schoolYear,schoolYear)==0){
				return p->left;
			}
			if(p->right->clAss.numberSemester == numberSemester && strcmp(p->right->clAss.schoolYear,schoolYear)==0){
				return p->right;
			}
			
		}
	}
	return NULL;
}

bool ListClass_Empty(listClassLK sv) { // kiem tra ds sinh vien co rong hay khong
	return sv.Head == NULL;
}

NODE_CLASS* FindClassDK (listClassLK dsl, unsigned int idClass){
	if (dsl.Head == NULL) return NULL;
	for (NODE_CLASS* p = dsl.Head; p != NULL; p = p->Next)
		if (p->IFCLASS.idClass == idClass)
			return p;
	return NULL;
}

NODE_CLASS* FindClassDK1 (listClassLK dsl, string idSubject, string schoolYear, int numberSemester,int idGroup){
	if (dsl.Head == NULL) return NULL;
	for (NODE_CLASS* p = dsl.Head; p != NULL; p = p->Next)
		if (strcmp(p->IFCLASS.idSubject, idSubject.c_str())==0 && strcmp(p->IFCLASS.schoolYear, schoolYear.c_str()) == 0 &&
			p->IFCLASS.numberSemester==numberSemester && p->IFCLASS.idGroup==idGroup)
			return p;
	return NULL;
}

bool Delete_HeadDK(listClassLK &dsl){
	if (ListClass_Empty(dsl)) return false;
	NODE_CLASS* p = dsl.Head;
	dsl.Head = p->Next;
	delete p;
	--dsl.n;
	return true;
}

bool Delete_TailDK(listClassLK &sv)
{
		if (ListClass_Empty(sv)) return false;
		for (NODE_CLASS *p = sv.Head; p != NULL; p = p->Next)
		{
			if (p->Next == sv.Tail)
			{
				delete sv.Tail;
				p->Next = NULL;
				sv.Tail = p;
				--sv.n;
				return true;
			}
		}
}

bool Delete_AfterDK(listClassLK &dsl, NODE_CLASS* p)
{
	if (p == NULL || p->Next == NULL) return false;
	NODE_CLASS* q = p->Next;
	p->Next = q->Next;
	delete q;
	--dsl.n;
	return true;
}

bool DeleteClass_Id(listClassLK &dsl, CLASS data)
{
	NODE_CLASS* p = FindClassDK(dsl, data.idClass);
	if (p == NULL) return false;
	if (p == dsl.Head) return Delete_HeadDK(dsl);
	if (p == dsl.Tail) return Delete_TailDK(dsl);
	else
	{
		NODE_CLASS* q = dsl.Head;
		while (q->Next != p)
			q = q->Next;
		return Delete_AfterDK(dsl, q);
	}
}

//void ClearlistDK( NODE_REGISTER &First)
//{  
//   NODE_REGISTER p;  
//  while(First.IFRegister.idClass != NULL)
//   {
//      p = First;
//      First = *First.Next;
//      delete p;
//   }
//}


void LoadSVDK(TREECLASS &t){
	//Khai bao bien
	ifstream infile;
	string data=""; char a;
	int n=0,m=0, idClass;
	Register sv;
	NodeClass *p;
		
	infile.open("dssvdk.txt",ios::in);
	
	//truong hop ko ko duoc file
	if(!infile) {
//		gotoxy(X_ThongBao,Y_ThongBao);
		cout<<"Khong mo duoc file";
		return;
	}
	int x=0;
	infile>>m;
	cout<<m<<endl;
//	while(!infile.eof()){
	for(int j=0;j<m;j++){
		infile>>a;
		infile>>idClass;
		infile>>n;
		cout<<"lan "<<++x<<": "; cout<<n<<endl;
		listRegister dsdk;
		for(int i=0;i<n;i++){
			
			infile>>data; 
			strcpy(sv.idStudent, data.c_str());
			infile>>sv.point;			
			Insert_after_dk(dsdk,sv);
//			gotoxy(X_ThongBao, Y_ThongBao+(++x));					
//			cout<<z<<endl;				
//			Insert_Order_DK(dsdk,sv);
		}
		
			
		
//		tim lop class
		p=FindClass(t,idClass);
				    	
//		gan gia tri dsdk cho con tro cua lop tin chi
		p->clAss.listRegisters=dsdk;
//        dsdk.n=0;      	
		infile.ignore();
	}
	infile.close();
}



void SaveSVDK(TREECLASS &t, ofstream &outFile){

	outFile<<t->clAss.idClass<<endl;
	outFile<<t->clAss.listRegisters.n<<endl;
	for(NODE_REGISTER* k=t->clAss.listRegisters.Head;k!=NULL;k=k->Next)
	{
		outFile<<k->IFRegister.idStudent<<endl; 
		outFile<<k->IFRegister.point<<endl;
    }
	
}

void LuuDSDK (TREECLASS &t,listClassLK &dsl)
{	
	ofstream outFile;
	outFile.open("dssvdk.txt",ios::out);	
	
	NodeClass *p;
	int count=0;
	for(NODE_CLASS *k=dsl.Head; k!=NULL; k=k->Next)
	{
        p=FindClass(t,k->IFCLASS.idClass);
        if(p->clAss.listRegisters.n!=0){
            ++count;
        }
	}
	
	outFile<<count<<endl;
	
	for(NODE_CLASS *k=dsl.Head; k!=NULL; k=k->Next)
	{	
		p=FindClass(t,k->IFCLASS.idClass);
		if(p->clAss.listRegisters.n!=0){
			outFile<<'-'<<endl;	
			outFile<<p->clAss.idClass<<endl;
			outFile<<p->clAss.listRegisters.n<<endl;
			for(NODE_REGISTER* k=p->clAss.listRegisters.Head;k!=NULL;k=k->Next)
			{
				outFile<<k->IFRegister.idStudent<<endl; 
				outFile<<k->IFRegister.point<<endl;
    		}
			
		}
	}
		
	outFile.close();
	
}

listRegister CapNhatSVDK(TREECLASS &t, listRegister &dsdk /*, unsigned int IDCLASS*/){
	ifstream infile;
	string data=""; char a;
	int n=0,m=0, idClass;
	Register sv;
	NodeClass *p; listRegister r=dsdk;listRegister r1;
	
	//mo file
	infile.open("dssvdk.txt",ios::in);
	
	//truong hop ko ko duoc file
	if(!infile) {
//		gotoxy(X_ThongBao,Y_ThongBao);
		cout<<"Khong mo duoc file";
		return r1;
	}
	
	//bat dau doc
	infile>>m;
//	while(!infile.eof()){
	for(int j=0;j<m;j++){
		infile>>a;
		infile>>idClass;
//		if(idClass==IDCLASS)
//		{
	       infile>>n;
		  for(int i=0;i<n;i++){
//		  	sv.idClass=idClass;
			infile>>data; 
			strcpy(sv.idStudent, data.c_str());
			infile>>sv.point;			
			Insert_after_dk(r,sv);
		  }	 
//	    }
	}
	infile.close();
	return r;
}

void ChinhSuaLopDK(listClassLK &dslTemp, listClassLK &dsl, TREECLASS &t, string idStudent, listRegister &dsdk){//dsl tam, dsl1 chinh
	ShowCur(false);
	Register svdk;
	listRegister dsdkTemp;	
	NodeClass *p;
//	dsdk=CapNhatSVDK(t,dsdk);
//    cout<<dsdk.n<<endl;
backMenu:	  									
	trangHientaiCB = 1;
//	XuatListLopDK(dslTemp, 0, 4);
	setColor(11, 0);
	int key;
	while(true){
		while(kbhit()){
			key = getch();
			if (key == 0 || key == 224){
				key = getch();				
				
				if (key == KEY_F5){ // F5:xoa
					gotoxy(24, Y_ThongBao + 3); cout << setw(65) << " ";
					
					NODE_CLASS* nsv = ChonLop2(dslTemp);
					if (nsv == NULL) goto backMenu;
					gotoxy(X_ThongBao, Y_ThongBao); cout << "Enter neu chac chan xoa !";
					key = getch();
					if (key == ENTER){
						if (DeleteClass_Id(dsl, nsv->IFCLASS)){
							ChuyenTrangQLyLop(dslTemp,dsl);
							gotoxy(X_ThongBao, Y_ThongBao); cout << "Xoa thanh cong !";
						}
					}
					else goto backMenu;
				}
				
				else if(key==KEY_F3){//Luu
				    //Luu thong tin sinh vien dang ky
					strcpy(svdk.idStudent, idStudent.c_str());
					svdk.point=0.0;
					int i=0;
				    //duyet danh sach lop da 
						for(NODE_CLASS *k=dslTemp.Head; k!=NULL; k=k->Next){
					
							//tìm lop tc trong danh sach dang ky
							p=FindClass(t,k->IFCLASS.idClass);
					    		
	                        //Them svdk vao listRegister cua ltc tuong uong
								if(FindStudentDK(p->clAss.listRegisters,(char*)svdk.idStudent)==NULL){
									Insert_First(p->clAss.listRegisters,svdk);
									++(p->clAss.listRegisters.n);
									gotoxy(X_ThongBao,Y_ThongBao+(++i));
									cout<<"Da them";
								}
					    		
//								gotoxy(X_ThongBao,Y_ThongBao+(++i));
//								cout<<"Da them";
							}
				}
				    
			}
				
		else if (key == ESC)
					return;
		}
	}
}

void DKLopTC(TREECLASS &t, listStudent &dssv, listRegister &dsdk){
	system("cls");
	
	
	//dsl chua danh sach toan bo danh sach trong cay 
	listClassLK dsl;
	CopyToListClass(t,dsl);
	
	listClassLK dslTemp;//dslTemp chua danh sach lop tc da chon de dang ky
	InitListClass(dslTemp);
	
	string idStudentSTR="";
	string schoolYear="";
	int numberSemester=0;
	nodeClass* loptc;
	
	bool isSave=false;
	int TrinhTu = 0, rangerow=3; trangHientaiCB = 1;
	int key;
	bool isMoveUp = false;

backMenu: 
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout<<"Vui long dien day du cac thong tin sau";
	gotoxy( 50,20 ); cout<<"Nhan F10: de bat dau dang ky lop";
	setColor(2,0);
	GiaoDienB1DKLopTC(tpGiaoDienB1DKLopTC,sizeof(tpGiaoDienB1DKLopTC) / sizeof(string), 55);
	while(true){
		//b1 nhap thong tin de tim kiem lop
		switch(TrinhTu){
			case 0: {
				NhapHoacEditString(idStudentSTR, isMoveUp, TrinhTu, isSave, -90);
				
				if(idStudentSTR.empty()){
					return;
				}
				
				break;
			}
			case 1: {
				NhapHoacEditString(schoolYear, isMoveUp, TrinhTu, isSave, -90);
				break;
			}
			case 2: {
				NhapHoacEditSo(numberSemester, isMoveUp, TrinhTu, isSave, -90, 3);
				break;
			}
		}
		if (isMoveUp){
		    if (TrinhTu == 0)
			isMoveUp = false;
			TrinhTu--;
	    }
        else {
		    if (TrinhTu == 3)
	        isMoveUp = true;
		    TrinhTu++;
       	}
        //b2 xuat ra danh sach ltc trung vs tt da nhao
		if(isSave){	
			
			if(idStudentSTR.empty() || schoolYear.empty() ||(int)log10(numberSemester) + 1 == 0 ){
				gotoxy( 100,10 ); cout<<"                                                  ";
				gotoxy( 100,10 ); cout<<"Khong duoc de trong dong nao! Xin cam on!";
			}
        	else if(FindStudent(dssv,(char *)idStudentSTR.c_str()) !=NULL && FindClassLK(dsl,(char *)schoolYear.c_str(),numberSemester)!=NULL)// tìm ra duoc thì chay tiep
	        {
					system("cls");

//					Chon ltc muon dang ky
		            loptc = ChonLop(CapNhatDSLHienThi(dsl,(char*)schoolYear.c_str(),numberSemester), dslTemp, 1);
					
					//dslTemp se tang sau khi chon
		            
		            //dua dslTemp da chon va toan bo danh sach lop tc, id cua sv, dsdk vao hàm chính sua
					ChinhSuaLopDK(dslTemp,dsl,t,idStudentSTR,dsdk);
								
		            if (loptc == NULL)
		            {
		               //LuuDSDK(t,dsl);
					   return;
		            }			
		            
	        }
	        else
	        {
	        	gotoxy( 100,10 ); cout<<"                                                  ";
	        	gotoxy( 100,10 ); cout<<"Khong co ket qua! moi nhap lai";
	        	goto backMenu;
			}
	    }
	}			
}

void ThietLapMauChoTungDongDSDK(CLASS sv, int ThuTu) // thiet lap thanh sáng màu cho tung` dong` cua dsl
{
	SetBGColor(7);
	XuatClass(sv, (ThuTu % SOLUONGMOITRANG) * 2);
	SetBGColor(0);
}


void XuatDSDK(TREECLASS t,listStudent dssv){
	system("cls");	
	bool isSave=false;
	int TrinhTu = 0; trangHientaiCB = 1; float diem;
	bool isMoveUp = false;
	
	listClassLK dsl;
	CopyToListClass(t,dsl);
	
	string idSubject="";
	string schoolYear="";
	int numberSemester=0;
	int idGroup=0;
	listRegister dsdk;
backMenu: 
	setColor(15, 6);
	gotoxy(X_TITLE, Y_TITLE); cout<<"Vui long dien day du cac thong tin sau";
	gotoxy( 50,20 ); cout<<"Nhan F10 de bat dau tim kiem";
	setColor(2,0);
	GiaoDienB1DKLopTC(tpGiaoDienXuatDSDK,sizeof(tpGiaoDienXuatDSDK) / sizeof(string), 55);
	while(true){
		switch(TrinhTu){
			case 0: {
				NhapHoacEditString(idSubject, isMoveUp, TrinhTu, isSave, -90);
				
				if(idSubject.empty()){
					return;
				}				
				break;
				
			}
			case 1: {
				NhapHoacEditString(schoolYear, isMoveUp, TrinhTu, isSave, -90);
				break;
			}
			case 2: {
				NhapHoacEditSo(numberSemester, isMoveUp, TrinhTu, isSave, -90, 3);
				break;
			}
			case 3:{
				NhapHoacEditSo(idGroup, isMoveUp, TrinhTu, isSave, -90, 100);	
			}
		}
		if (isMoveUp){
		    if (TrinhTu == 0)
			isMoveUp = false;
			TrinhTu--;
	    }
        else {
		    if (TrinhTu == 3)
	        isMoveUp = true;
		    TrinhTu++;
       	}
        
		if(isSave){	
			
			if(idSubject.empty() || schoolYear.empty() || (int)log10(numberSemester) + 1 == 0 || (int)log10(idGroup) + 1 == 0 ){
				gotoxy( 100,10 ); cout<<"                                                  ";
				gotoxy( 100,10 ); cout<<"Khong duoc de trong dong nao! Xin cam on!";
			}
        	else if(FindClassDK1(dsl,idSubject,schoolYear,numberSemester,idGroup)!=NULL)// tìm ra duoc thì chay tiep
	        {
				ShowCur(false);
				system("cls");	  									
				gotoxy(X_TITLE+10, Y_TITLE); cout << "DANH SACH SINH VIEN DANG KY";
				setColor(14, 0);
				Display1(tpGiaodienSVDK, sizeof(tpGiaodienSVDK) / sizeof(string));	
				
				NODE_CLASS* k= FindClassDK1(dsl,idSubject,schoolYear,numberSemester,idGroup);
				dsdk = FindClass(t,k->IFCLASS.idClass)->clAss.listRegisters;
				
				trangHientaiCB = 1;
				tongsoTrangSVLopHoc = ((dsdk.n) / SOLUONGMOITRANG) + 1;

				XuatListSVDKTheoTungTrang1(dsdk, dssv, (trangHientaiCB-1)*SOLUONGMOITRANG);
				
				int key;
				while(true){
					while(kbhit()){
						key = getch();
						if (key == 0 || key == 224){
							if (key == KEY_RIGHT && trangHientaiCB < tongsoTrangSVLopHoc){
								trangHientaiCB++;
								ChuyenTrangQLySVDK(dsdk,dssv);
							}
								
							else if (key == KEY_LEFT && trangHientaiCB > 1){
								trangHientaiCB--;
								ChuyenTrangQLySVDK(dsdk,dssv);
							}
						}
						else if(key==KEY_F2){
                       	
							NODE_REGISTER* svdk=ChooseStudentDK(dsdk,dssv);
							if(svdk!=NULL)
							{
								backstep:
								gotoxy(toadoxGiaoDien1[7]+10 , Y_DISPLAY + 3); 
								cout<<"Diem: ";	
                       			cin>>diem;
                       			if((int)log10(numberSemester) + 1 != 0){
//                       			
									ShowCur(false);
                       				k= FindClassDK1(dsl,idSubject,schoolYear,numberSemester,idGroup);
									dsdk = FindClass(t,k->IFCLASS.idClass)->clAss.listRegisters;	
									for(NODE_REGISTER* o=dsdk.Head;o!=NULL;o=o->Next){
										if(strcmp(o->IFRegister.idStudent,svdk->IFRegister.idStudent)==0){
											o->IFRegister.point=diem;
											break;
										}	
									}
								}
								else{
									goto backstep;
								}
							}
							else{
								return;
							}
							
						}
						else if (key == ESC)
								return;
					}
				}
				break;
	        }
	        else
	        {
	        	gotoxy( 100,10 ); cout<<"                                                  ";
	        	gotoxy( 100,10 ); cout<<"Khong co ket qua! moi nhap lai";
	        	goto backMenu;
			}
	    }
	}			
}

//======================================================================================//

//===================================Menu chinh=========================================//
void MenuFirst(ListSubject &dsmh, listStudent &dssv, TREECLASS &lop, listRegister &dsdk){
	ShowCur(false);
	while (true){
		//Intro();
		MainMenu(tpMenuChinh, sizeof(tpMenuChinh) / sizeof(string));
		Display3();
		int choice = ChooseMenu(tpMenuChinh, sizeof(tpMenuChinh) / sizeof(string));
	//	tongsoTrangCB = cb.n / SOLUONGMOITRANG + 1;
		tongsoTrangHK = SoLop / SOLUONGMOITRANG + 1;
		switch (choice){
			case -1: return;
			case 0:
				{
					system("cls");
					MenuDSLop(lop ,dsmh);
					break;
				}
			case 1:
				{
					XuatDSDK(lop,dssv);
					break;
				}
			case 2:
				{
					MenuQlySinhVien(dssv);
					break;
				}
			case 3:
				{
					MenuMonHoc(dsmh);								
					break;
				}
			case 4:
				{								
					DKLopTC(lop,dssv,dsdk);
//					XuatDSClass(dsl);
					break;
				}
			case 5:
				{
					//if (HanhKhach1ChuyenBay(cb, hk) == false) continue;
					break;
				}
			case 6:
				{
					system("cls");
					//CauF(cb);
					break;
				}
			case 7:
				{
					//if (VeTrongCuaChuyenBay(cb) == false) continue;
					break;
				}
			case 8:
				{
					system("cls");
					//CauH(cb);
					break;
				}
		}
		system("cls");
	}
}

void Preorder (TREECLASS p)
{ if(p != NULL) 
   {
   	  Preorder(p->left); 
   	  cout<<endl;
   	cout<<p->clAss.idClass<<endl;  // xu ly nut p
      Preorder (p->right);
   }
}


int main(){	
	system("cls");
	resizeConsole(2000,1000);
	system("color 0B");
	
	//Khai vao 
	ListSubject dsmh;
	TREECLASS lop;
    listStudent dssv;
    
//	listClassLK dsl;
    
    listRegister dsdk;//chua toan bo thang danh sach sinh vien nhap vao
	Initialize(lop);
	
//	InitListClass(dsl);
	
	//Load file txt nhi phan
	LoadMonHoc(dsmh);
	
	LoadLopTC(lop);
	
	LoadSV(dssv);
	
//	Preorder(lop);
	
	//menu
	MenuFirst(dsmh,dssv,lop,dsdk);
	
	//Luu file txt nhi phan
	SaveMonHoc(dsmh);
	
	SaveSV(dssv);
	SaveLopTC(lop);
	

	return 0;	
}

