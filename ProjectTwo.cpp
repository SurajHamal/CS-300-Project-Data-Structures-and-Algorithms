//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Suraj Hamal
// Version     : 2.0
// Copyright   : Copyright © 2025 [Suraj Hamal]
// Description : Course planner using a Binary Search Tree to manage and search courses with prerequisites
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Forward declarations
string trim(string str);
string toUpper(string str);

//============================================================================
// Define a structure to hold course information
//============================================================================
struct Course {
    string courseNumber;               // Unique course identifier (e.g., CS101)
    string courseName;                 // Course title (e.g., Introduction to Programming)
    vector<string> prerequisites;     // List of prerequisite course numbers

    // Default constructor
    Course() {
        courseNumber = "";
        courseName = "";
    }
};

//============================================================================
// Internal structure for BST Node
//============================================================================
struct Node {
    Course course;   // Course data held by the node
    Node* left;      // Pointer to left child
    Node* right;     // Pointer to right child

    // Default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // Constructor with course data
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================
class BinarySearchTree {
private:
    Node* root;  // Root node of the tree

    // Recursive helper methods
    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    Node* removeTree(Node* node);
    Node* searchNode(Node* node, string courseNumber);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();                    // Public method to display in-order traversal
    void Insert(Course course);       // Public method to insert a course
    Course Search(string courseNumber); // Public method to search course
    void Clear();                     // Public method to delete tree
};

//============================================================================
// BinarySearchTree Implementation
//============================================================================

// Constructor: Initialize root to nullptr
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// Destructor: Clean up all nodes from memory
BinarySearchTree::~BinarySearchTree() {
    root = removeTree(root);
}

// Public wrapper for in-order traversal
void BinarySearchTree::InOrder() {
    inOrder(root);
}

// Public wrapper to insert a course into BST
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course); // Set root if tree is empty
    }
    else {
        addNode(root, course);  // Otherwise, delegate to recursive helper
    }
}

// Public method to search for a course by number
Course BinarySearchTree::Search(string courseNumber) {
    Node* node = searchNode(root, courseNumber); // Search starting from root
    if (node != nullptr) {
        return node->course; // Return found course
    }
    return Course(); // Return default course if not found
}

// Public method to delete all nodes and reset the tree
void BinarySearchTree::Clear() {
    root = removeTree(root);
}

// Recursive method to insert a node in correct position based on courseNumber
void BinarySearchTree::addNode(Node* node, Course course) {
    if (course.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) {
            node->left = new Node(course); // Insert as left child
        }
        else {
            addNode(node->left, course);   // Recurse left
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course); // Insert as right child
        }
        else {
            addNode(node->right, course);   // Recurse right
        }
    }
}

// Recursive in-order traversal: left -> root -> right
void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) { // check if node exists
        inOrder(node->left); // traverse left subtree
        cout << node->course.courseNumber << ": " << node->course.courseName << endl; // print course details
        inOrder(node->right); // traverse right subtree
    }
}

// Recursively delete all nodes in post-order
Node* BinarySearchTree::removeTree(Node* node) {
    if (node == nullptr) return nullptr; // base case: return if null
    node->left = removeTree(node->left); // delete left subtree
    node->right = removeTree(node->right); // delete right subtree
    delete node; // free current node
    return nullptr; // return null pointer
}

// Recursively search for courseNumber starting from node
Node* BinarySearchTree::searchNode(Node* node, string courseNumber) {
    if (node == nullptr || node->course.courseNumber == courseNumber) { // base case: null or found
        return node; // return current node or nullptr
    }
    if (courseNumber < node->course.courseNumber) { // if course number is smaller
        return searchNode(node->left, courseNumber); // search left subtree
    }
    return searchNode(node->right, courseNumber); // search right subtree
}

//============================================================================
// Helper utility functions
//============================================================================

// Removes leading and trailing whitespaces
// trim whitespace from string
string trim(string str) {
    size_t start = str.find_first_not_of(" \t\n\r"); // find first non-whitespace character
    size_t end = str.find_last_not_of(" \t\n\r"); // find last non-whitespace character
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1); // return trimmed string or empty if all whitespace
}

// convert string to uppercase
string toUpper(string str) {
    string upperStr = str; // copy input string
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper); // convert each character to uppercase
    return upperStr; // return modified string
}

// display course and its prerequisites
void displayCourse(Course course, BinarySearchTree& tree) {
    cout << "--------------------------------------------------------- " << endl;
    cout << course.courseNumber << ": " << course.courseName << endl; // print course details
    cout << "--------------------------------------------------------- " << endl;
    
    if (course.prerequisites.empty()) { // check if no prerequisites
        cout << "--------------------------------------------------------- " << endl;
        cout << "Prerequisites: None" << endl; // indicate no prerequisites
        cout << "--------------------------------------------------------- " << endl;
    }
    else {
        cout << "---------------------------------------------------------" << endl;
        
        cout << "Prerequisites: " << endl; // start prerequisite list
        for (size_t i = 0; i < course.prerequisites.size(); ++i) { // iterate through prerequisites
            Course pre = tree.Search(course.prerequisites[i]); // search for prerequisite course
            
            if (!pre.courseNumber.empty()) { // if prerequisite found
                cout << "    " << pre.courseNumber << ": " << pre.courseName; // print prerequisite details
            }
            else {
                cout << course.prerequisites[i] << ": [Title not found]"; // indicate missing prerequisite
            }
            if (i < course.prerequisites.size() - 1) cout << ", " << endl; // add comma between prerequisites
        }
        cout << endl; // end prerequisite list
        cout << "--------------------------------------------------------- " << endl;
        
    }
}

// Load course data from a CSV file and populate the BST
// load courses from CSV file
void loadCourses(string csvPath, BinarySearchTree* bst) {
    ifstream file(csvPath); // open input file
    cout << "Loading CSV file " << csvPath << endl; // display file path

    if (!file.is_open()) { // check if file failed to open
        cout << "ERROR: Unable to open file '" << csvPath << "'" << endl; // report error
        return; // exit function
    }

    set<string> validCourseNumbers; // store valid course numbers for validation
    vector<string> courses; // store lines for second pass
    string line; // hold each line

    // first pass: collect course numbers
    while (getline(file, line)) { // read line by line
        if (line.empty()) continue; // skip empty lines
        courses.push_back(line); // store line
        stringstream ss(line); // create string stream
        string token; // hold each token
        vector<string> courseNumbers; // store tokens

        while (getline(ss, token, ',')) { // split by comma
            courseNumbers.push_back(trim(token)); // trim whitespace and add token
        }

        if (courseNumbers.size() < 2) { // check for minimum tokens
            cout << "ERROR: Invalid course data format.\n"; // report error
            file.close(); // close file
            return; // exit function
        }

        validCourseNumbers.insert(courseNumbers[0]); // add course number
    }

    file.clear(); // reset EOF flag
    file.seekg(0); // rewind file pointer
    bst->Clear(); // clear existing tree

    // second pass: insert courses
    for (const auto& l : courses) { // iterate stored lines
        stringstream ss(l); // create string stream
        string token; // hold each token
        vector<string> courseNumbers; // store tokens

        while (getline(ss, token, ',')) { // split by comma
            courseNumbers.push_back(trim(token)); // trim and add token
        }

        Course course; // create new course
        course.courseNumber = courseNumbers[0]; // set course number
        course.courseName = courseNumbers[1]; // set course name

        for (size_t i = 2; i < courseNumbers.size(); ++i) { // process prerequisites
            string prerequisite = courseNumbers[i]; // get prerequisite

            if (prerequisite.empty()) continue; // skip empty prerequisites
                if (validCourseNumbers.find(prerequisite) == validCourseNumbers.end()) { // check if valid
                    cout << "ERROR: Prerequisite '" << prerequisite << "' not found.\n"; // report error
                    file.close(); // close file
                    return; // exit function
                }
                course.prerequisites.push_back(prerequisite); // add valid prerequisite
        }

        bst->Insert(course); // insert course into tree
    }

    file.close(); // close file
    cout << "Courses loaded successfully from '" << csvPath << "'\n"; // confirm success
}


// Show main menu options
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "  1. Load Courses" << endl;
    cout << "  2. Display All Courses" << endl;
    cout << "  3. Find Course" << endl;
    cout << "  9. Exit" << endl;
    cout << "Enter choice: ";
}

//============================================================================
// Entry Point
//============================================================================
// main program entry point
int main(int argc, char* argv[]) {
    string csvPath; // hold CSV file path
    if (argc == 2) { // check for command-line argument
        csvPath = argv[1]; // use provided file path
    }
    else {
        csvPath = "courses.csv"; // default to courses.csv
    }

    BinarySearchTree* bst = new BinarySearchTree(); // create BST instance
    Course course; // store search results
    int choice = 0; // store user menu selection

    while (choice != 9) { // loop until exit option
        displayMenu(); // show menu options
        cin >> choice; // read user input

        if (cin.fail()) { // handle non-numeric input
            cin.clear(); // reset input stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
            cout << "Invalid input. Please enter a number from the menu." << endl; // report error
            continue; // restart loop
        }

        switch (choice) { // process user choice
        case 1:
            loadCourses(csvPath, bst); // load courses from file
            break; // exit case

        case 2:
            bst->InOrder(); // display all courses
            break; // exit case

        case 3: {
            cout << "Enter course number: "; // prompt for course number
            cin.ignore(); // clear input buffer
            string courseNum; // hold course number
            getline(cin, courseNum); // read full line
            courseNum = toUpper(trim(courseNum)); // convert input to Uppercase

            Course result = bst->Search(courseNum); // search for course
            if (!result.courseNumber.empty()) { // if course found
                displayCourse(result, *bst); // display course details
            }
            else {
                cout << "Course Id " << courseNum << " not found." << endl; // report not found
            }
            break; // exit case
        }

        case 9:
            cout << "Thank you for using the course planner!" << endl; // print exit message
            break; // exit case

        default:
            cout << choice << " is not a valid option." << endl; // handle invalid choice
            break; // exit case
        }
    }

    delete bst; // free BST memory
    cout << "Good bye." << endl; // print farewell message
    return 0; // exit program
}
