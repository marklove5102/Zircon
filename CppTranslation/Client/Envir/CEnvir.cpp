#include "CEnvir.h"
#include "../../Library/MirLibrary.h"
#include <filesystem>

namespace Client::Envir
{
    // Static member initialization
    CEnvir* CEnvir::Instance = nullptr;
    std::map<Library::LibraryFile, Library::MirLibrary*> CEnvir::LibraryList;
    std::string CEnvir::Language = "English";
    bool CEnvir::DebugLabel = false;
    CConnection* CEnvir::Connection = nullptr;
    
    CEnvir::CEnvir()
        : _Initialized(false)
    {
        Instance = this;
    }
    
    CEnvir::~CEnvir()
    {
        Shutdown();
        Instance = nullptr;
    }
    
    bool CEnvir::Initialize()
    {
        if (_Initialized) return true;
        
        LoadLibraries();
        
        _Initialized = true;
        return true;
    }
    
    void CEnvir::Shutdown()
    {
        if (!_Initialized) return;
        
        UnloadLibraries();
        
        if (Connection != nullptr)
        {
            Connection->Disconnect();
            delete Connection;
            Connection = nullptr;
        }
        
        _Initialized = false;
    }
    
    void CEnvir::Process()
    {
        if (!_Initialized) return;
        
        // Process connection if connected
        if (Connection != nullptr && Connection->GetConnected())
        {
            Connection->Process();
        }
    }
    
    bool CEnvir::GetLibrary(Library::LibraryFile file, Library::MirLibrary** outLibrary)
    {
        auto it = LibraryList.find(file);
        if (it != LibraryList.end())
        {
            if (outLibrary != nullptr)
                *outLibrary = it->second;
            return true;
        }
        
        if (outLibrary != nullptr)
            *outLibrary = nullptr;
        return false;
    }
    
    void CEnvir::LoadLibraries()
    {
        // Load library files from disk
        // This would iterate through LibraryFile enum and load each .lib file
        
        std::string libraryPath = "./Data/Library/";
        
        // Example loading - actual implementation would loop through all LibraryFile values
        Library::MirLibrary* interfaceLib = new Library::MirLibrary();
        if (interfaceLib->Load(libraryPath + "Interface.lib"))
        {
            LibraryList[Library::LibraryFile::Interface] = interfaceLib;
        }
        else
        {
            delete interfaceLib;
        }
        
        // Load other libraries...
    }
    
    void CEnvir::UnloadLibraries()
    {
        for (auto& pair : LibraryList)
        {
            if (pair.second != nullptr)
            {
                delete pair.second;
                pair.second = nullptr;
            }
        }
        
        LibraryList.clear();
    }
}
