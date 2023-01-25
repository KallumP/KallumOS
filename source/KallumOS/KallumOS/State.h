#pragma once
#include "raylib.h"

#include "Control.h"
#include "Point.h"
#include "InputPress.h"

#include <vector>

enum class States { null, login, createAccount, desktop };


struct Credentials {

	Credentials(std::string _username, std::string _password) {
		username = _username;
		password = _password;
	}

	std::string username;
	std::string password;
};

class State {
protected:
	Color backgroundColor;

	std::vector<Control*> controls;

	Point* mousePosition;
	bool mouseClicked;
	Control* focused;
	States nextState;


public:

	State();
	~State();

	virtual void Tick(float elapsedTime) = 0;
	virtual void Draw() = 0;

	virtual	void Click() = 0;
	virtual void MouseMove() = 0;
	virtual void OnKeyPress(KeyPress* e) = 0;
	virtual void OnMousePress(MousePress* e) = 0;
	virtual void OnMouseHold(MousePress* e) {}
	virtual States GetNextState();

	void Focus(Control* toFocus, bool click);
	void NextFocus();

private:



};

