#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std; 

// struct to represent student info
struct StudentInfo {
    string name;
    int regNo;
    vector<pair<string, double>> courses;

    StudentInfo() : regNo(0) {}  //sets default value to avoid tuple err

    StudentInfo(const string& name, int regNo) : name(name), regNo(regNo) {}

    void addCourse(const string& courseName, double courseScore) {
        courses.push_back(make_pair(courseName, courseScore));
    }
};

// function to evaluate the grade 
char gradeCalculator(double score){
    if (score > 100)
        return 'X';
    else if (70 <= score && score <= 100)
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
void individualStudentInfo(ofstream& analysisFile, const StudentInfo& student, map<string, pair<double, int>>& courseStats){ 
    analysisFile << "Student: " << student.name << '\n' << "Reg No.: "<< student.regNo << '\n';
    double totalScore = 0.0;  //total score for the students
    map<string, double> courseTotalScore;  //stores the total score obtained by the student in each course 
    map<string, int> courseStudentCount;  //stores the number of students taking each course

    
    // to iterate over each course-score pair for the student & calculate total score and course totals
    for (const auto& courseData : student.courses) {
        double courseScore = courseData.second;
        char courseGrade = gradeCalculator(courseScore);
        analysisFile << "Course Name: " << courseData.first << ", Score: " << courseScore << ", Grade: " << courseGrade << "." << '\n';

        totalScore += courseScore; //adds the courses score to the totalScore var
       
        // updates the course stats
        courseStats[courseData.first].first += courseScore;  //adds the score of the current course to the total score for that course
        courseStats[courseData.first].second++;  //increments the count of students taking the current course by 1
    }

    // calculates and outputs the overall grade for the student 
    double overallScore = totalScore / student.courses.size();
    char overallGrade = gradeCalculator(overallScore);
    analysisFile << "Overall Score: " << overallScore << ", Overall Grade: " << overallGrade << "." << '\n';

    analysisFile << '\n' << '\n';   
}

// function to compute class averages for courses
void classAverages(ofstream& analysisFile, const map<string, pair<double, int>>& courseStats) {
    analysisFile << "Class Averages: \n";

    for (const auto& courseData : courseStats) {
        const string& courseName = courseData.first;
        double totalScore = courseData.second.first;  // total score obtained by all students in this course
        int numStudents = courseData.second.second;  // no. of students taking this course

        if (numStudents > 0) {
            double avgScore = totalScore / numStudents;
            char avgGrade = gradeCalculator(avgScore);
            analysisFile << "Average score for " << courseName << ": " << avgScore << ", Average Grade: " << avgGrade << '\n';
        } else {
            analysisFile << "No students took " << courseName << '\n';
        }
    }   
}

int main() {
    // read input file
    ifstream resultFile("results.txt");    

    // creates the output file
    ofstream analysisFile("analysis.txt");   

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

    // key is the student reg no and the value is the student details, map name is studentData
    map<int, StudentInfo> studentData;

    // key is the course name, value is total score and no. of students
    map<string, pair<double, int>> courseStats;

    // reads each line from the result.txt and parses the info into the line var
    string line;      
    while (getline(resultFile, line)) {      
        stringstream ss(line);  // creates stringstream object ss initialized with the current line read from the resultFile
        string name, course; 
        int regNo;
        double score;
        ss >> name >> regNo >> course >> score;  // extracts data from the stringstream and stores them in the declared variables
        
        // ccheks if the student is already in the map, if not, add them
        if (studentData.find(regNo) == studentData.end()) {
            studentData[regNo] = StudentInfo(name, regNo);
        }
        // Add the course and score to the student's information
        studentData[regNo].addCourse(course, score); 
    }

    // loops thru each element in the map studentData and student as args
    for (const auto& entry : studentData) {
        const StudentInfo& student = entry.second;
        individualStudentInfo(analysisFile, student, courseStats);
    }
    classAverages(analysisFile, courseStats);

    cout << "Exam analysis results have been written to analysis.txt" << '\n';

    return 0;
}
