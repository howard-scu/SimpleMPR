#ifndef _LW_IMAGE_READER_H
#define _LW_IMAGE_READER_H

#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>


class lwImageReader
{
public:
	typedef short PixelType;
	typedef itk::Image< PixelType, 3 >				ImageType;
	typedef itk::ImageSeriesReader< ImageType >		ReaderType;

	typedef itk::GDCMImageIO				ImageIOType;
	typedef itk::GDCMSeriesFileNames		NamesGeneratorType;
	typedef std::vector<std::string>		FileNamesContainer;

	typedef itk::MetaDataDictionary					DictionaryType;
	typedef itk::MetaDataObject< std::string >		MetaDataStringType;

	lwImageReader();
	~lwImageReader();

	void SetDirectory(const char* path);
	void Update();
	ImageType::Pointer GetImage();
	void Print();

	// 患者信息
	std::string _patient_name{ "" };
	std::string _patient_sex{ "" };
	std::string _patient_age{ "" };
	std::string _patient_body_examined{ "" };
	std::string _patient_id{ "" };

	// 医院相关
	std::string _modality{ "" };
	std::string _manufacture{ "" };
	std::string _institution{ "" };
	std::string _station{ "" };

	// study信息
	std::string _study_date{ "" };
	std::string _study_time{ "" };
	std::string _study_desc{ "" };
	std::string _study_id{ "" };

	// MR信息
	std::string _scanning_sequence{ "" };
	std::string _sequence_name{ "" };
	std::string _magnetic_field_strength{ "" };
	std::string _protocol_name{ "" };

	// image信息
	std::string _window{ "" };
	std::string _level{ "" };

private:
	ImageType::Pointer _image;
	const char* _path;
};

#endif // !_LW_IMAGE_READER_H
