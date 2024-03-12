#include "include/app.hpp"
#include "include/color.hpp"
#include "include/control.hpp"
#include "include/input.hpp"
#include "include/reactivity.hpp"
#include "include/timer.hpp"

#include <clocale>
#include <ncurses.h>
#include <string>
#include <thread>

struct ExitAppException {};

static auto isDirty = true;
static auto currentPath = createSignal("/");

Element Route(const std::string &path, const Component<> &component) {
    return WHEN(path == currentPath()) {
        component(),
    } END_WHEN;
}

void navigate(const std::string &path) {
    currentPath.set(path);
}

void exitApp() {
    throw ExitAppException();
}

void playBeep() {
    beep();
}

int render(const Element &element) {
    setlocale(LC_ALL, "");
    initscr();
    Liquid::initializeInput();
    Liquid::initializeColor();

    while (true) {
        try {
            Liquid::processInput();
            Liquid::processTimer();

            if (isDirty) {
                isDirty = false;
                clear();
                element.render();
                refresh();
            }
        } catch (ExitAppException) {
            break;
        }

        std::this_thread::yield();
    }

    endwin();
    return 0;
}

namespace Liquid {
    void markDirty() {
        isDirty = true;
    }
}
