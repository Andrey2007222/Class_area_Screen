#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <Windows.h>


HANDLE hStdOut;


class Window
{
    std::string title;
    int x, y, width, height;
    bool visible, framed;
    WORD color;
public:
    Window(std::string atitle, int ax, int ay, int awidth, int aheight, bool avisible, bool aframed, int acolor) :
        title(atitle), x(ax), y(ay), width(awidth), height(aheight), visible(avisible), framed(aframed), color(acolor)
    {
        char t[100];

        strcpy(t, title.c_str());
        CharToOemA(t, t);
        title = t;

        if (visible) Draw();
    }

    void Resize(int new_width, int new_height)
    {
        width = new_width;
        height = new_height;
        Draw();
    }

    void Move(int new_x, int new_y)
    {
        x = new_x;
        y = new_y;
        Draw();
    }

    void Draw()
    {
        COORD c;
        //system("cls");
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, color);
        // верхняя часть рамки и заголовок
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(hStdOut, c);
        std::cout << '\xC9' << (title.length() > width - 2 ? title.substr(0, width - 2) : title);
        for (int i = x + 1 + title.length(); i < x + width - 2; ++i) std::cout << '\xCD';
        std::cout << '\xBB';
        // нижняя часть рамки
        c.X = x;
        c.Y = y + height - 2;
        SetConsoleCursorPosition(hStdOut, c);
        std::cout << '\xC8';
        for (int i = x + 1; i < x + width - 2; ++i) std::cout << '\xCD';
        std::cout << '\xBC';
        // левая часть рамки
        c.X = x;
        for (int i = y + 1; i < y + height - 2; ++i)
        {
            c.Y = i;
            SetConsoleCursorPosition(hStdOut, c);
            std::cout << '\xBA';
        }
        // правая часть рамки
        c.X = x + width - 2;
        for (int i = y + 1; i < y + height - 2; ++i)
        {
            c.Y = i;
            SetConsoleCursorPosition(hStdOut, c);
            std::cout << '\xBA';
        }
        // внутренняя область
        for (int i = x + 1; i < x + width - 2; ++i)
            for (int j = y + 1; j < y + height - 2; ++j)
            {
                c.X = i;
                c.Y = j;
                SetConsoleCursorPosition(hStdOut, c);
                std::cout << ' ';
            }
    }
};

int main()
{
    COORD c;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Window w1("Окно 1", 5, 5, 40, 10, true, false, BACKGROUND_GREEN | FOREGROUND_BLUE);
    Window w2("Окно 2", 50, 10, 20, 10, true, false, BACKGROUND_RED | FOREGROUND_GREEN);

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    c.X = 0;
    c.Y = 24;
    SetConsoleCursorPosition(hStdOut, c);

    system("pause");
    system("cls");

    w1.Move(1, 7);
    w2.Move(55, 2);
    w2.Resize(24, 15);

    SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    c.X = 0;
    c.Y = 24;
    SetConsoleCursorPosition(hStdOut, c);


    system("pause");
    return 0;
}