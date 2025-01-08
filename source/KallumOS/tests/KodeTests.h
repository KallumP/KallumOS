#pragma once
#include "../Process.h"

#include <string>
#include <vector>

class TestResult {
public:
	TestResult(std::string testName, std::string testStep, std::string message) :
		testName(testName), testStep(testStep), message(message) {}

	std::string testName;
	std::string testStep;
	std::string message;
};

struct ExpectedOutput {
	ExpectedOutput(int statementLink, std::string value) :
		statementLink(statementLink), value(value) {}

	int statementLink;
	std::string value;
};

class KodeTests : public Process {

public:
	KodeTests();
	KodeTests(Point _position, Point _size);

	void Draw(Point offset);
	void DrawTestOutputs(Point offset);

	void RunTests();
	TestResult KodeTestRun(std::string name, std::vector<std::string> statements, std::vector<ExpectedOutput> outputValues);

	TestResult Int_Add();
	TestResult Int_Sub();
	TestResult Int_Mult();
	TestResult Int_Div();
	TestResult Int_Div0();
	TestResult Int_CombinedTesting();

	TestResult Bool_Equals();
	TestResult Bool_NotEquals();
	TestResult Bool_More();
	TestResult Bool_MoreEqual();
	TestResult Bool_Less();
	TestResult Bool_LessEqual();
	TestResult Bool_IntMix();

	TestResult PureBool_Assign();
	TestResult PureBool_Equals();
	TestResult PureBool_Not();
	TestResult PureBool_And();
	TestResult PureBool_Or();
	TestResult PureBool_Combined();

	TestResult If_FalseCondition();
	TestResult If_TrueCondition();
	TestResult If_NoEnd();
	TestResult If_NoIf();

	TestResult NestedIf_BothTrue();
	TestResult NestedIf_OuterTrueInnerFalse();
	TestResult NestedIf_OuterFalseInnerTrue();
	TestResult NestedIf_BothFalse();
	TestResult NestedIf_NoEnds();
	TestResult NestedIf_OneEnd();

	TestResult MiscFibonacci();

	static std::string ValuesNotEqualMessage(std::string expected, std::string actual) { return "Expected: " + expected + " but recieved: " + actual; }
	const std::string PassString = "Pass";

	std::vector<TestResult> testOutputs;
	int fontSize;
};


//found bugs

//helper.h Intable() line 116
//intable boolean was being wrongly set to the converted int value casted to a bool
//which meant that any non-0 number returned true (seems like normal code flow)
//but any 0 value returned false (even though it could be converted to an int)
//caused by the intellisense asking me to save the return value of std::stoi (so i stupidly saved it into the bool)

//kode.cpp HandleOut()
//at the bottom of the function
//used to combine all chunks with a " " on the end (which wrongly added one onto the last chunk)
//This was not noticable until tests that checked the text out feature were failing

//kode.cpp ResolveBooleanOperation
//the < <= > >= operations were testing strings, which worked for small numbers
//solution was to make those functions convert to int first
//noticed when doing the fibonacci test, which used comparisons between biggers numbers