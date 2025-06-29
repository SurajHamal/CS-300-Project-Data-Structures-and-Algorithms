# **What was the problem you were solving in the projects for this course?**

The problem I was solving in these projects was to store, search, manage and retrieve course information with their prerequisites into suitable data structures by first analyzing their time complexity, memory usage and functionality to display the courses in alphanumeric order.

# **How did you approach the problem? Consider why data structures are important to understand?**

I approached the problem by creating the pseudocode for three different data structures to compare and evaluate their run time, memory, and advantages and disadvantages in our project case scenario to choose the appropriate data structure. Data structures are important and critical to understand as they directly affect the performance, scalability, and usability of the program. For example, I chose the Binary search tree data structure in my project because it has fast average insert, maintains sorted order, avoids and rejects duplication with the same course number, scalable to add more courses for the future and helps keep the data organized which is suitable for my course planner project.  

# **How did you overcome any roadblocks you encountered while going through the activities or project?**

One of the roadblocks I faced during this project was reading the datasets where course title and course name were mandatory, and the courses may have many prerequisites or none of the prerequisites. I overcame this challenge to parse each csv line and handle all edge cases by two pass file reading approach where the first pass collected all valid course numbers into a set and second pass build and inserted valid course objects into the BST making sure every prerequisite is referenced to a real course. I encountered other roadblocks by fixing logical errors through recursive calls ensuring left and right child pointers were assigned correctly based on course number comparisons.

# **How has your work on this project expanded your approach to designing software and developing programs?**

This project has expanded my ability to develop software by highlighting the importance of choosing the right data structures for specific tasks as it impacts performance, maintainability, scalability, and adaptability. Working on this project expanded my knowledge of trimming inputs, converting strings, using pointers appropriately after the insert and deletion, and recursively traversing trees to keep the data structures clean and modular. 

# **How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?**

This project has helped me to write maintainable, readable, and adaptable programs by enhancing my knowledge of various data structures, their time and space complexity, and taught me the ability and importance to choose appropriate data structure for a given task. I built the project using modular design by breaking down the codes into smaller reusable components, which made it easier to understand, maintain and adapt changes without affecting the entire system. Overall, the project enhanced my understanding of databases and algorithms, encouraged me to reuse the code components for efficiency and consistency, emphasized the importance of documentation and naming conventions which is crucial for future maintenance and collaboration, and encouraged me to use the industry-standard best practices of software developing lifecycle such as planning, coding, testing, and debugging. 

