#pragma once
class TimeController
{
public:
	TimeController();
	virtual ~TimeController();
	TimeController(const TimeController&) = delete;
	TimeController& operator=(const TimeController&) = delete;
};

