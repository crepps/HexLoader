/*****************************************************************//**
 * @file   loader.h
 * @brief  This file defines the interface of the HexLoader
 *         back end, and provides the functions for hex
 *         dumping bin files, storing them as resource files,
 *         then recompiling them into a separate application
 *         for launching the original bin beside their required
 *		   dlls from a temporary location, or spawning a series
 *		   of message boxes for a lightweight installer.
 * 
 * @author Kevin Crepps
 * @date   August 2024
 *********************************************************************/

#pragma once

#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <mutex>
#include <sys/stat.h>

#include <shlobj.h>
#include <Windows.h>

#include "resource.h"

/**
 * Custom return codes specifying that
 * a given operation:
 * 
 * - Succeeded (0)
 * - Failed and aborting is recommended (1)
 * - Failed but program can safely continue (2)
 */
#define SUCCESS 0
#define FAILURE_ABORT 1
#define FAILURE_CONTINUE 2

/**
 * Console output-related constants.
 * 
 * Buffer size is the chunk size of output
 * received after executing a system command.
 * 
 * Output delays are the amount of time in
 * milliseconds the thread will sleep between
 * buffer offloads.
 */
#define BUFFER_SIZE 128
#define DELAY_OUTPUT_LONG 100
#define DELAY_OUTPUT_SHORT 5

class Loader
{
public:
	/**
	 * Enumerator for specifying which file path the user would
	 * like to set or verify with SetPath() or ValidatePath().
	 */
	enum PATH_TYPE
	{
		PATH_ALL,
		PATH_BIN,
		PATH_LIB,
		PATH_EXPORT,
		PATH_RUN,
		PATH_INSTALLER
	};

	/**
	 * @brief
	 * Empty constructor with initializer list.
	 */
	Loader() noexcept
		:installer(false),
		cleanupThread(false),
		outputDelay(DELAY_OUTPUT_LONG),
		bufferLoaded(false),
		runPath("C:\\temp"),
		outputBuffer("") {}

	/**
	 * @brief
	 * Retrieve exception info and other
	 * error messages set with SetError().
	 */
	inline std::string GetError() const noexcept { return error; }

	/**
	 * @brief
	 * Sets appName, which is used in BuildImplFile()
	 * when building application installer.
	 */
	inline void SetAppName(std::string arg) noexcept { appName = arg; }

	/**
	 * @brief
	 * Specify whether to generate installer.
	 * 
	 * @param
	 * true - build installer application
	 * false - build loader application
	 */
	inline void SelectInstaller(bool arg) { installer = arg; }

	/**
	 * @brief
	 * Set whether to leave loader process open after launching and 
	 * delete temp files when user application terminates.
	 */
	inline void SetCleanUp(bool arg) { cleanupThread = arg; }

	/**
	 * @brief
	 * Check whether installer flag is set.
	 */
	inline bool CheckInstaller() { return installer; }

	/**
	 * @brief
	 * Set directory/file path.
	 * 
	 * @param
	 * Path type can be:
	 * 
	 * PATH_BIN       - path to executable file (only one)
	 * 
	 * PATH_LIB       - path to library file (can be several)
	 * 
	 * PATH_EXPORT    - directory in which application
	 *                  will be generated
	 * 
	 * PATH_RUN       - temporary location from which the user's
	 *                  application will be launched
	 *  
	 * PATH_INSTALLER - default installation path for user's
	 *                  application
	 * 
	 * @param
	 * Pass an absolute path.
	 */
	void SetPath(PATH_TYPE, const std::string&) noexcept;

	/**
	 * @brief
	 * Check whether a given path already exists.
	 * Pass PATH_BIN, PATH_LIB, PATH_EXPORT, or PATH_ALL.
	 */
	unsigned int ValidatePath(PATH_TYPE) const noexcept;

	/**
	 * @brief
	 * Retrieve file paths after verifying with ValidatePath().
	 */
	inline std::string GetBinPath() const noexcept { return binPath; };
	inline std::vector<std::string> GetLibPaths() const noexcept { return libPaths; };
	inline std::string GetExportPath() const noexcept { return exportPath; }
	inline std::string GetRunPath() const noexcept { return runPath; };

	/**
	 * @brief
	 * Check whether GNU compiler is installed using stat().
	 * 
	 * If false, check whether chocolatey is installed using
	 * ChocoInstalled(), then you can pass the following
	 * into SpawnProcThread():
	 * 
	 * "C:\\ProgramData\\chocolatey\\bin\\choco.exe install mingw -y --force"
	 */
	bool CompilerInstalled() const noexcept;

	/**
	 * @brief
	 * Check whether chocolatey is installed using stat().
	 * 
	 * If false, you can concatenate the following into a string
	 * object and pass it into SpawnProcThread():
	 * 
	 * "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe "
	 * "-NoProfile -InputFormat None -ExecutionPolicy Bypass -Command \" "
	 * "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex "
	 * "((New-Object System.Net.WebClient).DownloadString"
	 * "(\'https://chocolatey.org/install.ps1\'))\" && SET \"PATH=%PATH%;"
	 * "%ALLUSERSPROFILE%\\chocolatey\\bin\""
	 */
	bool ChocoInstalled() const noexcept;

	/**
	 * @brief
	 * Spawn separate thread to execute system command with _popen().
	 * 
	 * Output will be loaded into a buffer which can be read
	 * using OffloadBuffer().
	 * 
	 * The 'reading' flag will be set while there's output to be
	 * read - check with Reading(), then check whether output is
	 * ready to be offloaded with GetBufferLoaded().
	 * 
	 * @param
	 * Accepts rvalues - pass a literal, or std::move an lvalue.
	 * 
	 * @return 
	 * Custom return code defined at the top of loader.h.
	 */
	unsigned int SpawnProcThread(std::string&&) noexcept;

	/**
	 * @brief
	 * Check whether output buffer is ready for offloading after
	 * executing system command with SpawnProcThread().
	 */
	inline bool GetBufferLoaded() const noexcept { return bufferLoaded; }


	/**
	 * @brief
	 * Get system command output from SpawnProcThread(),
	 * check with GetBufferLoaded().
	 * 
	 * This function will block until outputMutex is unlocked
	 * inside of ClearBuffer().
	 */
	const char* OffloadBuffer() noexcept;

	/**
	 * @brief
	 * Clears the outputBuffer member, unlocks outputMutex,
	 * then clears (unsets) the bufferLoaded flag.
	 * 
	 * \return 
	 */
	void ClearBuffer() noexcept;

	/**
	 * @brief
	 * Check whether there is anymore output to be read after
	 * calling SpawnProcThread().
	 */
	inline bool Reading() const noexcept { return reading; }

	/**
	 * @brief 
	 * Sets outputDelay, used in LoadBuffer() to sleep the specified
	 * amount of milliseconds between outputs from SpawnProcThread().
	 */
	inline void DelayOutput(unsigned int arg) noexcept { outputDelay = arg; }

	/**
	 * @brief
	 * Check whether the working directory stored in appDataPath
	 * exists with stat().
	 * 
	 * This will attempt to create the folder if it doesn't
	 * already exist.
	 * 
	 * @return
	 * Return whether the folder exists, or, if it didn't,
	 * whether creating it was successful.
	 */
	bool CheckAppData() noexcept;

	/**
	 * @brief
	 * In the working directory (app data), a file containing
	 * the bin and lib hex dumps is generated.
	 * 
	 * @return 
	 * Custom return code defined at the top of loader.h.
	 */
	unsigned int BuildHeader() noexcept;

	/**
	 * @brief 
	 * In the working directory (app data), a file containing
	 * loader or installer-specific implementations are generated
	 * using two resource files, with variables injected in-between.
	 * 
	 * @return 
	 * Custom return code defined at the top of loader.h. 
	 */
	unsigned int BuildImplFile() noexcept;

	/**
	 * @brief
	 * The following is concatenated into a std::string
	 * to be passed to SpawnProcThread() in order to compile
	 * the loader or installer with g++:
	 * 
	 * - g++ bin path
	 * - Working directory path
	 * - Name of generated implementation file
	 * - Export path
	 * - Name of new executable (stored in fileNames[0])
	 * - Necessary Win32 library specifications (ole32 and uuid)
	 * 
	 * @return 
	 * Custom return code defined at the top of loader.h.
	 */
	unsigned int Compile() noexcept;

	/**
	 * @brief
	 * Clears all reusable vectors and purges all files from
	 * app data directory.
	 * 
	 * @return 
	 * Custom return code defined at the top of loader.h.
	 */
	unsigned int CleanUp() noexcept;

	~Loader() noexcept {}

private:
	unsigned int outputDelay;           // Milliseconds between SpawnProcThread()'s
                                        // output buffer offloads

	bool installer,                     // Whether to build installer (not loader)
		cleanupThread;                  // Whether to purge loader temp files

	std::string appName,                // Name of user's application
				binPath,                // Path to executable
				exportPath,             // Output location for loader/installer
				runPath,                // Temp location for running loader
				installerPath,          // Installation destination for installer
				error,                  // Error info set in SetError()
				outputBuffer,           // Holds chunks of output from SpawnProcThread()
				appDataPath;            // Working directory for building loader/installer

	std::vector<std::string> libPaths,  // Paths to user's lib files
							 fileNames, // Names of user's bin and lib files
							 varNames;  // Names of variables to be written to file
										// in BuildHeader()

	std::vector<uint64_t> fileSizes;	// Sizes of user's bin and lib files
		
	std::atomic<bool> bufferLoaded,		// Whether outputBuffer ready for offload

					  reading;			// Whether there's more output from command
										// executed with SpawnProcThread()

	std::mutex outputMutex;				// Mutex used to lock outputBuffer

	/**
	 * Constants for default paths.
	 */
	const char *PATH_COMPILER{ "C:\\ProgramData\\mingw64\\mingw64\\bin\\g++.exe" },
			   *PATH_CHOCO{ "C:\\ProgramData\\chocolatey" },
			   *PATH_DEFAULT_RUN{ "C:\\temp" };

	/**
	 * @brief
	 * Stores error description for later retrieval using GetError().
	 * 
	 * Overloaded for rvalues.
	 */
	inline void SetError(std::string&& arg) noexcept { error = std::move(arg); }

	/**
	 * @brief
	 * Stores error description for later retrieval using GetError().
	 * 
	 * Overloaded for lvalues.
	 */
	inline void SetError(const std::string& arg) noexcept { error = std::move(arg); }

	/**
	 * @brief
	 * Executes a system command with _popen().
	 * 
	 * Loads output into a buffer which can be read using OffloadBuffer().
	 * 
	 * The 'reading' flag will be set while there is output to be
	 * read - check with Reading().
	 */
	unsigned int Command(std::string&&) noexcept;

	/**
	 * @brief
	 * Loads buffer with output of system command passed into Command()
	 * from SpawnProcThread().
	 */
	void LoadBuffer(const std::string&) noexcept;

	/**
	 * @brief
	 * Takes path to binary file, returns std::string of comma-separated
	 * hex bytes.
	 */
	std::string HexDump(const std::string&) noexcept;

	/**
	 * @brief 
	 * Used for retrieving content of implementation files stored as resources.
	 * 
	 * @param
	 * Takes one of the following enumerations:
	 * 
	 * LOADER_DATA_0    (254)
	 * LOADER_DATA_1    (253)
	 * INSTALLER_DATA_0 (252)
	 * INSTALLER_DATA_1 (251)
	 * 
	 * @return std::string containing the file data.
	 */
	std::string GetResourceData(unsigned int arg) const noexcept;
};

/**
 * @brief
 * External function used by GetResourceData().
 */
extern HMODULE GetModule();