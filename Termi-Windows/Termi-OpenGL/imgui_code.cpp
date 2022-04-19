/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Windows version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file for ImGUI
 * INFORAMTION: Compile solution, else check Victor Gordan's video
*/

#include "imgui_code.hpp"

#include "dirent.h"

using namespace std;
using namespace ImGui;
using namespace nlohmann;

using namespace Translation;

#pragma warning(disable : 4996)

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Kernel32.lib")

Console console;
Renderer* render;

json j;

/* Commands main code */

/*
 * Return version of Windows operating system
 *
 * In own function
*/
static const char* OperatingSystem()
{
    OSVERSIONINFO vi;
    vi.dwOSVersionInfoSize = sizeof(vi);
    if (GetVersionEx(&vi) == 0)
    {
        return 0;
    }
    switch (vi.dwPlatformId)
    {
    case VER_PLATFORM_WIN32s:
        return "Windows 3.x";
    case VER_PLATFORM_WIN32_WINDOWS:
        return vi.dwMinorVersion == 0 ? "Windows 95" : "Windows 98";
    case VER_PLATFORM_WIN32_NT:
        return "Windows NT";
    default:
        return "Unknown";
}
}

/* Uptime part - in own functions */
/* Return uptime time in seoconds */
uint64_t UptimeS()
{
    return GetTickCount64() / 1000;
}

/* Return uptime time in minutes */
uint64_t UptimeM()
{
    return GetTickCount64() / 60000;
}

/* Return uptime time in hours */
uint64_t UptimeH()
{
    return GetTickCount64() / 3600000;
}

/* neofetch main function */
void neofetch(std::string argument, std::string argument2)
{
    /* Username and computer name */
    TCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName((TCHAR*)username, &username_len);

    TCHAR computer[UNLEN + 1];
    DWORD computer_len = UNLEN + 1;
    GetComputerName((TCHAR*)computer, &computer_len);

    char new_username[UNLEN];
    char new_computer[UNLEN];

    wcstombs(new_username, username, wcslen(username) + 1);
    wcstombs(new_computer, computer, wcslen(computer) + 1);

    /* Memory */
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);

    console.AddLog("\n");
    console.AddLog("\t %s @ %s\n", new_username, new_computer);
    console.AddLog("--------------------------------------------\n");

    console.AddLog("\n");
    console.AddLog("\tOperating system: %s\t\n", OperatingSystem());

    if (UptimeH() < 1)
    {
        console.AddLog("\tUptime : %d minutes\t\n", UptimeM());
    }
    else
    {
        console.AddLog("\tUptime : %d hours\t\n", UptimeH());
    }

    int regs[4] = { 0 };
    char vendor[13];
    __cpuid(regs, 0);              // mov eax,0; cpuid
    memcpy(vendor, &regs[1], 4);   // copy EBX
    memcpy(vendor + 4, &regs[3], 4); // copy EDX
    memcpy(vendor + 8, &regs[2], 4); // copy ECX
    vendor[12] = '\0';

    console.AddLog("\t--------------------- CPU --------------------\t\n");

    char CPUString[0x20];
    char CPUBrandString[0x40];
    int CPUInfo[4] = { -1 };
    int nSteppingID = 0;
    int nModel = 0;
    int nFamily = 0;
    int nProcessorType = 0;
    int nExtendedmodel = 0;
    int nExtendedfamily = 0;
    int nBrandIndex = 0;
    int nCLFLUSHcachelinesize = 0;
    int nLogicalProcessors = 0;
    int nAPICPhysicalID = 0;
    int nFeatureInfo = 0;
    int nCacheLineSize = 0;
    int nL2Associativity = 0;
    int nCacheSizeK = 0;
    int nPhysicalAddress = 0;
    int nVirtualAddress = 0;
    int nRet = 0;

    int nCores = 0;
    int nCacheType = 0;
    int nCacheLevel = 0;
    int nMaxThread = 0;
    int nSysLineSize = 0;
    int nPhysicalLinePartitions = 0;
    int nWaysAssociativity = 0;
    int nNumberSets = 0;

    unsigned    nIds, nExIds, i;

    bool    bSSE3Instructions = false;
    bool    bMONITOR_MWAIT = false;
    bool    bCPLQualifiedDebugStore = false;
    bool    bVirtualMachineExtensions = false;
    bool    bEnhancedIntelSpeedStepTechnology = false;
    bool    bThermalMonitor2 = false;
    bool    bSupplementalSSE3 = false;
    bool    bL1ContextID = false;
    bool    bCMPXCHG16B = false;
    bool    bxTPRUpdateControl = false;
    bool    bPerfDebugCapabilityMSR = false;
    bool    bSSE41Extensions = false;
    bool    bSSE42Extensions = false;
    bool    bPOPCNT = false;

    bool    bMultithreading = false;

    bool    bLAHF_SAHFAvailable = false;
    bool    bCmpLegacy = false;
    bool    bSVM = false;
    bool    bExtApicSpace = false;
    bool    bAltMovCr8 = false;
    bool    bLZCNT = false;
    bool    bSSE4A = false;
    bool    bMisalignedSSE = false;
    bool    bPREFETCH = false;
    bool    bSKINITandDEV = false;
    bool    bSYSCALL_SYSRETAvailable = false;
    bool    bExecuteDisableBitAvailable = false;
    bool    bMMXExtensions = false;
    bool    bFFXSR = false;
    bool    b1GBSupport = false;
    bool    bRDTSCP = false;
    bool    b64Available = false;
    bool    b3DNowExt = false;
    bool    b3DNow = false;
    bool    bNestedPaging = false;
    bool    bLBRVisualization = false;
    bool    bFP128 = false;
    bool    bMOVOptimization = false;

    bool    bSelfInit = false;
    bool    bFullyAssociative = false;


    // __cpuid with an InfoType argument of 0 returns the number of
    // valid Ids in CPUInfo[0] and the CPU identification string in
    // the other three array elements. The CPU identification string is
    // not in linear order. The code below arranges the information 
    // in a human readable form.
    __cpuid(CPUInfo, 0);
    nIds = CPUInfo[0];
    memset(CPUString, 0, sizeof(CPUString));
    *((int*)CPUString) = CPUInfo[1];
    *((int*)(CPUString + 4)) = CPUInfo[3];
    *((int*)(CPUString + 8)) = CPUInfo[2];

    // Get the information associated with each valid Id
    for (i = 0; i <= nIds; ++i)
    {
        __cpuid(CPUInfo, i);

        // Interpret CPU feature information.
        if (i == 1)
        {
            nSteppingID = CPUInfo[0] & 0xf;
            nModel = (CPUInfo[0] >> 4) & 0xf;
            nFamily = (CPUInfo[0] >> 8) & 0xf;
            nProcessorType = (CPUInfo[0] >> 12) & 0x3;
            nExtendedmodel = (CPUInfo[0] >> 16) & 0xf;
            nExtendedfamily = (CPUInfo[0] >> 20) & 0xff;
            nBrandIndex = CPUInfo[1] & 0xff;
            nCLFLUSHcachelinesize = ((CPUInfo[1] >> 8) & 0xff) * 8;
            nLogicalProcessors = ((CPUInfo[1] >> 16) & 0xff);
            nAPICPhysicalID = (CPUInfo[1] >> 24) & 0xff;
            bSSE3Instructions = (CPUInfo[2] & 0x1) || false;
            bMONITOR_MWAIT = (CPUInfo[2] & 0x8) || false;
            bCPLQualifiedDebugStore = (CPUInfo[2] & 0x10) || false;
            bVirtualMachineExtensions = (CPUInfo[2] & 0x20) || false;
            bEnhancedIntelSpeedStepTechnology = (CPUInfo[2] & 0x80) || false;
            bThermalMonitor2 = (CPUInfo[2] & 0x100) || false;
            bSupplementalSSE3 = (CPUInfo[2] & 0x200) || false;
            bL1ContextID = (CPUInfo[2] & 0x300) || false;
            bCMPXCHG16B = (CPUInfo[2] & 0x2000) || false;
            bxTPRUpdateControl = (CPUInfo[2] & 0x4000) || false;
            bPerfDebugCapabilityMSR = (CPUInfo[2] & 0x8000) || false;
            bSSE41Extensions = (CPUInfo[2] & 0x80000) || false;
            bSSE42Extensions = (CPUInfo[2] & 0x100000) || false;
            bPOPCNT = (CPUInfo[2] & 0x800000) || false;
            nFeatureInfo = CPUInfo[3];
            bMultithreading = (nFeatureInfo & (1 << 28)) || false;
        }
    }

    // Calling __cpuid with 0x80000000 as the InfoType argument
    // gets the number of valid extended IDs.
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];
    memset(CPUBrandString, 0, sizeof(CPUBrandString));

    // Get the information associated with each extended ID.
    for (i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(CPUInfo, i);

        if (i == 0x80000001)
        {
            bLAHF_SAHFAvailable = (CPUInfo[2] & 0x1) || false;
            bCmpLegacy = (CPUInfo[2] & 0x2) || false;
            bSVM = (CPUInfo[2] & 0x4) || false;
            bExtApicSpace = (CPUInfo[2] & 0x8) || false;
            bAltMovCr8 = (CPUInfo[2] & 0x10) || false;
            bLZCNT = (CPUInfo[2] & 0x20) || false;
            bSSE4A = (CPUInfo[2] & 0x40) || false;
            bMisalignedSSE = (CPUInfo[2] & 0x80) || false;
            bPREFETCH = (CPUInfo[2] & 0x100) || false;
            bSKINITandDEV = (CPUInfo[2] & 0x1000) || false;
            bSYSCALL_SYSRETAvailable = (CPUInfo[3] & 0x800) || false;
            bExecuteDisableBitAvailable = (CPUInfo[3] & 0x10000) || false;
            bMMXExtensions = (CPUInfo[3] & 0x40000) || false;
            bFFXSR = (CPUInfo[3] & 0x200000) || false;
            b1GBSupport = (CPUInfo[3] & 0x400000) || false;
            bRDTSCP = (CPUInfo[3] & 0x8000000) || false;
            b64Available = (CPUInfo[3] & 0x20000000) || false;
            b3DNowExt = (CPUInfo[3] & 0x40000000) || false;
            b3DNow = (CPUInfo[3] & 0x80000000) || false;
        }

        // Interpret CPU brand string and cache information.
        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000006)
        {
            nCacheLineSize = CPUInfo[2] & 0xff;
            nL2Associativity = (CPUInfo[2] >> 12) & 0xf;
            nCacheSizeK = (CPUInfo[2] >> 16) & 0xffff;
        }
        else if (i == 0x80000008)
        {
            nPhysicalAddress = CPUInfo[0] & 0xff;
            nVirtualAddress = (CPUInfo[0] >> 8) & 0xff;
        }
        else if (i == 0x8000000A)
        {
            bNestedPaging = (CPUInfo[3] & 0x1) || false;
            bLBRVisualization = (CPUInfo[3] & 0x2) || false;
        }
        else if (i == 0x8000001A)
        {
            bFP128 = (CPUInfo[0] & 0x1) || false;
            bMOVOptimization = (CPUInfo[0] & 0x2) || false;
        }
    }

    // Display all the information in user-friendly format.

    console.AddLog("\tCPU String: %s\t\n", CPUString);

    if (nIds >= 1)
    {
        if (nSteppingID)
            console.AddLog("\tStepping ID = %d\t\n", nSteppingID);
        if (nModel)
            console.AddLog("\tModel = %d\t\n", nModel);
        if (nFamily)
            console.AddLog("\tFamily = %d\t\n", nFamily);
        if (nProcessorType)
            console.AddLog("\tProcessor Type = %d\t\n", nProcessorType);
        if (nExtendedmodel)
            console.AddLog("\tExtended model = %d\t\n", nExtendedmodel);
        if (nExtendedfamily)
            console.AddLog("\tExtended family = %d\t\n", nExtendedfamily);
        if (nBrandIndex)
            console.AddLog("\tBrand Index = %d\t\n", nBrandIndex);
        if (nCLFLUSHcachelinesize)
            console.AddLog("\tCLFLUSH cache line size = %d\t\n",
                nCLFLUSHcachelinesize);
        if (bMultithreading && (nLogicalProcessors > 0))
            console.AddLog("\tLogical Processor Count = %d\t\n", nLogicalProcessors);
        if (nAPICPhysicalID)
            console.AddLog("\tAPIC Physical ID = %d\t\n", nAPICPhysicalID);
    }

    console.AddLog("\n");

    if (nExIds >= 0x80000004)
        console.AddLog("\tCPU Brand String: %s\t\n", CPUBrandString);

    if (nExIds >= 0x80000006)
    {
        console.AddLog("\tCache Line Size = %d\t\n", nCacheLineSize);
        console.AddLog("\tL2 Associativity = %d\t\n", nL2Associativity);
        console.AddLog("\tCache Size = %dK\t\n", nCacheSizeK);
    }


    for (i = 0;; i++)
    {
        __cpuidex(CPUInfo, 0x4, i);
        if (!(CPUInfo[0] & 0xf0)) break;

        if (i == 0)
        {
            nCores = CPUInfo[0] >> 26;
            console.AddLog("\tNumber of Cores = %d\t\n", nCores + 1);
        }

        nCacheType = (CPUInfo[0] & 0x1f);
        nCacheLevel = (CPUInfo[0] & 0xe0) >> 5;
        bSelfInit = (CPUInfo[0] & 0x100) >> 8;
        bFullyAssociative = (CPUInfo[0] & 0x200) >> 9;
        nMaxThread = (CPUInfo[0] & 0x03ffc000) >> 14;
        nSysLineSize = (CPUInfo[1] & 0x0fff);
        nPhysicalLinePartitions = (CPUInfo[1] & 0x03ff000) >> 12;
        nWaysAssociativity = (CPUInfo[1]) >> 22;
        nNumberSets = CPUInfo[2];

        console.AddLog("\n");

        console.AddLog("\tECX Index %d\t\n", i);
        switch (nCacheType)
        {
        case 0:
            console.AddLog("\t   Type: Null\t\n");
            break;
        case 1:
            console.AddLog("\t   Type: Data Cache\t\n");
            break;
        case 2:
            console.AddLog("\t   Type: Instruction Cache\t\n");
            break;
        case 3:
            console.AddLog("\t   Type: Unified Cache\t\n");
            break;
        default:
            console.AddLog("\t   Type: Unknown\t\n");
        }

        console.AddLog("\t   Level = %d\t\n", nCacheLevel + 1);
        if (bSelfInit)
        {
            console.AddLog("\t   Self Initializing\t\n");
        }
        else
        {
            console.AddLog("\t   Not Self Initializing\t\n");
        }
        if (bFullyAssociative)
        {
            console.AddLog("\t   Is Fully Associatve\t\n");
        }
        else
        {
            console.AddLog("\t   Is Not Fully Associatve\t\n");
        }
        console.AddLog("\t   Max Threads = %d\t\n",
            nMaxThread + 1);
        console.AddLog("\t   System Line Size = %d\t\n",
            nSysLineSize + 1);
        console.AddLog("\t   Physical Line Partions = %d\t\n",
            nPhysicalLinePartitions + 1);
        console.AddLog("\t   Ways of Associativity = %d\t\n",
            nWaysAssociativity + 1);
        console.AddLog("\t   Number of Sets = %d\t\n",
            nNumberSets + 1);
    }

    console.AddLog("\t--------------------- CPU --------------------\t\n");

    console.AddLog("\tMemory: %f GB\t\n", (float)statex.ullTotalPhys / (1024 * 1024 * 1024));
    console.AddLog("\n");
}

void openfile(std::string file, std::string argument)
{
    fstream my_file;
    my_file.open(file, ios::in);
    if (!my_file)
    {
        console.AddLog("No such file %s!\n", file.c_str());
    }

    else
    {
        std::string str;
        while (getline(my_file, str))
        {
            console.AddLog("%s\n", str.c_str());
        }
    }
    console.AddLog("\n");
    my_file.close();
}

void list(std::string argument, std::string argument2)
{
    struct dirent* d;
    struct stat dst;

    DIR* dr;

    string path = ".\\";

    dr = opendir(path.c_str());

    if (dr != NULL)
    {
        for (d = readdir(dr); d != NULL; d = readdir(dr))
        {
            string type = d->d_name;
            type = path + type;
            if (stat(type.c_str(), &dst) == 0)
            {
                if (dst.st_mode & S_IFDIR)
                {
                    type = "FOLDER";
                }
                else if (dst.st_mode & S_IFREG)
                {
                    type = "FILE";
                }
            }
            console.AddLog("%s - %s", d->d_name, type.c_str());
        }
        closedir(dr);
    }
}

void writefile(std::string file, std::string content)
{
    auto mode = ios::in;

    ofstream myfile;
    myfile.open(file, mode);
    myfile << content;
    myfile.close();
}

/*
 * Console class - everything for drawing and managing console
 * Code for functions here
 * Code from imgui_demo.cpp
*/
Console::Console()
{
    FullClearLog();
    memset(InputBuf, 0, sizeof(InputBuf));
    HistoryPos = -1;

    // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
    Commands.push_back("help");
    Commands.push_back("credits");
    Commands.push_back("clear");
    Commands.push_back("cls");
    Commands.push_back("exit");

    for (auto& x : commands)
    {
        Commands.push_back(x.first.c_str());
    }

    AutoScroll = true;
    ScrollToBottom = false;

    AddLog("Termi> ");
}
Console::~Console()
{
    FullClearLog();
    for (int i = 0; i < History.Size; i++)
        free(History[i]);
}


void Console::ClearLog()
{
    for (int i = 0; i < Items.Size; i++)
        free(Items[i]);
    Items.clear();

    TypeTermi();
}

void Console::FullClearLog()
{
    for (int i = 0; i < Items.Size; i++)
        free(Items[i]);
    Items.clear();
}

void Console::AddLog(const char* fmt, ...)
{
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    Items.push_back(Strdup(buf));
}

void Console::Draw()
{
    // TODO: display items starting from the bottom

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
    BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (BeginPopupContextWindow())
    {
        if (Selectable("Clear")) ClearLog();
        if (Selectable("Copy")) Copy = true;
        EndPopup();
    }

    /* 
        *  Display every line as a separate entry so we can change their color or add custom widgets.
        *  If you only want raw text you can use TextUnformatted(log.begin(), log.end());
        *  NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
        *  to only process visible items. The clipper will automatically measure the height of your first item and then
        *  "seek" to display only items in the visible area.
        *  To use the clipper we can replace your standard loop:
        *      for (int i = 0; i < Items.Size; i++)
        *  With:
        *      ImGuiListClipper clipper;
        *      clipper.Begin(Items.Size);
        *      while (clipper.Step())
        *          for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        *  - That your items are evenly spaced (same height)
        *  That you have cheap random access to your elements (you can access them given their index,
        *  without processing all the ones before)
        *   You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
        *  We would need random-access on the post-filtered list.
        * A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
        * or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
        * and appending newly elements as they are inserted. This is left as a task to the user until we can manage
        * to improve this example code!
        * If your items are of variable height:
        * - Split them into same height items would be simpler and facilitate random-seeking into your list.
        * - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
    */
    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    if (Copy)
        LogToClipboard();
    for (int i = 0; i < Items.Size; i++)
    {
        const char* item = Items[i];
        if (!Filter.PassFilter(item))
            continue;

        // Normally you would store more information in your item than just a string.
        // (e.g. make Items[] an array of structure, store color/type etc.)
        ImVec4 color;
        bool has_color = false;
        if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
        else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
        if (has_color)
            PushStyleColor(ImGuiCol_Text, color);
        TextUnformatted(item);
        if (has_color)
            PopStyleColor();
    }
    if (Copy)
        LogFinish();

    if (ScrollToBottom || (AutoScroll && GetScrollY() >= GetScrollMaxY()))
        SetScrollHereY(1.0f);
    ScrollToBottom = false;

    PopStyleVar();
    EndChild();
    Separator();

    bool reclaim_focus = false;
    if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0) && !help_focus)
    {
        ImGui::SetKeyboardFocusHere(0);
        help_focus = true;
    }
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (InputText(render->ChooseLanguage("input"), InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
    {
        s = InputBuf;
        Strtrim(s);
        if (s[0])
            ExecCommand(s);
        strcpy(s, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    SetItemDefaultFocus();
    if (reclaim_focus)
        SetKeyboardFocusHere(-1); // Auto focus previous widget
}

void Console::ExecCommand(string command_line, ...)
{
    const char* tmp;
    string arg;
    string arg2;
    bool _switch = false;
    bool __switch = false;
    tmp = strtok(const_cast<char*>(command_line.c_str()), " ");

    while (tmp != NULL)
    {
        if (_switch)
        {
            if (__switch)
            {
                arg2 = tmp;
            }

            else
            {
                arg = tmp;
            }
        }

        else
        {
            command_line = tmp;
            _switch = true;
        }
        
        tmp = strtok(NULL, " , ");
    }

    AddLog("# %s\n", command_line.c_str());

    auto command = commands.find(command_line);

    /* 
        * Insert into history. First find matchand delete it so it can be pushed to the back.
        * This isn't trying to be smart or optimal
    */
    HistoryPos = -1;
    for (int i = History.Size - 1; i >= 0; i--)
    {
        if (Stricmp(History[i], command_line.c_str()) == 0)
        {
            free(History[i]);
            History.erase(History.begin() + i);
            break;
        }
    }

    History.push_back(Strdup(command_line.c_str()));

    if (command != commands.end())
    {
        /* execute execuatable */
        commands[command_line](arg, arg2);
    }

    else if (Stricmp(command_line.c_str(), "clear") == 0 || Stricmp(command_line.c_str(), "cls") == 0)
    {
        FullClearLog();
    }

    else if (Stricmp(command_line.c_str(), "help") == 0)
    {
        AddLog("Commands:");
        for (int i = 0; i < Commands.Size; i++)
        {
            AddLog("- %s", Commands[i]);
        }
    }

    else if (Stricmp(command_line.c_str(), "credits") == 0)
    {
        AddLog("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic"); /* todo: font which support č, ć, š, đ and ž */
        AddLog("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui. If you have issue check our GitHub repo and report issue.");
        AddLog("If you know how to fix fell free to contribute it through pull requests on GitHub.");
        AddLog("LICENSE > BSD-3-Clause-License");
        AddLog("REPO > https://github.com/ringwormGO-organization/Termi");
    }

    else if (Stricmp(command_line.c_str(), "exit") == 0)
    {
        AddLog("Exiting...");
        exit(0);
    }

    else
    {
        AddLog("Unknown command: '%s'\n", command_line.c_str());
    }

    // On command input, we scroll to bottom even if AutoScroll==false
    ScrollToBottom = true;
    TypeTermi();
}

void Console::TypeTermi()
{
    AddLog("\nTermi> ");
}

int Console::TextEditCallback(ImGuiInputTextCallbackData* data)
{
    //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
    switch (data->EventFlag)
    {
        case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for (int i = 0; i < Commands.Size; i++)
                if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(Commands[i]);

            if (candidates.Size == 0)
            {
                // No match
                AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if (candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0]);
                data->InsertChars(data->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can..
                // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                AddLog("Possible matches:\n");
                for (int i = 0; i < candidates.Size; i++)
                    AddLog("- %s\n", candidates[i]);
            }

            break;
        }
        case ImGuiInputTextFlags_CallbackHistory:
        {
            // Example of HISTORY
            const int prev_history_pos = HistoryPos;
            if (data->EventKey == ImGuiKey_UpArrow)
            {
                if (HistoryPos == -1)
                    HistoryPos = History.Size - 1;
                else if (HistoryPos > 0)
                    HistoryPos--;
            }
            else if (data->EventKey == ImGuiKey_DownArrow)
            {
                if (HistoryPos != -1)
                    if (++HistoryPos >= History.Size)
                        HistoryPos = -1;
            }

            // A better implementation would preserve the data on the current input line along with cursor position.
            if (prev_history_pos != HistoryPos)
            {
                const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
        }
    }
    return 0;
}

/* Code for Renderer class */
/* PRIVATE INSTANCES OF Renderer class */
/* Draw new teminal tab */
void Renderer::DrawNewTab()
{

}

/* Check if file exists */
int Renderer::CheckFile(const char* name)
{
    fstream file;
    file.open(name);

    if (!file)
    {
        return 1;
    }

    file.close();

    return 0;
}

/* Draw context menu */
void Renderer::DrawContextMenu()
{
    if (BeginMenuBar())
    {
        if (BeginMenu(ChooseLanguage("terminal")))
        {
            if (MenuItem(ChooseLanguage("new tab"), "Ctrl+N"))
            {

            }

            if (MenuItem((ChooseLanguage("new profile")), "Ctrl+Shift+N"))
            {

            }

            Separator();

            if (MenuItem(ChooseLanguage("exit"), "Ctrl+X"))
            {
                exit(0);
            }

            ImGui::EndMenu();
        }

        if (BeginMenu(ChooseLanguage("edit")))
        {
            if (MenuItem(ChooseLanguage("font picker"), "Ctrl+F"))
            {
                if (isFont == false)
                {
                    Font(NULL);
                    isFont = true;
                }

                else
                {
                    isFont = false;
                }
            }

            Separator();

            if (MenuItem(ChooseLanguage("change theme"), "Ctrl+T"))
            {
                if (!isDarkTheme)
                {
                    StyleColorsLight();
                    isDarkTheme = true;
                }

                else
                {
                    StyleColorsDark();
                    isDarkTheme = false;
                }
            }

            Separator();

            if (MenuItem(ChooseLanguage("change language"), "Ctrl+L"))
            {
                if (!language_dialog)
                {
                    language_dialog = true;
                    ChooseLanguageDialog(NULL);
                }
            }

            Separator();

            if (MenuItem(ChooseLanguage("configure settings"), "Ctrl+S"))
            {
                Settings(j, 0);
            }

            if (MenuItem(ChooseLanguage("settings dialog"), "Ctrl+Shift+S"))
            {
                if (!settings_dialog)
                {
                    settings_dialog = true;
                    SettingsDialog(NULL);
                }
            }

            ImGui::EndMenu();
        }

        if (BeginMenu(ChooseLanguage("about")))
        {
            if (MenuItem(ChooseLanguage("about termi")))
            {
                if (termi_dialog == false) 
                    termi_dialog = true;
                else 
                    termi_dialog = false;
            }

            if (MenuItem(ChooseLanguage("about imgui")))
            {
                if (imgui_dialog == false) 
                    imgui_dialog = true;
                else 
                    imgui_dialog = false;
            }

            ImGui::EndMenu();
        }

        EndMenuBar();
    }
}

/* Font dialog */
void Renderer::Font(bool* p_open)
{
    ImGuiIO& io1 = GetIO();

    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(200, 200));
    if (!Begin("Font dialog", p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) isFont = false;
        EndPopup();
    }

    if (InputText("Enter name of font file", font_filename, IM_ARRAYSIZE(font_filename), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        //io1.Fonts->AddFontFromFileTTF(font.font_filename, font.size_pixels); todo
    }
    
    End();
}

/* Choose language function - return word on specified language */
const char* Renderer::ChooseLanguage(const char* word)
{
    if (language == "croatian")
    {
        if (word == "input") return Croatian::input;

        if (word == "terminal") return Croatian::terminal;
        if (word == "edit") return Croatian::edit;
        if (word == "about") return Croatian::about;

        if (word == "new tab") return Croatian::new_tab;
        if (word == "new profile") return Croatian::new_profile;
        if (word == "exit") return Croatian::exit_string;

        if (word == "font picker") return Croatian::font_picker;
        if (word == "change theme") return Croatian::change_theme;
        if (word == "change language") return Croatian::change_language;

        if (word == "about termi") return Croatian::about_termi;
        if (word == "about imgui") return Croatian::about_imgui;

        if (word == "settings") return Croatian::settings;
        if (word == "configure settings") return Croatian::configure_settings;
        if (word == "settings dialog") return Croatian::settings_dialog;
    }

    /* Default language - English */
    else
    {
        if (word == "input") return English::input;

        if (word == "terminal") return English::terminal;
        if (word == "edit") return English::edit;
        if (word == "about") return English::about;

        if (word == "new tab") return English::new_tab;
        if (word == "new profile") return English::new_profile;
        if (word == "exit") return English::exit_string;

        if (word == "font picker") return English::font_picker;
        if (word == "change theme") return English::change_theme;
        if (word == "change language") return English::change_language;

        if (word == "about termi") return English::about_termi;
        if (word == "about imgui") return English::about_imgui;

        if (word == "settings") return English::settings;
        if (word == "configure settings") return English::configure_settings;
        if (word == "settings dialog") return English::settings_dialog;
    }

    /* nothing matches */
    return "Unknown word";
}

/* Choose a language using dialog */
void Renderer::ChooseLanguageDialog(bool *p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(500, 500));
    if (!Begin("Language dialog", p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) language_dialog = false;
        EndPopup();
    }

    Text("Choose language / Odaberi jezik");
    Text(" "); /* empty space */

    if (Button("English (default)")) language = "english";
    if (Button("Croatian / Hrvatski")) language = "croatian";
    if (Button("Close window / Zatvori prozor")) language_dialog = false;

    End();
}

/* Dialog about Termi */
void Renderer::TermiDialog(bool* p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(400, 600));
    if (!Begin(ChooseLanguage("about termi"), p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) language_dialog = false;
        EndPopup();
    }

    Text("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic"); /* todo: font which support č, ć, š, đ and ž */
    Text("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui.\nIf you have issue check our GitHub repo and report issue.");
    Text("If you know how to fix fell free to contribute it through pull requests on GitHub.");
    Text("LICENSE > BSD-3-Clause-License");
    Text("REPO > https://github.com/ringwormGO-organization/Termi");

    End();
}

/* Dialog about ImGui */
void Renderer::ImGuiDialog(bool* p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(400, 200));
    if (!Begin(ChooseLanguage("about imgui"), p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) language_dialog = false;
        EndPopup();
    }

    Text("ABOUT > Dear ImGui: Bloat-free Graphical User interface\nfor C++ with minimal dependencies.");
    Text("REPO > https://github.com/ocornut/imgui");

    End();
}

template<typename T>
int Renderer::Settings(T, int id)
{
    auto mode = ios::app | ios::in;
    string temp_str = "";

    if (CheckFile("settings.json") != 0)
    {
        fstream json_file_new("settings.json", mode);
    }

    else /* temporary */
    {
        remove("settings.json");
    }

    fstream json_file("settings.json", mode);

    switch (id)
    {
        case 0:
            /* set up all defaults and read file */

            j["width"] = window_width;
            j["height"] = window_height;
            json_file << j;
            break;

        case 1:
            /* read resulution */
            break;
            

        default:
            console.AddLog("Invalid id %d!\n", id);
            break;
    }

    json_file.close();
    return 0;
}

void Renderer::SettingsDialog(bool* p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(400, 600));
    if (!Begin(ChooseLanguage("settings dialog"), p_open))
    {
        language_dialog = false;
        End();
        return;
    }

    int id = 0;

    if (InputInt("Enter id: ", &id, 1, 100, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        Settings(j, id);
    }

    language_dialog = false;
    End();
}

void main_code()
{
    /* ImGUI window creation */
    SetNextWindowPos(ImVec2(pos_x, pos_y));
    SetNextWindowSize(ImVec2(window_width, window_height));
    Begin
    ("Termi",
        NULL,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_MenuBar |
        ImGuiInputTextFlags_AllowTabInput
    );

#ifdef PRINT_WHEN_WINDOW_IS_CREATED
    if (!alReadyPrinted)
    {
        cout << "ImGui window is created.\n";
        alReadyPrinted = true;
    }
#endif

#ifdef PRINT_FPS
    SetCursorPosX(window_width + window_width / 200 - 100);
    TextColored(ImVec4(0, 0.88f, 0.73f, 1.00f), "(%.1f FPS)", GetIO().Framerate);
#endif

    /* Draw menu bar */
    render->DrawContextMenu();

    /* Draw console */
    console.Draw();

    /* Font dialog */
    if (isFont)
    {
        render->Font(NULL);
    }

    /* Language dialog */
    if (language_dialog)
    {
        render->ChooseLanguageDialog(NULL);
    }

    /* About Termi dialog */
    if (termi_dialog)
    {
        render->TermiDialog(NULL);
    }

    /* About ImGui dialog */
    if (imgui_dialog)
    {
        render->ImGuiDialog(NULL);
    }

    /* Settings dialog */
    if (settings_dialog)
    {
        render->SettingsDialog(NULL);
    }

    /* Get window width and height */
    window_width = GetWindowWidth();
    window_height = GetWindowHeight();


    /* End of window */
    End();
}
