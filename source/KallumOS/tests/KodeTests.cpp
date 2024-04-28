#include "kodeTests.h"
#include "../kGraphics.h"
#include "../Kode.h"

KodeTests::KodeTests(Point _position, Point _size) : Process("Kode tests", _position, _size) {

	fontSize = 20;
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
	int charsPerLine = (size.GetX() - padding * 2) / MeasureText("X", fontSize);

	//loops through each statement
	int lineCount = 0;
	for (int i = 0; i < testOutputs.size(); i++) {

		//sets up the statement with the line number
		std::string text =
			testOutputs[i].message == PassString ?
			testOutputs[i].testName + " - " + PassString :
			testOutputs[i].testName + " - " + testOutputs[i].testStep + " - " + testOutputs[i].message;
		text = std::to_string(i) + ": " + text;


		Color toDraw = testOutputs[i].message == PassString ? GREEN : RED;

		//if there wasn't enough characters to fill a line
		if (text.size() < charsPerLine) {

			kGraphics::DrawString(text, padding + offset.GetX(), offset.GetY() + padding + (Helper::GetNextLineY(lineCount, fontSize)), fontSize, toDraw);
			lineCount++;

		} else {

			//gets the number of lines that need to be drawn for this statemenet
			int linesToDraw = std::ceil(text.size() / (float)charsPerLine);

			//loops through each line
			for (int j = 0; j < linesToDraw; j++) {

				std::string line = text.substr(j * charsPerLine, charsPerLine);
				kGraphics::DrawString(line, padding + offset.GetX(), offset.GetY() + padding + Helper::GetNextLineY(lineCount, fontSize), fontSize, toDraw);
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


	testOutputs.push_back(BoolEquals());
	testOutputs.push_back(BoolNotEquals());
	testOutputs.push_back(BoolMore());
	testOutputs.push_back(BoolLess());
	testOutputs.push_back(BoolIntMix());

	testOutputs.push_back(PureBoolAssign());
	testOutputs.push_back(PureBoolEquals());
	testOutputs.push_back(PureBoolNot());
	testOutputs.push_back(PureBoolAnd());
	testOutputs.push_back(PureBoolOr());
	testOutputs.push_back(PureBoolCombined());
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

TestResult KodeTests::IntAdd() {
	std::string name = "Int Add";

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
	std::string name = "Int Subtract";

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
	std::string name = "Int Multiply";

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
	std::string name = "Int Divide";

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
	std::string name = "Int Divide by 0";

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

TestResult KodeTests::BoolEquals() {
	std::string name = "Bool Equals";

	std::vector<std::string> statements;
	statements.push_back("bool t = 4 == 4");
	statements.push_back("out t"); //should out true
	statements.push_back("bool f = 5 == 4");
	statements.push_back("out f"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::BoolNotEquals() {
	std::string name = "Bool Not equals";

	std::vector<std::string> statements;
	statements.push_back("bool t = 3 != 4");
	statements.push_back("out t"); //should out true
	statements.push_back("bool f = 3 != 3");
	statements.push_back("out f"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::BoolMore() {
	std::string name = "Bool More than";

	std::vector<std::string> statements;
	statements.push_back("bool t = 5 > 4");
	statements.push_back("out t"); //should out true
	statements.push_back("bool f = 5 > 6");
	statements.push_back("out f"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::BoolLess() {
	std::string name = "Bool Less than";

	std::vector<std::string> statements;
	statements.push_back("bool t = 5 < 6");
	statements.push_back("out t"); //should out true
	statements.push_back("bool f = 5 < 4");
	statements.push_back("out f"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::BoolIntMix() {
	std::string name = "Bool and Int mix";

	std::vector<std::string> statements;
	statements.push_back("int x = 1");
	statements.push_back("int y = 2");
	statements.push_back("bool f = x == y");
	statements.push_back("bool t = x == y - 1");
	statements.push_back("out f"); //should out false
	statements.push_back("out t"); //should out true

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(4, "false"));
	expectedOutputs.push_back(ExpectedOutput(5, "true"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::PureBoolAssign() {
	std::string name = "Pure Bool Assign";

	std::vector<std::string> statements;
	statements.push_back("bool t = true");
	statements.push_back("out t"); //should out true
	statements.push_back("bool f = false");
	statements.push_back("out f"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::PureBoolEquals() {
	std::string name = "Pure Bool Equals";

	std::vector<std::string> statements;
	statements.push_back("bool t = true == true");
	statements.push_back("out t"); //should out true
	statements.push_back("bool f = true == false");
	statements.push_back("out f"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::PureBoolNot() {
	std::string name = "Pure Bool Not";

	std::vector<std::string> statements;
	statements.push_back("bool t = true == true");
	statements.push_back("out t"); //should out true
	statements.push_back("bool f = true == false");
	statements.push_back("out f"); //should out false
	statements.push_back("bool a = false == false");
	statements.push_back("out a"); //should out true

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));
	expectedOutputs.push_back(ExpectedOutput(5, "true"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::PureBoolAnd() {
	std::string name = "Pure Bool And";

	std::vector<std::string> statements;
	statements.push_back("bool a = true && true");
	statements.push_back("out a"); //should out true
	statements.push_back("bool b = true && false");
	statements.push_back("out b"); //should out false
	statements.push_back("bool c = false && true");
	statements.push_back("out c"); //should out false
	statements.push_back("bool d = false && false");
	statements.push_back("out d"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));
	expectedOutputs.push_back(ExpectedOutput(5, "false"));
	expectedOutputs.push_back(ExpectedOutput(7, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::PureBoolOr() {
	std::string name = "Pure Bool Or";

	std::vector<std::string> statements;
	statements.push_back("bool a = true ^^ true");
	statements.push_back("out a"); //should out true
	statements.push_back("bool b = true ^^ false");
	statements.push_back("out b"); //should out true
	statements.push_back("bool c = false ^^ true");
	statements.push_back("out c"); //should out true
	statements.push_back("bool d = false ^^ false");
	statements.push_back("out d"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "true"));
	expectedOutputs.push_back(ExpectedOutput(5, "true"));
	expectedOutputs.push_back(ExpectedOutput(7, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::PureBoolCombined() {
	std::string name = "Pure Bool Combined";

	std::vector<std::string> statements;
	statements.push_back("bool foo = true");
	statements.push_back("out foo"); //should out true

	statements.push_back("bool bar = true == false");
	statements.push_back("out bar"); //should out false

	statements.push_back("bool a = bar == foo");
	statements.push_back("out a"); //should out false

	statements.push_back("bool b = true == ! false");
	statements.push_back("out b"); //should out true

	statements.push_back("bool c = foo && foo == ! false ^^ bar");
	statements.push_back("out c"); //should out true

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "false"));
	expectedOutputs.push_back(ExpectedOutput(5, "false"));
	expectedOutputs.push_back(ExpectedOutput(7, "true"));
	expectedOutputs.push_back(ExpectedOutput(9, "true"));

	return KodeTestRun(name, statements, expectedOutputs);
}