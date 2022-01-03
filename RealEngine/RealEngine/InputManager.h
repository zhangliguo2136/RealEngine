#pragma once
#include <vector>
#include "REKey.h"

#include "math.h"

namespace RealEngine
{
	class InputManager
	{
	public:
		InputManager() {};
		~InputManager() {};

		static InputManager& getInstance()
		{
			static InputManager instance;
			return instance;
		}

		InputManager(const InputManager&) = delete;
		InputManager& operator = (const InputManager&) = delete;

	public:
		void InputKeyDown(int key);
		void InputKeyUp(int key);

		void InputCursor(double x, double y);
		void InputScroll(double x, double y);

		void InputCursorEnter(bool isEnter);

	public:
		Vector2d getCursorPosition();
		Vector2d getScrollPosition();

		bool isPressed(int key);
	private:
		std::vector<int> _keys;

		double _currCursorX;
		double _currCursorY;

		double _currScrollX = 0.0;
		double _currScrollY = 0.0;
	};
}