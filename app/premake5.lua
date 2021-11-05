-----------------------------------------------
-- Application configuration file.
-----------------------------------------------
project "Application"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    --disablewarnings{"26812"}
    --linkoptions { "-IGNORE:4075", "-IGNORE:4098", "-IGNORE:4099"}

    targetdir("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/build/bin-int/" .. outputdir .. "/%{prj.name}")


    -- Define the location(s) of files.
    files {
        "%{wks.location}/app/include/**.h",
		"%{wks.location}/app/source/**.cpp",
        "%{wks.location}/resources/scripts/**.lua",
        "%{wks.location}/tests/**.h",
    }


    -- Specifies a list of include file search directories.
    includedirs {
        "%{wks.location}/app/source/",
        "%{wks.location}/app/include/",
		"%{wks.location}/resources/scripts/",
        "%{wks.location}/tests/",
		"%{wks.location}/libs/irrlicht/lib/x64/",
		"%{wks.location}/libs/irrlicht/include/",
		"%{wks.location}/libs/lua542/include/",
    }
    
    -- This is the place to add filters.
    vpaths {
        ["Headers/"] = { "**.h", "**.hpp" },
        ["Sources/"] = { "**.c", "**.cpp"},
        ["Scripts/"] = { "**.lua"},
        ["Tests/"] = { "LuaTests.h"},
    }

	links {
	}

	libdirs {
		"%{wks.location}/libs/irrlicht/lib/x64/",
	}

     -- Define a macro/symbol which applies on a windows system.
    filter {"system:windows"}  
        defines {
            "_WIN32",
            "_CRT_SECURE_NO_WARNINGS",
        }
        -- Specifies shell commands to run after build is finished.
	    postbuildcommands {
	        --"{COPYFILE} %{wks.location}/resources/dlls/Irrlicht.dll %{wks.location}/build/bin/" .. outputdir .. "/Application/",
            --"{COPYFILE} %{wks.location}/resources/dlls/lua54.dll %{wks.location}/build/bin/" .. outputdir .. "/Application/",
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
        