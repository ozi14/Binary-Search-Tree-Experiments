#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>


class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;
    int comparisonCount;

    BST() : root(nullptr), comparisonCount(0) {}

    void reset() { comparisonCount = 0; }

    int getCount() { return comparisonCount; }

    void insert(int data) {
        root = insert(root, data);
    }

    bool find(int data) {
        return find(root, data);
    }

    void remove(int data) {
        root = remove(root, data);
    }

private:

    Node* insert(Node* node, int data);
    bool find(Node* node, int data);
    Node* remove(Node* node, int data);

    Node* minValueNode(Node* node);
};
void insertVector(BST& bst, const std::vector<int>& values) {
    for (int value : values) {
        bst.insert(value);
    }
}
void removeVector(BST& bst, const std::vector<int>& values) {
    for (int value : values) {
        bst.remove(value);
    }
}
void shuffle(std::vector<int>& vec, int numSwaps) {
    int size = vec.size();
    std::srand(std::time(nullptr));

    for (int i = 0; i < numSwaps; ++i) {
        int index1 = std::rand() % size;
        int index2 = std::rand() % size;
        std::swap(vec[index1], vec[index2]);
    }
}
void shake(std::vector<int>& vec, int numShakes, int maxDistance) {
    int size = vec.size();
    std::srand(std::time(nullptr));

    for (int i = 0; i < numShakes; ++i) {
        int index = std::rand() % size;
        int distance = (std::rand() % maxDistance) + 1;
        int direction = (std::rand() % 2) == 0 ? -1 : 1;

        int newIndex = index + (distance * direction);
        newIndex = std::max(newIndex, 0);
        newIndex = std::min(newIndex, size - 1);

        int value = vec[index];
        vec.erase(vec.begin() + index);
        vec.insert(vec.begin() + newIndex, value);
    }
}

void sumDepth(Node* node, int depth, int& sum, int& count) {
    if (node == nullptr) {
        return;
    }

    sum += depth;
    count++;

    sumDepth(node->left, depth + 1, sum, count);
    sumDepth(node->right, depth + 1, sum, count);
}

float averageDepth(BST& bst) {
    int sum = 0;
    int count = 0;
    sumDepth(bst.root, 0, sum, count);
    return count > 0 ? static_cast<float>(sum) / count : 0.0f;
}
int height(Node* node) {
    if (node == nullptr) {
        return -1;
    }
    return 1 + std::max(height(node->left), height(node->right));
}

int height(BST& bst) {
    return height(bst.root);
}
Node* BST::insert(Node* node, int data) {
    if (node == nullptr) {
        return new Node(data);
    }

    comparisonCount++; 
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    }

    return node;
}

bool BST::find(Node* node, int data) {
    if (node == nullptr) {
        return false;
    }

    comparisonCount++; 
    if (data == node->data) {
        return true;
    } else if (data < node->data) {
        return find(node->left, data);
    } else {
        return find(node->right, data);
    }
}

Node* BST::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* BST::remove(Node* node, int data) {
    if (node == nullptr) {
        return node;
    }

    comparisonCount++; 
    if (data < node->data) {
        node->left = remove(node->left, data);
    } else if (data > node->data) {
        node->right = remove(node->right, data);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = minValueNode(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }

    return node;
}
int main() {
    std::srand(std::time(nullptr));

    std::vector<int> values(1000);
    for (int i = 0; i < 1000; ++i) {
        values[i] = i + 1;
    }

    std::ofstream results_file("results.txt");

    int num_trees = 3;
    
    std::vector<std::pair<int, int>> shuffle_shake_configurations = {
        {1000, 0},  
        {500, 100}, 
        {500, 500}  
    };

    for (const auto& config : shuffle_shake_configurations) {
        int num_shuffles = config.first;
        int num_shakes = config.second;

        results_file << "Configuration: " << num_shuffles << " shuffles, " << num_shakes << " shakes\n";
        results_file << "-----------------------------------------------\n";

        for (int t = 0; t < num_trees; ++t) {
            std::vector<int> experiment_values = values;
            shuffle(experiment_values, num_shuffles);
            shake(experiment_values, num_shakes, 2);

            BST bst;
            insertVector(bst, experiment_values);

            results_file << "Tree " << t + 1 << ":\n";
            results_file << "Height: " << height(bst) << std::endl;
            results_file << "Average Depth: " << averageDepth(bst) << std::endl;

            int total_comparisons = 0;
            for (int i = 1; i <= 1000; ++i) {
                bst.reset();
                bool found = bst.find(i);
                total_comparisons += bst.getCount();
            }

            results_file << "Total Comparisons (Find): " << total_comparisons << std::endl;
            results_file << "Average Comparisons per Find: " << static_cast<float>(total_comparisons) / 1000 << std::endl;
            results_file << std::endl;
        }

        results_file << std::endl;
    }

    results_file.close();
    std::cout << "Experiments completed. Results saved to 'results.txt'." << std::endl;

    return 0;
}