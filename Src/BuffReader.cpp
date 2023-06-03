#include "BuffReader.h"

void BuffReader::change_buff(uint8_t* buff_start, uint8_t new_size)
{

	buff = buff_start;
	size = new_size;

}

uint8_t BuffReader::operator[](const int i)
{

	if (i < 0 || i >= size)
	{

		throw "IndexOutOfRangeError for buffer index.";

	}

	return buff[i];

}

std::string BuffReader::read_buff_value()
{

	std::string value;
	value.reserve(size);

	for (int i = 0; i < size; i++)
	{

		value += buff[i];

	}

	return value;

}