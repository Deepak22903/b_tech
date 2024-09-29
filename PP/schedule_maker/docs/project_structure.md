
/-- ScheduleMaker/
    |
    |-- src/                    # Source files
    |   |-- main.cpp             # Main entry point
    |   |-- Task.cpp             # Implementation of Task class
    |   |-- Schedule.cpp         # Implementation of Schedule class
    |   |-- DBManager.cpp        # Implementation of DBManager class
    |   |-- AppManager.cpp       # Optional, main application logic
    |
    |-- include/                 # Header files
    |   |-- Task.h               # Task class declaration
    |   |-- Schedule.h           # Schedule class declaration
    |   |-- DBManager.h          # DBManager class declaration
    |   |-- AppManager.h         # AppManager class declaration
    |
    |-- tests/                   # Unit tests
    |   |-- test_task.cpp        # Unit test for Task class
    |   |-- test_schedule.cpp    # Unit test for Schedule class
    |   |-- test_dbmanager.cpp   # Unit test for DBManager class
    |
    |-- lib/                     # External libraries (e.g., SQLite)
    |   |-- sqlite3/             # SQLite library source and headers
    |
    |-- build/                   # Build directory
    |   |-- Makefile             # Makefile for building the project
    |   |-- CMakeLists.txt       # CMake configuration file (optional)
    |
    |-- data/                    # Data directory for storing database files
    |   |-- schedules.db         # SQLite database file for storing schedules
    |
    |-- README.md                # Project documentation
    |-- LICENSE                  # License for the project
