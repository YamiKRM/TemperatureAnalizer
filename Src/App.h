#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>

#include "Requests.h"

#include <Windows.h> //Must be included after Requests.h to avoid some linker errors.
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define SOUND_BUFFER_LENGTH 100

constexpr const char* config_path = "Config.ini";

#define DEFAULT_LOW_TEMPERATURE 99.f
#define DEFAULT_HIGH_TEMPERATURE -1.0f

namespace app
{

	struct ARGS
	{

		float temperature = 0.0f;
		float min_temperature = 0.0f;
		float max_temperature = 0.0f;

		float lowest_temperature = DEFAULT_LOW_TEMPERATURE;
		float highest_temperature = DEFAULT_HIGH_TEMPERATURE;

		float* plot_temperature = NULL;

		std::string sound_path = "";


		//char* lowest_t_date = NULL;
		//char* highest_t_date = NULL;

		bool app_finished = false;
		bool use_alarm = false;

		ARGS()
		{
			sound_path.reserve(100);
		}

	};

	ARGS load_config();

	void save_config(ARGS* args);

	void perform_requests(ARGS* args, BuffReader* reader);

	void loop(ARGS* args);

	void sound_alarm(ARGS* args);

}