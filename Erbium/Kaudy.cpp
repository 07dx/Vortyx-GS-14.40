#include "pch.h"
#include "Kaudy.h"
#include <iostream>
#include "Globals.h"


std::wstring Kdy::apikey = L"Key-7656237846Tzy87655DoNotChangeDueToArena";

std::wstring Kdy::GetHttpResponse(const std::wstring& url) {
    HINTERNET hInternet = InternetOpen(L"WinINetExample", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) return L"";
    HINTERNET hConnect = InternetOpenUrl(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) { InternetCloseHandle(hInternet); return L""; }
    const DWORD bufferSize = 4096; char buffer[bufferSize]; DWORD bytesRead; std::wstring response;
    while (InternetReadFile(hConnect, buffer, bufferSize, &bytesRead) && bytesRead) response.append(buffer, buffer + bytesRead);
    InternetCloseHandle(hConnect); InternetCloseHandle(hInternet);
    return response;
}

std::wstring Kdy::PostHttpRequest(const std::wstring& url, const std::string& postData) {
    HINTERNET hInternet = InternetOpen(L"WinINetExample", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) return L"";
    URL_COMPONENTS urlComp = { sizeof(URL_COMPONENTS) }; wchar_t host[256], path[1024];
    urlComp.lpszHostName = host; urlComp.dwHostNameLength = _countof(host);
    urlComp.lpszUrlPath = path; urlComp.dwUrlPathLength = _countof(path);
    if (!InternetCrackUrl(url.c_str(), (DWORD)url.length(), 0, &urlComp)) { InternetCloseHandle(hInternet); return L""; }
    HINTERNET hConnect = InternetConnect(hInternet, urlComp.lpszHostName, urlComp.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) { InternetCloseHandle(hInternet); return L""; }
    HINTERNET hRequest = HttpOpenRequest(hConnect, L"POST", urlComp.lpszUrlPath, NULL, NULL, NULL,
        (urlComp.nScheme == INTERNET_SCHEME_HTTPS ? INTERNET_FLAG_SECURE : 0), 0);
    if (!hRequest) { InternetCloseHandle(hConnect); InternetCloseHandle(hInternet); return L""; }
    BOOL sent = HttpSendRequest(hRequest, L"Content-Type: application/x-www-form-urlencoded",
        (DWORD)wcslen(L"Content-Type: application/x-www-form-urlencoded"),
        (LPVOID)postData.c_str(), (DWORD)postData.size());
    if (!sent) { InternetCloseHandle(hRequest); InternetCloseHandle(hConnect); InternetCloseHandle(hInternet); return L""; }
    const DWORD bufferSize = 4096; char buffer[bufferSize]; DWORD bytesRead = 0; std::wstring response;
    while (InternetReadFile(hRequest, buffer, bufferSize, &bytesRead) && bytesRead) response.append(buffer, buffer + bytesRead);
    InternetCloseHandle(hRequest); InternetCloseHandle(hConnect); InternetCloseHandle(hInternet);
    return response;
}



void Kdy::GiveVbucksForKill(std::wstring username) {
    std::thread([username]() {
        std::wstring url = L"http://26.157.83.30:3013/api/Chaos/" + username + L"/Kill/" + Kdy::apikey;// ip and : for port for to use vps
        std::wstring res = Kdy::GetHttpResponse(url);
        std::wcout << L"Backend response: " << res << std::endl;
        }).detach();
}


std::wstring Kdy::string_to_wstring(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}
