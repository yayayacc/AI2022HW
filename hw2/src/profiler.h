#pragma once

#include <chrono>
#include <string>
#include <vector>

struct ProfileTaskResult {
    std::string name;
    long long   start{0};
    long long   end{0};
    long long   getLength() { return end - start; }
};

class StepTimer;

class Profiler {
    friend class StepTimer;

public:
    static Profiler& getInstance() {
        static Profiler instance;
        return instance;
    }

    Profiler(const Profiler&)            = delete;
    Profiler& operator=(const Profiler&) = delete;

    void display() {
        printf("--------------Result--------------\n");
        for (auto& ret : m_profile_tasks)
            printf("name: %s, cost time: %.3f s\n", ret.name.c_str(), double(ret.getLength() / 1000.0 / 1000.0));
        printf("--------------Result--------------\n");
        m_profile_tasks.clear();
    }

private:
    Profiler()  = default;
    ~Profiler() = default;

private:
    std::vector<ProfileTaskResult> m_profile_tasks;
};

class StepTimer {
public:
    StepTimer(const char* name) :
        m_name(name), m_stopped(false) {
        m_startTime_point = std::chrono::high_resolution_clock::now();
    }

    ~StepTimer() {
        if (!m_stopped)
            stop();
    }

    void stop() {
        auto endTime_point = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTime_point).time_since_epoch().count();
        long long end   = std::chrono::time_point_cast<std::chrono::microseconds>(endTime_point).time_since_epoch().count();

        Profiler::getInstance().m_profile_tasks.push_back({m_name, start, end});

        m_stopped = true;
    }

private:
    const char*                                                 m_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime_point;
    bool                                                        m_stopped;
};

#define PROFILE_SCOPE(name) StepTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#define PROFILE_DISPLAY() Profiler::getInstance().display()