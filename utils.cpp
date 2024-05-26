#include "utils.h"
#include <iostream>
#include <algorithm>

bool Time::operator>(const Time& other) const {
    return this->toSeconds() > other.toSeconds();
}

int Time::toSeconds() const {
    return hours * 3600 + minutes * 60 + seconds;
}

int InternetSession::usageTime() const {
    return end.toSeconds() - start.toSeconds();
}

int InternetSession::totalBytes() const {
    return bytesReceived + bytesSent;
}

std::vector<InternetSession> filterByProgram(const std::vector<InternetSession>& sessions, const std::string& programName) {
    std::vector<InternetSession> result;
    std::copy_if(sessions.begin(), sessions.end(), std::back_inserter(result), [&](const InternetSession& session) {
        return session.program.find(programName) != std::string::npos;
        });
    return result;
}

std::vector<InternetSession> filterByStartTime(const std::vector<InternetSession>& sessions, const Time& threshold) {
    std::vector<InternetSession> result;
    std::copy_if(sessions.begin(), sessions.end(), std::back_inserter(result), [&](const InternetSession& session) {
        return session.start > threshold;
        });
    return result;
}

void insertionSort(std::vector<InternetSession>& sessions, bool(*comp)(const InternetSession&, const InternetSession&)) {
    for (size_t i = 1; i < sessions.size(); ++i) {
        InternetSession key = sessions[i];
        int j = i - 1;
        while (j >= 0 && comp(sessions[j], key)) {
            sessions[j + 1] = sessions[j];
            --j;
        }
        sessions[j + 1] = key;
    }
}

int partition(std::vector<InternetSession>& sessions, int low, int high, bool(*comp)(const InternetSession&, const InternetSession&)) {
    InternetSession pivot = sessions[high];
    int i = (low - 1);
    for (int j = low; j < high; ++j) {
        if (!comp(sessions[j], pivot)) {
            ++i;
            std::swap(sessions[i], sessions[j]);
        }
    }
    std::swap(sessions[i + 1], sessions[high]);
    return (i + 1);
}

void quickSortUtil(std::vector<InternetSession>& sessions, int low, int high, bool(*comp)(const InternetSession&, const InternetSession&)) {
    if (low < high) {
        int pi = partition(sessions, low, high, comp);
        quickSortUtil(sessions, low, pi - 1, comp);
        quickSortUtil(sessions, pi + 1, high, comp);
    }
}

void quickSort(std::vector<InternetSession>& sessions, bool(*comp)(const InternetSession&, const InternetSession&)) {
    quickSortUtil(sessions, 0, sessions.size() - 1, comp);
}

bool usageTimeDescending(const InternetSession& a, const InternetSession& b) {
    return a.usageTime() > b.usageTime();
}

bool programAscending(const InternetSession& a, const InternetSession& b) {
    if (a.program == b.program) {
        return a.totalBytes() > b.totalBytes();
    }
    return a.program < b.program;
}

void printSessions(const std::vector<InternetSession>& sessions) {
    for (const auto& session : sessions) {
        std::cout << session.start.hours << ":" << session.start.minutes << ":" << session.start.seconds << " "
            << session.end.hours << ":" << session.end.minutes << ":" << session.end.seconds << " "
            << session.bytesReceived << " " << session.bytesSent << " "
            << session.program << std::endl;
    }
}