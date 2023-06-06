#include "App.h"

app::ARGS app::load_config()
{

    std::ifstream config_file(config_path);

    //Check if config file exists
    if (!config_file.good())
    {
        
        ARGS default_args = ARGS();

        save_config(&default_args);

        return default_args;

    }

    ARGS app_args = ARGS();

    std::string line;

    uint8_t ln_num = 0;

    while (std::getline(config_file, line))
    {

        switch (ln_num)
        {
        
        case 0:
            app_args.use_alarm = std::stoi(line);
            break;

        case 1:
            app_args.max_temperature = std::stof(line);
            break;

        case 2:
            app_args.min_temperature = std::stof(line);
            break;

        case 3:
            app_args.sound_path = line;
            break;

        }

        ln_num += 1;

    }

    config_file.close();

    return app_args;

}

void app::save_config(ARGS* args)
{

    std::ofstream config_file(config_path);

    //The insertion operation formats the input, while the .write() method
    //writes the input as it is into the stream

    config_file << args->use_alarm << "\n";
    config_file << args->max_temperature << "\n";
    config_file << args->min_temperature << "\n";
    config_file << args->sound_path;

    config_file.close();
    
}

void app::sound_alarm(ARGS* args)
{
    PlaySound(std::wstring(args->sound_path.begin(), args->sound_path.end()).c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void app::perform_requests(ARGS* args, BuffReader* reader)
{

    HEADERS token_header{ {"x-ubidots-apikey" , API_KEY} };
    HEADERS temperature_header{ {"x-auth-token" , "" } };

    try
    {

        //Request the token
        temperature_header[0].second = requests::request_token(reader);

        auto response = requests::get_request(TEMPERATURE_REQUEST, temperature_header);

        requests::get_response_value(response, reader);

        args->temperature = std::stof(reader->read_buff_value());

    }
    catch (std::exception& e)
    {

        std::cerr << "Request failed, error: " << e.what() << '\n';

    }

}

void app::loop(ARGS* args)
{

    using namespace std::literals::chrono_literals;

    if (args == NULL)
    {
        throw "Invalid argument value";
    }

    BuffReader reader(NULL, 0);

    while (!args->app_finished)
    {

        std::this_thread::sleep_for(3s);

        perform_requests(args, &reader);

        //Perform the temperature checks

        if (args->max_temperature != 0 && args->temperature > args->max_temperature)
        {

            app::sound_alarm(args);
            continue;

        }

        if (args->min_temperature != 0 && args->temperature < args->min_temperature)
        {
            app::sound_alarm(args);
            continue;

        }

    }

}