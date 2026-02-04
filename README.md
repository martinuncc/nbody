N-Body simulation
Author: Martin Anuonye

This program is set up to run the n-body simulation on multiple particles 
on either a model of the solar system, or for a user specified number of particles.

Run this program with command line arguments for the timestep size, 
number of timesteps, and the frequency to dump the state in order to run the simulation
on a model of the solar system. (./executable .01 20 5)

Or, run the program including a argument for the number of random particles 
you would like before the timestep size argument (./executable 30 .01 20 5)

Simulation Benchmark:

100 particles dt=1 for 10000 steps: 9980428 microseconds
1000 particles dt=1 for 10000 steps: 1005802831 microseconds
Solar system with dt = 200 and for 5000000 steps: 2396702143 microseconds