#pragma once
#include "../Process.h"

#include <string>
#include <vector>

class Asserter {

public:
	static std::string ValuesNotEqualMessage(std::string expected, std::string actual) {
		return "Expected: " + expected + " but recieved : " + actual;
	}
};

class TestResult {
public:
	TestResult(std::string _testName, std::string _testStep, std::string _message)
	{
		testName = _testName;
		testStep = _testStep;
		message = _message;
	}
	std::string testName;
	std::string testStep;
	std::string message;
};

struct ExpectedOutput {
	ExpectedOutput(int _statementLink, std::string _value)
	{
		statementLink = _statementLink;
		value = _value;
	}

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
	TestResult IntAdd();
	TestResult IntSub();
	TestResult IntMult();
	TestResult IntDiv();
	TestResult IntDiv0();
	TestResult IntCombinedTesting();


	TestResult KodeTestRun(std::string name, std::vector<std::string> statements, std::vector<ExpectedOutput> outputValues);

	std::vector<TestResult> testOutputs;
	std::string PassString = "Pass";
};

