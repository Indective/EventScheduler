#include "schd.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    schd s;
    fs::path temp = fs::current_path().parent_path();
    std::string base_path = temp.string();

    if (argc > 1)
    {
        std::string mode = argv[1];
        if (mode == "interactive")
        {
            int command_code = -1;
            std::string command;
            while (true)
            {
                std::cout << "\nWelcome Back!" << std::endl;
                std::cout << "What would you like to do?" << std::endl;
                std::cout << "Commands: schd, check, show, dtls, exit" << std::endl;
                std::cout << "Enter command: ";
                std::getline(std::cin, command);

                if (command == "schd")          command_code = 1;
                else if (command == "check")      command_code = 2;
                else if (command == "show")       command_code = 3;
                else if (command == "dtls")       command_code = 4;
                else if (command == "exit")       command_code = 5;
                else                            command_code = -1;

                switch (command_code)
                {
                    case 1:
                        s.ScheduleEvent(base_path);
                        break;
                    case 2:
                    {
                        std::string eventname;
                        std::cout << "Enter the name of the event: ";
                        std::getline(std::cin, eventname);
                        s.notifyEvent(base_path, eventname);
                        break;
                    }
                    case 3:
                        s.showCurrentEvents(base_path);
                        break;
                    case 4:
                    {
                        std::string eventname;
                        std::cout << "Enter the name of the event: ";
                        std::getline(std::cin, eventname);
                        std::vector<std::string> event_details = s.getEventDetails(base_path, eventname);
                        std::cout << "Event details:" << std::endl;
                        for (const auto &detail : event_details)
                        {
                            std::cout << detail << std::endl;
                        }
                        break;
                    }
                    case 5:
                        return 0;
                    default:
                        std::cout << "Invalid command!" << std::endl;
                }
            }
        }
    }

    std::cout << "Running in background mode using fixed directory \"events\"... (Press Ctrl+C to exit)" << std::endl;
    while (true)
    {
        std::vector<std::string> events = s.getEvents(base_path);
        for (const auto &event : events)
        {
            if (s.checkEvent(base_path, event))
            {
                s.notifyEvent(base_path, event);
            }
        }
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
    
    return 0;
}