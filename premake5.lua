workspace "Renderer2D"
    configurations
    {
        "Debug",
        "Release",
        "UnitTest",
        "IntegrationTest"
    }
    startproject "Renderer2D"

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "Renderer2D"
    platforms { "x64" }
    architecture "x64"
    location "src"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/build/%{cfg.buildcfg}")
    objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "src/**.h",
        "src/**.hpp",
        "src/**.cpp",
        "src/**.cc",
        "vendor/imgui/**.cpp"
    }

    includedirs
    {
        "$(SolutionDir)vendor/glew-2.1.0/include",
        "$(SolutionDir)vendor/glfw-3.3.8/include",
        "$(SolutionDir)vendor/imgui",
        "$(SolutionDir)vendor/imgui/backends",
        "$(SolutionDir)vendor/stb-image",
        "$(SolutionDir)vendor/glm",
        "$(SolutionDir)src/",
        "$(SolutionDir)vendor/yaml-cpp/include"
    }

    libdirs 
    { 
        "vendor/glfw-3.3.8/lib-vc2019", 
        "vendor/glew-2.1.0/lib/Release/x64",
        "vendor/yaml-cpp/build/Debug/",
        "vendor/yaml-cpp/build/Release/"
    }

    links 
    { 
        "opengl32.lib", 
        "glfw3.lib", 
        "glew32s.lib", 
        "winmm.lib",
    }

    staticruntime "Off"

    filter "system:windows"
        cppdialect "C++20"

    filter "configurations:Debug"
        defines { "DEBUG", "GLEW_STATIC", 'BASE_APP_PATH="../resources/"', "YAML_CPP_DLL" }
        symbols "On"
        runtime "Debug"
        staticruntime "Off"
        links { "yaml-cppd.lib" }

    filter "configurations:Release"
        defines { "NDEBUG", "GLEW_STATIC", 'BASE_APP_PATH="../resources/"', "YAML_CPP_DLL"  }
        optimize "On"
        links { "yaml-cpp.lib" }
        runtime "Release"

    filter "configurations:UnitTest"
        defines { "NDEBUG", "GLEW_STATIC", 'BASE_APP_PATH="../resources/"', "BUILD_LIB"  }
        optimize "On"
        staticruntime "Off"
        links { "yaml-cpp.lib" }
        targetextension (".lib")
        kind ("StaticLib")
        runtime "Release"


    filter "configurations:IntegrationTest"
        defines { "NDEBUG", "GLEW_STATIC", 'BASE_APP_PATH="../resources/"', "YAML_CPP_DLL", "TESTING"  }
        optimize "On"
        links { "yaml-cpp.lib" }
        runtime "Release"

project "GoogleTests"
    platforms { "x64" }
    architecture "x64"
    location "tests/GoogleTests"
    kind "ConsoleApp"
    language "C++"
    dependson "Renderer2D"

    targetdir ("bin/build/%{cfg.buildcfg}")
    objdir ("bin/obj/" .. outputdir .. "/%{prj.name}")


    nuget { "Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn:1.8.1.7" }

    filter "system:windows"
        cppdialect "C++latest"

    files 
    {
        "tests/GoogleTests/**.h",
        "tests/GoogleTests/**.hpp",
        "tests/GoogleTests/**.cpp",
        "tests/GoogleTests/**.cc"
    }

    libdirs 
    { 
        "vendor/glfw-3.3.8/lib-vc2019", 
        "vendor/glew-2.1.0/lib/Release/x64",
        "vendor/yaml-cpp/build/Debug/",
        "vendor/yaml-cpp/build/Release/",
        "bin/build/UnitTest/",
        "packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.7/lib/native/v140/windesktop/msvcstl/static/rt-dyn/x64/Release"
    }

    includedirs
    {
        "$(SolutionDir)vendor/glew-2.1.0/include",
        "$(SolutionDir)vendor/glfw-3.3.8/include",
        "$(SolutionDir)vendor/yaml-cpp/include",
        "$(SolutionDir)vendor/glm",
        "$(SolutionDir)packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.7/build/native/include/",
        "$(SolutionDir)src/",
    }

    links 
    { 
        "opengl32.lib", 
        "glfw3.lib", 
        "glew32s.lib", 
        "winmm.lib",
        "Renderer2D.lib",
        "yaml-cpp.lib",
        "gtest.lib"
    }

    defines { "GLEW_STATIC", "WIN32", "x64", "_CONSOLE" }

    staticruntime "Off"
    optimize "On"
    runtime "Release"

    filter "configurations:Debug"
        defines { "_DEBUG", "DEBUG"}
        symbols "On"
        runtime "Debug"
        links { "yaml-cppd.lib" }
        optimize "Off"

project "ScreenshotTests"
    configurations
    {
        "Debug",
        "Release"
    }

    configmap {
        ["IntegrationTest"] = "Release",
        ["Release"] = "Release",
        ["Debug"] = "Debug",
        ["UnitTest"] = "Release"
    }

    location "tests/ScreenshotTests"
    kind "ConsoleApp"
    language "C#"
    dependson "Renderer2D"
    clr "NetCore"

    dotnetframework "net6.0"

    system "Windows"

    nuget { "Codeuctivity.ImageSharpCompare:2.0.76" , "System.Drawing.Common:7.0.0" }

    files 
    {
        "tests/ScreenshotTests/*.cs",
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        flags { "Symbols" }


    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

        
    -- filter "platforms:x86"
    --     system "Windows"
    --     architecture "x86"

    -- filter "platforms:x86_64"
    --     system "Windows"
    --     architecture "x86_64"
    