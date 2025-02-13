# EventScheduler

## Overview
EventScheduler is a project designed to help users manage and schedule their events efficiently. This application allows users to create events and store them into files and get notifed on thier pc when the time for there event comes, ensuring they stay organized and never miss an important date.
Once the time of a notification comes, you will be notified on your machine through Burnttoast Notifications.

## Features
- **Create Events**: Users can create new events with specific details such as title, date, time, and description.
- **View Events**: Users can view a list of all their scheduled events.

## Project Structure
The project is organized into several key folders and files:

### `events/`
This folder contains all the event-related files and logic. Each event is represented by a file that includes details such as the event title, date, time.

note : this folder will be automatically created by the application when the program is first run, and will be created in the project's root directory

this is the event file structure : 

line 1 : event name.
line 2 : event date .
line 3 : event hour/time.

### `src/`
This folder contains the main source code for the application, including the core logic for managing events.

### `include/`
this folder includes schd.h which is a header file for the functions that manage the events.

### `README.md`
This file provides an overview of the project, its features, and its structure.

## Installation
To install and run the EventScheduler project, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/Indective/EventScheduler.git
    ```
2. Navigate to the project directory:
    ```sh
    cd EventScheduler
    ```
3. To start the application simply create a build folder and run cmake.

## Usage
The application has 2 modes : 

1 - interactive mode :
in this mode the user can manage the event logic without getting notified of the events.
To run the application in this mode, run the excutable and add "Interactive" as an argument.

2 - background mode :
in this mode the application runs in the background checking for events and notifying you of them. but you can not control the event logic. 
To run the application in this mode run the excutable with no arguments.

## Contributing
Contributions are welcome! If you would like to contribute to the project, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Make your changes and commit them.
4. Push your changes to your fork.
5. Submit a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

