#include "main.h"
#include <fstream>
#include <sstream>

std::vector<Task> tasks;
int editIndex = -1;

HWND hName, hDesc, hPriority, hStatus, hTaskList;
const char* CSV_FILE = "tasks.csv";

HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // for background
HBRUSH hYellowBrush = CreateSolidBrush(RGB(255, 255, 100)); // for edit fields


void SaveTaskToCSV(const Task& task) {
	std::ofstream file(CSV_FILE, std::ios::app);
	if (file.is_open()) {
		file << task.name << "," << task.description << "," << task.priority << "," << task.status << "\n";
		file.close();
	}
}

void RewriteCSV() {
    std::ofstream file(CSV_FILE, std::ios::trunc);
  for (size_t i = 0; i < tasks.size(); ++i) {
    Task& task = tasks[i];
    file << task.name << "," << task.description << "," << task.priority << "," << task.status << "\n";
}

    file.close();
}


void LoadTasksFromCSV(HWND hwnd) {
	std::ifstream file(CSV_FILE);
	std::string line;
	while (getline(file, line)) {
		std::istringstream ss(line);
		std::string name, desc, priority, status;
		getline(ss, name, ',');
		getline(ss, desc, ',');
		getline(ss, priority, ',');
		getline(ss, status, ',');

		Task task = { name, desc, priority, status };
		tasks.push_back(task);

		std::ostringstream display;
		display << task.name << " | " << task.priority << " | " << task.status;
		SendMessage(hTaskList, LB_ADDSTRING, 0, (LPARAM)display.str().c_str());
	}
	file.close();
}

std::string GetWindowTextStr(HWND hWnd) {
	char buffer[256];
	GetWindowText(hWnd, buffer, 256);
	return std::string(buffer);
}

void AddControls(HWND hwnd) {
	CreateWindow("STATIC", "Task Name:", WS_VISIBLE | WS_CHILD, 20, 20, 80, 20, hwnd, NULL, NULL, NULL);
	hName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 20, 200, 20, hwnd, (HMENU)ID_INPUT_NAME, NULL, NULL);

	CreateWindow("STATIC", "Description:", WS_VISIBLE | WS_CHILD, 20, 50, 80, 20, hwnd, NULL, NULL, NULL);
	hDesc = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 50, 200, 20, hwnd, (HMENU)ID_INPUT_DESC, NULL, NULL);

	CreateWindow("STATIC", "Priority:", WS_VISIBLE | WS_CHILD, 20, 80, 80, 20, hwnd, NULL, NULL, NULL);
	hPriority = CreateWindow("COMBOBOX", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_BORDER,
		110, 80, 200, 100, hwnd, (HMENU)ID_INPUT_PRIORITY, NULL, NULL);
	SendMessage(hPriority, CB_ADDSTRING, 0, (LPARAM)"Low");
	SendMessage(hPriority, CB_ADDSTRING, 0, (LPARAM)"Medium");
	SendMessage(hPriority, CB_ADDSTRING, 0, (LPARAM)"High");

	CreateWindow("STATIC", "Status:", WS_VISIBLE | WS_CHILD, 20, 110, 80, 20, hwnd, NULL, NULL, NULL);
//	hStatus = CreateWindow("COMBOBOX", "", WS_VISIBLE | WS_CHILD | CBS_DROPDDOWNLIST | WS_BORDER,
hStatus = CreateWindow("COMBOBOX", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_BORDER,

		110, 110, 200, 100, hwnd, (HMENU)ID_INPUT_STATUS, NULL, NULL);
	SendMessage(hStatus, CB_ADDSTRING, 0, (LPARAM)"Pending");
	SendMessage(hStatus, CB_ADDSTRING, 0, (LPARAM)"In Progress");
	SendMessage(hStatus, CB_ADDSTRING, 0, (LPARAM)"Completed");

	CreateWindow("BUTTON", "Add Task", WS_VISIBLE | WS_CHILD, 110, 140, 200, 25, hwnd, (HMENU)ID_BTN_ADD_TASK, NULL, NULL);
	CreateWindow("BUTTON", "Delete Task", WS_VISIBLE | WS_CHILD, 320, 20, 120, 25, hwnd, (HMENU)ID_BTN_DELETE_TASK, NULL, NULL);
	CreateWindow("BUTTON", "Edit Task", WS_VISIBLE | WS_CHILD, 320, 50, 120, 25, hwnd, (HMENU)ID_BTN_EDIT_TASK, NULL, NULL);

	hTaskList = CreateWindow("LISTBOX", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL,
		20, 180, 420, 150, hwnd, (HMENU)ID_LIST_TASKS, NULL, NULL);
}

void AddTask(HWND hwnd) {
	Task task;
	task.name = GetWindowTextStr(hName);
	task.description = GetWindowTextStr(hDesc);
	task.priority = GetWindowTextStr(hPriority);
	task.status = GetWindowTextStr(hStatus);

	if (task.name.empty()) {
		MessageBox(hwnd, "Task name is required.", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	std::ostringstream oss;
	oss << task.name << " | " << task.priority << " | " << task.status;

	if (editIndex >= 0) {
		tasks[editIndex] = task;
		SendMessage(hTaskList, LB_DELETESTRING, editIndex, 0);
		SendMessage(hTaskList, LB_INSERTSTRING, editIndex, (LPARAM)oss.str().c_str());
		editIndex = -1;
	} else {
		tasks.push_back(task);
		SendMessage(hTaskList, LB_ADDSTRING, 0, (LPARAM)oss.str().c_str());
	}

	RewriteCSV();

	SetWindowText(hName, "");
	SetWindowText(hDesc, "");
	SendMessage(hPriority, CB_SETCURSEL, -1, 0);
	SendMessage(hStatus, CB_SETCURSEL, -1, 0);
}

void DeleteTask(HWND hwnd) {
	int selected = SendMessage(hTaskList, LB_GETCURSEL, 0, 0);
	if (selected == LB_ERR) {
		MessageBox(hwnd, "Select a task to delete.", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	tasks.erase(tasks.begin() + selected);
	SendMessage(hTaskList, LB_DELETESTRING, selected, 0);
	RewriteCSV();
}

void EditTask(HWND hwnd) {
	int selected = SendMessage(hTaskList, LB_GETCURSEL, 0, 0);
	if (selected == LB_ERR) {
		MessageBox(hwnd, "Select a task to edit.", "Error", MB_OK | MB_ICONERROR);
		return;
	}

	Task& task = tasks[selected];
	SetWindowText(hName, task.name.c_str());
	SetWindowText(hDesc, task.description.c_str());
	SendMessage(hPriority, CB_SELECTSTRING, -1, (LPARAM)task.priority.c_str());
	SendMessage(hStatus, CB_SELECTSTRING, -1, (LPARAM)task.status.c_str());
	editIndex = selected;
}

//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
//	switch (msg) {
//	case WM_CREATE:
//		AddControls(hwnd);
//		LoadTasksFromCSV(hwnd);
//		break;
//	case WM_COMMAND:
//		switch (LOWORD(wParam)) {
//		case ID_BTN_ADD_TASK: AddTask(hwnd); break;
//		case ID_BTN_DELETE_TASK: DeleteTask(hwnd); break;
//		case ID_BTN_EDIT_TASK: EditTask(hwnd); break;
//		}
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hwnd, msg, wParam, lParam);
//	}
//	return 0;
//}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
		AddControls(hwnd);
		LoadTasksFromCSV(hwnd);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BTN_ADD_TASK: AddTask(hwnd); break;
		case ID_BTN_DELETE_TASK: DeleteTask(hwnd); break;
		case ID_BTN_EDIT_TASK: EditTask(hwnd); break;
		}
		break;

	// ? Add color for labels (STATIC) and edit/combo fields
	case WM_CTLCOLORSTATIC: {
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(0, 0, 255));          // Blue text
		SetBkColor(hdcStatic, RGB(255, 255, 255));        // White background
		return (INT_PTR)hWhiteBrush;
	}

	case WM_CTLCOLOREDIT: {
		HDC hdcEdit = (HDC)wParam;
		SetTextColor(hdcEdit, RGB(0, 100, 0));            // Dark green text
		SetBkColor(hdcEdit, RGB(255, 255, 100));          // Light yellow background
		return (INT_PTR)hYellowBrush;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "TaskManagerWindow";
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&wc);

	HWND hwnd = CreateWindow("TaskManagerWindow", "Task Manager File",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 480, 400,
		NULL, NULL, hInstance, NULL);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DeleteObject(hWhiteBrush);
DeleteObject(hYellowBrush);

	return 0;
}

