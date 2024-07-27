//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <fstream>
using namespace std;

void fullscreen() { //To launch program in full screen
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void UI() {
	fullscreen();
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 400); //To change UI color
	system("mode 650");
	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 610;
	fontex.dwFontSize.X = 36;
	fontex.dwFontSize.Y = 36;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex); // To change UI font

	cout << "\n\n\n\n\n\n\n\n\t\t\t\t\tWELCOME TO SIS\n\n\n\t\t\t\t ";
	system("pause"); //To pause program until a key is pressed
	system("cls"); //To clear the previous output

}

struct Course;
struct EnrolledCourse {
	Course* courseReference;
	EnrolledCourse* next;
	EnrolledCourse* previous;
};
struct EnrolledCourseList {
	EnrolledCourse* head, * tail;
};
struct Student {
	int studentID;
	char firstName[30], lastName[30], emailAddress[50];
	EnrolledCourseList* enrolledCourses;
	Student* next;
};
struct UniversityStudentList {
	Student* head;
};
struct EnrolledStudent {
	Student* studentReference;
	EnrolledStudent* next;
};
struct EnrolledStudentList {
	EnrolledStudent* head;
};
struct Course {
	int courseID, courseCapacity;
	char courseName[50], instructorName[50];
	string timeSchedule;
	EnrolledStudentList* attendees;
	Course* next;
	Course* previous;
};
struct UniversityCourseList {
	Course* head, * tail;
};

void InsertDoublyTail(UniversityCourseList*& L, Course* cur) {
	cur->previous = NULL;
	if (L->head == NULL) { L->head = cur; L->tail = cur; }
	else {
		cur->previous = L->tail;
		L->tail->next = cur;
	}
	L->tail = cur;
}
void InsertAtTail(UniversityStudentList*& L, Student* s) {
	s->next = NULL;
	if (L->head == NULL) {
		L->head = s; return;
	}
	Student* cur = L->head;
	while (cur->next != NULL) {
		cur = cur->next;
	} 
	cur->next = s;
}

void ReadCourse(UniversityCourseList*& L) {
	fstream f("courses.csv");	
	string s; int i = 0, j = -1;
	Course* cur;
	while (f) {
		cur = new Course;
		cur->next = NULL;
		if (i > 0)j = cur->courseID; 
		f >> cur->courseID; if (cur->courseID == j)break;
		f.ignore(1);
		f >> cur->courseCapacity;
		f.ignore(1);
		getline(f, s, ','); strcpy_s(cur->courseName, s.c_str()); // Copying from string to char array
		getline(f, s, ','); strcpy_s(cur->instructorName, s.c_str());
		getline(f, cur->timeSchedule, '\n');
		InsertDoublyTail(L, cur);
		cur = cur->next; i++;
	}f.close();
}
//Test
void Display_Enrolled_C(Student* st) {   
	EnrolledCourse* cur = st->enrolledCourses->head;
	cout << endl << "Student Name: " << st->firstName;
	while (cur != NULL) {
		cout << endl << "CourseID: " << cur->courseReference->courseID;
		cout << endl << "Course Name: " << cur->courseReference->courseName;
		cur = cur->next;
	} Sleep(100000);
}
void Displays(UniversityStudentList*& L) {
	Student* cur = new Student;
	cur = L->head;
	while (cur != NULL) {
		cout << cur->studentID << "<==>";
		cur = cur->next;
	}
	if (cur == NULL)
		cout << "NULL";
}//Test

bool ifexist(string e, int& sid) {
	string str, adr; int s, i = 0, j = -1;
	fstream file("students.csv"); //initialising
	while (file) {
		if (i > 0) j = s;
		file >> s; file.ignore(1); if (s == j)break; sid = s;
		getline(file, str, ',');
		getline(file, str, ',');
		getline(file, adr, '\n'); i++; //email address
		if (adr == e)return true;
	}file.close();
	return false;
}

bool emailcheck(string c) {
	int i = 0, a = c.find("@"), b = c.find(".");
	if ((isalnum(c[0])) && (c.at(c.length() - 1) != '.'))i++; //first char has to be alpha or num and last can't be '.'
	if ((a != string::npos) && (b != string::npos))i++; //to check if '@' and '.' exist

	for (int j = 0; j < c.length(); j++) {
		if (c[j] == '@')a = j;
		else if (c[j] == '.') b = j;
	}if (a < b)i++;   // '.' must be after the '@'

	if (i == 3) return true;
	return false;
}

int idcount() {
	string str;
	int ID = -1, row = 0;
	fstream file("students.csv");
	while (file) {
		file >> ID;
		getline(file, str, '\n'); //to finish the line
		row++;
	}file.close();
	if (ID == -1) return 1;
	else return row;
}
void nameinp(Student*& s) {
	do {
		system("cls");
		cout << "New account creation in process \n\n"
			<< "First and last name must both contain at least 1 character\n\n\nPlease enter your first name:";
		cin.getline(s->firstName, 29);
		cout << endl << "Please enter your last name:";
		cin.getline(s->lastName, 29);
	} while ((strlen(s->firstName) < 1) || (strlen(s->lastName) < 1));
}

void userinput(Student*& s) {
	system("cls");
	if (strlen(s->emailAddress) > 1)
	{
		cout << "New account creation in process\n\nFirst name entered:" << s->firstName << "\n\n"
			<< "Last name entered:" << s->lastName << "\n\nEmail address entered:" << s->emailAddress << "\n\n";
	}
}

void readStudents(UniversityStudentList*& L) {
	int i = 0, j = -1;
	Student* s;
	string str;
	fstream file("students.csv"); //initialising
	while (file) {
	    s = new Student;
		if (i > 0) j = s->studentID;
		file >> s->studentID; if (s->studentID == j)break; //ID
		file.ignore(1);
		getline(file, str, ','); strcpy_s(s->firstName, str.c_str()); //Fname 
		getline(file, str, ','); strcpy_s(s->lastName, str.c_str()); //Lname
		getline(file, str, '\n'); strcpy_s(s->emailAddress, str.c_str()); //Email
		InsertAtTail(L, s); i++;
	}file.close();
	
}
void exportStudents(UniversityStudentList*& L) {
	Student* cur = new Student;
	cur = L->head;
	fstream file("students.csv", ios::out);
	while (cur != NULL) { 
		file << cur->studentID << "," << cur->firstName << "," << cur->lastName << "," << cur->emailAddress << "\n";
		cur = cur->next;
	}file.close();
}
void signup(UniversityStudentList *&L, int& sid) {
	int i = 0, j = 0;
	Student* s = new Student;
	s->next = NULL;
	s->studentID = idcount();
	nameinp(s);
	cout << "\nPlease enter your email address:";
	do {
		if (j > 0)cout << "\nAn account associated with this email address already exists\nPlease re-enter your email address:";
		do {
			if (i > 0) cout << "\nInvalid email. Please re-enter your email address:";
			cin.getline(s->emailAddress, 49); userinput(s);
			i++;
		} while (emailcheck(s->emailAddress) == false);
		j++; i = 0;
	} while (ifexist(s->emailAddress, sid));
	readStudents(L);    //Reading file and copying it to the List
	InsertAtTail(L, s); //Inserting new Student at List tail
	exportStudents(L);  //Inserting List into Student file (Updating file with new Student)
	cout << "\n\n\n\n\n\t\t\t\tStudent Successfully Registered";
	Sleep(3000);
}
bool login(int& sid) {
	int i = 0;
	string em;
	system("cls");
	cout << "\n\nPlease enter your email address:";
	do {
		if (i > 0) { system("cls"); cout << "\n\nInvalid email. Please re-enter your email address:"; }
		getline(cin, em); i++;
	} while (emailcheck(em) == 0); system("cls"); cout << "\n\nEmail entered:" << em;
	if (ifexist(em, sid)) {
		cout << "\n\n\nStudent Logged in Successfully"; Sleep(3000); system("cls"); return 1;
	}
	cout << "\n\n\nStudent does not exist"; Sleep(3000); system("cls"); return 0;
}

EnrolledCourse* sortlist(EnrolledCourseList* ec) {
	EnrolledCourse* temp = new EnrolledCourse;
	EnrolledCourse* cur = new EnrolledCourse;
	cur = ec->head;
	EnrolledCourse* cur2 = new EnrolledCourse;
	while (cur != NULL) {
		cur2 = ec->head;
		while (cur2 != NULL) {
			if (cur->courseReference->courseName[0] < cur2->courseReference->courseName[0]) {
				temp->courseReference = cur->courseReference;
				cur->courseReference = cur2->courseReference;
				cur2->courseReference = temp->courseReference;
			}cur2 = cur2->next;
		}cur = cur->next;
	}
	return ec->head;
}

void Display_Your_sch(Student* st) {
	system("cls");
	cout << "\n\t\t\t\t\tCourses Schedule:\n\n"
		<< "\n-------------------------------------------------------------------------------------------------"
		<< "\n|    ID     |   Capacity   |         Name         |     Instructor     |     Time Schedule      |"
		<< "\n-------------------------------------------------------------------------------------------------";
	EnrolledCourse* cur = sortlist(st->enrolledCourses);
	while (cur != NULL) {
		cout << "\n|" << setw(6) << cur->courseReference->courseID << "     |" << setw(8) << cur->courseReference->courseCapacity << "      |";
			if (strlen(cur->courseReference->courseName) <= 8) cout << setw(15) << cur->courseReference->courseName << "       |";
			else cout << setw(18) << cur->courseReference->courseName << "    |";
		cout << setw(12) << cur->courseReference->instructorName << "        |" << setw(21) << cur->courseReference->timeSchedule << "   |";
		cout << "\n-------------------------------------------------------------------------------------------------";
		cur = cur->next;
	}cout << "\n\n";
}

void Display_Course_enr(Course* c) {
	system("cls");
	cout << "\n\t\t\t   ---------------------------------------------"
		<< "\n\t\t\t   |      Course ID     |      Course Name     |"
		<< "\n\t\t\t   ---------------------------------------------"
		<< "\n\t\t\t   |" << setw(11) << c->courseID << "         |";
	if (strlen(c->courseName) <= 8) cout << setw(15) << c->courseName << "       |";
	else cout << setw(18) << c->courseName << "    |";
	cout << "\n\t\t\t   ---------------------------------------------";

	cout << "\n\n\t\t\t\t\tEnrolled Students:\n\n"
		<< "\n-------------------------------------------------------------------------------------------------"
		<< "\n|          Student ID          |       Student First Name       |       Student Last Name       |"
		<< "\n-------------------------------------------------------------------------------------------------";
	EnrolledStudent* es = new EnrolledStudent;
	es = c->attendees->head;
	while (es != NULL) {
		cout << "\n|" << setw(16) << es->studentReference->studentID << "              |";
		if (strlen(es->studentReference->firstName) <= 8) cout << setw(19) << es->studentReference->firstName << "             |";
		else cout << setw(20) << es->studentReference->firstName << "    |";
		if (strlen(es->studentReference->lastName) <= 8) cout << setw(19) << es->studentReference->lastName << "            |";
		else cout << setw(18) << es->studentReference->lastName << "    |";
		cout << "\n-------------------------------------------------------------------------------------------------";
		es = es->next;
	}cout << "\n\n"; system("pause");
}

Course* get_course_by_id(UniversityCourseList*& CL, int cid) {
		Course* c = new Course;
		c = CL->head;
		while (c != NULL) {
			if (cid == c->courseID) return c;
			c = c->next;
		}
}

bool if_course_exist(UniversityCourseList* CL, int cid) {
	Course* c = new Course;
	c = CL->head;
	while (c != NULL) {
		if (cid == c->courseID) return 1;
		c = c->next;
	}return 0;
}

void checkint(int& n) {
	while (1) {
		if (cin >> n)break; // valid number
		else { cout << "Invalide number, please re-enter:"; cin.clear(); while (cin.get() != '\n'); }
	}
}

void display_course_options(UniversityCourseList* CL) {
	int cid;
	Course* cur = CL->head; 
	system("cls");
	cout << "\n\t\t\t\t\tUniversity Courses:\n\n"
		<< "\n\t\t\t   ---------------------------------------------"
		<< "\n\t\t\t   |      Course ID     |      Course Name     |"
		<< "\n\t\t\t   ---------------------------------------------";
	while (cur != NULL) {
		cout << "\n\t\t\t   |" << setw(11) << cur->courseID << "         |";
			if (strlen(cur->courseName) <= 8) cout << setw(15) << cur->courseName << "       |";
		else cout << setw(18) << cur->courseName << "    |";
		cout << "\n\t\t\t   ---------------------------------------------";
		cur = cur->next;
	}cout << "\n\n";
	cid = 0;
	cout << "\t\t\t\t       Enter Course ID: ";
	checkint(cid); if (if_course_exist(CL, cid)) Display_Course_enr(get_course_by_id(CL, cid));
	else { cout << "\t\t\t\t       Course ID Not Found"; Sleep(3000); }
}

void display_instructor_courses(UniversityCourseList* CL, string name, int& cid, int i) {
	Course* cur = CL->head;
	system("cls");
	cout << "\n\t\t\t\t\tInstructor Courses:\n\n"
		<< "\n\t\t\t   ---------------------------------------------"
		<< "\n\t\t\t   |      Course ID     |      Course Name     |"
		<< "\n\t\t\t   ---------------------------------------------";
	while (cur != NULL) {
		if (cur->instructorName == name) {
			cout << "\n\t\t\t   |" << setw(11) << cur->courseID << "         |";
			if (strlen(cur->courseName) <= 8) cout << setw(15) << cur->courseName << "       |";
			else cout << setw(18) << cur->courseName << "    |";
			cout << "\n\t\t\t   ---------------------------------------------";
		}cur = cur->next;
	}cout << "\n\n";
	if (i == 1) {
		cid = 0;
		cout << "\t\t\t\t Enter Course ID: ";
		checkint(cid); if (if_course_exist(CL, cid)) Display_Course_enr(get_course_by_id(CL, cid));
		else { cout << "\t\t\t\t       Course ID Not Found"; Sleep(3000); }
	}
}


void menu1() {
	cout << "\n\t\t\t >>>>>>>>>  Student Information System  <<<<<<<<<\n\n\n"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   1:   To log in with an existing account"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   2:   To create an account for new Student"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   3:   To log in as instructor"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   4:   To exit program"
		<< "\n\t\t\t------------------------------------------------\t\t\t\t";
}
void menu2() {
	cout << "\n\t\t\t >>>>>>>>>  Student Enrollement Menu  <<<<<<<<<\n\n\n"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   1:   To Check your Courses Schedule"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   2:   To Check Enrolled Students"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   3:   To Enroll In a Course"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   4:   To Drop a Course"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   5:   To Swap a Course"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   6:   To Check for Grades"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   7:   To Log Out"
		<< "\n\t\t\t------------------------------------------------\t\t\t\t";
}
void menu3() {
	cout << "\n\t\t\t >>>>>>>>>  Instructor Menu  <<<<<<<<<\n\n\n"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   1:   To Check your Courses"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   2:   To do classs attendance"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   3:   To grade students"
		<< "\n\t\t\t------------------------------------------------"
		<< "\n\t\t\tPRESS   4:   To Log Out"
		<< "\n\t\t\t------------------------------------------------\t\t\t\t";
}
void close() {
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "\n\t\t\t     ----------------------------------------\n";
	cout << "\t\t\t\t THANKS FOR USING THIS SOFTWARE";
	cout << "\n\t\t\t     ----------------------------------------\n";
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
	exit(0);
}

void find_student_by_id(int sid, Student* student, Course*& c, EnrolledStudentList* ES) { //To find the student from all students by id and fill it in the course enrolled student list
	EnrolledStudent* es = new EnrolledStudent;
	es->next = NULL; EnrolledStudent* cur = new EnrolledStudent;
	if (ES->head == NULL) { ES->head = es; }
	else {
		cur = ES->head;
		while (cur->next != NULL) {
			cur = cur->next;
		}cur->next = es;
	}
	while (student != NULL) {
		if (sid == student->studentID) {
			c->attendees = ES;
			es->studentReference = student;
		}
		student = student->next;
	}
}

void find_course_by_id(Student*& st, Course* c, EnrolledCourseList* EC, int id) { //finding course by id to put it in the student enrolled courses list
	EnrolledCourse* ec = new EnrolledCourse;
	ec->next = NULL; ec->previous = NULL;
	Course* cur = c;
	if (EC->head == NULL) { EC->head = ec; EC->tail = ec; }
	else {
		ec->previous = EC->tail;
		EC->tail->next = ec;
	}EC->tail = ec;
	cur = c;
	while (cur != NULL) {
		if (id == cur->courseID) {
			ec->courseReference = cur;
			st->enrolledCourses = EC;
		}
		cur = cur->next; 
	}
}

void fill_enr_c_in_s(UniversityStudentList*& SL, UniversityCourseList*& CL) { //filling the enrolled courses in the students enrolled courses list
	int i = 0, j = -1, id = 0, sid = 0;
	Student* st = SL->head;
	Course* c = CL->head;
	string str, s;
	fstream file("enrollement.csv");
	while (st != NULL) {
		EnrolledCourseList* E = new EnrolledCourseList;
		E->head = NULL; E->tail = NULL; st->enrolledCourses = E;
		sid = st->studentID;
		while (file) {
			if (i > 0) j = id;
			file >> id; if (id == j)break;// Course ID
			file.ignore(1);
			getline(file, str, '\n'); str = str.substr(0, (str.find(",,"))); str = "," + str + ","; //we save the line of student ids in a string
			s = to_string(sid); s = "," + s + ","; //placing in s ",id," to check in str if student is enrolled
			if (str.find(s) != string::npos) // checking if ids are in the row/str
				find_course_by_id(st, c, E, id);
			i++;
		}st = st->next;
		file.clear();
		file.seekg(0);
	}file.close();
}

void fill_enrollement(UniversityStudentList*& SL, UniversityCourseList*& CL) { //To Read data from enrollement database to fill the course list with enrolled students
	int i = 0, j = -1, id = 0, sid = 0;
	Course* c = CL->head; 
	string str, s;
	Student* student = new Student;
	fstream file("enrollement.csv"); //initialising
	while (c != NULL) { //while that goes through the univ courses
		EnrolledStudentList* ES = new EnrolledStudentList;
		ES->head = NULL; c->attendees = ES;
		student = SL->head;
		while (file) { //while that goes through the file courses
			if (i > 0) j = id;
			file >> id; if (id == j) { break; } // Course ID
			file.ignore(1);
			if (id == c->courseID) { //if the course is enrolled by any students
				getline(file, str, '\n'); str = str.substr(0, (str.find(",,"))); //we save the line of student ids in a string
				stringstream s(str); //we cut the string into different strings seperated by ','
				while (getline(s, str, ',')) { //we go through the ids of students by ',' as delimiter
					sid = stoi(str); //we transform the string id to integer
					find_student_by_id(sid, student, c, ES); //we find the students by id and make the enrolled student list in each course
				}
			}else getline(file, str, '\n');
			i++;
		} c = c->next; 
		file.clear(); file.seekg(0); //To get back to pos 0 in file
	}file.close(); fill_enr_c_in_s(SL,CL);
}

void update_enrollement(UniversityCourseList* C) {
	Course* c = C->head;
	fstream file("new.csv", ios::out);
	while (c != NULL) {
			file << c->courseID << ",";
			EnrolledStudent* s = c->attendees->head;
			while (s != NULL) {
				file << s->studentReference->studentID << ",";
				s = s->next;
			}file << "\n";
			c = c->next;
	}file.close();
	remove("enrollement.csv");
	rename("new.csv", "enrollement.csv");
}

Student* get_student_by_id(UniversityStudentList*& L, int sid) {
	Student* cur = new Student;
	cur = L->head;
	while (cur != NULL) {
		if (cur->studentID == sid) return cur;
		cur = cur->next;
	}
}

void enroll_student_in_list(Student*& s, UniversityCourseList*& CL, int cid) {
	EnrolledCourse* cur = s->enrolledCourses->head;
	EnrolledCourse* course = new EnrolledCourse;
	course->next = NULL;
	course->courseReference = get_course_by_id(CL, cid);
	if (cur == NULL) {
		cur = course; s->enrolledCourses->tail = course;
	}
	else {
		while (cur->next != NULL) {
			cur = cur->next;
		} course->previous = cur;
		cur->next = course;
		s->enrolledCourses->tail = course;
	}
	EnrolledStudent* student = new EnrolledStudent;
	student->studentReference = s;
	student->next = NULL;
	Course* c = new Course; c = CL->head;
	while (c != NULL) {
		if (cid == c->courseID) {
			EnrolledStudent* cur2 = new EnrolledStudent;
			cur2 = c->attendees->head;
			if (cur2 == NULL) cur2 = student;
			else {
				while (cur2->next != NULL) {
					cur2 = cur2->next;
				}cur2->next = student;
			}
		}
		c = c->next;
	}
}

bool is_not_enrolled(Student* s, int cid) {
	EnrolledCourse* cur = new EnrolledCourse;
	cur = s->enrolledCourses->head;
	while (cur != NULL) {
		if (cid == cur->courseReference->courseID) return 0;
		cur = cur->next;
	}return 1;
}
bool is_not_a_course(UniversityCourseList* CL, int cid) {
	Course* cur = new Course;
	cur = CL->head;
	while (cur != NULL) {
		if (cid == cur->courseID) return 0;
		cur = cur->next;
	}return 1;
}
bool is_not_a_student(UniversityStudentList* SL, int sid) {
	Student* cur = new Student;
	cur = SL->head;
	while (cur != NULL) {
		if (sid == cur->studentID) return 0;
		cur = cur->next;
	}return 1;
}

void drop(Student* st, int cid) {
	int id = 0, j = -1, i = 0;
	string str, s, string;
	if (is_not_enrolled(st, cid) == 0) {
		fstream file("enrollement.csv");
		fstream f("new.csv", ios::out);
		while (file) {
			if (i > 0) j = id;
			file >> id; if (id == j)break;// Course ID
			file.ignore(1);
			getline(file, str, '\n'); str = str.substr(0, (str.find(",,"))); str = "," + str + ","; //we save the line of student ids in a string
			s = to_string(st->studentID); s = "," + s + ","; //placing in s ",id," to check in str if student is enrolled
			if (str.find(s) != string::npos && id == cid) { // checking if ids are in the row/str
				string = str.substr(0, (str.find(s))) + str.substr(str.find(s) + s.length() - 1, str.length());
				f << id << string << '\n';
			}
			else {
				f << id << str << '\n';
			}i++;
		}file.close(); f.close();
		remove("enrollement.csv");
		rename("new.csv", "enrollement.csv");

		cout << endl << "Successfully dropped"; Sleep(2000);
	}
	else { cout << endl << "Course ID not found or not enrolled"; Sleep(2000); }
}

void drop_course(Student*& st) {
	Display_Your_sch(st);
	if (st->enrolledCourses->head == NULL) { cout << endl << "You are not enrolled in any courses yet."; system("pause"); return; }
	int cid = 0;
	cout << endl << "Please Enter the Course ID to Drop: "; checkint(cid);
	drop(st, cid);
}

void swap_course(Student*& st, UniversityCourseList* &CL, UniversityStudentList* &S) {
	if (st->enrolledCourses->head == NULL) { cout << endl << "You are not enrolled in any courses yet."; system("pause"); return; }
	int cid = 0, cid2 = 0, id = 0, j = -1, i = 0;
	string str, s, string;
	cout << endl << "Please Enter the Enrolled Course ID to Swap: "; checkint(cid);
	cout << endl << "Please Enter the Course ID to Swap with Enrolled: "; checkint(cid2);
	if (is_not_enrolled(st, cid) == 0 && is_not_enrolled(st, cid2) && is_not_a_course(CL, cid2) == 0) {
		drop(st, cid);
		fill_enrollement(S, CL);
		enroll_student_in_list(st, CL, cid2);
		update_enrollement(CL);
	}
	else {
		cout << endl << "Course IDs not found or not enrolled"; Sleep(2000); return;
	}
	update_enrollement(CL); cout << endl << "Successfully Swapped"; Sleep(2000);

}

bool capacity_full(UniversityCourseList *CL, int cid) {
	Course* c = get_course_by_id(CL, cid); int i = 0;
	EnrolledStudent* cur = c->attendees->head;
	while (cur != NULL) {
		i++;
		cur = cur->next;
	}
	if (c->courseCapacity == i) return 1;
	return 0;
}

void display_courses_to_enroll(Student*& s, UniversityCourseList*& CL) {
	system("cls"); int i = 0, cid = 0;
		cout << "\n\t\t\t\t\tCourses to Enroll:\n\n"
			<< "\n-------------------------------------------------------------------------------------------------"
			<< "\n|    ID     |   Capacity   |         Name         |     Instructor     |     Time Schedule      |"
			<< "\n-------------------------------------------------------------------------------------------------";
		Course* c = new Course;
		c = CL->head;
		while (c != NULL) {
			if (is_not_enrolled(s, c->courseID)) {
				i = 1;
				cout << "\n|" << setw(6) << c->courseID << "     |" << setw(8) << c->courseCapacity << "      |";
				if (strlen(c->courseName) <= 8) { cout << setw(15) << c->courseName << "       |"; }
				else { cout << setw(18) << c->courseName << "    |"; }
				cout << setw(12) << c->instructorName << "        |" << setw(21) << c->timeSchedule << "   |";
				cout << "\n-------------------------------------------------------------------------------------------------";
			} c = c->next;
		}cout << "\n\n";
		if (i == 0) { cout << endl << "You are already enrolled in all courses."; system("pause"); }
		else {
			cout << endl << "Please Enter the Course ID to Enroll: "; checkint(cid);
			if (is_not_enrolled(s, cid) == 0 || is_not_a_course(CL, cid) || capacity_full(CL, cid)) {
				cout << endl << "Course ID not found or capacity exceeded already enrolled"; Sleep(2000); return;
			}
			enroll_student_in_list(s, CL, cid);
			update_enrollement(CL); cout << endl << "Successfully enrolled"; Sleep(2000);
	    }
}

bool instructor_login(string& name) {
	system("cls");
	string str;
	cout << endl << "Enter Instructor Name: ";
	getline(cin, name);
	fstream file("courses.csv");
		while (file) {
			getline(file, str, ',');
			getline(file, str, ',');
			getline(file, str, ',');
			getline(file, str, ',');
			if (name == str) {
				cout << endl << "Instructor logged in"; Sleep(2000);
				return true;
			}
		}file.close();	 cout << endl << "Instructor not found"; Sleep(2000); return false;
}

bool file_is_empty(fstream &f) {
	f.seekg(0, ios::end);
	if (f.tellg() == 0) {
		return true;
	}return 0;
}

bool s_is_not_enrolled(Student* s, int cid) {
	EnrolledCourse* cur = new EnrolledCourse;
	cur = s->enrolledCourses->head;
	while (cur != NULL) {
		if (cid == cur->courseReference->courseID) return 0;
		cur = cur->next;
	}return 1;
}

void add_grades(UniversityStudentList*& S, UniversityCourseList*& C, int cid, string name) {
	int sid;
	display_instructor_courses(C, name, cid, 1);
	cout << endl << "Enter Student ID to grade: "; checkint(sid);
	if (is_not_a_student(S, sid) || s_is_not_enrolled(get_student_by_id(S, sid), cid)) { cout << endl << "Student does not exist or not enrolled in your course"; Sleep(2000); return; }
	cout << endl << "Enter Grade for the Student: "; int grade; checkint(grade);
	fstream file("grades.csv", ios::out);
	file << cid << "," << sid << "," << grade << "\n";
	file.close(); cout << endl << "Grade Entered Successfully"; Sleep(2000);
}

void check_grades(Student* s, UniversityCourseList* CL) {
	Display_Your_sch(s); int cid, i = 0, j = -1, c, sid, grd; string str;
	cout << endl << "Enter the course ID to check grade: "; checkint(cid);
	if (is_not_enrolled(s, cid) || is_not_a_course(CL, cid)) { cout << endl << "Course does not exist or not enrolled"; Sleep(2000); return; }
	fstream f("grades.csv");
		while (f) {
			if(i > 0) j = c;
			f >> c; f.ignore(1); if (c == j)break;
			f >> sid; f.ignore(1);
			f >> grd; f.ignore(1);
			if (c == cid && sid == s->studentID) {
				cout << endl << "Your Grade is " << grd; Sleep(2000); return;
			}	getline(f, str, '\n');
			i++;
		}f.close(); cout << "No Grades Found"; Sleep(2000); return;
}

void instructor(UniversityStudentList*& S, UniversityCourseList*& C, string name) {
	char choice = 0; int c = 0, cid = 0;
	do {
		system("cls");
		menu3();
		if (c == 0)choice = _getch();//function takes single character as an input (doesn't need "Enter" key to be pressed)
		switch (choice)
		{
		case '1':
			display_instructor_courses(C, name, cid, 0);
			system("pause");
			break;
		case '2':
			display_instructor_courses(C, name, cid, 1);
			break;
		case '3':
			add_grades(S, C, cid, name);
			break;
		case '4':
			return;
			break;
		default:
			system("cls"); menu3();
			cout << "\n\n\n\t\t\t" << choice << " is not a Valid Choice, please choose again \t\t\t\t\t\t";
			choice = _getch();
			c = 1;
			break;
		}
	} while (choice); //To get back to menu after break
}
void student(UniversityStudentList*& S, UniversityCourseList*& C, int sid) {
	char choice = 0; int c = 0;
	Student* s = get_student_by_id(S, sid);
	do {
		system("cls");
		menu2();
		if (c == 0)choice = _getch();//function takes single character as an input (doesn't need "Enter" key to be pressed)
		switch (choice)
		{
		case '1':
			Display_Your_sch(s);
			system("pause");
			break;
		case '2': 
			display_course_options(C);
			//display list of students enrolled in a particular course
			break;
		case '3':
			display_courses_to_enroll(s, C);
			fill_enrollement(S, C);
			//enroll
			break;
		case '4':
			drop_course(s);
			fill_enrollement(S, C);
			//drop
			break;
		case '5':
			Display_Your_sch(s);
			swap_course(s, C, S);
			fill_enrollement(S, C);
			//swap
			break;
		case '6':
			check_grades(s, C);
			break;
		case '7':
			return;
			break;
		default:
			system("cls"); menu2();
			cout << "\n\n\n\t\t\t" << choice << " is not a Valid Choice, please choose again \t\t\t\t\t\t";
			choice = _getch();
			c = 1;
			break;
		}
	} while (choice); //To get back to menu after break
}
int main() {
	UI();
	char choice = 0;
	UniversityCourseList* C = new UniversityCourseList;
	UniversityStudentList* S = new UniversityStudentList;
	EnrolledCourseList* EC = new EnrolledCourseList;
	EnrolledStudentList* ES = new EnrolledStudentList;
	EC->head = NULL; EC->tail = NULL; ES->head = NULL;
	C->head = NULL; C->tail = NULL; S->head = NULL; string name;
	int c = 0, sid = 0;
	ReadCourse(C);
	readStudents(S);
	fill_enrollement(S, C);
	do {
		system("cls");
		menu1();
		if (c == 0) choice = _getch(); //function takes single character as an input (doesn't need "Enter" key to be pressed)
		switch (choice)
		{
		case '1':
			fill_enrollement(S, C);
			if (login(sid))student(S, C, sid);
			break;
		case '2':
			signup(S, sid);
			system("cls");
			break;
		case '3':
			if (instructor_login(name)) {
				instructor(S, C, name);
			}
			break;
		case '4':
			close();
			break;
		default:
				system("cls"); menu1();
				cout << "\n\n\n\t\t\t" << choice << " is not a Valid Choice, please choose again \t\t\t\t\t\t";
				choice = _getch();
				c = 1;
			break;
		}
	} while (choice);
}
