#include <iostream>
#include <string>

struct Student {
    int student_id;
    std::string name;
    std::string generation;

    Student(int id = 0, std::string name = "", std::string generation = "")
        : student_id(id), name(name), generation(generation) {}
};

struct TreeNode {
    Student student;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Student s) : student(s), left(nullptr), right(nullptr) {}
};

class StudentManager {
    TreeNode* root;

public:
    StudentManager() : root(nullptr) {}

    // Add a new student
    void addStudent() {
        int id;
        std::string name, generation;
        std::cout << "Enter Student ID: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Generation: ";
        std::cin >> generation;

        root = insert(root, Student(id, name, generation));
        std::cout << "Student added successfully.\n";
    }

    // Retrieve a student by ID
    void retrieveStudent() {
        int id;
        std::cout << "Enter Student ID to retrieve: ";
        std::cin >> id;
        TreeNode* node = search(root, id);
        if (node) {
            displayStudent(node->student);
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Update a student's details
    void updateStudent() {
        int id;
        std::cout << "Enter Student ID to update: ";
        std::cin >> id;
        TreeNode* node = search(root, id);
        if (node) {
            std::string name, generation;
            std::cout << "Enter new Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Enter new Generation: ";
            std::cin >> generation;
            node->student.name = name;
            node->student.generation = generation;
            std::cout << "Student updated successfully.\n";
        } else {
            std::cout << "Student not found.\n";
        }
    }

    // Remove a student by ID
    void removeStudent() {
        int id;
        std::cout << "Enter Student ID to remove: ";
        std::cin >> id;
        root = remove(root, id);
    }

    // Display all students (in-order traversal)
    void displayAll() {
        if (!root) {
            std::cout << "No students to display.\n";
            return;
        }
        displayInOrder(root);
    }

private:
    // Insert a new student in the BST
    TreeNode* insert(TreeNode* node, const Student& student) {
        if (!node) return new TreeNode(student);
        if (student.student_id < node->student.student_id) {
            node->left = insert(node->left, student);
        } else if (student.student_id > node->student.student_id) {
            node->right = insert(node->right, student);
        } else {
            std::cout << "Student ID already exists.\n";
        }
        return node;
    }

    // Search for a student by ID in the BST
    TreeNode* search(TreeNode* node, int id) {
        if (!node || node->student.student_id == id) return node;
        if (id < node->student.student_id) {
            return search(node->left, id);
        } else {
            return search(node->right, id);
        }
    }

    // Remove a student by ID in the BST
    TreeNode* remove(TreeNode* node, int id) {
        if (!node) {
            std::cout << "Student not found.\n";
            return nullptr;
        }

        if (id < node->student.student_id) {
            node->left = remove(node->left, id);
        } else if (id > node->student.student_id) {
            node->right = remove(node->right, id);
        } else {
            // Node to be deleted
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                std::cout << "Student removed successfully.\n";
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                std::cout << "Student removed successfully.\n";
                return temp;
            }

            // Node with two children
            TreeNode* temp = findMin(node->right);
            node->student = temp->student;
            node->right = remove(node->right, temp->student.student_id);
        }
        return node;
    }

    // Find the node with the minimum value in a subtree
    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // In-order traversal to display students
    void displayInOrder(TreeNode* node) {
        if (!node) return;
        displayInOrder(node->left);
        displayStudent(node->student);
        displayInOrder(node->right);
    }

    // Display a single student
    void displayStudent(const Student& student) {
        std::cout << "ID: " << student.student_id
                  << ", Name: " << student.name
                  << ", Generation: " << student.generation << std::endl;
    }
};

// Console Menu
void menu() {
    StudentManager manager;
    int choice;
    do {
        std::cout << "\nMenu:\n"
                  << "1. Add Student\n"
                  << "2. Retrieve Student\n"
                  << "3. Update Student\n"
                  << "4. Remove Student\n"
                  << "5. Display All Students\n"
                  << "6. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.retrieveStudent(); break;
            case 3: manager.updateStudent(); break;
            case 4: manager.removeStudent(); break;
            case 5: manager.displayAll(); break;
            case 6: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

int main() {
    menu();
    return 0;
}

