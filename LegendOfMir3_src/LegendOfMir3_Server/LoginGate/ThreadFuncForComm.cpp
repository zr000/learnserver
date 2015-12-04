#include "stdafx.h"
#include "../Common/ServerConfig.h"

#define PACKET_KEEPALIVE		"%--$"

extern HWND				g_hToolBar;
extern HWND				g_hStatusBar;

extern SOCKET			g_csock;
extern SOCKADDR_IN		g_caddr;

void					SendExToServer(char *pszPacket,int nLen);

BOOL					jRegGetKey(LPCTSTR pSubKeyName, LPCTSTR pValueName, LPBYTE pValue);

VOID WINAPI OnTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	switch (idEvent)
	{
		case _ID_TIMER_KEEPALIVE:
		{
			if (g_csock != INVALID_SOCKET)
			{
				SendExToServer(PACKET_KEEPALIVE,strlen(PACKET_KEEPALIVE));
				SendMessage(g_hStatusBar, SB_SETTEXT, MAKEWORD(2, 0), (LPARAM)_TEXT("Check Activity"));
			}

			break;
		}
		case _ID_TIMER_CONNECTSERVER:
		{
			if (g_csock == INVALID_SOCKET)
			{
				DWORD	dwIP = 0;
				int		nPort = 0;

				InsertLogMsg(IDS_APPLY_RECONNECT);

				ENGINE_COMPONENT_INFO info = g_SeverConfig.getLoginSrvInfo();

				nPort = info.intport?info.intport:5500;
				ConnectToServer(g_csock, &g_caddr, _IDM_CLIENTSOCK_MSG, info.intip.c_str(),dwIP, nPort, FD_CONNECT|FD_READ|FD_CLOSE);
			}

			break;
		}
	}
}
