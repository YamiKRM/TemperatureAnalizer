#pragma once

#include <iostream>
#include <string>

class BuffReader
{

public:

	BuffReader(uint8_t* buff_start, uint8_t buff_size) : size(buff_size), buff(buff_start)
	{


	}

	void change_buff(uint8_t* buff_start, uint8_t new_size);

	uint8_t operator [](const int i);

	std::string read_buff_value();

private:

	uint8_t size = 0;

	uint8_t* buff;

};