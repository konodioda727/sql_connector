#include "../headers/utils.h"
float strToFloat(const char* str) {
    float result;
    sscanf(str, "%f", &result);
    return result;
}
void getTime(char* timeString) {
    time_t currentTime;
    time(&currentTime);
    // 将时间戳转换为本地时间
    struct tm* localTime = localtime(&currentTime);

    // 格式化时间字符串
    strftime(timeString, 50, "%Y-%m-%d", localTime);
}

void Arr2Str(char* result, const char* str[]) {
    int i = 0;
    strcat(result, "(");
    while (str[i] != NULL) {
        strcat(result, str[i]);
        if (str[i + 1] != NULL)
            strcat(result, ",");
        i++;
    }
    strcat(result, ")");
}
void AddTab(char* result, const char* type, const char* str[]) {
    int i = 0;
    AddTab(result, type);
    while (str[i] != NULL) {
        AddTab(result, str[i]);
        if (str[i + 1] != NULL)
            strcat(result, ",");
        i++;
    }

}
void AddTab(char* result, const char* add) {
    strcat(result, " ");
    strcat(result, add);
    strcat(result, " ");
}
void AddTab(char* result, const char* addname, const char* addbody) {
    strcat(result, " ");
    strcat(result, addname);
    strcat(result, " ");
    strcat(result, addbody);
    strcat(result, " ");
}

