#pragma once
#include "FileViewer.h"
#include "Helper.h"
#include "Control.h"
#include "Button.h"

#include <filesystem>


class FileSelector : public FileViewer {

public:

	FileSelector();
	FileSelector(Point _position, Point _size, std::filesystem::path appPath);

	void Draw(Point offset);
	bool Hover(Point* mousePosition);
	bool Click(Point* mousePosition);

	bool GetReady() { return ready; }
	std::string GetSelectedFileName() { return selectedFile->fileName; }
	std::filesystem::path GetSelectedFilePath() { return selectedFile->filePath; }

private:

	FileOption* selectedFile;

	void HandleFileClick();
	
	void SetData();

	Button submit;
	bool ready;
};

