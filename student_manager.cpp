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
