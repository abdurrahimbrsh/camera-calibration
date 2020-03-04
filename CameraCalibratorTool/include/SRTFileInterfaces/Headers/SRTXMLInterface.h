#pragma once

#include "tinyxml2.h"

#include <string>
#include <list>
#include <vector>

typedef struct
{
	std::string 							database;
	std::string 							annotation;
	std::string 							image;
	std::list<std::string>					environmentTags;
	std::string 							camera;
} AimeeAnnotationSourceData;

typedef struct
{
	int 									width;
	int 									height;
	int 									depth;
} AimeeAnnotationImageDims;

typedef struct
{
	int										xmin;
	int										ymin;
	int										xmax;
	int										ymax;
} AimeeAnnotationObjectBoundingBox;

typedef struct
{
	int										id;
	int										occluded;
	AimeeAnnotationObjectBoundingBox		bBox;
	int										truncated;
	int										difficult;
	std::string								objectClassName;
	std::list<std::string>					tags;
	int										pose;
	int										ignore;
	int										occluder;
	int										duplicated;
} AimeeAnnotationObject;

typedef struct
{
	std::string 							folder;
	std::string 							filename;
	AimeeAnnotationSourceData 				sourceData;
	bool 									segmented;
	AimeeAnnotationImageDims 				imageDimensions;
	std::vector<AimeeAnnotationObject>		objects;
} AimeeAnnotationData;

typedef struct
{
	std::string 							imageFilePath;
	std::string 							annotationFilePath;
	AimeeAnnotationData 					annotationData;
}AimeeAnnotation;

class CSRTXMLInterface
{
public:
	CSRTXMLInterface(void);
	~CSRTXMLInterface(void);

	static bool	LoadDataFromAnnotationXMLFile		(std::string annotationXMLFilePath, AimeeAnnotationData& annotationData);

	static bool	ParseXMLAnnotationNode				(tinyxml2::XMLNode* xmlNode, AimeeAnnotationData& annotationData);

private:
};
