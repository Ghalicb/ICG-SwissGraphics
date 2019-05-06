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
    else if ((argc == 2) && argv[1][0] == '0') {
        jobs = { {
            {"../scenes/spheres/spheres.sce",         "../results/provided_scenes/spheres.png"},
            {"../scenes/cylinders/cylinders.sce",     "../results/provided_scenes/cylinders.png"},
            {"../scenes/combo/combo.sce",             "../results/provided_scenes/combo.png"},
            {"../scenes/molecule/molecule.sce",       "../results/provided_scenes/molecule.png"},
            {"../scenes/molecule2/molecule2.sce",     "../results/provided_scenes/molecule2.png"},
            {"../scenes/cube/cube.sce",               "../results/provided_scenes/cube.png"},
            {"../scenes/mask/mask.sce",               "../results/provided_scenes/mask.png"},
            {"../scenes/mirror/mirror.sce",           "../results/provided_scenes/mirror.png"},
            {"../scenes/toon_faces/toon_faces.sce",   "../results/provided_scenes/toon_faces.png"},
            {"../scenes/office/office.sce",           "../results/provided_scenes/office.png"},
            {"../scenes/rings/rings.sce",             "../results/provided_scenes/rings.png"},
            {"../scenes/cornell_box/cornell_box.sce", "../results/cornell_box.png"}
        } };
    }
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
