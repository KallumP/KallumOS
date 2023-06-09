#include "DiffMatrixApp.h"


DiffMatrixApp::DiffMatrixApp() {

}

DiffMatrixApp::DiffMatrixApp(Point _position, Point _size) : Process("DiffMatrix", _position, _size) {

	int boxSize = 200;


	source = TextBox(Point(10, 40), Point(boxSize, 30), "", "Source");
	source.Tether(&position);
	source.SetFontSize(10);

	target = TextBox(Point(10 + boxSize + 10, 40), Point(boxSize, 30), "", "Target");
	target.Tether(&position);
	target.SetFontSize(10);

	go = Button(Point(10 + (boxSize + 10) * 2, 40), Point(30, 30), "Go");
	go.Tether(&position);
	go.SetFontSize(10);

}


void DiffMatrixApp::Tick(float elapsedTime) {


	if (display) {

		target.Hover(new Point(GetMouseX(), GetMouseY()));
		source.Hover(new Point(GetMouseX(), GetMouseY()));
		go.Hover(new Point(GetMouseX(), GetMouseY()));

	}
}


void DiffMatrixApp::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));


		go.Draw(offset);
		source.Draw(offset);
		target.Draw(offset);

		int buttonOffSet = go.GetSize().GetY() + 20;
		offset.Add(Point(0, buttonOffSet));


		Point dimensions = Point(target.GetValue().size() + 2, source.GetValue().size() + 2);
		Point boxSize;

		if (dimensions.GetX() != 0)
			boxSize.SetX(size.GetX() / dimensions.GetX());
		if (dimensions.GetY() != 0)
			boxSize.SetY((size.GetY() - buttonOffSet) / dimensions.GetY());

		DrawBorders(offset, dimensions, boxSize);
		DrawStrings(offset, dimensions, boxSize);
	}
}

void DiffMatrixApp::DrawBorders(Point offset, Point dimensions, Point boxSize) {
	
	for (int i = 0; i < dimensions.GetX(); i++) {

		DrawLine(
			offset.GetX() + i * boxSize.GetX(),
			offset.GetY(),
			offset.GetX() + i * boxSize.GetX(),
			offset.GetY() + dimensions.GetY() * boxSize.GetY(),
			BLACK);
	}

	for (int i = 0; i < dimensions.GetY(); i++) {

		DrawLine(
			offset.GetX(),
			offset.GetY() + i * boxSize.GetY(),
			offset.GetX() + dimensions.GetX() * boxSize.GetX(),
			offset.GetY() + i * boxSize.GetY(),
			BLACK);
	}
}
void DiffMatrixApp::DrawStrings(Point offset, Point dimensions, Point boxSize) {




}

void DiffMatrixApp::OnKeyPress(KeyPress* e) {

	//enter key should hit go
	if (e->GetKeyCode() == KEY_ENTER) {

		Go();
		return;
	}

	//no text box was selected
	if (focused == nullptr)
		return;

	//sends the keypress into the focused textbox
	focused->OnKeyPress(e);

}
void DiffMatrixApp::OnMousePress(MousePress* e) {

	SuperMousePress(NormaliseMousePos());


	if (source.Click(new Point(GetMouseX(), GetMouseY())))
		focused = &source;

	else if (target.Click(new Point(GetMouseX(), GetMouseY())))
		focused = &target;

	else if (go.Click(new Point(GetMouseX(), GetMouseY())))
		Go();

}

void DiffMatrixApp::GenerateEmptyMatrix() {

	std::vector<int> rowInts;
	std::vector<std::string> rowStrings;

	//makes a row for each letter in the source
	for (int i = 0; i < source.GetValue().size() + 1; i++) {

		rowInts.clear();
		rowStrings.clear();

		//makes a column for each letter in the target
		for (int j = 0; j < target.GetValue().size() + 1; j++) {

			rowInts.push_back(0);
			rowStrings.push_back("");
		}

		distanceMatrix.push_back(rowInts);
		fromMatrix.push_back(rowStrings);

	}
}


void DiffMatrixApp::FillMatrix() {

	//loops through the rows
	for (int row = 0; row < distanceMatrix.size(); row++) {

		//if this is the first row
		if (row == 0) {

			//loops through each column in this row
			for (int col = 0; col < distanceMatrix[row].size(); col++) {

				distanceMatrix[row][col] = col;

				if (col != 0)
					fromMatrix[row][col] = insert;
				else
					fromMatrix[row][col] = nothing;

			}

			continue;
		}


		//loops through all the columns in this row
		for (int col = 0; col < distanceMatrix[row].size(); col++) {

			//if this is the first column, just take the value from the cell above + 1
			if (col == 0) {
				distanceMatrix[row][col] = distanceMatrix[row - 1][col] + 1;
				fromMatrix[row][col] = delete_;
				continue;
			}

			//skip rule
			if (target.GetValue().substr(col - 1, 1) == source.GetValue().substr(row - 1, 1)) {
				distanceMatrix[row][col] = distanceMatrix[row - 1][col - 1];
				fromMatrix[row][col] = skip;
				continue;
			}


			int aboveValue = distanceMatrix[row - 1][col];
			int leftValue = distanceMatrix[row][col - 1];
			if (leftValue <= aboveValue) {

				distanceMatrix[row][col] = leftValue + 1; //insert rule
				fromMatrix[row][col] = insert;

			} else {

				distanceMatrix[row][col] = aboveValue + 1; // delete rule
				fromMatrix[row][col] = delete_;
			}
		}
	}
}

void DiffMatrixApp::OutputMatrix() {

	std::filesystem::path appPath = "hardDrive/DiffMatrix";

	if (!Helper::VerifyPathExists(appPath)) //if the path didn't exist
		if (!Helper::CreatePath(appPath)) //if the path could not be made
			return;


	std::cout << "\nWriting to file\n";
	std::ofstream matrixFile("hardDrive/DiffMatrix/Matrix.csv");

	std::string line;

	for (int i = 0; i < distanceMatrix.size(); i++) {

		line = "";
		for (int j = 0; j < distanceMatrix[i].size(); j++) {

			line += std::to_string(distanceMatrix[i][j]) + fromMatrix[i][j];
			line += ",";
		}

		if (i == 0)
			line += " ";
		else
			line += source.GetValue().substr(i - 1, 1);

		matrixFile << line << std::endl;
	}

	//adds the target at the bottom
	line = " ";
	for (int i = 0; i < target.GetValue().size(); i++) {
		line += ",";
		line += target.GetValue().substr(i, 1);
	}
	matrixFile << line << std::endl;


	matrixFile.close();
	std::cout << "\nWriting finished\n";
}
