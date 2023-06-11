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
}

void DiffMatrixApp::Tick(float elapsedTime) {


	if (display) {

		target.Hover(new Point(GetMouseX(), GetMouseY()));
		source.Hover(new Point(GetMouseX(), GetMouseY()));
	}
}

void DiffMatrixApp::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		source.Draw(offset);
		target.Draw(offset);

		int buttonOffSet = source.GetSize().GetY() + 20;
		offset.Add(Point(0, buttonOffSet));


		Point dimensions = Point(target.GetValue().size() + 2, source.GetValue().size() + 2);
		Point boxSize;

		if (dimensions.GetX() != 0)
			boxSize.SetX(size.GetX() / dimensions.GetX());
		if (dimensions.GetY() != 0)
			boxSize.SetY((size.GetY() - buttonOffSet) / dimensions.GetY());

		DrawPath(offset, dimensions, boxSize);
		DrawBorders(offset, dimensions, boxSize);
		DrawStrings(offset, dimensions, boxSize);
		DrawMatrix(offset, dimensions, boxSize);
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


	int lastRow = dimensions.GetY() - 1;
	for (int i = 0; i < target.GetValue().size(); i++)

		DrawText(
			target.GetValue().substr(i, 1).c_str(),
			offset.GetX() + (i + 1) * boxSize.GetX() + boxSize.GetX() / 2,
			offset.GetY() + lastRow * boxSize.GetY() + boxSize.GetY() / 2,
			10, BLACK);

	int lastCol = dimensions.GetX() - 1;
	for (int i = 0; i < source.GetValue().size(); i++)

		DrawText(
			source.GetValue().substr(i, 1).c_str(),
			offset.GetX() + lastCol * boxSize.GetX() + boxSize.GetX() / 2,
			offset.GetY() + (i + 1) * boxSize.GetY() + boxSize.GetY() / 2,
			10, BLACK);

}
void DiffMatrixApp::DrawMatrix(Point offset, Point dimensions, Point boxSize) {

	for (int i = 0; i < distanceMatrix.size(); i++) {

		for (int j = 0; j < distanceMatrix[i].size(); j++) {

			std::string content = "";
			content += std::to_string(distanceMatrix[i][j]);
			content += fromMatrix[i][j];

			DrawText(
				content.c_str(),
				offset.GetX() + j * boxSize.GetX() + boxSize.GetX() / 2,
				offset.GetY() + i * boxSize.GetY() + boxSize.GetY() / 2,
				10, BLACK);
		}

	}
}
void DiffMatrixApp::DrawPath(Point offset, Point dimensions, Point boxSize) {

	for (int i = 0; i < path.size(); i++) {
		DrawRectangle(offset.GetX() + path[i].GetX() * boxSize.GetX(), offset.GetY() + path[i].GetY() * boxSize.GetY(), boxSize.GetX(), boxSize.GetY(), GREEN);
	}
}


void DiffMatrixApp::OnKeyPress(KeyPress* e) {

	//no text box was selected
	if (focused == nullptr)
		return;

	//sends the keypress into the focused textbox
	focused->OnKeyPress(e);
	Go();
}

void DiffMatrixApp::OnMousePress(MousePress* e) {

	SuperMousePress(NormaliseMousePos());

	if (source.Click(new Point(GetMouseX(), GetMouseY())))
		focused = &source;

	else if (target.Click(new Point(GetMouseX(), GetMouseY())))
		focused = &target;
}

void DiffMatrixApp::GenerateEmptyMatrix() {

	distanceMatrix.clear();
	fromMatrix.clear();

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
				continue;
			}

			distanceMatrix[row][col] = aboveValue + 1; // delete rule
			fromMatrix[row][col] = delete_;
		}
	}
}

void DiffMatrixApp::FindPath() {

	path.clear();
	Point currentSpot = Point(fromMatrix[fromMatrix.size() - 1].size() - 1, fromMatrix.size() - 1);

	while (currentSpot.GetX() != 0 || currentSpot.GetY() != 0) {

		path.push_back(currentSpot);

		if (fromMatrix[currentSpot.GetY()][currentSpot.GetX()] == skip)
			currentSpot.Add(Point(-1, -1));

		else if (fromMatrix[currentSpot.GetY()][currentSpot.GetX()] == insert)
			currentSpot.Add(Point(-1, 0));

		else if (fromMatrix[currentSpot.GetY()][currentSpot.GetX()] == delete_)
			currentSpot.Add(Point(0, -1));
	}

	path.push_back(currentSpot);
}