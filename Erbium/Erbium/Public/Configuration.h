#pragma once

struct FConfiguration
{
    static inline auto Playlist = L"/Game/Athena/Playlists/Showdown/Playlist_ShowdownAlt_Duos.Playlist_ShowdownAlt_Duos"; 
    static inline auto MaxTickRate = 60;
    static inline auto bLateGame = true;
    static inline auto LateGameZone = 3; // starting zone
    static inline auto bLateGameLongZone = false; // zone doesnt close for a long time
    static inline auto bEnableCheats = false;
    static inline auto SiphonAmount = 50; // set to 0 to disable
    static inline auto bInfiniteMats = false;
    static inline auto bInfiniteAmmo = false;
    static inline auto bForceRespawns = false; // build your client with this too!
    static inline auto bJoinInProgress = false;
    static inline auto bAutoRestart = true;
    static inline auto bKeepInventory = false;
    static inline auto Port = 7777;
    static inline constexpr auto bEnableIris = true; 
    static inline constexpr auto bGUI = true;
    static inline constexpr auto bCustomCrashReporter = true;
    static inline constexpr auto bUseStdoutLog = false;
    static inline constexpr auto WebhookURL = ""; // fill in if you want status to send to a webhook

    static inline constexpr auto bDuos = true; // to enable/disable duos on the gs -> tzy

    static inline const char* BackendUrl = "http://26.157.83.30:3013";
    static inline const char* MatchmakerUrl = "http://26.157.83.30:1111";
};
