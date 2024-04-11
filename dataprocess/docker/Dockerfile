# Use Ubuntu 20.04 LTS as the base image
FROM ubuntu:20.04

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Update the package repository and install packages
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Your additional commands here
# For example, copy your application's source code into the container

# Set the working directory
# WORKDIR /myapp

# Run any necessary commands to set up your application
# RUN pip3 install -r requirements.txt

# Specify the default command to run
# CMD ["python3", "app.py"]

