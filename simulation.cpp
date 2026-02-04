#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include "particle.h"

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        double timestep = atof(argv[1]);
        int steps = atoi(argv[2]);
        int dumpState = atoi(argv[3]);

        std::cout << "Enter name of output log file: ";

        std::string logFileName;
        std::cin >> logFileName;

        std::ofstream logFile(logFileName);
        if (!logFile)
        {
            std::cerr << "Error opening log file." << std::endl;
            return 1;
        }

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<Particle> particles = Particle::readParticles("solar.tsv");
        for (int s = 0; s < steps; s++)
        {
            for (size_t i = 0; i < particles.size(); ++i)
            {
                for (size_t j = i + 1; j < particles.size(); ++j)
                {
                    Particle::calculateState(particles[i], particles[j], timestep);
                }
            }
            if (dumpState && (s % dumpState == 0))
            {
                logFile << particles.size() << "\t";
                for (const auto &p : particles)
                {
                    logFile << p.mass << "\t" << p.x << "\t" << p.y << "\t" << p.z << "\t" << p.vx << "\t" << p.vy << "\t" << p.vz << "\t" << p.fx << "\t" << p.fy << "\t" << p.fz << "\t";
                }
                logFile << "\n";
            }
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "Simulation took " << duration.count() << " microseconds." << std::endl;
        logFile.close();
    }
    else if (argc == 5)
    {
        {
            int numParticles = atoi(argv[1]);
            double timestep = atof(argv[2]);
            int steps = atoi(argv[3]);
            int dumpState = atoi(argv[4]);

            std::cout << "Enter name of output log file: ";

            std::string logFileName;
            std::cin >> logFileName;

            std::ofstream logFile(logFileName);

            if (!logFile)
            {
                std::cerr << "Error opening log file." << std::endl;
                return 1;
            }

            std::vector<Particle> particles;
            for (int i = 0; i < numParticles; i++)
            {
                Particle p;
                p.initParticleRandom();
                particles.push_back(p);
            }
            auto start = std::chrono::high_resolution_clock::now();

            for (int s = 0; s < steps; s++)
            {
                for (size_t i = 0; i < particles.size(); ++i)
                {
                    for (size_t j = i + 1; j < particles.size(); ++j)
                    {
                        Particle::calculateState(particles[i], particles[j], timestep);
                    }
                }
                if (dumpState && (s % dumpState == 0))
                {
                    logFile << particles.size() << "\t";
                    for (const auto &p : particles)
                    {
                        logFile << p.mass << "\t" << p.x << "\t" << p.y << "\t" << p.z << "\t" << p.vx << "\t" << p.vy << "\t" << p.vz << "\t" << p.fx << "\t" << p.fy << "\t" << p.fz << "\t";
                    }
                    logFile << "\n";
                }
            }
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << "Simulation took " << duration.count() << " microseconds." << std::endl;
            logFile.close();
            return 0;
        }
    }
}
