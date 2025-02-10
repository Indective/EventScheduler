#include "schd.h"
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main()
{
    schd s;
    fs::path temp  = fs::current_path().parent_path();
    std::string dir_path = temp.string();
    std::string dir_name;
    while(true)
    {
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "1. Create a new events directory" << std::endl;
        std::cout << "2. Schedule an event" << std::endl;
        std::cout << "3. Check if an event is happening now" << std::endl;
        std::cout << "4. Exit" << std::endl;
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        switch(choice)
        {
            case 1:
                std::cout << "Enter the name of the directory: ";
                std::getline(std::cin, dir_name);
                s.createdir(dir_path, dir_name);
                break;
            case 2:
                std::cout << "Enter the name of the directory: ";
                std::getline(std::cin, dir_name);
                s.ScheduleEvent(dir_path, dir_name);
                break;
            case 3:
            {
                std::string eventname;
                std::cout << "Enter the name of the event: ";
                std::getline(std::cin, eventname);
                s.notifyEvent(dir_path, dir_name, eventname);
                break;
            }
            case 4:
                exit(0);
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
    return 0;
}