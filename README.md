# Binary Search Tree (BST) Experiments

This repository contains a C++ program that performs experiments on Binary Search Trees (BSTs). It measures the height, average depth, and average number of comparisons for finding elements in a BST under various shuffle and shake configurations.

## Overview

A Binary Search Tree (BST) is a data structure in which each node has at most two children, and the left child is less than the parent, while the right child is greater. This program implements a BST class and conducts experiments on different trees with shuffled and shaken configurations of input values.

## Installation

1. Clone the repository to your local machine:

```bash
git clone https://github.com/your_username/your_repository.git
```

2. Compile the C++ program using your preferred C++ compiler. For example, with g++, run:

```bash
g++ -o bst_experiments bst_experiments.cpp
```

## Usage

1. Run the compiled program:

```bash
./bst_experiments
```

2. The program will conduct experiments with different shuffle and shake configurations and save the results in `results.txt`.

## Experiment Results

The experiments in this program are conducted with different configurations of shuffling and shaking. Each configuration consists of a number of shuffles and shakes applied to the input values. The program calculates the height, average depth, total comparisons for finding elements, and average comparisons per find for each tree created with the respective configuration.

The `results.txt` file will contain the results of all experiments, organized by configuration and individual trees.

## Contributing

Contributions to this repository are welcome! If you have any suggestions, improvements, or bug fixes, feel free to open an issue or submit a pull request.
