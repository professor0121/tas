# Task Manager Application

A Windows desktop application for managing tasks with a graphical user interface built using C++ and the Win32 API.

## Overview

This Task Manager application allows users to create, edit, delete, and organize tasks with different priorities and statuses. All tasks are automatically saved to a CSV file for persistence between application sessions.

## Features

- **Add Tasks**: Create new tasks with name, description, priority, and status
- **Edit Tasks**: Modify existing tasks by selecting them from the list
- **Delete Tasks**: Remove tasks from the list
- **Persistent Storage**: Tasks are automatically saved to and loaded from a CSV file
- **Priority Levels**: Three priority levels (Low, Medium, High)
- **Status Tracking**: Three status options (Pending, In Progress, Completed)
- **Visual Feedback**: Color-coded interface with blue labels and yellow input fields

## System Requirements

- Windows operating system
- MinGW-w64 compiler (or compatible C++ compiler with Windows API support)
- Dev-C++ IDE (optional, for project file support)

## Project Structure

```
project_dev/
├── main.cpp           # Main application source code
├── main.h             # Header file with declarations and constants
├── Makefile.win       # Build configuration for MinGW
├── project_dev.dev    # Dev-C++ project file
├── project_dev.exe    # Compiled executable (generated)
├── tasks.csv          # Task data storage (generated)
└── README.md          # This documentation file
```

## Building the Application

### Using Dev-C++
1. Open `project_dev.dev` in Dev-C++
2. Press F9 or go to Execute → Compile & Run

### Using Command Line (MinGW)
```bash
g++ -o project_dev.exe main.cpp -mwindows
```

### Using the Provided Makefile
```bash
make -f Makefile.win
```

## Usage

1. **Starting the Application**
   - Run `project_dev.exe`
   - The application window will open with the task management interface

2. **Adding a Task**
   - Fill in the "Task Name" field (required)
   - Add a description (optional)
   - Select a priority level from the dropdown
   - Choose a status from the dropdown
   - Click "Add Task"

3. **Editing a Task**
   - Select a task from the list
   - Click "Edit Task"
   - The form fields will populate with the task's current information
   - Modify the fields as needed
   - Click "Add Task" to save changes

4. **Deleting a Task**
   - Select a task from the list
   - Click "Delete Task"
   - The task will be removed from both the list and the CSV file

## Data Storage

Tasks are stored in `tasks.csv` with the following format:
```
TaskName,Description,Priority,Status
```

The CSV file is automatically:
- Created when the first task is added
- Updated whenever tasks are added, edited, or deleted
- Loaded when the application starts

## User Interface

The application window contains:
- **Input Fields**: Task name, description, priority dropdown, status dropdown
- **Buttons**: Add Task, Edit Task, Delete Task
- **Task List**: Displays all tasks in format "Name | Priority | Status"
- **Color Scheme**: Blue text on white background for labels, dark green text on yellow background for input fields

## Technical Details

### Key Components

- **Task Structure**: Defined in `main.h`, contains name, description, priority, and status
- **CSV Operations**: Functions for saving individual tasks and rewriting the entire file
- **Window Procedure**: Handles all Windows messages and user interactions
- **Control Management**: Creates and manages all UI elements

### Important Functions

- `SaveTaskToCSV()`: Appends a single task to the CSV file
- `RewriteCSV()`: Overwrites the entire CSV file with current task list
- `LoadTasksFromCSV()`: Reads tasks from CSV file on application startup
- `AddTask()`: Handles adding new tasks or updating existing ones
- `EditTask()`: Populates form fields with selected task data
- `DeleteTask()`: Removes selected task from list and file

## Error Handling

- **Empty Task Name**: Shows error message if task name is not provided
- **No Selection**: Shows error message when trying to edit/delete without selecting a task
- **File Operations**: Basic file handling for CSV read/write operations

## Limitations

- Single-user application (no multi-user support)
- No task sorting or filtering options
- No due dates or reminders
- Basic CSV format (no escaping for commas in task data)
- Windows-only compatibility

## Future Enhancements

Potential improvements could include:
- Due date functionality
- Task categories or tags
- Search and filter capabilities
- Export to other formats
- Task completion timestamps
- Better CSV handling with proper escaping
- Cross-platform compatibility

## License

This project is provided as-is for educational and personal use.
#   t a s  
 