#include "schd.h"
#include <iostream>

struct{
    std::string event_name;
    std::string event_date;
    std::string event_time;
    std::string event_location;
    std::string event_description;
}event;

void schd::prin()
{
    std::cout << "Enter event name: ";
    std::getline(std::cin, event.event_name);
    std::cout << "Enter event date: ";
    std::getline(std::cin, event.event_date);
    std::cout << "Enter event time: ";
    std::getline(std::cin, event.event_time);
    std::cout << "Enter event location: ";
    std::getline(std::cin, event.event_location);
    std::cout << "Enter event description: ";
    std::getline(std::cin, event.event_description);
    std::cout << "Event name: " << event.event_name << std::endl;
    std::cout << "Event date: " << event.event_date << std::endl;
    std::cout << "Event time: " << event.event_time << std::endl;
    std::cout << "Event location: " << event.event_location << std::endl;
    std::cout << "Event description: " << event.event_description << std::endl;
}
