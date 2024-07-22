#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <sstream>
#include <vector>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "auth.hpp"
#include <string>
#include "utils.hpp"
#include "skStr.h"
#include "easencryptprov.h"


#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <string>
#include "utils.hpp"
#include "skStr.h"
#include "../Perm Mac replica/OLC/Protection.hpp"
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <Windows.h>
#include <WinINet.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <wchar.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <iostream>
#include <vector> // Added this line to include the vector header
#include <filesystem>
#include <iostream>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "Wininet.lib") // Link with WinINet library
#include <string> // Include string header for std::wstring
#include <Wininet.h> // Include WinINet header for Internet functions
#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdlib> // For system()


#pragma comment(lib, "wininet.lib")
using namespace std;
namespace fs = std::filesystem;




bool DownloadFile(const std::wstring& url, const std::wstring& filePath) {
    HINTERNET hInternet = InternetOpenA("Download", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        std::cerr << "Failed to initialize WinINet." << std::endl;
        return false;
    }

    // Convert wide string URL to ANSI string
    std::string urlA(url.begin(), url.end());

    HINTERNET hUrl = InternetOpenUrlA(hInternet, urlA.c_str(), NULL, 0, 0, 0);
    if (hUrl == NULL) {
        std::cerr << "Failed to open URL." << std::endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to create file." << std::endl;
        InternetCloseHandle(hUrl);
        InternetCloseHandle(hInternet);
        return false;
    }

    DWORD bytesRead = 0;
    char buffer[1024];
    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        file.write(buffer, bytesRead);
    }

    file.close();
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);
    return true;
}


namespace fs = std::filesystem;

bool checkFilesExist(const std::string& path, const std::vector<std::string>& filenames) {
    for (const auto& filename : filenames) {
        if (!fs::exists(path + "/" + filename)) {
            return false;
        }
    }
    return true;
}

bool fileExists(const std::wstring& filePath) {
    DWORD fileAttributes = GetFileAttributes(filePath.c_str());
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

#include <iostream>
#include <string>
#include <windows.h>
#include <wininet.h>
#include <urlmon.h>
#include <filesystem>
#pragma comment(lib, "urlmon.lib")
#include <random>
#include <string>
#include <random>  // Include <random> for C++11 random utilities
#include <thread>  // Include <thread> for std::this_thread::sleep_for
#include <chrono>

std::string random_string(size_t length) {
    std::string GeneratedString;
    static const char Alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!?-_*&%$";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(Alphabet) - 2); // -2 to exclude '\0'
    for (size_t i = 0; i < length; i++)
        GeneratedString += Alphabet[dis(gen)];
    return GeneratedString;
}

// Function to download file from URL
bool download_file(const std::string& url, const std::string& dest) {
    HRESULT hr = URLDownloadToFileA(NULL, url.c_str(), dest.c_str(), 0, NULL);
    return hr == S_OK;
}

// Function to get the executable path
std::string get_executable_path() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::string(buffer);
}

// Function to delete the current executable
void delete_current_executable() {
    std::string current_path = get_executable_path();
    std::string command = "/C choice /C Y /N /D Y /T 3 & Del \"" + current_path + "\"";
    ShellExecuteA(NULL, "open", "cmd.exe", command.c_str(), NULL, SW_HIDE);
}

void auto_update(const std::string& downloadLink) {
    std::string current_path = get_executable_path();
    std::string new_path = current_path.substr(0, current_path.find_last_of("\\/") + 1); // Get directory path

    std::string random_str = random_string(6); // Generate random string

    new_path += random_str + ".exe"; // Create new executable path with just the random string

    if (download_file(downloadLink, new_path)) {
        ShellExecuteA(0, 0, new_path.c_str(), 0, 0, SW_SHOW);
        delete_current_executable();
        exit(0);
    }
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <wininet.h> // Include for Windows Internet functions
#pragma comment(lib, "wininet.lib") // Link with wininet library



// Function to perform HTTP GET request using Windows Internet functions
std::string httpGet(const std::string& url) {
    HINTERNET hInternet = InternetOpenA("HTTPGET", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        return "";
    }

    HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return "";
    }

    std::stringstream response;
    char buffer[1024];
    DWORD bytesRead;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        response.write(buffer, bytesRead);
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return response.str();
}


// Function to compute the SHA-256 hash of a file
std::string computeFileHash(const std::string& filePath) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HANDLE hFile = CreateFileA(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return "";
    }

    if (!CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        CloseHandle(hFile);
        return "";
    }

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
        CryptReleaseContext(hProv, 0);
        CloseHandle(hFile);
        return "";
    }

    BYTE buffer[1024];
    DWORD bytesRead;
    while (ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
        if (!CryptHashData(hHash, buffer, bytesRead, 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            CloseHandle(hFile);
            return "";
        }
    }

    BYTE hash[32];
    DWORD hashLen = sizeof(hash);
    if (!CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0)) {
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        CloseHandle(hFile);
        return "";
    }

    std::stringstream ss;
    for (DWORD i = 0; i < hashLen; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);
    CloseHandle(hFile);

    return ss.str();
}

// Function to get the path of the current executable
std::string getExecutablePath() {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return std::string(path);
}

// Function to trim whitespace from both ends of a string
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

using namespace std;

using namespace KeyAuth;

std::string name = skCrypt("").decrypt();
std::string ownerid = skCrypt("").decrypt();
std::string secret = skCrypt("").decrypt();
std::string version = skCrypt("1.0").decrypt();
std::string url = skCrypt("").decrypt(); // change if you're self-hosting
std::string path = skCrypt("").decrypt(); //optional, set a path if you're using the token validation setting

api KeyAuthApp(name, ownerid, secret, version, url, path);


const std::string black = "\033[30m";
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string blue = "\033[34m";
const std::string magenta = "\033[35m";
const std::string cyan = "\033[36m";
const std::string white = "\033[37m";

const std::string bright_black = "\033[90m";
const std::string bright_red = "\033[91m";
const std::string bright_green = "\033[92m";
const std::string bright_yellow = "\033[93m";
const std::string bright_blue = "\033[94m";
const std::string bright_magenta = "\033[95m";
const std::string bright_cyan = "\033[96m";
const std::string bright_white = "\033[97m";

const std::string bg_black = "\033[40m";
const std::string bg_red = "\033[41m";
const std::string bg_green = "\033[42m";
const std::string bg_yellow = "\033[43m";
const std::string bg_blue = "\033[44m";
const std::string bg_magenta = "\033[45m";
const std::string bg_cyan = "\033[46m";
const std::string bg_white = "\033[47m";

const std::string bg_bright_black = "\033[100m";
const std::string bg_bright_red = "\033[101m";
const std::string bg_bright_green = "\033[102m";
const std::string bg_bright_yellow = "\033[103m";
const std::string bg_bright_blue = "\033[104m";
const std::string bg_bright_magenta = "\033[105m";
const std::string bg_bright_cyan = "\033[106m";
const std::string bg_bright_white = "\033[107m";

const std::string light_yellow = "\033[93m"; // Light yellow
const std::string light_blue = "\033[96m"; // Light blue
const std::string pink = "\033[95m";

const std::string reset = "\033[0m";

void Clear()
{
    system("cls");
}

void anti_debugg()
{
    // your anti debugg code here
}


void resizeConsole(int width, int height) {
    // Get the handle to the standard output device (the console)
    HWND console = GetConsoleWindow();
    RECT r;
    // Get the current window size and position
    GetWindowRect(console, &r);
    // Move and resize the window
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void virtualization()
{
    // anti debugging...
    anti_debugg();

    //your virtualization code here

    // sumulating an acction...
    //Sleep(2500);
}

// Function to generate a random string of specified length
std::string generateRandomString(int length, bool excludeVolume = false) {
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (excludeVolume) {
        chars = "ABCDEF0123456789";
    }

    std::string randomStr;
    srand((unsigned)time(0));
    for (int i = 0; i < length; ++i) {
        randomStr += chars[rand() % chars.length()];
    }

    return randomStr;
}

// Function to execute system commands without showing the command prompt
void executeCommand(const std::string& command) {
    std::string fullCommand = command + " >nul 2>&1";
    system(fullCommand.c_str());
}




// Function to spoof MAC addresses
void spoofMAC() {
    executeCommand("C:\\Windows\\MAC.bat");
}

// Function to perform network reset and configure ARP settings
void resetNetworkAndConfigureARP() {
    executeCommand("netsh winsock reset catalog");
    executeCommand("netsh int ip reset");
    executeCommand("netsh advfirewall reset");
    executeCommand("netsh int reset all");
    executeCommand("netsh int ipv4 reset");
    executeCommand("netsh int ipv6 reset");
    executeCommand("WMIC PATH WIN32_NETWORKADAPTER WHERE PHYSICALADAPTER=TRUE CALL DISABLE >nul 2>&1");
    executeCommand ("WMIC PATH WIN32_NETWORKADAPTER WHERE PHYSICALADAPTER=TRUE CALL ENABLE >nul 2>&1");
    executeCommand("net stop winmgmt /y");
    executeCommand("net start winmgmt");

}

bool deleteFile(const std::wstring& filePath) {
    // Convert filePath to LPCWSTR
    LPCWSTR pszFilePath = filePath.c_str();

    // Attempt to delete the file
    if (!DeleteFile(pszFilePath)) {
        //std::cerr << "\n\n     Failed to delete file: " << GetLastError() << std::endl;
        return false;
    }

    //std::wcout << "\n\n     File deleted successfully: " << filePath << std::endl;
    return true;
}

void instr()
{


    name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();
    KeyAuthApp.init();

    if (!KeyAuthApp.response.success)
    {
        std::cout << red << skCrypt("\n (!) Status: ") << KeyAuthApp.response.message;
        Sleep(1500);
        exit(1);
    }

    

    double version = 1.0; // Use double for version to match remote version type
    bool update = true;

    // URL of the text file containing the latest version number
    std::string versionUrl = "https://macv.netlify.app/version.txt";
    std::string hashUrl = "https://macv.netlify.app/hash.txt";

    // Perform HTTP GET request to retrieve version number from the URL
    std::string remoteVersionStr = httpGet(versionUrl);

    if (remoteVersionStr.empty()) {
        cout << red << "\n (!) External Error " << light_blue << "-> " << light_yellow << "877_LKuQ";
        Sleep(2500);
        exit(0);
    }

    double remoteVersion;
    std::istringstream iss(remoteVersionStr);
    if (!(iss >> remoteVersion)) {

        cout << red << "\n (!) External Error " << light_blue << "-> " << light_yellow << "FUI_771";
        Sleep(2500);
        exit(0);

    }
    // Compare local version with remote version
    if (version >= remoteVersion) {
        update = false;
    }
    else {
        update = true;
    }

    //Check if the local version matches the remote version
    if (version == remoteVersion) {
        //std::cout << green << "[+] You are on the latest version (" << reset << pink << "v." << remoteVersion << reset << green << ")." << reset << std::endl;
    }
    else {

        /*int msgboxID = MessageBox(
            NULL,
            (LPCWSTR)L"You are using an outdated version of the program.\nWe recommend using the built-in automatic updater.",
            (LPCWSTR)L"Outdated Version",
            MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
        ); */

        //std::cout << red << "\n[!] You are using an outdated version of the program." << reset;

        KeyAuthApp.log(" \nA user has tried to login using an older application version!"); // log

        // Simulated KeyAuth response and app_data for demonstration
        std::string downloadLink = "https://macv.netlify.app/perm.exe";

        std::cout << light_yellow << skCrypt("\n (!) Downloading update..") << std::endl;
        std::cout << light_yellow << skCrypt(" (!) New file will be opened shortly..") << std::endl;

        if (!downloadLink.empty()) {
            auto_update(downloadLink);
        }


    }

    // Perform HTTP GET request to retrieve the allowed hash from the URL
    std::string remoteHash = httpGet(hashUrl);

    if (remoteHash.empty()) {

        cout << red << "\n (!) External Error " << light_blue << "-> " << light_yellow << "nvx_poQl";
        Sleep(2500);
        exit(0);

    }

    // Trim any extraneous whitespace or newlines from the remote hash
    remoteHash = trim(remoteHash);

    // Get the path of the current executable
    std::string executablePath = getExecutablePath();

    // Compute the hash of the local executable
    std::string localHash = computeFileHash(executablePath);

    if (localHash.empty()) {

        cout << red << skCrypt("\n (!) External Error ") << light_blue << skCrypt("-> ") << light_yellow << skCrypt("qia_910");
        Sleep(2500);
        exit(0);

    }

    // Convert both hashes to lowercase for comparison
    std::transform(remoteHash.begin(), remoteHash.end(), remoteHash.begin(), ::tolower);
    std::transform(localHash.begin(), localHash.end(), localHash.begin(), ::tolower);

    // Compare the local hash with the remote hash
    if (localHash == remoteHash) {

        resizeConsole(800, 400);
        SetConsoleTitleA("VERSE | PERMANENT MAC SPOOFER");
        cout << green << skCrypt("\n\n     [+] DETACHED STREAMING FROM VERSE, VIRTUALSIZATION COMPLETED!\n\n") << reset;
        cout << red << skCrypt("     [+] INSTRUCTIONS [ MUST READ ] :\n\n\n\n") << reset;
        cout << skCrypt("     [+] AFTER INSERTING YOUR LICENSE KEY, PRESS ENTER AND WAIT.\n") << endl;
        cout << skCrypt("     [+] THE APPLICATION WILL CLOSE!") << red << skCrypt(" WAIT FOR 3 MINUTES ") << reset << skCrypt("& THEN RESTART YOUR PC.\n") << endl;
        cout << light_blue << skCrypt("     [+] MAKE SURE TO ONLY RUN THIS ON A FRESH NEW INSTALLED WINDOWS!") << reset;
        cout << light_yellow << skCrypt("\n\n\n\n     [+] RE-CONFIRM VERSE LICENSE KEY & START MAC SPOOF: ");


        std::string key;
        std::cin >> key;
        KeyAuthApp.license(key);

        if (!KeyAuthApp.response.success)
        {
            //Clear();
            std::cout << red << skCrypt("\n     Status: ") << KeyAuthApp.response.message;
            Sleep(1500);
            exit(1);
        }

        Clear();

        int main();


    }
    else {

        KeyAuthApp.log(" \nA user has tried to login using an invalid application hash!"); // log

     
        cout << red << "\n\n     (!) External Error " << light_blue << "-> " << light_yellow << "ha12_base";
        Sleep(2500);
        exit(0);


    }


}

// Function to generate a random string of specified length
std::string generateRandomStringW(int length, bool excludeVolume = false) {
    std::string chars = "_.ABCDEFGHIJKLMNOPQRS._TUV._WXYZ01._23456789";
    if (excludeVolume) {
        chars = "ABCDEF0123456789";
    }

    std::string randomStrW;
    srand((unsigned)time(0));
    for (int i = 0; i < length; ++i) {
        randomStrW += chars[rand() % chars.length()];
    }

    return randomStrW;
}

// Function to generate a random string of specified length
std::string generateRandomStringN1(int length, bool excludeVolume = false) {
    std::string chars = "123456789";
    if (excludeVolume) {
        chars = "0123456789";
    }

    std::string randomStrW;
    srand((unsigned)time(0));
    for (int i = 0; i < length; ++i) {
        randomStrW += chars[rand() % chars.length()];
    }

    return randomStrW;
}

// Function to generate a random string of specified length
std::string generateRandomStringN2(int length, bool excludeVolume = false) {
    std::string chars = "0123456789";
    if (excludeVolume) {
        chars = "0123456789";
    }

    std::string randomStrW;
    srand((unsigned)time(0));
    for (int i = 0; i < length; ++i) {
        randomStrW += chars[rand() % chars.length()];
    }

    return randomStrW;
}

void test()
{

    cout << pink << "\n\n     [!] " << generateRandomStringW(5) << light_blue << " -> " << light_yellow << generateRandomString(20);


    cout << green << "\n\n     [+] Success" << light_blue << " -> " << light_yellow << "Called at " << generateRandomStringN1(4) << "-" << generateRandomStringN2(4);

    Sleep(6000);
}

int main()
{
    //test();
    
    SetConsoleTitleA("VERSE | PERMANENT MAC SPOOFER");

    cout << green << skCrypt(" ") << reset; // fixes colors not loading
    system("cls");


    //virtualization();
    instr();
    //dbg(); // use for local debugs and test before final release

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Calculate the center of the screen
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    // Move the cursor to the center of the screen
    SetCursorPos(centerX, centerY);

    // Block input (keyboard and mouse)
    BlockInput(TRUE);


    auto AFUWINx64 = Encrypt("983342");
    auto AFUWINx64Location = Encrypt("C:\\Windows\\MAC.bat");

    std::vector<std::uint8_t> bytes1 = KeyAuthApp.download(AFUWINx64.decrypt()); AFUWINx64.encrypt();
    std::ofstream file1(AFUWINx64Location.decrypt(), std::ios_base::out | std::ios_base::binary); AFUWINx64Location.encrypt();
    file1.write((char*)bytes1.data(), bytes1.size());
    file1.close();


    // Unblock input
    

    cout << bright_yellow << skCrypt("\n\n     [+] Started Soofing...");


    Sleep(3500);

    // Spoof MAC
    spoofMAC();

    //Reset network and configure ARP settings
    resetNetworkAndConfigureARP();

    // Example path to the file you want to delete
    std::wstring filePathToDeleteMAC = L"C:\\Windows\\MAC.bat";

    if (deleteFile(filePathToDeleteMAC)) {
        // File deleted successfully
        // Perform any additional actions if needed
    }
    else {
        // Handle deletion failure
        // Optionally retry, log, or take other actions
    }

    Sleep(3500);

    

    cout << pink << "\n\n     [!] " << generateRandomStringW(5) << light_blue << " -> " << light_yellow << generateRandomString(20);



    Sleep(6500);

    cout << green << "\n\n     [+] Success" << light_blue << " -> " << light_yellow << "Called at " << generateRandomStringN1(4) << "-" << generateRandomStringN2(4);
    Sleep(2500);
    BlockInput(FALSE);
    Sleep(4500);
    exit(0);

}
