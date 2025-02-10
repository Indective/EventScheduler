#include<iostream>
#include <vector>
#include <string>

#ifndef POWERSHELL_H
#define POWERSHELL_H

class schd
{
public:
    void ScheduleEvent(const std::string dir_path, const std::string dir_name);
    bool checkdir(const std::string dir_path, const std::string dir_name);
    void createdir(const std::string dir_path, const std::string dir_name);
    bool checkEvent(const std::string dir_path, const std::string dir_name, const std::string event_name);
    std::string getCurrentTime();
    void notifyEvent(const std::string dir_path, const std::string dir_name, const std::string event_name);
    std::vector<std::string> getEventDetails(const std::string dir_path, const std::string dir_name, const std::string event_name);
    std::string getCurrentDate();
};


#endif