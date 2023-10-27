#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <windows.h>

bool IsFullWidthCharacter(const std::wstring& utf16String) {
    // 获取控制台信息，以确定字符宽度
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // 控制台缓冲区宽度
    int consoleWidth = csbi.dwSize.X;

    // 检查字符是否占用两个字符宽度
    if (utf16String.length() == 1) {
        return utf16String[0] >= 0x1100 && utf16String[0] <= 0x115F;
    } else {
        return false;
    }
}

int main() {
    // 输入要测量的 UTF-8 字符串
    std::string utf8Character = "你"; // 例如，你可以将要测量的 UTF-8 字符串放在这里

    // 将 UTF-8 字符串转换为 UTF-16
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring utf16Character = converter.from_bytes(utf8Character);

    if (IsFullWidthCharacter(utf16Character)) {
        std::cout << "全角字符" << std::endl;
    } else {
        std::cout << "半角字符" << std::endl;
    }

    return 0;
}
