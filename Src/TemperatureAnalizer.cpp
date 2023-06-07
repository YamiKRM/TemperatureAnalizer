#include "App.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"

#include "GLFW/glfw3.h"

#define WIDTH 800
#define HEIGHT 600

#define YELLOW ImVec4(1, 1, 0, 1)

int main()
{

    app::ARGS args = app::load_config();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "Medidor de temperatura", nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 
    glfwSwapInterval(1); //Enable vsync.

    //Setup ImGui Context.
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    //Setup Platform/Renderer backends.
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool show_temperature = true;
    bool show_analysis = false;
    bool show_config = false;

    float tmp_array[100];
    
    for (uint8_t i = 0; i < 100; i++)
        tmp_array[i] = 0;

    args.plot_temperature = tmp_array;

    //Start requesting the temperature continously on another thread.

    std::thread temperature_thread(app::loop, &args);

    while(!glfwWindowShouldClose(window))
    {


        glfwPollEvents();

        //Start ImGui Frame.
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Shows the main menu bar below the window name
        if (ImGui::BeginMainMenuBar())
        {

            if (ImGui::BeginMenu("Archivo"))
            {

                if (ImGui::MenuItem("Salir"))
                    break;

                ImGui::EndMenu();

            }

            if (ImGui::BeginMenu("Vista"))
            {

                if (ImGui::MenuItem("Medidor"))
                    show_temperature = true;

                if (ImGui::MenuItem("Analisis"))
                    show_analysis = true;

                ImGui::EndMenu();

            }

            if (ImGui::BeginMenu("Opciones"))
            {

                if (ImGui::MenuItem("Configuracion"))
                    show_config = true;

                ImGui::EndMenu();

            }

            ImGui::EndMainMenuBar();

        }

        if (show_temperature)
        {

            ImGui::Begin("Medidor de temperatura", &show_temperature, ImGuiWindowFlags_NoResize);

            ImGui::TextColored(YELLOW, ("Temperatura actual: " + std::to_string(args.temperature) + " C").c_str());

            ImGui::End();

        }

        if (show_config)
        {

            ImGui::Begin("Configuracion", &show_config);

            ImGui::Checkbox("Reproducir un sonido de alarma cuando la temperatura este por fuera de un intervalo.", &args.use_alarm);

            if (args.use_alarm)
            {

                ImGui::BeginChild("Alarma", ImVec2(500, 165), true, ImGuiWindowFlags_NoResize);

                ImGui::Text("El sonido debe de estar en formato .wav");
                ImGui::InputText("Ruta del sonido.", &args.sound_path);

                ImGui::Text("Se puede dejar en 0 para no considerarla.");
                ImGui::InputFloat("Temperatura alta.", &args.max_temperature);

                ImGui::Text("Se puede dejar en 0 para no considerarla");
                ImGui::InputFloat("Temperatura baja.", &args.min_temperature);


                if (args.max_temperature < 0 || args.min_temperature < 0)
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "Los valores de temperatura deben ser positivos!");


                else if (args.max_temperature < args.min_temperature)
                    ImGui::TextColored(ImVec4(1, 0, 0, 1), "La temperatura alta debe ser mayor que la temperatura baja!");


                if (ImGui::Button("Reproducir sonido", ImVec2(200, 30)))
                    app::sound_alarm(&args);


                ImGui::EndChild();

            }

            ImGui::End();

        }

        if (show_analysis)
        {

            ImGui::Begin("Analisis de temperatura", &show_analysis, ImGuiWindowFlags_NoResize);
            
            ImGui::Text("Los siguientes datos son con respecto a la sesion actual.");

            if (args.lowest_temperature == DEFAULT_LOW_TEMPERATURE)
                ImGui::TextColored(YELLOW, "Temperatura mas baja: 0");

            else
                ImGui::TextColored(YELLOW, ("Temperatura mas baja: " + std::to_string(args.lowest_temperature)).c_str());

            
            if (args.highest_temperature == DEFAULT_HIGH_TEMPERATURE)
                ImGui::TextColored(YELLOW, "Temperatura mas alta: 0");

            else
                ImGui::TextColored(YELLOW, ("Temperatura mas alta: " + std::to_string(args.highest_temperature)).c_str());

            ImGui::PlotLines("Temperatura", tmp_array, 100, 0, NULL, FLT_MIN, FLT_MAX, ImVec2(200, 50));

            ImGui::End();

        }

        // Rendering.
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }
    
    args.app_finished = true;

    temperature_thread.join();

    app::save_config(&args);

    // Cleanup.
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
