# Developer Guide

This guide provides information for developers who want to understand, modify, or extend the Task Manager application.

## Development Environment Setup

### Required Tools
- **Compiler**: MinGW-w64 or Visual Studio with C++ support
- **IDE**: Dev-C++, Code::Blocks, Visual Studio, or any C++ IDE
- **Build System**: Make (optional, for using provided Makefile)

### Setting Up Dev-C++
1. Download and install Dev-C++ with MinGW-w64
2. Open the project file `project_dev.dev`
3. Configure compiler settings if needed
4. Build and run with F9

### Alternative Setup (Command Line)
```bash
# Compile directly
g++ -o project_dev.exe main.cpp -mwindows

# Or use the Makefile
make -f Makefile.win
```

## Code Architecture

### File Organization
```
main.h          # Header with declarations, constants, and Task struct
main.cpp        # Implementation of all functionality
Makefile.win    # Build configuration
project_dev.dev # IDE project file
```

### Design Patterns
- **Procedural Programming**: Functions handle specific operations
- **Global State**: Tasks stored in global vector for simplicity
- **Event-Driven**: UI responds to Windows messages
- **File I/O**: Simple CSV format for data persistence

### Key Design Decisions
1. **Single File Implementation**: All code in main.cpp for simplicity
2. **Global Variables**: Simplified state management
3. **CSV Storage**: Human-readable, simple format
4. **Win32 API**: Native Windows controls for performance

## Code Structure Analysis

### Initialization Flow
```
WinMain() 
├── RegisterClass()
├── CreateWindow()
└── Message Loop
    └── WndProc()
        ├── WM_CREATE
        │   ├── AddControls()
        │   └── LoadTasksFromCSV()
        └── WM_COMMAND (button clicks)
```

### Task Management Flow
```
User Action → Button Click → WM_COMMAND → Function Call → Update Data → Save CSV
```

### Data Flow
```
CSV File ↔ Global Vector ↔ UI Controls ↔ User Input
```

## Extending the Application

### Adding New Task Fields

1. **Update Task Structure** (main.h):
```cpp
struct Task {
    std::string name;
    std::string description;
    std::string priority;
    std::string status;
    std::string dueDate;  // New field
};
```

2. **Add UI Control** (AddControls function):
```cpp
// Add new control ID to main.h
#define ID_INPUT_DUE_DATE 109

// Add control creation in AddControls()
CreateWindow("STATIC", "Due Date:", WS_VISIBLE | WS_CHILD, 
    20, 140, 80, 20, hwnd, NULL, NULL, NULL);
hDueDate = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
    110, 140, 200, 20, hwnd, (HMENU)ID_INPUT_DUE_DATE, NULL, NULL);
```

3. **Update CSV Operations**:
- Modify SaveTaskToCSV() to include new field
- Update LoadTasksFromCSV() parsing logic
- Adjust RewriteCSV() format

4. **Update Task Operations**:
- Modify AddTask() to read new field
- Update EditTask() to populate new field
- Adjust form clearing logic

### Adding New Features

#### Search Functionality
1. Add search input control
2. Implement filter function for task vector
3. Update list display based on search criteria

#### Task Sorting
1. Add sort criteria dropdown
2. Implement comparison functions
3. Sort vector before displaying

#### Categories/Tags
1. Add category field to Task structure
2. Create category management UI
3. Update file format and operations

### Performance Considerations

#### Current Limitations
- **File I/O**: Rewrites entire CSV on each change
- **Memory**: Loads all tasks into memory
- **UI Updates**: Rebuilds entire list on changes

#### Optimization Strategies
1. **Incremental File Updates**: Append-only operations where possible
2. **Virtual List**: Load tasks on-demand for large datasets
3. **Caching**: Cache frequently accessed data
4. **Background Operations**: Move file I/O to separate thread

## Debugging and Testing

### Common Issues
1. **CSV Parsing**: Commas in task data break parsing
2. **Memory Leaks**: Ensure brush cleanup
3. **UI Responsiveness**: File operations block UI thread

### Debugging Techniques
```cpp
// Add debug output
#ifdef DEBUG
    OutputDebugString("Debug message\n");
#endif

// Use MessageBox for quick debugging
MessageBox(NULL, "Debug info", "Debug", MB_OK);
```

### Testing Strategies
1. **Manual Testing**: Test all UI operations
2. **Edge Cases**: Empty fields, special characters
3. **File Operations**: Test with missing/corrupted CSV
4. **Memory Testing**: Run with debug heap

## Code Quality Guidelines

### Naming Conventions
- **Functions**: PascalCase (AddTask, DeleteTask)
- **Variables**: camelCase (editIndex, hTaskList)
- **Constants**: UPPER_CASE (ID_BTN_ADD_TASK)
- **Global Variables**: Descriptive names with type prefix

### Error Handling Best Practices
```cpp
// Check return values
if (file.is_open()) {
    // Perform operation
    file.close();
} else {
    // Handle error
    MessageBox(hwnd, "Failed to open file", "Error", MB_OK);
}

// Validate user input
if (task.name.empty()) {
    MessageBox(hwnd, "Task name is required.", "Error", MB_OK);
    return;
}
```

### Memory Management
```cpp
// Always clean up resources
DeleteObject(hWhiteBrush);
DeleteObject(hYellowBrush);

// Use RAII where possible
std::ofstream file(CSV_FILE);
// File automatically closed when out of scope
```

## Security Considerations

### Input Validation
- Validate all user input before processing
- Sanitize data before writing to file
- Check file permissions before operations

### File Security
- Use secure file operations
- Validate file format before parsing
- Handle file access errors gracefully

## Migration and Compatibility

### Upgrading Data Format
1. Detect old format version
2. Convert data to new format
3. Backup original data
4. Update version identifier

### Cross-Platform Considerations
- Replace Win32 API calls with cross-platform alternatives
- Use portable file path handling
- Abstract UI layer for different platforms

## Build Configuration

### Compiler Flags
```makefile
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LDFLAGS = -mwindows -static-libgcc -static-libstdc++
```

### Debug vs Release
```makefile
# Debug build
CXXFLAGS += -g -DDEBUG

# Release build  
CXXFLAGS += -O2 -DNDEBUG
```

## Documentation Standards

### Code Comments
```cpp
/**
 * Adds a new task or updates existing task
 * @param hwnd Handle to main window for error dialogs
 * @note Sets editIndex to -1 after successful operation
 */
void AddTask(HWND hwnd);
```

### Function Documentation
- Purpose and behavior
- Parameter descriptions
- Return value information
- Side effects and state changes
- Error conditions
