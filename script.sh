#!/bin/bash
#SBATCH --job-name=nbody
#SBATCH --partition=Centaurus
#SBATCH --time=00:60:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem=10G

g++ simulation.cpp -o s
./s 200 5000000 5000 <<< "log1.tsv"
