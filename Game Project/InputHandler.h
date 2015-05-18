#pragma once
#include <SDL.h>
#include <vector>
#include "Vector2D.h"
enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};
class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	//start joysticks
	void initialiseJoysticks();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }

	//update stuff
	void update();
	void clean();
	void reset();

	//keyboard events
	bool isKeyDown(SDL_Scancode key);

	//joystick events
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);
	bool getButtonState(int joy, int buttonNumber);

	//mouse events
	bool getMouseButtonState(int buttonNumber);
	Vector2D* getMousePosition();




private:

	//mouse
	Vector2D* m_mousePosition;
	std::vector<bool> m_mouseButtonStates;

	//joystick
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	std::vector<SDL_Joystick*> m_joysticks;
	bool m_bJoysticksInitialised;
	const int m_joystickDeadZone = 10000;

	//keyboard
	const Uint8* m_keystates;

	~InputHandler() {}
	InputHandler();


	// handle keyboard events
	void onKeyDown();
	void onKeyUp();

	// mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	// handle joysticks events
	//void onJoystickAxisMove(SDL_Event& event);
	//void onJoystickButtonDown(SDL_Event& event);
	//void onJoystickButtonUp(SDL_Event& event);

	//singleton
	static InputHandler* s_pInstance;

};
typedef InputHandler TheInputHandler;
