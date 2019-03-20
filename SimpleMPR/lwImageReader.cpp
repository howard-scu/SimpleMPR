#include "lwImageReader.h"


lwImageReader::lwImageReader()
{
}


lwImageReader::~lwImageReader()
{
}

void lwImageReader::SetDirectory(const char * path)
{
	_path = path;
}

std::string GetTagValue(const lwImageReader::DictionaryType &dictionary, std::string tag)
{
	auto itr = dictionary.Begin();
	auto end = dictionary.End();

	auto tagItr = dictionary.Find(tag);
	if (tagItr != end)
	{
		lwImageReader::MetaDataStringType::ConstPointer entryvalue = dynamic_cast<const lwImageReader::MetaDataStringType *>(tagItr->second.GetPointer());
		if (entryvalue)
		{
			return entryvalue->GetMetaDataObjectValue();
		}
	}
	return "";
}

void lwImageReader::Update()
{
	ReaderType::Pointer reader = ReaderType::New();
	ImageIOType::Pointer dicomIO = ImageIOType::New();
	reader->SetImageIO(dicomIO);
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->SetUseSeriesDetails(true);
	nameGenerator->AddSeriesRestriction("0008|0021");
	nameGenerator->SetGlobalWarningDisplay(false);
	nameGenerator->SetDirectory(_path);

	FileNamesContainer fileNames = nameGenerator->GetInputFileNames();
	reader->SetFileNames(fileNames);
	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject &ex)
	{
		std::cout << ex << std::endl;
	}

	const DictionaryType & dictionary = dicomIO->GetMetaDataDictionary();

	_patient_name = GetTagValue(dictionary, "0010|0010");
	_patient_sex = GetTagValue(dictionary, "0010|0040");
	_patient_age = GetTagValue(dictionary, "0010|1010");
	_patient_body_examined = GetTagValue(dictionary, "0018|0015");
	_patient_id = GetTagValue(dictionary, "0010|0020");

	_modality = GetTagValue(dictionary, "0008|0060");
	_manufacture = GetTagValue(dictionary, "0008|0070");
	_institution = GetTagValue(dictionary, "0008|0080");
	_station = GetTagValue(dictionary, "0008|1010");

	_study_date = GetTagValue(dictionary, "0008|0020");
	_study_time = GetTagValue(dictionary, "0008|0030");
	_study_desc = GetTagValue(dictionary, "0008|1030");
	_study_id = GetTagValue(dictionary, "0020|0010");

	_study_id = GetTagValue(dictionary, "0020|0010");
	_study_id = GetTagValue(dictionary, "0020|0010");
	_study_id = GetTagValue(dictionary, "0020|0010");
	_study_id = GetTagValue(dictionary, "0020|0010");


	_scanning_sequence = GetTagValue(dictionary, "0018|0020");
	_sequence_name = GetTagValue(dictionary, "0018|0024");
	_magnetic_field_strength = GetTagValue(dictionary, "0018|0087");
	_protocol_name = GetTagValue(dictionary, "0018|1030");

	_window = GetTagValue(dictionary, "0028|1051");
	_level = GetTagValue(dictionary, "0028|1050");

	// 读取首个序列
	using SeriesIdContainer = std::vector< std::string >;
	const SeriesIdContainer & seriesUID = nameGenerator->GetSeriesUIDs();
	auto seriesItr = seriesUID.begin();
	auto seriesEnd = seriesUID.end();
	if (seriesItr != seriesEnd)
	{
		using FileNamesContainer = std::vector< std::string >;
		FileNamesContainer fileNames = nameGenerator->GetFileNames(seriesItr->c_str());
		using ReaderType = itk::ImageSeriesReader< ImageType >;
		ReaderType::Pointer reader = ReaderType::New();
		using ImageIOType = itk::GDCMImageIO;
		ImageIOType::Pointer dicomIO = ImageIOType::New();
		reader->SetImageIO(dicomIO);
		reader->SetFileNames(fileNames);
		reader->Update();

		_image = reader->GetOutput();
	}
}

lwImageReader::ImageType::Pointer lwImageReader::GetImage()
{
	return _image;
}


void lwImageReader::Print()
{
	//std::string info1 = _patient_name + "/" + _patient_sex + "/" + _patient_age + "\n" + _patient_body_examined;
	//std::cout << info1 << std::endl;

	//std::cout << _patient_name << std::endl;
	//std::cout << _patient_sex << std::endl;
	//std::cout << _patient_age << std::endl;
	//std::cout << _patient_body_examined << std::endl;
	//std::cout << _patient_id << std::endl;
	//std::cout << _modality << std::endl;
	//std::cout << _manufacture << std::endl;
	//std::cout << _institution << std::endl;
	//std::cout << _station << std::endl;
	//std::cout << _study_date << std::endl;
	//std::cout << _study_time << std::endl;
	//std::cout << _study_desc << std::endl;
	//std::cout << _study_id << std::endl;
	//std::cout << _scanning_sequence << std::endl;
	//std::cout << _sequence_name << std::endl;
	//std::cout << _magnetic_field_strength << std::endl;
	//std::cout << _protocol_name << std::endl;
	//std::cout << _window << std::endl;
	//std::cout << _level << std::endl;
}
