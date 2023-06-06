#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>

#include "Requests.h"

#include <Windows.h> //Must be included after Requests.h to avoid some linker errors.
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define SOUND_BUFFER_LENGTH 100

constexpr const char* config_path = "Config.ini";

namespace app
{

	struct ARGS
	{

		float temperature = 0.0f;
		float min_temperature = 0.0f;
		float max_temperature = 0.0f;

		std::string sound_path = "";

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