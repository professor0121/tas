#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <vector>
#include <string>

struct Task {
	std::string name;
	std::string description;
	std::string priority;
	std::string status;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Control IDs
#define ID_INPUT_NAME       101
#define ID_INPUT_DESC       102
#define ID_INPUT_PRIORITY   103
#define ID_INPUT_STATUS     104
#define ID_BTN_ADD_TASK     105
#define ID_LIST_TASKS       106
#define ID_BTN_DELETE_TASK  107
#define ID_BTN_EDIT_TASK    108

extern std::vector<Task> tasks;

#endif

