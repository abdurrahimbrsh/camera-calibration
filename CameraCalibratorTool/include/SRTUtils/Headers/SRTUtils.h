#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <sstream>
#include <iomanip>

class CSRTUtils
{
private:
	CSRTUtils(void);
	~CSRTUtils(void);
public:
		static int						ByteArrayFind                       	(unsigned char* inBufPtr, int inBufSz, unsigned char* tokenPtr, int tokenSz, int startIndex = 0);
		static int						ByteArrayFindLast                   	(unsigned char* inBufPtr, int inBufSz, unsigned char* tokenPtr, int tokenSz, int startIndex = 0);

		static bool						CheckIfDirectoryExists					(std::string directoryPath);
		static bool						CheckIfFileExists						(std::string filePath);
		static bool                     CleanupDir                          	(const char* path, std::string& errorStr);
		static bool                     CompareStringNoCase                 	(std::string str1, std::string str2);
        static unsigned int             CompareTickCountsSafely             	(long long start, long long end);
        static bool 					CompareTickCountsSafely					(long long start, long long end, unsigned int interval);
        static bool                     CopyFile                          		(const char* originalFilePath, const char* newFilePath);
        static bool						CountNumberOfFilesInDirectory			(std::string dirPath, unsigned int& numFiles);
        static bool						CreateDir                           	(const char* path, std::string& errorStr);

        static bool                     DeleteFile                          	(const char* filePath);

        static bool						ExtractDirectoryFromLinuxFilePath		(std::string filePath, std::string& directory);
        static bool						ExtractFilenameFromLinuxFilePath		(std::string filePath, std::string& filename);

        static bool						GetAllFileNamesInDir					(std::string dirPath, std::vector<std::string>& fileNames);
        static bool						GetAllFileNamesWithExtensionInDir		(std::string dirPath, std::string fileExtension, std::vector<std::string>& fileNames);
        static double                   GetAvailableDiskSpace					(const char* path, char choice);
        static void                     GetCurrentDateTime                  	(tm& datetime);
        static std::string              GetCurrentDateTimeStr               	(bool msec = true);
        static void                     GetCurrentUTCDateTime               	(tm& datetime);
        static bool                     GetNextArchiveDirectory             	(std::string rootDir, std::string& nextDirPath, unsigned int* index, unsigned int startYear, unsigned int startMonth, unsigned int startDay);
        static unsigned long long       GetSystemTimeAsMS                   	();
        static long long                GetTickCount                        	();
        static bool                     GmTimeSafe                          	(time_t inTime, struct tm& stm);

        static std::vector<uint8_t>     HexToBytes                          	(const std::string& hex);

        static bool                     IsDir                               	(std::string dir, std::string& error);
        static bool                     IsDirEmpty                          	(const char* path, std::string& errorStr);

        static bool                     LocalTimeSafe                       	(time_t inTime, struct tm& stm);

        static bool                     MoveFile                          		(const char* originalFilePath, const char* newFilePath);

        static bool						PathExists                         	 	(const char* pathtocheck, std::string& errorStr);
        static void						PrintFloatMatrix						(std::vector<std::vector<float> > matrix, int numRows, int numColumns, std::string matrixHeader, float highlightNumber = -1.0f);

        static void                     SafelyIncrementDate                 	(unsigned int& year, unsigned int& month, unsigned int& day);
        static bool						SolveAssignmentProblemHungarianAlgorithm(std::vector<std::vector<float> > matrix, int numRowsColumns, bool isMaximizationProblem, bool verbose, std::vector<int>& columnToRowMatchIndices);

        static std::string              TickCountToString                   	(long long tickCount);
	

        template< typename T >
		static std::string              IntToHex                            	(T i)
																				{
																					std::stringstream stream;
																					stream << std::setfill('0') << std::setw(sizeof(T)* 2)
																							<< std::hex << i;
																					return stream.str();
																				};
};
