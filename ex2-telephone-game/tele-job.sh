#!/bin/bash
#SBATCH --job-name=hello-mpi
#SBATCH --account=COMS033964
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=5
#SBATCH --cpus-per-task=1
#SBATCH --output=job-output.out
#SBATCH --partition=teach_cpu

srun --mpi=pmi2 ./hello-mpi