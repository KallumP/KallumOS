#include "kodeTests.h"
#include "../kGraphics.h"
#include "../Kode.h"

KodeTests::KodeTests(Point _position, Point _size) : Process("Kode tests", _position, _size) {

	fontSize = 10;
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
	testOutputs.push_back(Int_Add());
	testOutputs.push_back(Int_Sub());
	testOutputs.push_back(Int_Mult());
	testOutputs.push_back(Int_Div());
	testOutputs.push_back(Int_Div0());
	testOutputs.push_back(Int_CombinedTesting());

	testOutputs.push_back(Bool_Equals());
	testOutputs.push_back(Bool_NotEquals());
	testOutputs.push_back(Bool_More());
	testOutputs.push_back(Bool_MoreEqual());
	testOutputs.push_back(Bool_Less());
	testOutputs.push_back(Bool_LessEqual());
	testOutputs.push_back(Bool_IntMix());

	testOutputs.push_back(PureBool_Assign());
	testOutputs.push_back(PureBool_Equals());
	testOutputs.push_back(PureBool_Not());
	testOutputs.push_back(PureBool_And());
	testOutputs.push_back(PureBool_Or());
	testOutputs.push_back(PureBool_Combined());

	testOutputs.push_back(If_FalseCondition());
	testOutputs.push_back(If_TrueCondition());
	testOutputs.push_back(If_NoEnd());
	testOutputs.push_back(If_NoIf());
	testOutputs.push_back(NestedIf_BothTrue());
	testOutputs.push_back(NestedIf_OuterTrueInnerFalse());
	testOutputs.push_back(NestedIf_OuterFalseInnerTrue());
	testOutputs.push_back(NestedIf_BothFalse());
	testOutputs.push_back(NestedIf_NoEnds());
	testOutputs.push_back(NestedIf_OneEnd());

	testOutputs.push_back(MiscFibonacci());
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
		return TestResult(name, "Number of outputs", ValuesNotEqualMessage(std::to_string(expectedOutputCount), std::to_string(actualOutputCount)));

	//goes through the different expected outputs
	for (int i = 0; i < expectedOutputs.size(); i++) {

		//value linked to correct statement
		int expectedLink = expectedOutputs[i].statementLink;
		int actualLink = generatedConsole[i].linkedToStatement;
		if (expectedLink != actualLink)
			return TestResult(name, "Statement link: " + std::to_string(i + 1), ValuesNotEqualMessage(std::to_string(expectedLink), std::to_string(actualLink)));

		//output value
		std::string expectedValue = expectedOutputs[i].value;
		std::string actualValue = k.GetConsole()[i].text;
		if (actualValue != expectedValue)
			return TestResult(name, "Output value: " + std::to_string(i + 1), ValuesNotEqualMessage(expectedValue, actualValue));
	}

	//no error :)
	return TestResult(name, "", PassString);
}

TestResult KodeTests::Int_Add() {
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
TestResult KodeTests::Int_Sub() {
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
TestResult KodeTests::Int_Mult() {
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
TestResult KodeTests::Int_Div() {
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
TestResult KodeTests::Int_Div0() {
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
TestResult KodeTests::Int_CombinedTesting() {
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

//add tests for
//invalid equation
//invalid string to int

TestResult KodeTests::Bool_Equals() {
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
TestResult KodeTests::Bool_NotEquals() {
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
TestResult KodeTests::Bool_More() {
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
TestResult KodeTests::Bool_MoreEqual() {
	std::string name = "Bool More than or equal to";

	std::vector<std::string> statements;
	statements.push_back("bool a = 5 >= 4");
	statements.push_back("out a"); //should out true
	statements.push_back("bool b = 5 >= 5");
	statements.push_back("out b"); //should out true
	statements.push_back("bool c = 5 >= 6");
	statements.push_back("out c"); //should out false

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "true"));
	expectedOutputs.push_back(ExpectedOutput(3, "true"));
	expectedOutputs.push_back(ExpectedOutput(5, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::Bool_Less() {
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
TestResult KodeTests::Bool_LessEqual() {
	std::string name = "Bool Less than or equal to";

	std::vector<std::string> statements;
	statements.push_back("bool a = 5 <= 4");
	statements.push_back("out a"); //should out false
	statements.push_back("bool b = 5 <= 5");
	statements.push_back("out b"); //should out true
	statements.push_back("bool b = 5 <= 6");
	statements.push_back("out b"); //should out true

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(1, "false"));
	expectedOutputs.push_back(ExpectedOutput(3, "true"));
	expectedOutputs.push_back(ExpectedOutput(5, "true"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::Bool_IntMix() {
	std::string name = "Bool and Int mix";

	std::vector<std::string> statements;
	statements.push_back("int x = 1");
	statements.push_back("int y = 2");
	statements.push_back("bool f = x == y");
	statements.push_back("bool t = x == y - 1");
	statements.push_back("out f"); //should out false
	statements.push_back("out t"); //should out true
	statements.push_back("bool a = x <= y - 1");
	statements.push_back("bool b = x >= y");
	statements.push_back("out a"); //should out true
	statements.push_back("out b"); //should out false



	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(4, "false"));
	expectedOutputs.push_back(ExpectedOutput(5, "true"));
	expectedOutputs.push_back(ExpectedOutput(8, "true"));
	expectedOutputs.push_back(ExpectedOutput(9, "false"));

	return KodeTestRun(name, statements, expectedOutputs);
}

TestResult KodeTests::PureBool_Assign() {
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
TestResult KodeTests::PureBool_Equals() {
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
TestResult KodeTests::PureBool_Not() {
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
TestResult KodeTests::PureBool_And() {
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
TestResult KodeTests::PureBool_Or() {
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
TestResult KodeTests::PureBool_Combined() {
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

//add tests for
//invalid equation
//invalid string to boolean
//invalid arithmetic 

TestResult KodeTests::If_FalseCondition() {
	std::string name = "If False condition";

	std::vector<std::string> statements;
	statements.push_back("bool foo = false");
	statements.push_back("if foo");
	statements.push_back("out inside if statement"); //should not run
	statements.push_back("endif");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(4, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::If_TrueCondition() {
	std::string name = "If True condition";

	std::vector<std::string> statements;
	statements.push_back("int bar = 3");
	statements.push_back("int car = 2");
	statements.push_back("if bar > car");
	statements.push_back("out inside if statement"); //should run
	statements.push_back("endif");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(3, "inside if statement"));
	expectedOutputs.push_back(ExpectedOutput(5, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::If_NoEnd() {
	std::string name = "If No end";

	std::vector<std::string> statements;
	statements.push_back("int bar = 3");
	statements.push_back("int car = 2");
	statements.push_back("if bar == car");
	statements.push_back("out inside if statement"); //should run
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(2, "No endif instruction found to complete this if statement"));
	expectedOutputs.push_back(ExpectedOutput(3, "inside if statement"));
	expectedOutputs.push_back(ExpectedOutput(4, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::If_NoIf() {
	std::string name = "If No if";

	std::vector<std::string> statements;
	statements.push_back("int bar = 3");
	statements.push_back("int car = 2");
	statements.push_back("out inside if statement"); //should run
	statements.push_back("endif");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(2, "inside if statement"));
	expectedOutputs.push_back(ExpectedOutput(4, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}

//add tests for 
//resolve boolean variables
//resolve boolean pure boolean
//resolve arithmetic boolean
//invalid resolve boolean

TestResult KodeTests::NestedIf_BothTrue() {
	std::string name = "Nested If: Both true";

	std::vector<std::string> statements;
	statements.push_back("if true");
	statements.push_back("if true");
	statements.push_back("out inner if");
	statements.push_back("endif");
	statements.push_back("out outer if");
	statements.push_back("endif");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(2, "inner if"));
	expectedOutputs.push_back(ExpectedOutput(4, "outer if"));
	expectedOutputs.push_back(ExpectedOutput(6, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::NestedIf_OuterTrueInnerFalse() {
	std::string name = "Nested If: Outer true, inner false";

	std::vector<std::string> statements;
	statements.push_back("if true");
	statements.push_back("if false");
	statements.push_back("out inner if");
	statements.push_back("endif");
	statements.push_back("out outer if");
	statements.push_back("endif");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(4, "outer if"));
	expectedOutputs.push_back(ExpectedOutput(6, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::NestedIf_OuterFalseInnerTrue() {
	std::string name = "Nested If: Outer false, inner true";

	std::vector<std::string> statements;
	statements.push_back("if false");
	statements.push_back("if true");
	statements.push_back("out inner if");
	statements.push_back("endif");
	statements.push_back("out outer if");
	statements.push_back("endif");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(6, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::NestedIf_BothFalse() {
	std::string name = "Nested If: Both false";

	std::vector<std::string> statements;
	statements.push_back("if false");
	statements.push_back("if false");
	statements.push_back("out inner if");
	statements.push_back("endif");
	statements.push_back("out outer if");
	statements.push_back("endif");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(6, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::NestedIf_NoEnds() {
	std::string name = "Nested If: No ends";

	std::vector<std::string> statements;
	statements.push_back("if false");
	statements.push_back("if false");
	statements.push_back("out inner if");
	statements.push_back("out outer if");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(0, "No endif instruction found to complete this if statement"));
	expectedOutputs.push_back(ExpectedOutput(1, "No endif instruction found to complete this if statement"));
	expectedOutputs.push_back(ExpectedOutput(2, "inner if"));
	expectedOutputs.push_back(ExpectedOutput(3, "outer if"));
	expectedOutputs.push_back(ExpectedOutput(4, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}
TestResult KodeTests::NestedIf_OneEnd() {

	std::string name = "Nested If: One end";

	std::vector<std::string> statements;
	statements.push_back("if false");
	statements.push_back("if false");
	statements.push_back("out inner if");
	statements.push_back("endif");
	statements.push_back("out outer if");
	statements.push_back("out rest of program");

	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(0, "No endif instruction found to complete this if statement"));
	expectedOutputs.push_back(ExpectedOutput(4, "outer if"));
	expectedOutputs.push_back(ExpectedOutput(5, "rest of program"));

	return KodeTestRun(name, statements, expectedOutputs);
}


TestResult KodeTests::MiscFibonacci() {
	std::string name = "miscellaneous Fibonacci numbers";

	std::vector<std::string> statements;
	statements.push_back("int input = 20");
	statements.push_back("int current = 0");
	statements.push_back("int previous = 1");
	statements.push_back("int iterations = 1");
	statements.push_back("int buffer = 1");
	statements.push_back("bool exit = false");

	statements.push_back("if input < 2");
	statements.push_back("exit = true");
	statements.push_back("current = 1");
	statements.push_back("endif");

	statements.push_back("while ! exit");

	statements.push_back("buffer = current");
	statements.push_back("current = current + previous");
	statements.push_back("previous = buffer");
	statements.push_back("iterations = iterations + 1");

	statements.push_back("if iterations > input");
	statements.push_back("exit = true");
	statements.push_back("endif");

	statements.push_back("out current");
	statements.push_back("endwhile");
	statements.push_back("out done");



	std::vector<ExpectedOutput> expectedOutputs;
	expectedOutputs.push_back(ExpectedOutput(18, "1"));
	expectedOutputs.push_back(ExpectedOutput(18, "1"));
	expectedOutputs.push_back(ExpectedOutput(18, "2"));
	expectedOutputs.push_back(ExpectedOutput(18, "3"));
	expectedOutputs.push_back(ExpectedOutput(18, "5"));
	expectedOutputs.push_back(ExpectedOutput(18, "8"));
	expectedOutputs.push_back(ExpectedOutput(18, "13"));
	expectedOutputs.push_back(ExpectedOutput(18, "21"));
	expectedOutputs.push_back(ExpectedOutput(18, "34"));
	expectedOutputs.push_back(ExpectedOutput(18, "55"));
	expectedOutputs.push_back(ExpectedOutput(18, "89"));
	expectedOutputs.push_back(ExpectedOutput(18, "144"));
	expectedOutputs.push_back(ExpectedOutput(18, "233"));
	expectedOutputs.push_back(ExpectedOutput(18, "377"));
	expectedOutputs.push_back(ExpectedOutput(18, "610"));
	expectedOutputs.push_back(ExpectedOutput(18, "987"));
	expectedOutputs.push_back(ExpectedOutput(18, "1597"));
	expectedOutputs.push_back(ExpectedOutput(18, "2584"));
	expectedOutputs.push_back(ExpectedOutput(18, "4181"));
	expectedOutputs.push_back(ExpectedOutput(18, "6765"));
	expectedOutputs.push_back(ExpectedOutput(20, "done"));

	return KodeTestRun(name, statements, expectedOutputs);
}