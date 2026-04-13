#pragma once

#include "../../Common/CSharpCompat.h"
#include "../../Library/Network/BaseConnection.h"
#include <map>
#include <memory>

namespace Library
{
    class MirLibrary;
    enum class LibraryFile : int32;
}

namespace Client::Envir
{
    class DXManager;
    class CConnection;
    
    class CEnvir
    {
    public:
        // Static Properties
        static CEnvir* Instance;
        
        static std::map<Library::LibraryFile, Library::MirLibrary*> LibraryList;
        static std::string Language;
        static bool DebugLabel;
        
        // Connection
        static CConnection* Connection;
        
        // Methods
        static bool GetLibrary(Library::LibraryFile file, Library::MirLibrary** outLibrary);
        static void LoadLibraries();
        static void UnloadLibraries();
        
        // Constructor
        CEnvir();
        ~CEnvir();
        
        // Instance methods
        bool Initialize();
        void Shutdown();
        void Process();
        
    private:
        bool _Initialized;
    };
}
