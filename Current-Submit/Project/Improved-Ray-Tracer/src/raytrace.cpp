//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

//== includes =================================================================

#include "StopWatch.h"
#include "Scene.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

/// Program entry point.
int main(int argc, char **argv) {
    // Parse input scene file/output path from command line arguments
    struct RaytraceJob { std::string scenePath, outPath; };
    std::vector<RaytraceJob> jobs;

    if (argc == 3)
        jobs.emplace_back(RaytraceJob{argv[1], argv[2]});
    else {
        std::cerr << "Usage: " << argv[0] << " input.sce output.png\n";
        std::cerr << "Or: " << argv[0] << " 0\n";
        std::cerr << std::flush;
        exit(1);
    }

    for (const auto &job : jobs) {
        std::cout << "Read scene '" << job.scenePath << "'..." << std::flush;
        Scene s(job.scenePath);
        std::cout << "\ndone (" << s.numObjects() << " objects)\n";

        StopWatch timer;
        std::cout << "Ray tracing..." << std::flush;
        timer.start();
        auto image = s.render();
        timer.stop();
        std::cout << " done (" << timer << ")\n";

        std::cout << "Write image...";
        image.write(job.outPath);
        std::cout << "done\n";
    }
}
