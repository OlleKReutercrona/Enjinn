local WORKSPACE_NAME = "Enjinn Engine"
local ENGINE_NAME = "Engine Core"
local EDITOR_NAME = "Editor"
local EXTERNAL_NAME = "External"
local PROJECT_NAME_SHORT = "Enjinn"

local DO_LOGGING = true

local LOG = DO_LOGGING and print or function() end

local SHADER_INCLUDE_PATH = [[/I"..\\Core\\Source\\Graphics\\Shaders"]]

local USE_ABSOLUTE_PATHS = false
local basePath = USE_ABSOLUTE_PATHS and os.realpath("../") or "../"

local cppVersion = "C++20"

local PROJECT_KIND = "WindowedApp"
local EDITOR_KIND = "StaticLib"

local DEBUG_BUILD_NAME = "Debug"
local RELEASE_BUILD_NAME = "Release"

local CONFIG_FILTERS = {
    DEBUG = "configurations:"..tostring(DEBUG_BUILD_NAME),
    RELEASE = "configurations:"..tostring(RELEASE_BUILD_NAME),
}

local LINKER_OPTIONS =  {
    "/ignore:4099", -- linking object as if no debug info
}

local USE_PCH = true
local function UsePrecompiled()
    if not USE_PCH then return end
    pchheader ("stdafx.h")
    pchsource ("../Core/Source/stdafx.cpp")
end

local directories = {
    root            = basePath,
    bin             = basePath .. "Bin/",
    temp            = basePath .. "Temp/",
    shaders         = basePath .. "Bin/Shaders/",

    intermediateLib = basePath .. "Temp/IntermediateLib",

    pchPath         = basePath .. "Core/Source/",

    -- Project
    project         = basePath .. "Project/",
    projectSource   = basePath .. "Project/Source/",

    -- Core
    core            = basePath .. "Core/",
    coreSource      = basePath .. "Core/Source/",
    coreShaders     = basePath .. "Core/Source/Graphics/Shaders/",
    -- Editor
    editor          = basePath .. "Editor/",
    editorSource    = basePath .. "Editor/Source/",

    -- External
    external        = basePath .. "External/",
    externalDLL     = basePath .. "/External/dll/",
    externalInclude = basePath .. "/External/Include/",
    externalLib     = basePath .. "/External/Lib/",
    debugLib        = basePath .. "/External/Lib/Debug/",
    releaseLib      = basePath .. "/External/Lib/Release/",

    premake         = basePath .. "Premake",
 }

 workspace(WORKSPACE_NAME)
    location(directories.root)
    startproject(PROJECT_NAME_SHORT)
    architecture("x64")

    configurations {
        DEBUG_BUILD_NAME,
        RELEASE_BUILD_NAME
    }

    -- TODO | Check this against DX12
    shadermodel("5.0")
    filter("files:**PS.hlsl")
    removeflags("ExcludeFromBuild")
    shadertype("Pixel")
    shaderobjectfileoutput(directories.shaders .. "/%%(Filename).cso")
    
    filter("files:**VS.hlsl")
    removeflags("ExcludeFromBuild")
    shadertype("Vertex")
    shaderobjectfileoutput(directories.shaders .. "/%%(Filename).cso")
    
    filter("files:**CS.hlsl")
    removeflags("ExcludeFromBuild")
    shadertype("Compute")
    shaderobjectfileoutput(directories.shaders .. "/%%(Filename).cso")
    
project(EXTERNAL_NAME)
    location(directories.temp)
    language("C++")
    cppdialect(cppVersion)
    kind("StaticLib")

    debugdir(directories.intermediateLib)
    targetdir(directories.intermediateLib)
    targetname(EXTERNAL_NAME.."_%{cfg.buildcfg}")
    objdir(directories.temp.."/"..EXTERNAL_NAME.."/%{cfg.buildcfg}")

    files {
        directories.external.."**.h",
        directories.external.."**.hpp",
        directories.external.."**.cpp",

        directories.external.."**.hlsl",
        directories.external.."**.hlsli"
    }

    includedirs {
        directories.externalInclude,
        directories.root,
    }

    filter (CONFIG_FILTERS.DEBUG)
        runtime "Debug"
        symbols "on"
    filter (CONFIG_FILTERS.RELEASE)
        runtime "Release"
        optimize "on"

    filter "system:windows"
        staticruntime "off"
        symbols "On"
        systemversion "latest"
        warnings "Off"
    
    flags {
        "MultiProcessorCompile"
    }

    links {
        "DXGI"
    }


project(ENGINE_NAME)
    location(directories.temp)
    language("C++")
    cppdialect(cppVersion)
    kind("StaticLib")

    debugdir(directories.intermediateLib)
    targetdir(directories.intermediateLib)
    targetname(ENGINE_NAME.."_%{cfg.buildcfg}")
    objdir(directories.temp.."/"..ENGINE_NAME.."/%{cfg.buildcfg}")

    UsePrecompiled()

    files {
        directories.coreSource.."**.h",
        directories.coreSource.."**.hpp",
        directories.coreSource.."**.cpp",

        directories.pchPath.."**",

        directories.coreSource.."**.hlsl",
        directories.coreSource.."**.hlsli"
    }

    includedirs {
        directories.externalInclude,
        directories.root,
        directories.coreSource,
        directories.pchPath,
    }

    filter (CONFIG_FILTERS.DEBUG)
        runtime "Debug"
        symbols "on"
    filter (CONFIG_FILTERS.RELEASE)
        runtime "Release"
        optimize "on"

    filter "system:windows"
        staticruntime "off"
        symbols "On"
        systemversion "latest"
        warnings "Extra"
    
    flags {
        "MultiProcessorCompile"
    }

    links {
        "D3d12",        -- D3d12.lib
        "dxgi",         -- 
        "d3dcompiler"   -- To compile shaders
    }

local function FindLibraries()
    LOG("\nFinding Libraries to link:")

    local foundNames = {}
    local out = {}
    for _, lib in pairs(os.matchfiles(directories.externalLib.."**")) do        
        if (path.getextension(lib) == ".lib") then
            local name = path.getname(lib)
            if not foundNames[name] then
                out[#out+1] = path.getname(lib)
                foundNames[name] = true
                LOG(name)
            end
        end
    end
    
    LOG("\n")

    return out
end

local LIBRARY_LIST = FindLibraries()
LIBRARY_LIST[#LIBRARY_LIST + 1] = EXTERNAL_NAME
LIBRARY_LIST[#LIBRARY_LIST + 1] = ENGINE_NAME

project(PROJECT_NAME_SHORT)
    location(directories.temp)
    kind("WindowedApp")
    language "C++"
    cppdialect(cppVersion)

    debugdir(directories.bin)
    targetdir(directories.bin)
    targetname(PROJECT_NAME_SHORT.."_%{cfg.buildcfg}")
    objdir(directories.temp.."/"..PROJECT_NAME_SHORT.."/%{cfg.buildcfg}") -- add to directories?

    dependson{ENGINE_NAME, EXTERNAL_NAME}

    shaderincludedirs(directories.engineShaders)

    links(LIBRARY_LIST)

    files {
        directories.projectSource.."**.h",
        directories.projectSource.."**.hpp",
        directories.projectSource.."**.cpp",
    }
    
    includedirs {
        directories.externalInclude,
        directories.coreSource,
        directories.projectSource
    }
    
    libdirs {
        directories.externalLib,
        directories.intermediateLib
    }

    flags {
        "MultiProcessorCompile"
    }

    filter (CONFIG_FILTERS.DEBUG)
        runtime "Debug"
        symbols "on"
        defines {[[_ENJINN_BUILD=L"]]..tostring(DEBUG_BUILD_NAME)..[["]]}
        libdirs {directories.debugLib}

    filter (CONFIG_FILTERS.RELEASE)
        runtime "Release"
        optimize "on"
        defines {[[_ENJINN_BUILD=L"]]..tostring(RELEASE_BUILD_NAME)..[["]]}
        libdirs {directories.releaseLib}

    filter "system:windows"
        staticruntime "off"
        symbols "On"
        systemversion "latest"
        warnings "Extra"

        linkoptions(LINKER_OPTIONS)
    
    local function MakeFolderStructure()
        for _, dir in pairs(directories) do
            if not os.isdir(dir) then
                os.mkdir(dir)
            end
        end
    end
    
    MakeFolderStructure()