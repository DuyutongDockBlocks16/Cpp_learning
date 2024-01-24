//#include <iostream>
//#include <chrono>
//
//int main() {
//    // 获取当前日期和时间
//    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//
//    // 获取当前日期的年、月和日
//    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
//    std::tm* now_tm = std::localtime(&now_time);
//    int currentYear = now_tm->tm_year + 1900;
//    int currentMonth = now_tm->tm_mon + 1;
//    int currentDay = now_tm->tm_mday;
//
//    // 计算下一个月的年和月
//    int nextYear = currentYear;
//    int nextYear = currentYear;
//    int nextMonth = currentMonth + 1;
//    if (nextMonth > 12) {
//        nextMonth = 1;
//        nextYear++;
//    }
//    int nextDay = currentDay;
//
//    std::cout << nextYear << std::endl;
//    std::cout << nextMonth << std::endl;
//    std::cout << nextDay << std::endl;
//
//    return 0;
//}
