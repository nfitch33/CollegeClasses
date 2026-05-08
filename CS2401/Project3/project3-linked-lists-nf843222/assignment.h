/**
 * @file assignment.h
 * 
 * This class stores the record of an assignment.
 * It includes the assignment's name, course, date created and due date
 * 
 * Overloaded comparison operators compare the due dates,
 * with less than meaning that the left operand is due before
 * the right operand (i.e. the student has less time to complete it).
 * 
 * Patricia Lindner		February 2024	OU EECS
 */

#include <iostream>
#include <string>
#include "date_time.h"

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H


class Assignment{
	public:
		/**
		 * @brief Construct a new Assignment object
		 * 
		 */
		Assignment();

		/**
		 * @brief Return the name member
		 * 
		 * @return std::string - the name of the assignment
		 */
		std::string get_name()const {return name;}

		/**
		 * @brief Return the course member
		 * 
		 * @return std::string - the course this assignment is for
		 */
        std::string get_course()const {return course;}

		/**
		 * @brief Return the entered member
		 * 
		 * @return DateTime - the date and time this assignment was entered
		 */
		DateTime get_entered()const {return entered;}

		/**
		 * @brief Return the due member
		 * 
		 * @return DateTime - the date and time the assignment is due
		 */
		DateTime get_due()const {return due;}

		/**
		 * @brief Less than operator that compares due dates.
		 * 
		 * @param ap - the assignment you are comparing to
		 * @return true - assignment is due before ap
		 * @return false - assignment is not due before ap
		 */
		bool operator < (const Assignment& ap)const {return due < ap.due;}

		/**
		 * @brief Greater than operator that compares due dates.
		 * 
		 * @param ap - the assignment you are comparing to
		 * @return true - assignment is due after ap
		 * @return false - assignment is not due after ap
		 */
		bool operator > (const Assignment& ap)const {return ap.due < due;}

		/**
		 * @brief Less than or equal to operator that compares due dates
		 * 
		 * @param ap - the assignment you are comparing to
		 * @return true - assignment is due before or at the same time as ap
		 * @return false - assignment is due after ap
		 */
		bool operator <= (const Assignment& ap)const {return !(ap.due < due);}

		/**
		 * @brief Greater than or equal to operator that compares due dates
		 * 
		 * @param ap - the assignment you are comparing to
		 * @return true - assignment is due after or at the same time as ap
		 * @return false - assignment is due before ap
		 */
		bool operator >= (const Assignment& ap)const {return !(due < ap.due);}

		/**
		 * @brief Not equal operator that compares due dates
		 * 
		 * @param ap - the assignment you are comparing to
		 * @return true - the assignments are not due at the same time and day
		 * @return false - the assignments are due at the same time and day
		 */
		bool operator != (const Assignment& ap)const {return (due < ap.due || ap.due < due);}

		/**
		 * @brief Equality operator that compares due dates
		 * 
		 * @param ap - the assignment you are comparing to
		 * @return true - the assignments are due on the same day at the same time
		 * @return false - the assignments are not due at the same time or on the same day
		 */
		bool operator == (const Assignment& ap)const {return !(due < ap.due || ap.due < due);}
		
		/**
		 * @brief Determine the number of minutes until an assignment is due
		 * 
		 * @return unsigned - the number of minutes until the assignment is due, 0 if it is past due
		 */
		unsigned minutes_til_due()const;

		/**
		 * @brief Determine the number of minutes an assignment has been waiting to be completed
		 * 
		 * @return unsigned - the number of minutes since the assignment was added
		 */
        unsigned minutes_waiting()const;

		/**
		 * @brief Read in the data for a single assignment object
		 * 
		 * @param ins - the stream to read data from
		 */
		void input(std::istream& ins);

		/**
		 * @brief Output the data for a single assignment object
		 * 
		 * @param outs - the stream to write data to
		 */
		void output(std::ostream& outs)const;

	private:
		std::string name;
        std::string course;
		DateTime entered;
		DateTime due;
};

/**
 * @brief Output a large number of minutes as Days, hours, minutes
 * 
 * @param m - the number of minutes to convert
 */
void convert_minutes(unsigned m);

/**
 * @brief Overloaded extraction operator for assignments
 * 
 * @param ins - the stream to read data from
 * @param ap - the assignment to read the data into
 * @return std::istream& - the stream that was passed in
 */
std::istream& operator >> (std::istream& ins, Assignment& ap);

/**
 * @brief Overloaded insertion operator for assignments
 * 
 * @param outs - the stream to write data to
 * @param ap - the assignment who's data you want to output
 * @return std::ostream& - the stream that was passed in
 */
std::ostream& operator << (std::ostream& outs, const Assignment& ap);

#endif