cmake_minimum_required(VERSION 3.9)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(Windows_API_Experiments)

#================================#
#  Global Configuration          #
#================================#

# Set C++ 14 Standard
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
   message(" [INFO] 64 bits build.")
else()
   message(" [INFO] 32 bits build.")
endif()

# ===>>>> TARGET fs: Fale system
# Sample application that shows file system operations.
#--------------------------------------------------------------
add_executable(fs src/fs.cpp)

# ===>>>> TARGET upscale: Upscale child process
# Sample application that shows UAC elevation dialog.
#--------------------------------------------------------------
add_executable(upscale src/upscale.cpp)

# ===>>>> TARGET gpo: Windows API GPO
# Sample application that shows GPO settings.
# Uses: UseEnv API  userenv.dll
#--------------------------------------------------------------
add_executable(gpo src/gpo.cpp)
#target_link_libraries(gpo PUBLIC usrenv)

# ===>>>> TARGET winver: Windows API base 64 facilities    
# Sample application that shows current Windows installation version.
#--------------------------------------------------------------
add_executable(winver src/windowsVersion.cpp)

# ===>>>> TARGET wihttp: Http download and requests with Winapis urlmon.dll and wininet.dll 
# Sample application that shows current Windows installation version.
#--------------------------------------------------------------
add_executable(winhttp src/winhttp.cpp)

# ===>>>> TARGET base64: Windows API base 64 facilities    
# Uses: Wincrypt API  crypt32.dll 
#--------------------------------------------------------------
add_executable(base64 src/base64.cpp)
# Link against crypt32.dll (crypt32.lib)
target_link_libraries(base64 PUBLIC crypt32)

# ====>>>> TARGET: guiBasic1 - Minimal graphical user interface - WinMain entry point, 
# window subsystem 
# Flag WIN32 => Compiles program to Windows subsystem (without console window)
# Reference: https://stackoverflow.com/questions/33400777/
#---------------------------------------------------------------
add_executable(guiBasic1 WIN32 src/guiBasic1.cpp)
# target_link_libraries(guiBasic1 user32 gdi32)

# ====>>>> TARGET: guiBasicNOWinmain - Minimal graphical user interface - WinMain entry point, 
# Add icon to executable. 
# icon.rc => Resource script which is compiled by the resource compiler.
#--------------------------------------------------------------
add_executable(guiBasicNOWinmain WIN32 src/guiBasicNOWinmain.cpp src/icon.rc)
# target_link_libraries(guiBasicNOWinmain user32 gdi32)

if(MSVC)
	set_target_properties(guiBasicNOWinmain PROPERTIES LINK_FLAGS "/entry:mainCRTStartup")
else()
	 message(FATAL_ERROR " [ERROR] Linker flags of target guiBasicNOWinmain not set for this compiler")
endif()

#==========>>> Helper Targets <<<====================#

# Copy targets to ./ - Directory where is this file CMakeLists.txt (project top level dir)
install(TARGETS fs
		        gpo
		        upscale
		        winver
				winhttp 
				base64 
				guiBasic1 
				guiBasicNOWinmain 
		DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin)
