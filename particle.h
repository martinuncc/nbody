#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cmath>
#include <ctime>
#ifndef particle_h
#define particle_h

class Particle {
    public:
        
        int id;
        double mass;
        double x, y, z;
        double vx, vy, vz;
        double fx, fy, fz;
        std::vector<double> properties;

        Particle() {};

        void initParticle(double m, 
                          double posX, double posY, double posZ, 
                          double velX, double velY, double velZ) {
            mass = m;
            x = posX; y = posY; z = posZ;
            vx = velX; vy = velY; vz = velZ;
            fx = fy = fz = 0.0;
            properties = {mass, x, y, z, vx, vy, vz, fx, fy, fz};
        }

        void initParticleRandom() {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            mass = rand() / (double)RAND_MAX * 1e30; 
            x = rand() / (double)RAND_MAX * 1e12;
            y = rand() / (double)RAND_MAX * 1e12;
            z = rand() / (double)RAND_MAX * 1e12;
            vx = rand() / (double)RAND_MAX * 50000;
            vy = rand() / (double)RAND_MAX * 50000;
            vz = rand() / (double)RAND_MAX * 50000;
            fx = fy = fz = 0.0;
            properties = {mass, x, y, z, vx, vy, vz, fx, fy, fz};
        }

        static void initParticles() {
            Particle earth;
            earth.initParticle(5.972e24, 10.0, 15.0, 20.0, 0, 0, 0);
            Particle sun;
            sun.initParticle(1.9891e+30, 530.0, 940.0, 1000.0, 0, 0, 0);
            Particle moon;
            moon.initParticle(7.346e22, 12.0, 18.0, 20.0, 0, 0, 0);
        }

        static std::vector<Particle> readParticles(const std::string &filename) {
            std::ifstream infile(filename);
            if (!infile) {
                std::cerr << "Error opening file: " << filename << std::endl;
                return {};
            }

            std::vector<std::vector<double>> particlesVector;
            std::vector<double> currentParticleValues;
            int numberParticles;

            std::string line;
            std::getline(infile, line);
            std::stringstream stream(line);
            stream >> numberParticles;
            while (std::getline(stream, line, '\t')) {
                if (!line.empty()) {
                    currentParticleValues.push_back(std::stod(line));
                    if (currentParticleValues.size() == 10) {
                        particlesVector.push_back(currentParticleValues);
                        currentParticleValues.clear();
                    }
                }
            }
            infile.close();

            std::vector<Particle> particles;
            std::cout << "Read " << particlesVector.size() << " particles from " << filename << std::endl;
            std::cout << "Number of particles: " << numberParticles << std::endl;
            //std::cout << "Initial States:" << std::endl;

            for (size_t i = 0; i < particlesVector.size(); ++i) {
                const auto &p = particlesVector[i];
                /*
                std::cout << "Particle " << i + 1 << ": " << std::endl;
                std::cout << "Mass: " << p[0] << ", ";
                std::cout << "Position: (" << p[1] << ", " << p[2] << ", " << p[3] << "), ";
                std::cout << "Velocity: (" << p[4] << ", " << p[5] << ", " << p[6] << "), ";
                std::cout << "Force: (" << p[7] << ", " << p[8] << ", " << p[9] << "), ";
                std::cout << std::endl;
                */

                Particle particle;
                particle.initParticle(p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
                particle.id = static_cast<int>(i) + 1;
                particles.push_back(particle);
            }
            //std::cout << "---------------------------------" << std::endl;
            return particles;
        }

        static void clearForces(Particle &p) {
            p.fx = 0.0;
            p.fy = 0.0;
            p.fz = 0.0;
        }

        static void calculateState(Particle &p1, Particle &p2, double timestep) {
            const double sfactor = 0.01;
            constexpr double G = 6.674 * 10e-12;

            clearForces(p1);
            clearForces(p2);

            double dx = p2.x - p1.x;
            double dy = p2.y - p1.y;
            double dz = p2.z - p1.z;
            std::vector<double> distances = {dx, dy, dz};

            double rSqr = dx * dx + dy * dy + dz * dz + (sfactor * sfactor);
            double r = std::sqrt(rSqr);

            double force = (G * p1.mass * p2.mass) / (rSqr * r);

            p1.fx += force * dx;
            p1.fy += force * dy;
            p1.fz += force * dz;
            p2.fx -= force * dx;
            p2.fy -= force * dy;
            p2.fz -= force * dz;

            double acceleration = force / p1.mass;
            p1.vx += acceleration * (timestep);
            p1.vy += acceleration * (timestep);
            p1.vz += acceleration * (timestep);

            p1.x += p1.vx * (timestep);
            p1.y += p1.vy * (timestep);
            p1.z += p1.vz * (timestep);

        }
};

#endif