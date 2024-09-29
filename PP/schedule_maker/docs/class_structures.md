
+-------------------------------+
|           Task                 |
+-------------------------------+
| - description: std::string     |
| - duration: std::chrono::minutes|
| - status: Status               |
+-------------------------------+
| + getDescription(): std::string|
| + getDuration(): std::chrono::minutes|
| + getStatus(): Status          |
| + setStatus(newStatus: Status) |
| + toString(): std::string      |
+-------------------------------+


+--------------------------------+
|           Schedule             |
+--------------------------------+
| - tasks: std::vector<Task>     |
| - title: std::string           |
+--------------------------------+
| + addTask(task: Task)          |
| + removeTask(index: int)       |
| + getTasks(): std::vector<Task>|
| + getTask(index: int): Task    |
| + archiveSchedule()            |
| + displaySchedule()            |
+--------------------------------+

+--------------------------------+
|          DBManager             |
+--------------------------------+
| - dbFile: std::string          |
| - db: sqlite3*                 |
+--------------------------------+
| + saveTask(task: Task)         |
| + saveSchedule(schedule: Schedule)|
| + loadSchedule(scheduleId: int): Schedule |
| + getAllSchedules(): std::vector<Schedule>|
| + deleteSchedule(scheduleId: int)         |
+--------------------------------+

+--------------------------------+
|         AppManager             |
+--------------------------------+
| - dbManager: DBManager         |
| - activeSchedule: Schedule     |
+--------------------------------+
| + run()                        |
| + showMenu()                   |
| + handleInput()                |
+--------------------------------+

