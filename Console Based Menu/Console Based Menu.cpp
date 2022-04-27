#include <iostream>
#include <Windows.h>
#include <functional>
#include <algorithm>
#include <thread>

#include "globals.hpp"

void draw_menu(std::string_view string, const int& value) {
	if (value == n_globals::currently_selected) {

		printf("> %s \n", string.data());
		return;
	}
	
	printf("%s\n", string.data());
}

void draw_checkbox(std::string_view string, const int& value, bool& var) {
	if (value == n_globals::menu_selected) {
		if ((GetAsyncKeyState(0xD) & 1))
			var = !var;

		printf("> %s: %i \n", string.data(), var);

		return;
	}

	printf("%s: %i \n", string.data(), var);
}

void draw_slider_int(std::string_view string, const int& value, int& var, const int& min, const int& max) {
	if (value == n_globals::menu_selected) {
		if ((GetAsyncKeyState(VK_RIGHT) & 1)) {
			var++;
		}

		if ((GetAsyncKeyState(VK_LEFT) & 1)) {
			var--;
		}

		var = std::clamp(var, min, max);

		printf("> %s: %i \n", string.data(), var);
		return;
	}

	printf("%s: %i \n", string.data(), var);
}

void draw_slider_float(std::string_view string, const int& value, float& var, const float& min, const float& max, const float& inc_value) {
	if (value == n_globals::menu_selected) {
		if ((GetAsyncKeyState(VK_RIGHT) & 1)) {
			var += inc_value;
		}

		if ((GetAsyncKeyState(VK_LEFT) & 1)) {
			var-= inc_value;
		}

		var = std::clamp(var, min, max);

		printf("> %s: %f \n", string.data(), var);
		return;
	}

	printf("%s: %f \n", string.data(), var);
}

void draw_colour_picker(std::string_view string, const int& value, colour_t& col) {
	static const char* colours[] = { "red", "green", "blue", "orange" };
	static colour_t colours_value[] = { colour_t(255, 0,0,255), colour_t(0, 255, 0, 255), colour_t(0, 0, 255, 255), colour_t(255,128,0, 255) };

	static int col_value;

	if (value == n_globals::menu_selected) {
		if ((GetAsyncKeyState(VK_RIGHT) & 1)) {
			col_value++;
		}

		if ((GetAsyncKeyState(VK_LEFT) & 1)) {
			col_value--;
		}

		col_value = std::clamp(col_value, 0, (int(sizeof(colours) / sizeof(const char*))) - 1);

		col = colours_value[col_value];

		printf("> %s: %s", string.data(), colours[col_value]);

		return;
	}

	printf("%s: %s", string.data(), colours[col_value]);
}

void draw_backbutton(const int& value) {
	if (value == n_globals::menu_selected) {
		if ((GetAsyncKeyState(0xD) & 1)) {
			n_globals::run_selected = -1;
		}
		printf(">back \n");

		return;
	}

	printf("back \n");
}

void example() {
	Sleep(50);
	system("cls");

	draw_backbutton(0);
	draw_checkbox("test 1", 1, n_vars::bool_var1);
	draw_checkbox("test 2", 2, n_vars::bool_var2);
	draw_checkbox("test 3", 3, n_vars::bool_var3);
	draw_slider_int("test 4", 4, n_vars::int_var1, 0, 100);
	draw_slider_float("test 5", 5, n_vars::float_var1, 0, 1, 0.1f);
	draw_colour_picker("test 6", 6, n_vars::col_var1);

	n_globals::menu_selected = std::clamp(n_globals::menu_selected, 0, 6);
}

void example2() {
	Sleep(50);
	system("cls");

	draw_backbutton(0);

	n_globals::menu_selected = std::clamp(n_globals::menu_selected, 0, 3);
}

void example3() {
	Sleep(50);
	system("cls");

	draw_backbutton(0);

	n_globals::menu_selected = std::clamp(n_globals::menu_selected, 0, 3);
}

DWORD run_functions(LPVOID thread) {
	while (true) {
		if (n_globals::run_selected != -1) {
			if ((GetAsyncKeyState(VK_DOWN) & 1))
				n_globals::menu_selected++;

			if ((GetAsyncKeyState(VK_UP) & 1))
				n_globals::menu_selected--;
		}

		switch (n_globals::run_selected) {
		case 0:
			example();
			break;
		case 1:
			example2();
			break;
		case 2:
			example3();
			break;
		}
	}

	return 1;
}

int main()
{
	static int stored_selected = -1;

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run_functions, 0, 0, nullptr);

	while (true) {
		static bool force_refresh = false;

		if (n_globals::run_selected != -1) {
			force_refresh = true;
			continue;
		}

		if ((GetAsyncKeyState(VK_DOWN) & 1))
			n_globals::currently_selected++;

		if ((GetAsyncKeyState(VK_UP) & 1))
			n_globals::currently_selected--;

		if (n_globals::currently_selected != stored_selected || force_refresh) {
			stored_selected = n_globals::currently_selected;
			force_refresh = false;

			system("cls");
			
			draw_menu("example 1", 0);
			draw_menu("example 2", 1);
			draw_menu("example 3", 2);

			n_globals::currently_selected = std::clamp(n_globals::currently_selected, 0, 2);
		}

		if ((GetAsyncKeyState(0xD) & 1))
			n_globals::run_selected = n_globals::currently_selected;
	}
}
