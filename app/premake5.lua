-----------------------------------------------
-- Application configuration file.
-----------------------------------------------
project "Application"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/build/bin-int/" .. outputdir .. "/%{prj.name}")

    -- Define the location of pre-compiled header.
    pchheader "pch.h"
    pchsource "%{wks.location}/app/src/source/pch.cpp"

    -- Define the location(s) of files.
    files {
        "%{wks.location}/app/src/include/**.h",
		"%{wks.location}/app/src/source/**.cpp",
        "%{wks.location}/resources/scripts/**.lua",
        "%{wks.location}/tests/**.h",
		"%{wks.location}/resources/texture/**.png",
		"%{wks.location}/resources/mesh/**.obj",
    }


    -- Specifies a list of include file search directories.
    includedirs {
        "%{wks.location}/app/src",
        "%{wks.location}/app/src/include",
		"%{wks.location}/app/src/source",
		"%{wks.location}/resources/scripts",
		"%{wks.location}/resources/texture",
		"%{wks.location}/resources/mesh",
        "%{wks.location}/tests",
		"%{wks.location}/libs/raylib/include",
		"%{wks.location}/libs/lua542/include",
    }
    
    -- This is the place to add filters.
    vpaths {
        ["src/"] = { "**main.cpp" },
            ["src/Application/"] = { "**Application.*", "**ResourceManager.*", "**pch.*" },
            ["src/GameStates/"] = { "**StateMachine.*", "**IState.*", "**MainMenu.*", "**Game.*", "**Highscore.*", "**Editor.*" },
            ["src/Enitity/"] = { "**Entity.*", "**Player.*", "**Enemy.*", "**EnemyManager.*" },
        ["src/Scripts/"] = { "**.lua"},
        ["src/Tests/"] = { "**LuaTests.*"},
    }

	links {
        "raylib.lib",
        "winmm.lib",
	}

	libdirs {
		"%{wks.location}/libs/raylib/",
	}

     -- Define a macro/symbol which applies on a windows system.
    filter {"system:windows"}  
        defines {
            "_WIN32",
            "_CRT_SECURE_NO_WARNINGS",
        }
        -- Specifies shell commands to run after build is finished.
	    postbuildcommands {
	        "{COPYFILE} %{wks.location}/resources/dlls/raylib.dll %{wks.location}/build/bin/" .. outputdir .. "/Application/",
            "{COPYFILE} %{wks.location}/resources/dlls/lua54.dll %{wks.location}/build/bin/" .. outputdir .. "/Application/",
		}


    -- Define a macro/symbol which applies only to debug builds.
    filter {"configurations:Debug"}
        staticruntime "on"
        runtime "Debug"
        defines{"_DEBUG", "_UNICODE", "UNICODE"}
        symbols "on"

    -- Define a macro/symbol which applies only to release builds.
    filter {"configurations:Release"}
        staticruntime "on"
        runtime "Release"
        defines{"NDEBUG", "_UNICODE", "UNICODE"}
        symbols "on"
        optimize "Full"
        