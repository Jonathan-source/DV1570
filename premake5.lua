-----------------------------------------------
-- Solution configuration file.
-----------------------------------------------
workspace "DV1570"
    system "Windows"
    architecture "x86_64"
    flags { 
        "MultiProcessorCompile" 
    }
    
    configurations {
        "Debug",
        "Release"
    }

    -- Set the startup project.
    startproject "Application"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	postbuildcommands {
       -- "{COPY} Irrlicht.dll %{wks.location}/app/build/bin/" .. outputdir .. "/app/",
		--"{COPY} lua54.dll %{wks.location}/app/build/bin/" .. outputdir .. "/app/"
	}

-- Subprojects.
include "app"


-----------------------------------------------
-- Cleanup configuration.
-----------------------------------------------
newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("build/bin")

        print("Removing intermediate binaries")
        os.rmdir("build/bin-int")

        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}