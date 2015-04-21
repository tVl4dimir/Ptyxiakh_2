#include "Functions.h"

#include "Simulation.h"
#include "General_events.h"

#include <iostream>

#include <thread>
#include <mutex>
#include <chrono>

void wait_for_input(Simulation& sim);

std::future<void> simulation_event_generator(Simulation& sim)
{
    std::future<void> input = std::async(std::launch::async,
            wait_for_input, std::ref(sim));
    return input;
}

void wait_for_input(Simulation& sim)
{
    char s;
    std::mutex m;
    std::lock_guard<std::mutex> lock(m);
    if (std::cin >> s)
    {
        switch (s)
        {
        case 'r':
            break;
        case 's':
            break;
        case 'e':
            sim.schedule_event(Events::SIM_END);
            break;
        default:
            break;
        }
        
    }
    else
    {
        std::this_thread::yield();
    }
}

bool check_message(Simulation& sim)
{
    if (sim.get_event() == Events::SIM_END)
    {
        return true;
    }
    return false;
}
