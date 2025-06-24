# Changelog

All notable changes to the Task Manager application will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Planned Features
- Due date functionality for tasks
- Task categories and tags
- Search and filter capabilities
- Export functionality (JSON, XML)
- Task completion timestamps
- Improved CSV handling with proper escaping
- Cross-platform compatibility (Linux, macOS)
- Dark mode theme option
- Task priority sorting
- Backup and restore functionality

### Known Issues
- CSV parsing fails if task data contains commas
- No validation for special characters in task names
- File operations may fail silently in some cases
- Application window is not resizable
- No keyboard shortcuts for common operations

## [1.0.0] - Current Version

### Added
- **Core Task Management**
  - Create new tasks with name, description, priority, and status
  - Edit existing tasks by selecting from list
  - Delete tasks with confirmation
  - Persistent storage using CSV format

- **User Interface**
  - Windows native GUI using Win32 API
  - Form-based task input with validation
  - List display showing task summary (Name | Priority | Status)
  - Color-coded interface (blue labels, yellow input fields)
  - Three priority levels: Low, Medium, High
  - Three status options: Pending, In Progress, Completed

- **Data Management**
  - Automatic CSV file creation and management
  - Load tasks on application startup
  - Save changes immediately after each operation
  - Simple CSV format: `name,description,priority,status`

- **Build System**
  - Dev-C++ project file for easy compilation
  - Makefile for command-line building
  - MinGW-w64 compatibility

### Technical Implementation
- **Language**: C++ with Win32 API
- **Architecture**: Single-file procedural design
- **Storage**: CSV file format
- **UI Framework**: Native Windows controls
- **Memory Management**: STL containers with automatic cleanup

### File Structure
```
project_dev/
├── main.cpp           # Main application source
├── main.h             # Header with declarations
├── Makefile.win       # Build configuration
├── project_dev.dev    # Dev-C++ project file
├── project_dev.exe    # Compiled executable
└── tasks.csv          # Task data storage
```

### Dependencies
- Windows operating system
- MinGW-w64 compiler or compatible
- Standard C++ library
- Windows API libraries

### Limitations
- Windows-only compatibility
- Single-user application
- No multi-threading support
- Basic error handling
- Limited input validation
- No undo/redo functionality
- Fixed window size
- No configuration options

## Development History

### Initial Development
The Task Manager application was developed as a desktop productivity tool using C++ and the Win32 API. The focus was on creating a simple, functional task management system with persistent storage.

### Design Decisions
1. **Win32 API Choice**: Selected for native Windows integration and performance
2. **CSV Storage**: Chosen for simplicity and human readability
3. **Single File Design**: Kept simple for educational purposes and easy maintenance
4. **Procedural Approach**: Used for straightforward implementation and debugging

### Architecture Evolution
The application follows a traditional Windows desktop application pattern:
- Message-driven event handling
- Global state management
- Direct file I/O operations
- Immediate persistence model

## Version History Notes

### Version Numbering
- **Major Version**: Significant feature additions or breaking changes
- **Minor Version**: New features that maintain backward compatibility
- **Patch Version**: Bug fixes and minor improvements

### Backward Compatibility
- CSV file format is stable and backward compatible
- Configuration and data files maintain compatibility across versions
- API changes will be documented with migration guides

## Future Roadmap

### Short Term (Next Release)
- [ ] Input validation improvements
- [ ] Better error handling and user feedback
- [ ] CSV escaping for special characters
- [ ] Window resizing support
- [ ] Keyboard shortcuts

### Medium Term
- [ ] Due date functionality
- [ ] Task categories
- [ ] Search and filtering
- [ ] Export/import features
- [ ] Configuration options

### Long Term
- [ ] Cross-platform support
- [ ] Database storage option
- [ ] Multi-user support
- [ ] Web interface
- [ ] Mobile companion app

## Contributing

### Reporting Issues
When reporting bugs or requesting features, please include:
- Operating system version
- Compiler version used
- Steps to reproduce the issue
- Expected vs actual behavior
- Sample data files if relevant

### Development Guidelines
- Follow existing code style and conventions
- Add appropriate comments and documentation
- Test changes thoroughly before submitting
- Update documentation for new features
- Maintain backward compatibility when possible

### Testing Checklist
- [ ] All basic operations work (add, edit, delete)
- [ ] CSV file operations function correctly
- [ ] UI responds appropriately to user input
- [ ] Error conditions are handled gracefully
- [ ] Memory leaks are avoided
- [ ] Application starts and shuts down cleanly

## License and Credits

This project is provided as-is for educational and personal use. The code demonstrates basic Windows desktop application development using C++ and the Win32 API.

### Acknowledgments
- Microsoft Windows API documentation
- MinGW-w64 project for compiler toolchain
- Dev-C++ IDE for development environment
- C++ standard library for data structures and file I/O
