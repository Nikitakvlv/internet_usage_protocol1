#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

struct Time {
    int hours, minutes, seconds;
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}
    Time() : hours(0), minutes(0), seconds(0) {}
    bool operator>(const Time& other) const;
    int toSeconds() const;
};

struct InternetSession {
    Time start;
    Time end;
    int bytesReceived;
    int bytesSent;
    std::string program;
    int usageTime() const;
    int totalBytes() const;
};

std::vector<InternetSession> filterByProgram(const std::vector<InternetSession>& sessions, const std::string& programName);
std::vector<InternetSession> filterByStartTime(const std::vector<InternetSession>& sessions, const Time& threshold);

void insertionSort(std::vector<InternetSession>& sessions, bool(*comp)(const InternetSession&, const InternetSession&));
void quickSort(std::vector<InternetSession>& sessions, bool(*comp)(const InternetSession&, const InternetSession&));

bool usageTimeDescending(const InternetSession& a, const InternetSession& b);
bool programAscending(const InternetSession& a, const InternetSession& b);

void printSessions(const std::vector<InternetSession>& sessions);

#endif // UTILS_H