#include "kodeTests.h"
#include "../kGraphics.h"
#include "../Kode.h"

KodeTests::KodeTests(Point _position, Point _size) : Process("Kode tests", _position, _size) {

	defaultFontSize = 20;
	RunTests();
}

void KodeTests::Draw(Point offset) {

	if (display) {

		DrawBoxBar(offset, true);
		offset.Set(new Point(offset.GetX() + position.GetX(), offset.GetY() + position.GetY() + barHeight));

		DrawTestOutputs(offset);
	}
}

void KodeTests::DrawTestOutputs(Point offset) {
	int padding = 10;

	//how many of the biggest char can fit in the box
	int charsPerLine = (size.GetX() - padding * 2) / MeasureText("X", defaultFontSize);

	//loops through each statement
	int lineCount = 0;
	for (int i = 0; i < testOutputs.size(); i++) {

		//sets up the statement with the line number
		std::string text =
			testOutputs[i].message == PassString ?
			testOutputs[i].testName + " - " + PassString :
			testOutputs[i].testName + " - " + testOutputs[i].testStep + " - " + testOutputs[i].message;

		Color toDraw = testOutputs[i].message == PassString ? GREEN : RED;

		//if there wasn't enough characters to fill a line
		if (text.size() < charsPerLine) {

			kGraphics::DrawString(text, padding + offset.GetX(), offset.GetY() + padding + (Helper::GetNextLineY(lineCount, defaultFontSize)), defaultFontSize, toDraw);
			lineCount++;

		} else {

			//gets the number of lines that need to be drawn for this statemenet
			int linesToDraw = std::ceil(text.size() / (float)charsPerLine);

			//loops through each line
			for (int j = 0; j < linesToDraw; j++) {

				std::string line = text.substr(j * charsPerLine, charsPerLine);
				kGraphics::DrawString(line, padding + offset.GetX(), offset.GetY() + padding + Helper::GetNextLineY(lineCount, defaultFontSize), defaultFontSize, toDraw);
				lineCount++;
			}
		}
	}
}

void KodeTests::RunTests() {
	testOutputs.push_back(IntAdd());
	testOutputs.push_back(IntSub());
	testOutputs.push_back(IntMult());
	testOutputs.push_back(IntDiv());
	testOutputs.push_back(IntDiv0());
	testOutputs.push_back(IntCombinedTesting());
}

TestResult KodeTests::IntAdd() {
	std::string name = "IntAdd";

	std::vector<std::string> statements;
	statements.push_back("int x = 2");
	statements.push_back("int y = 3");
	statements.push_back("int z = y + x");
	statements.push_back("out z"); //should out 5

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(3, "5"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::IntSub() {
	std::string name = "IntSub";

	std::vector<std::string> statements;
	statements.push_back("int x = 2");
	statements.push_back("int y = 3");
	statements.push_back("int z = y - x");
	statements.push_back("out z"); //should out 1

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(3, "1"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::IntMult() {
	std::string name = "IntMult";

	std::vector<std::string> statements;
	statements.push_back("int x = 2");
	statements.push_back("int y = 3");
	statements.push_back("int z = y * x");
	statements.push_back("out z"); //should out 6

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(3, "6"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::IntDiv() {
	std::string name = "IntDiv";

	std::vector<std::string> statements;
	statements.push_back("int x = 2");
	statements.push_back("int y = 12");
	statements.push_back("int z = y / x");
	statements.push_back("out z"); //should out 6

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(3, "6"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::IntDiv0() {
	std::string name = "IntDiv0";

	std::vector<std::string> statements;
	statements.push_back("int z = 6");
	statements.push_back("int y = 0");
	statements.push_back("z = z / y");
	statements.push_back("out z"); //should out 6

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(2, "Tried to divide by zero. Division operation skipped"));
	expectedOutputs.push_back(ExpectedOutput(3, "6"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::IntCombinedTesting() {
	std::string name = "Int Full";

	std::vector<std::string> statements;
	statements.push_back("int x = 2");
	statements.push_back("int y = 3");
	statements.push_back("int z = y + x");
	statements.push_back("out z"); //should out 5

	statements.push_back("z = y - x");
	statements.push_back("out z"); //should out 1

	statements.push_back("z = y * x");
	statements.push_back("out z");//should out 6

	statements.push_back("z = z + z");
	statements.push_back("out z"); //should out 12

	statements.push_back("z = z ^ 2");
	statements.push_back("out z"); //should out 144

	statements.push_back("z = z / 2");
	statements.push_back("out z"); //should out 72

	statements.push_back("z = z / 0"); //should out error
	statements.push_back("out z"); //should out 72

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(3, "5"));
	expectedOutputs.push_back(ExpectedOutput(5, "1"));
	expectedOutputs.push_back(ExpectedOutput(7, "6"));
	expectedOutputs.push_back(ExpectedOutput(9, "12"));
	expectedOutputs.push_back(ExpectedOutput(11, "144"));
	expectedOutputs.push_back(ExpectedOutput(13, "72"));
	expectedOutputs.push_back(ExpectedOutput(14, "Tried to divide by zero. Division operation skipped"));
	expectedOutputs.push_back(ExpectedOutput(15, "72"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::KodeTestRun(std::string name, std::vector<std::string> statements, std::vector<ExpectedOutput> expectedOutputs) {

	Kode k = Kode();
	k.SetStatements(statements);
	k.Run();

	std::vector<ConsoleText> generatedConsole = k.GetConsole();

	//right number of outputs
	int expectedOutputCount = expectedOutputs.size();
	int actualOutputCount = generatedConsole.size();
	if (expectedOutputCount != actualOutputCount)
		return TestResult(name, "Number of outputs", Asserter::ValuesNotEqualMessage(std::to_string(expectedOutputCount), std::to_string(actualOutputCount)));

	//goes through the different expected outputs
	for (int i = 0; i < expectedOutputs.size(); i++) {

		//value linked to correct statement
		int expectedStatementLink = expectedOutputs[i].statementLink;
		int actualStatementLink = generatedConsole[i].linkedToStatement;
		if (expectedStatementLink != actualStatementLink)
			return TestResult(name, "Statement link: " + std::to_string(i), Asserter::ValuesNotEqualMessage(std::to_string(expectedStatementLink), std::to_string(actualStatementLink)));

		//output value
		std::string expectedValue = expectedOutputs[i].value;
		std::string actualValue = k.GetConsole()[i].text;
		if (actualValue != expectedValue)
			return TestResult(name, "Output value: " + std::to_string(i), Asserter::ValuesNotEqualMessage(expectedValue, actualValue));
	}

	//no error :)
	return TestResult(name, "", PassString);
}