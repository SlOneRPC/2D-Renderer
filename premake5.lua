workspace "Renderer2D"
    platforms { "x64" }
    architecture "x64"


    configurations
    {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "Renderer2D"
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
    }

    libdirs { "vendor/glfw-3.3.8/lib-vc2019", "vendor/glew-2.1.0/lib/Release/x64" }

    filter "system:windows"
        cppdialect "C++20"

    filter "configurations:Debug"
        defines { "DEBUG", "GLEW_STATIC" }
        symbols "On"
        runtime "Debug"
        links { "opengl32.lib", "glfw3.lib", "glew32s.lib" }
  
    filter "configurations:Release"
        defines { "NDEBUG", "GLEW_STATIC" }
        optimize "On"
        staticruntime "on"
        links { "opengl32.lib", "glfw3.lib", "glew32s.lib" }
