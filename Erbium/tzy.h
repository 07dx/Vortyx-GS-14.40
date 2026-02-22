#pragma once
#include "pch.h"
#include <windows.h>
#include <wininet.h>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include "FortniteGame/Public/FortPlayerControllerAthena.h"

#pragma comment(lib, "wininet.lib")

class Tzy {
    static inline HINTERNET hSession = InternetOpenA("tzy", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
public:
    static std::string apikey;
    static std::string GetHttpResponse(const std::string& url);
    static std::string PostHttpRequest(const std::string& url, const std::string& postData);
    static void LetPlayersIn();
    static void GiveVbucksForKill(const std::string& username);
    static inline bool bMatchStarted = false;

    static void FuckExploiter(AFortPlayerControllerAthena* PC) {
        if (!PC) return;
        if (auto* Pawn = PC->MyFortPawn)
            Pawn->K2_DestroyActor();
        GPlayerControllers.Add(PC);
    }

    static std::string GETResponse(const std::string& url) {
        if (url.empty()) return "";
        URL_COMPONENTSA c{};
        c.dwStructSize = sizeof(c);
        char host[256]{}, path[1024]{};
        c.lpszHostName = host;
        c.dwHostNameLength = sizeof(host);
        c.lpszUrlPath = path;
        c.dwUrlPathLength = sizeof(path);
        if (!InternetCrackUrlA(url.c_str(), 0, 0, &c)) return "";
        if (!hSession) hSession = InternetOpenA("tzy", INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);
        if (!hSession) return "";
        DWORD flags = INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_RELOAD;
        if (c.nScheme == INTERNET_SCHEME_HTTPS) flags |= INTERNET_FLAG_SECURE;
        HINTERNET conn = InternetConnectA(hSession, host, c.nPort, 0, 0, INTERNET_SERVICE_HTTP, 0, 0);
        if (!conn) return "";
        HINTERNET req = HttpOpenRequestA(conn, "GET", path, 0, 0, 0, flags, 0);
        if (!req) { InternetCloseHandle(conn); return ""; }
        std::string data;
        if (HttpSendRequestA(req, 0, 0, 0, 0)) {
            char buf[4096];
            DWORD read;
            while (InternetReadFile(req, buf, sizeof(buf), &read) && read)
                data.append(buf, read);
        }
        InternetCloseHandle(req);
        InternetCloseHandle(conn);
        return data;
    }

    inline size_t CallBack(void* ptr, size_t size, size_t nmemb, std::string* data) {
        data->append((char*)ptr, size * nmemb);
        return size * nmemb;
    }

    static std::string POSTResponse(const std::string& url, const std::string& body) {
        std::string ret;
        URL_COMPONENTSA c{};
        c.dwStructSize = sizeof(c);
        char host[256]{}, path[1024]{};
        c.lpszHostName = host;
        c.dwHostNameLength = sizeof(host);
        c.lpszUrlPath = path;
        c.dwUrlPathLength = sizeof(path);
        if (!InternetCrackUrlA(url.c_str(), 0, 0, &c)) return ret;
        DWORD flags = INTERNET_FLAG_RELOAD | ((c.nScheme == INTERNET_SCHEME_HTTPS) ? INTERNET_FLAG_SECURE : 0);
        if (HINTERNET conn = InternetConnectA(hSession, host, c.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0)) {
            if (HINTERNET req = HttpOpenRequestA(conn, "POST", path, NULL, NULL, NULL, flags, 0)) {
                if (HttpSendRequestA(req, "Content-Type: application/json", -1L, (LPVOID)body.c_str(), (DWORD)body.size())) {
                    char buf[4096];
                    DWORD read = 0;
                    ret.reserve(8192);
                    while (InternetReadFile(req, buf, sizeof(buf), &read) && read)
                        ret.append(buf, read);
                }
                InternetCloseHandle(req);
            }
            InternetCloseHandle(conn);
        }
        return ret;
    }

    static std::string JsonBody(const std::map<std::string, std::string>& values) {
        std::string body = "{";
        bool first = true;
        for (const auto& [key, value] : values) {
            if (!first) body += ",";
            first = false;
            body += "\"" + key + "\":\"" + value + "\"";
        }
        body += "}";
        return body;
    }


    static inline void CheckPlayer(AFortPlayerControllerAthena* PC) {
        auto PlayerState = (AFortPlayerStateAthena*)PC->PlayerState;
        std::string name = PlayerState->GetPlayerName().ToString().c_str();
        /*auto ip = Tzy::GETResponse("http://127.0.0.1:3013/fortnite/api/matchmaking/session/player-ip/" + name);
        printf("nigga ip: %s\n", ip.c_str());
        if (ip == "Invalid" || ip == "")
        {
            FuckExploiter(PC);
            return;
        }
        std::map<std::string, std::string> json = {
            { "backend", "Chaos"},
            { "ip", ip }
        };
        printf("nigga payload: %s\n", JsonBody(json).c_str());
        auto Response = Tzy::POSTResponse("http://backend.projectlumicmp.xyz:2737/tac/socket/player/check", JsonBody(json));
        printf("nigga response: %s\n", Response.c_str());
        if (!Response.contains("yes")) {
            FuckExploiter(PC);
            return;
        }*/
        //auto response = Tzy::GETResponse("http://26.157.83.30:3013/tzy/anticheat/" + name + "/oWIedhweofawhfgTzyTheGoat");
        //if (response != "Player verified" || response.empty())
       // {
          // FuckExploiter(PC);
        //   return;
      //  }

    }
};
