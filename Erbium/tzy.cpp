#include "pch.h"
#include "tzy.h"
#include <iostream>
#include "Globals.h"

std::string Tzy::apikey = "Key-7656237846Tzy87655DoNotChangeDueToArena";

std::string Tzy::GetHttpResponse(const std::string& url)
{
    HINTERNET hInternet = InternetOpenA("tuff", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) return {};
    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return {};
    }
    std::string response;
    char buffer[4096];
    DWORD bytesRead = 0;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead)
        response.append(buffer, bytesRead);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    while (!response.empty() && (response.back() == '\n' || response.back() == '\r'))
        response.pop_back();
    return response;
}

std::string Tzy::PostHttpRequest(const std::string& url, const std::string& postData)
{
    HINTERNET hInternet = InternetOpenA("tuff", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) return {};
    URL_COMPONENTSA urlComp{};
    urlComp.dwStructSize = sizeof(urlComp);
    char host[256]{}, path[1024]{};
    urlComp.lpszHostName = host; urlComp.dwHostNameLength = sizeof(host);
    urlComp.lpszUrlPath = path; urlComp.dwUrlPathLength = sizeof(path);
    if (!InternetCrackUrlA(url.c_str(), 0, 0, &urlComp)) {
        InternetCloseHandle(hInternet);
        return {};
    }
    HINTERNET hConnect = InternetConnectA(hInternet, host, urlComp.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return {};
    }
    DWORD flags = (urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? INTERNET_FLAG_SECURE : 0;
    HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", path, NULL, NULL, NULL, flags, 0);
    if (!hRequest) {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return {};
    }
    HttpSendRequestA(hRequest, "Content-Type: application/json\r\n", -1, (LPVOID)postData.data(), (DWORD)postData.size());
    std::string response;
    char buffer[4096];
    DWORD bytesRead = 0;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead) && bytesRead)
        response.append(buffer, bytesRead);
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return response;
}

void Tzy::LetPlayersIn()
{
    std::thread([]() {
        using namespace std::chrono_literals;
        const std::string url = "http://26.157.83.30:1111/started";
        while (!Tzy::bMatchStarted) {
            std::string res = Tzy::PostHttpRequest(url, "");
            std::this_thread::sleep_for(1000ms);
        }
        }).detach();
}

void Tzy::GiveVbucksForKill(const std::string& username)
{
    std::thread([username]() {
        std::string url = "http://26.157.83.30:3013/api/Chaos/" + username + "/Kill/" + Tzy::apikey;
        std::string res = Tzy::GetHttpResponse(url);
        }).detach();
}


