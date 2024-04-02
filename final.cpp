#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std; 

// class for the Course
class Course {
public:
    string name;
    double score;

    Course(const string& name, double score) : name(name), score(score) {}
};

// class for the Students
// it enables the user to have more than one course under their name 
class Student {
public:
    string name;
    int regNo;
    vector<Course> courses;

    Student(const string& name, int regNo) : name(name), regNo(regNo) {}

    void addCourse(const string& courseName, double courseScore) {
        courses.push_back(Course(courseName, courseScore));
    }
};

// function to evaluate the grade 
char gradeCalculator(double score){
    if (score > 100)
        return 'X';
    else if (79 <= score && score <= 100)
        return 'A';
    else if (60 <= score && score <= 69)
        return 'B';
    else if (50 <= score && score <= 59)
        return 'C';
    else if (40 <= score && score <= 49)
        return 'D';
    else
        return 'F';
}

// function to output student info
void outputStudentInfo( ofstream& analysisFile, const string& studentName, const vector<pair<string, double>>& courses){ 
    analysisFile << "Student: " << studentName << '\n';
    double totalScore = 0.0;
    map<string, double> courseTotalScore; //stores the total score obtained by the student in each course 
    map<string, int> courseStudentCount;  //stores the number of students taking each course

    // iterates over each course-score pair for the given student  
    // calculates total score and course totals
    for (const auto& courseScore : courses) {
        double score = courseScore.second;
        char grade = gradeCalculator(score);
        analysisFile << "Course Name: " << courseScore.first << ", Score: " << score << ", Grade: " << grade << "." << '\n';

        totalScore += score; //adds the courses score to the totalScore var
        courseTotalScore[courseScore.first] += score;  //adds the score of the current course to the total score for that course
        courseStudentCount[courseScore.first]++; //increments the count of students taking the current course
    }

    // calculates and outputs the overall grade for the student 
    double overallGrade = totalScore / courses.size();
    char overallLetterGrade = gradeCalculator(overallGrade);
    analysisFile << "Overall Grade: " << overallGrade << ", Overall Letter Grade: " << overallLetterGrade << "." << '\n';

    // loops thru the courseTotalScore map and calculates the avgScore for each course 
    for (const auto& courseEntry : courseTotalScore) {
        double avgScore = courseEntry.second / courseStudentCount[courseEntry.first];
        char avgLetterGrade = gradeCalculator(avgScore);
        analysisFile << "Average score for " << courseEntry.first << ": " << avgScore << ", Average Grade: " << avgLetterGrade << '\n';
    }

    analysisFile << '\n';
}

int main() {
    ifstream resultFile("results.txt");    // read input file

    ofstream analysisFile("analysis.txt");   // creates the output file

    // checks if the file was read
    if(!resultFile){
        cerr << "Error: Unable to read the result file.";
        return 1;
    }

    // checks if the file was created 
    if(!analysisFile){
        cerr << "Error: Unable to create the output file.";
        return 1;
    }

    // creates a map in which the key-value pair is the student name and the value is the course and the score the map name is studentData
    map<string, vector<pair<string, double>>> studentData;

    // reads each line from the result.txt
    string line;      
    while (getline(resultFile, line)) {      
        stringstream ss(line);    // creates stringstream object ss initialized with the current line read from the resultFile
        string name, regNo, course; 
        double score;
        ss >> name >> regNo >> course >> score; // extracts data from the stringstream and stores them in the declared variables
        studentData[name].push_back(make_pair(course, score)); 
    }
    
    // loops thru each element in the map studentData and passes it as args to the outputStudentInfo function
    for (const auto& entry : studentData) {
        outputStudentInfo(analysisFile, entry.first, entry.second);
    }

    cout << "Exam analysis has been written to analysis.txt" << '\n';

    return 0;
}
