#ifndef POWERSHELL_H
#define POWERSHELL_H

#include <vector>
#include <string>

class schd
{
private:
    const std::string fixed_dir = "Events";
public:
    void ScheduleEvent(const std::string& base_path);
    bool checkdir(const std::string& base_path);
    void createdir(const std::string& base_path);
    bool checkEvent(const std::string& base_path, const std::string& event_name);
    std::string getCurrentTime();
    void notifyEvent(const std::string& base_path, const std::string& event_name);
    std::vector<std::string> getEventDetails(const std::string& base_path, const std::string& event_name);
    std::string getCurrentDate();
    std::vector<std::string> getEvents(const std::string& base_path);
    void showCurrentEvents(const std::string& base_path);
    void deleteEvent(const std::string& base_path, const std::string& event_name);
};

#endif
