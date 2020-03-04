#pragma once

#include "SRTXMLInterface.h"

#include <string>
#include <map>

typedef struct
{
	int 	imageId;
	int 	objectClassId;
	float 	confidence;
	int 	xmin;
	int 	ymin;
	int 	xmax;
	int 	ymax;
}SSDObjectDetection;

class CSRTAimeeUtils
{
public:
	CSRTAimeeUtils(void);
	~CSRTAimeeUtils(void);

	static 	bool CreateAnnotationMapFromDir				(std::string annotationDirPath, std::map<std::string, AimeeAnnotation>& annotationMap,
													 	 std::string imageFileExtension, std::string annotationFileExtension);

	static  bool ExtractAnnotationMapSubset				(std::map<std::string, AimeeAnnotation> completeAnnotationMap, float extractionPercentage,
													 	 std::map<std::string, AimeeAnnotation>& subsetAnnotationMap);

	static	bool FindSnapShotSolverStateFilePath		(std::string snapShotPrefix, std::string& snapShotSolverStateFilePath);

	static 	void InsertValueInTop5Vector				(float confidence, int index, std::vector<float>& classConfidences, std::vector<int>& classIndices);

	static 	void PrintAnnotationInfo					(AimeeAnnotation annotationInfo);
	static  void ProcessOutputDataImageClassification	(float* outputData, int numOutputValues, int numImages, std::vector<std::vector<float>>& maxConfValues,
														 std::vector<std::vector<int>>& maxConfClassIndices);
	static void	ProcessOutputDataSSDObjectDetection		(float* outputData, int outputDataSize, int imageWidth, int imageHeight,
														 std::vector<SSDObjectDetection>& detections);


	static  bool SplitAnnotationMap						(std::map<std::string, AimeeAnnotation> completeAnnotationMap, float firstPoritionPercentage,
														 std::map<std::string, AimeeAnnotation>& firstPortionAnnotationMap,
														 std::map<std::string, AimeeAnnotation>& secondPortionAnnotationMap);

	static 	bool VerifyAnnotationMap					(std::map<std::string, AimeeAnnotation>& annotationMap, std::string logFilePath = "");

private:
};
