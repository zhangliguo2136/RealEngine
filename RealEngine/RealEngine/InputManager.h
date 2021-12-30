#pragma once
#include <vector>
#include "REKey.h"

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

	private:
		std::vector<int> m_keys;

	private:
		double m_currCursorX;
		double m_currCursorY;
	};
}