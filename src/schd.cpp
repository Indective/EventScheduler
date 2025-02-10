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

struct{
    std::string name;
    std::string date;
    std::string time;
    std::string location;
    std::string description;
}event;
    

bool schd::checkdir(const std::string dir_path, const std::string dir_name)
{
    try {
        for (auto const& dir_entry : fs::directory_iterator{dir_path})
        {
            if (dir_entry.path().filename() == dir_name)
            {
                return true;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cout <<  e.what() << "\n";
    }
    return false;
}

void schd::createdir(const std::string dir_path, const std::string dir_name)
{
    try {
        if (!checkdir(dir_path, dir_name))
        {
            std::string new_path = dir_path + "/" + dir_name;
            fs::create_directory(new_path);
            fs::current_path(new_path);
            std::cout << "Directory created: " << fs::current_path().string() << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cout <<  e.what() << "\n";
    }
}

bool schd::checkEvent(const std::string dir_path, const std::string dir_name, const std::string event_name)
{
    std::string current_time = getCurrentTime();
    std::string current_date = getCurrentDate();
    std::string event_path = dir_path + "/" + dir_name + "/" + event_name + ".txt";
    std::ifstream file(event_path);
    bool is_date = false;
    bool is_time = false;

    std::string line = "";
    int current_line = 0;
    while (std::getline(file, line)) {
        if (++current_line == 3) {
            if (line == current_time) {
                is_time = true;
            }
        }
        if(std::getline(file,line))
        {
            if (++current_line == 2) {
                if (line == current_date) {
                    is_date = true;
                }
            }
        }
    }       
    if (is_date && is_time) {
        return true;
    }
    return false;
}

std::string schd::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::tm tm = *std::localtime(&time);  // Convert to local time
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M");  // Format as hours and minutes (HH:MM)
    std::cout << oss.str() << std::endl;
    
    return oss.str();
}

void schd::notifyEvent(const std::string dir_path, const std::string dir_name, const std::string event_name)
{
    if (checkEvent(dir_path, dir_name, event_name))
    {
        std::vector<std::string> event_details = getEventDetails(dir_path, dir_name, event_name);
        std::cout << "Event is happening now!" << std::endl;
        std::cout << "Event details: " << std::endl;
        for (auto i : event_details) {
            std::cout << i << std::endl;
        }
    }
    else
    {
        std::cout << "Event is not happening now!" << std::endl;
    }
}

std::vector<std::string> schd::getEventDetails(const std::string dir_path, const std::string dir_name, const std::string event_name)
{
    std::string event_path = dir_path + "/" + dir_name + "/" + event_name;
    std::ifstream file(event_path);
    std::string line = "";
    std::vector<std::string> event_details;
    int current_line = 0;
    while (std::getline(file, line)) {
        if (current_line == 0) {
            event.name = line;
            event_details.push_back(event.name);
        }
        else if (current_line == 1) {
            event.date = line;
            event_details.push_back(event.date);
        }
        else if (current_line == 2) {
            event.time = line;
            event_details.push_back(event.time);
        }
        else if (current_line == 3) {
            event.location = line;
            event_details.push_back(event.location);
        }
        else if (current_line == 4) {
            event.description = line;
            event_details.push_back(event.description);
        }
        current_line++;
    }
    for (auto i : event_details) {
        std::cout << i << std::endl;
    }
    return event_details;
}

std::string schd::getCurrentDate()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    
    std::tm tm = *std::localtime(&time);  // Convert to local time
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d/%m/%Y");  // Format as day/month/year (d/m/y)
    std::cout << oss.str() << std::endl;
    return oss.str();
}

void schd::ScheduleEvent(const std::string dir_path, const std::string dir_name)
{   
    std::string new_path = dir_path + "/" + dir_name;
    fs::current_path(new_path);
    std::cout << fs::current_path().string() << std::endl;
    std::cout << "Enter event name: ";
    std::getline(std::cin, event.name);
    std::cout << "Enter event date: ";
    std::getline(std::cin, event.date);
    std::cout << "Enter event time (HH:M) : ";
    std::getline(std::cin, event.time);

    std::string text;
    std::ofstream outfile(event.name + ".txt");
    outfile << event.name << std::endl;
    outfile << event.date << std::endl;
    outfile << event.time << std::endl;
    outfile << event.location << std::endl;
    outfile.close();
}
