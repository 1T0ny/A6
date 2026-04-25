# A6

A6: Bloom Filters
CIS 350: Advanced Data Structures and Algorithms
Design and implement an efficient solution to check username availability for a new gaming
platform. Design a Bloom filter with filter size of 1000 bits and 2 hash functions. Pick any hash
functions you like. Preload your username database with some existing online database. Then
develop an UI for a sign up process. When user is asked to enter his/her preferred username, do a
duplicate check in your database. If found, prompt the user to enter a different choice, otherwise
add the newly added user to your database. Also implement to identify edge cases (e.g., empty
string, single character, extremely long username, non-alphanumeric characters and
whitespaces).
Submission:
• Your C++ code file (one file should include everything)
• Your database in CSV (make sure you have at least 10,000 preloaded users)
• Compare a random test for 100 username search with linear search
• A document in .pdf with problem discussion, pseudocode, flowcharts, implementation
details. Also include a complexity and runtime analysis compared with the test linear
search you did in the earlier step.
Rubric:
• Correctness (20): Accuracy and functionality of solutions.
• Design (20): The UI and nicety of the user’s experience.
• Creativity (20): Innovation in approach and effort to optimize solutions.
• Code Quality (20): Structure, readability, and adherence to best practices.
• Presentation (20): Clarity, formatting and thoroughness of documentation.
