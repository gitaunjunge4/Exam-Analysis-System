PSEUDOCODE

Define data structures to represent students, courses, and their scores

Read input files containing student scores and course information

Analyze scores to calculate average scores per student and per course

Assign grades based on predefined grading criteria

Calculate class average scores for students and courses

Write analysis results to an output file.



My Understanding

the system 
1. accepts a file that has 
-name of the students and their reg no. courses taken by the student and their score

2. reads the file
-checks if the file is created
-parses each line and stores it

3. create a function to perform the following other steps 

4. calculates the grades per course for the student
-passing the values through the grade calculator 

5. calculates the overall grade for the courses taken per student
-takes the summation of the individual grades for a student
-does the total/no. courses
-the value is run thru the grade calculator

6. calulates the average marks per course 
-takes the summation of indiviudal grades for students doing THE PARTICULAR course
-does the value/no of students
-the value is run thru the grade calculator

7. calulates the average score for the class
-takes the summation of average marks per course for students in THAT class
-does the value/no of students
-the value is run thru the grade calculator

outputs all this info into a file called analysis.text


outside functions
1.defines the grading system
2.outputs the data into the analysis text