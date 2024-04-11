#!/bin/bash

# Stop on error
set -e

# Download Miniconda installer
echo "Downloading Miniconda installer..."
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O Miniconda3.sh

# Make the installer executable
chmod +x Miniconda3.sh

# Run the Miniconda installer
echo "Installing Miniconda..."
./Miniconda3.sh -b -p $HOME/miniconda

# Delete the installer to save space
rm Miniconda3.sh

# Initialize Conda
echo "Initializing Miniconda..."
$HOME/miniconda/bin/conda init bash

# Activate conda
source $HOME/.bashrc

echo "Miniconda installation is complete."
echo "Please close and reopen your terminal to start using conda."
