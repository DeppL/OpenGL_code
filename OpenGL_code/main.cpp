//
//  main.cpp
//  OpenGL_code
//
//  Created by DeppL on 3/5/19.
//  Copyright © 2019 DeppL. All rights reserved.
//


#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "Render.hpp"

#include <chrono>
#include <thread>
#include <functional>


const int FRAMES_PER_SECOND = 60;
const double SKIP_TICK_1000 = 1.0f / FRAMES_PER_SECOND;

Render* render;

int main(int argc, const char * argv[]) {
    for (int i = 0; i < argc; i++) {
        std::cout << "argc." << i << ":" << argv[i] << std::endl;
    }
    
    // Render Initialize
    render = new Render();
    render->Initialize();
    
    // Render rendering
    double sleepTime = 0;
    unsigned int ceil_time = 0;
    unsigned int total_frame = 0;
    double next_game_tick = glfwGetTime();
    double current_time = 0;
    
    struct timespec spec = {0};
    spec.tv_sec = 0;
    spec.tv_nsec = 0;
    
    while(!render->shouldClose) {
        next_game_tick += SKIP_TICK_1000;
        render->FixedUpdate();
        current_time = glfwGetTime();
        
        ++total_frame;
        if (current_time > ceil_time) {
            std::cout << "current_time = " << current_time << "; total_frame = " << total_frame << ";" << std::endl;
            ceil_time = ceil(current_time);
            total_frame = 0;
        }
        
        sleepTime = next_game_tick - current_time;
        if (sleepTime > 0) {
            spec.tv_nsec = sleepTime * 100000000L;
            nanosleep(&spec, &spec);
        }
    }
    
    
    // Render Destroy
    render->Destroy();
    delete render;
    
    return 0;
}




