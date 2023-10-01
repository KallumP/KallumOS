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
	bool OnMousePress(MousePress* e);
	bool OnMouseMove(Point* e);

	bool GetReady() { return ready; }
	std::string GetSelectedFileName() { return selectedFile->fileName; }
	std::filesystem::path GetSelectedFilePath() { return selectedFile->filePath; }

private:
	void HandleFileClick();
	void SetData();

	FileOption* selectedFile;
	Button submit;
	bool ready;
};

