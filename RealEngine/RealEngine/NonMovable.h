#pragma once

struct NonMovable 
{
	NonMovable(NonMovable &&) = delete;
	NonMovable &operator = (NonMovable &&) = delete;

	NonMovable() = default;
};