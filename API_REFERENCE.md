# API Reference

This document provides detailed information about the functions, structures, and constants used in the Task Manager application.

## Data Structures

### Task Structure
```cpp
struct Task {
    std::string name;        // Task name (required)
    std::string description; // Task description (optional)
    std::string priority;    // Priority level: "Low", "Medium", "High"
    std::string status;      // Status: "Pending", "In Progress", "Completed"
};
```

## Global Variables

### Task Management
- `std::vector<Task> tasks` - Vector containing all tasks
- `int editIndex` - Index of task being edited (-1 if adding new task)

### UI Controls
- `HWND hName` - Handle to task name input field
- `HWND hDesc` - Handle to description input field  
- `HWND hPriority` - Handle to priority dropdown
- `HWND hStatus` - Handle to status dropdown
- `HWND hTaskList` - Handle to task list box

### File Management
- `const char* CSV_FILE` - Path to CSV file ("tasks.csv")

### UI Styling
- `HBRUSH hWhiteBrush` - White brush for label backgrounds
- `HBRUSH hYellowBrush` - Yellow brush for input field backgrounds

## Control IDs

```cpp
#define ID_INPUT_NAME       101  // Task name input field
#define ID_INPUT_DESC       102  // Description input field
#define ID_INPUT_PRIORITY   103  // Priority dropdown
#define ID_INPUT_STATUS     104  // Status dropdown
#define ID_BTN_ADD_TASK     105  // Add/Update task button
#define ID_LIST_TASKS       106  // Task list box
#define ID_BTN_DELETE_TASK  107  // Delete task button
#define ID_BTN_EDIT_TASK    108  // Edit task button
```

## Core Functions

### File Operations

#### `void SaveTaskToCSV(const Task& task)`
Appends a single task to the CSV file.

**Parameters:**
- `task` - Task structure to save

**Behavior:**
- Opens CSV file in append mode
- Writes task data in CSV format: `name,description,priority,status`
- Automatically closes file

#### `void RewriteCSV()`
Overwrites the entire CSV file with current task vector.

**Behavior:**
- Opens CSV file in truncate mode
- Writes all tasks from the global `tasks` vector
- Used after edit/delete operations to maintain file consistency

#### `void LoadTasksFromCSV(HWND hwnd)`
Loads tasks from CSV file into memory and populates the UI list.

**Parameters:**
- `hwnd` - Handle to main window

**Behavior:**
- Reads CSV file line by line
- Parses each line into Task structure
- Adds tasks to global vector and UI list
- Displays tasks in format: "Name | Priority | Status"

### UI Management

#### `void AddControls(HWND hwnd)`
Creates all UI controls and adds them to the main window.

**Parameters:**
- `hwnd` - Handle to main window

**Controls Created:**
- Static labels for each input field
- Edit controls for name and description
- Combo boxes for priority and status with predefined options
- Buttons for Add, Edit, and Delete operations
- List box for displaying tasks

#### `std::string GetWindowTextStr(HWND hWnd)`
Utility function to get text from a window control as std::string.

**Parameters:**
- `hWnd` - Handle to window control

**Returns:**
- String containing the window text (max 256 characters)

### Task Operations

#### `void AddTask(HWND hwnd)`
Adds a new task or updates an existing task.

**Parameters:**
- `hwnd` - Handle to main window

**Behavior:**
- Validates that task name is not empty
- Creates Task structure from form inputs
- If `editIndex >= 0`: updates existing task
- If `editIndex < 0`: adds new task
- Updates CSV file and clears form fields

#### `void EditTask(HWND hwnd)`
Prepares a task for editing by populating form fields.

**Parameters:**
- `hwnd` - Handle to main window

**Behavior:**
- Gets selected task from list
- Populates all form fields with task data
- Sets `editIndex` to selected task index
- Shows error if no task is selected

#### `void DeleteTask(HWND hwnd)`
Removes the selected task from list and file.

**Parameters:**
- `hwnd` - Handle to main window

**Behavior:**
- Gets selected task index
- Removes task from vector and UI list
- Updates CSV file
- Shows error if no task is selected

## Window Procedure

### `LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)`
Main window message handler.

**Messages Handled:**

#### `WM_CREATE`
- Calls `AddControls()` to create UI
- Calls `LoadTasksFromCSV()` to load existing tasks

#### `WM_COMMAND`
Handles button clicks:
- `ID_BTN_ADD_TASK`: Calls `AddTask()`
- `ID_BTN_DELETE_TASK`: Calls `DeleteTask()`
- `ID_BTN_EDIT_TASK`: Calls `EditTask()`

#### `WM_CTLCOLORSTATIC`
Sets color scheme for static labels:
- Text: Blue (RGB(0, 0, 255))
- Background: White (RGB(255, 255, 255))

#### `WM_CTLCOLOREDIT`
Sets color scheme for edit controls:
- Text: Dark green (RGB(0, 100, 0))
- Background: Light yellow (RGB(255, 255, 100))

#### `WM_DESTROY`
- Posts quit message to exit application
- Cleans up brush resources

## Application Entry Point

### `int WINAPI WinMain(...)`
Windows application entry point.

**Behavior:**
- Registers window class with custom procedure
- Creates main window (480x400 pixels)
- Enters message loop
- Cleans up resources on exit

## Error Handling

### Validation
- Task name is required (shows error dialog if empty)
- Selection required for edit/delete operations

### File Operations
- Basic file handling with automatic close
- No explicit error handling for file I/O failures

## Memory Management

- Automatic cleanup of brush objects on application exit
- Standard C++ containers handle memory automatically
- No manual memory allocation/deallocation required
