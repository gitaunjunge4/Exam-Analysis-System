#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std; 

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
void outputStudentInfo(ofstream& analysisFile, const string& studentName, const vector<pair<string, double>>& courses){ 
    analysisFile << "Student: " << studentName << '\n';
    double totalScore = 0.0;  //total score for the students
    map<string, double> courseTotalScore; //stores the total score obtained by the student in each course 
    map<string, int> courseStudentCount;  //stores the number of students taking each course

    
    // to iterate over each course-score pair for the student & calculate total score and course totals
    for (const auto& courseData : courses) {
        double courseScore = courseData.second;
        char courseGrade = gradeCalculator(courseScore);
        analysisFile << "Course Name: " << courseData.first << ", Score: " << courseScore << ", Grade: " << courseGrade << "." << '\n';

        totalScore += courseScore; //adds the courses score to the totalScore var
        courseTotalScore[courseData.first] += courseScore;  //adds the score of the current course to the total score for that course
        courseStudentCount[courseData.first]++; //increments the count of students taking the current course by 1
    }

    // calculates and outputs the overall grade for the student 
    double overallScore = totalScore / courses.size();
    char overallGrade = gradeCalculator(overallScore);
    analysisFile << "Overall Score: " << overallScore << ", Overall Grade: " << overallGrade << "." << '\n';

    // // loops thru the courseTotalScore map and calculates the avgScore for each course 
    // for (const auto& courseEntry : courseTotalScore) {
    //     double avgScore = courseEntry.second / courseStudentCount[courseEntry.first];
    //     char avgLetterGrade = gradeCalculator(avgScore);
    //     analysisFile << "Average score for " << courseEntry.first << ": " << avgScore << ", Average Grade: " << avgLetterGrade << '\n';
    // }

    analysisFile << '\n' << '\n';
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

    // key is the student name and the value is the course and the score as a pair, map name is studentData
    map<string, vector<pair<string, double>>> studentData;

    // reads each line from the result.txt and parses the info into the line var for storage
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
        const string& studentName = entry.first;
        const vector<pair<string, double>>& courses = entry.second;
        outputStudentInfo(analysisFile, studentName, courses);
    }

    cout << "Exam analysis has been written to analysis.txt" << '\n';

    return 0;
}
