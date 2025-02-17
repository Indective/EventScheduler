#include "schd.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

bool schd::checkdir(const std::string& base_path)
{
    std::string full_path = base_path + "/" + fixed_dir;
    try {
        for (auto const& dir_entry : fs::directory_iterator{base_path})
        {
            if (dir_entry.path().filename() == fixed_dir)
            {
                return true;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << e.what() << "\n";
    }
    return false;
}

void schd::createdir(const std::string& base_path)
{
    try {
        if (!checkdir(base_path))
        {
            std::string new_path = base_path + "/" + fixed_dir;
            fs::create_directory(new_path);
            fs::current_path(new_path);
            std::cout << "Directory created: " << fs::current_path().string() << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << e.what() << "\n";
    }
}

void schd::ScheduleEvent(const std::string& base_path)
{   
    try {
        createdir(base_path);
        std::string new_path = base_path + "/" + fixed_dir;
        fs::current_path(new_path);
        
        std::string eventName, eventDate, eventTime;
        std::cout << "Enter event name: ";
        std::getline(std::cin, eventName);
        std::cout << "Enter event date: ";
        std::getline(std::cin, eventDate);
        std::cout << "Enter event time (HH:MM): ";
        std::getline(std::cin, eventTime);
    
        std::ofstream outfile(eventName);
        outfile << eventName << std::endl;
        outfile << eventDate << std::endl;
        outfile << eventTime << std::endl;
        outfile.close();
        std::cout << "Event scheduled!" << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cout << e.what() << "\n";
    }
}

std::string schd::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M");
    return oss.str();
}

std::string schd::getCurrentDate()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");
    return oss.str();
}

bool schd::checkEvent(const std::string& base_path, const std::string& event_name)
{
    try {
        std::string current_time = getCurrentTime();
        std::string current_date = getCurrentDate();
        std::string new_path = base_path + "/" + fixed_dir;
        fs::current_path(new_path);
        std::ifstream file(event_name);
        bool is_date = false;
        bool is_time = false;
    
        std::string line = "";
        int current_line = 0;
        while (current_line < 4 && std::getline(file, line)) {
            if (current_line == 2) { 
                if (line == current_time) {
                    is_time = true;
                }
            } 
            if (current_line == 1) {
                if (line == current_date) {
                    is_date = true;
                }
            }
            current_line++;
        }       
        return is_date && is_time;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

void schd::notifyEvent(const std::string& base_path, const std::string& event_name) 
{
    fs::current_path(base_path);
    std::string image_path = base_path + "/" + "NotifImage.jpg";
    if (checkEvent(base_path, event_name))
    {
        fs::current_path(base_path);
        std::vector<std::string> event_details = getEventDetails(base_path, event_name);

        std::string command = "powershell -Command \"& { New-BurntToastNotification -Text \\\"Event Reminder\\\", \\\"" + event_details[0] + "\\\" -AppLogo \\\"" + image_path + "\\\" }\"";
        system(command.c_str());
    }
    else
    {
        std::cout << std::endl << "Event is not happening now!" << std::endl;
    }
}

std::vector<std::string> schd::getEventDetails(const std::string& base_path, const std::string& event_name)
{
    std::string event_path = base_path + "/" + fixed_dir + "/" + event_name;
    std::ifstream file(event_path);
    std::string line = "";
    std::vector<std::string> event_details;
    int current_line = 0;
    while (std::getline(file, line)) {
        event_details.push_back(line);
        current_line++;
    }
    return event_details;
}

std::vector<std::string> schd::getEvents(const std::string& base_path)
{   
    std::vector<std::string> event_names;
    try{
        std::string new_path = base_path + "/" + fixed_dir;
        for (auto const& dir_entry : fs::directory_iterator{new_path})
        {
            std::string event_name = dir_entry.path().filename().string();
            std::vector<std::string> details = getEventDetails(base_path, event_name);
            if (!details.empty())
                event_names.push_back(details[0]);
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "Error in getEvents: " << e.what() << "\n";
    }
    return event_names;
}

void schd::showCurrentEvents(const std::string& base_path)
{
    try {
        std::vector<std::string> events = getEvents(base_path);
        std::cout << "Current events:" << std::endl;
        for (const auto& event : events) {
            std::cout << event << std::endl;
        } 
    } catch (const fs::filesystem_error& e) {
        std::cout << e.what() << "\n";
    }  
}

void schd::deleteEvent(const std::string &base_path, const std::string &event_name)
{
    try{
        std::string new_path = base_path + "/" + fixed_dir;
        fs::current_path(new_path);
        fs::remove(event_name);
        std::cout << "Event deleted!" << std::endl;
    }catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
