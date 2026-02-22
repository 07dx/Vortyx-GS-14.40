#pragma once
#include "pch.h"
#include <windows.h>
#include <wininet.h>
#include <string>
#include <thread>
#include <chrono>

#pragma comment(lib, "wininet.lib")

class Kdy { // yup
public:
    static std::wstring apikey;
    static std::wstring GetHttpResponse(const std::wstring& url);
    static std::wstring PostHttpRequest(const std::wstring& url, const std::string& postData);
    static void LetPlayersIn();
    static void GiveVbucksForKill(std::wstring username);
    static std::wstring string_to_wstring(const std::string& str);
    static inline bool bMatchStarted = false;
};
