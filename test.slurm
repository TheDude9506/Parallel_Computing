#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --mem-per-cpu=1G
#SBATCH --time=01:00:00
#SBATCH --partition=week-long-cpu
#SBATCH --job-name=HelloWorld
#SBATCH --error=job.%J.err
#SBATCH --output=job.%J.out

echo "HelloWorld"
sleep 300