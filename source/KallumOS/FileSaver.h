#pragma once
#include "FileViewer.h"
#include "Button.h"
#include "TextBox.h"

class FileSaver : public FileViewer {

public:
	FileSaver();
	FileSaver(Point _position, Point _size, std::filesystem::path appPath);

	void Draw(Point offset);
	bool Hover(Point* mousePosition);
	bool Click(Point* mousePosition);
	void OnKeyPress(KeyPress* e);

	bool GetReady() { return ready; }
	std::string GetSelectedFileName() { return name.GetValue(); }
	std::filesystem::path GetSelectedFilePath() { return std::filesystem::path(path/ name.GetValue()); }

private:
	void HandleFileClick();
	void SetData();

	Button submit;
	TextBox name;
	bool ready;
};

