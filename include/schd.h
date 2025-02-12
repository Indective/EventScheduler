// schd.h
#ifndef POWERSHELL_H
#define POWERSHELL_H

#include <vector>
#include <string>

class schd
{
private:
    // Fixed directory name for all operations
    const std::string fixed_dir = "Events";
public:
    // The functions now only require the base path (e.g. the parent directory) and event name when needed.
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
};

#endif
