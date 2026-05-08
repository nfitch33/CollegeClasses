/***********************************************
 *
 *	Test cases for CS2401 Lab 6, Linked Lists2
 *	Made by Kyle Chiasson, kc428921@ohio.edu
 *	Last updated 2/19/2024
 *	For automatic grading to work, do not change this file.
 *	Students are encouraged to read through to understand project requirements, however.
 *
 * ********************************************/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "../header_lab6.h"

using namespace std;

node* ARRtoLL(int* arr, std::size_t len){
	if(len == 0)
		return nullptr;
	node* head = new node();
	head -> data = arr[0];
	head -> next = nullptr;
	node* ptr = head;
	for(size_t i = 1; i < len; i++){
		ptr -> next = new node();
		ptr = ptr -> next;
		ptr -> data = arr[i];
		ptr -> next = nullptr;
	}
	return head;
}
void LLtoARR(const node* head, int*& arr, std::size_t& len){
	len = 0;
	for(const node* ptr = head; ptr != nullptr; ptr = ptr -> next)
		len++;
	arr = new int[len];
	const node* ptr = head;
	for(size_t i = 0; i < len; i++){
		arr[i] = ptr -> data;
		ptr = ptr -> next;
	}
}
bool arrEquals(const int* arr1, std::size_t len1, const int* arr2, std::size_t len2){
	if(len1 != len2)
		return false;
	for(size_t i = 0; i < len1; i++)
		if(arr1[i] != arr2[i])
			return false;
	return true;
}
TEST_CASE("Remove Repeats"){
	SECTION("Empty Test"){
		node* head = ARRtoLL(new int[0], 0);
		remove_repeats(head);
		size_t oSize = 0;
		int* oArr = nullptr;
		LLtoARR(head, oArr, oSize);
		REQUIRE(arrEquals(new int[0], 0, oArr, oSize));
	}
	SECTION("Last Duplicate"){
		node* head = ARRtoLL(new int[20]{8, 6, 9, 4, 9, 7, 8, 6, 3, 5, 1, 0, 1, 8, 6, 6, 4, 1, 8, 1}, 20);
		remove_repeats(head);
		size_t oSize = 0;
		int* oArr = nullptr;
		LLtoARR(head, oArr, oSize);
		REQUIRE(arrEquals(new int[9]{8, 6, 9, 4, 7, 3, 5, 1, 0}, 9, oArr, oSize));
	}
	SECTION("Last Unique"){
		node* head = ARRtoLL(new int[20]{8, 6, 9, 4, 9, 7, 8, 6, 3, 5, 1, 0, 1, 8, 6, 6, 4, 1, 8, 2}, 20);
		remove_repeats(head);
		size_t oSize = 0;
		int* oArr = nullptr;
		LLtoARR(head, oArr, oSize);
		REQUIRE(arrEquals(new int[10]{8, 6, 9, 4, 7, 3, 5, 1, 0, 2}, 10, oArr, oSize));
	}
}
TEST_CASE("Split List"){
	SECTION("Empty Test"){
		node* head = ARRtoLL(new int[0], 0);
		node *less = nullptr, *more = nullptr;
		split_list(head, less, more, 5);
		size_t oLSize = 0, oMSize = 0;
		int *oLArr = nullptr, *oMArr = nullptr;
		LLtoARR(less, oLArr, oLSize);
		LLtoARR(more, oMArr, oMSize);
		REQUIRE(arrEquals(new int[0], 0, oLArr, oLSize));
		REQUIRE(arrEquals(new int[0], 0, oMArr, oMSize));
	}
	SECTION("Normal"){
		node* head = ARRtoLL(new int[9]{8, 6, 9, 4, 7, 3, 5, 1, 0}, 9);
		node *less = nullptr, *more = nullptr;
		split_list(head, less, more, 5);
		size_t oLSize = 0, oMSize = 0;
		int *oLArr = nullptr, *oMArr = nullptr;
		LLtoARR(less, oLArr, oLSize);
		LLtoARR(more, oMArr, oMSize);
		REQUIRE(arrEquals(new int[4]{4, 3, 1, 0}, 4, oLArr, oLSize));
		REQUIRE(arrEquals(new int[4]{8, 6, 9, 7}, 4, oMArr, oMSize));
	}
	SECTION("Number Not In List"){
		node* head = ARRtoLL(new int[9]{8, 6, 9, 4, 7, 3, 5, 1, 0}, 9);
		node *less = nullptr, *more = nullptr;
		split_list(head, less, more, 2);
		size_t oLSize = 0, oMSize = 0;
		int *oLArr = nullptr, *oMArr = nullptr;
		LLtoARR(less, oLArr, oLSize);
		LLtoARR(more, oMArr, oMSize);
		REQUIRE(arrEquals(new int[2]{1, 0}, 2, oLArr, oLSize));
		REQUIRE(arrEquals(new int[7]{8, 6, 9, 4, 7, 3, 5}, 7, oMArr, oMSize));
	}
	SECTION("Empty Lesser"){
		node* head = ARRtoLL(new int[9]{8, 6, 9, 4, 7, 3, 5, 1, 0}, 9);
		node *less = nullptr, *more = nullptr;
		split_list(head, less, more, -1);
		size_t oLSize = 0, oMSize = 0;
		int *oLArr = nullptr, *oMArr = nullptr;
		LLtoARR(less, oLArr, oLSize);
		LLtoARR(more, oMArr, oMSize);
		REQUIRE(arrEquals(new int[0], 0, oLArr, oLSize));
		REQUIRE(arrEquals(new int[9]{8, 6, 9, 4, 7, 3, 5, 1, 0}, 9, oMArr, oMSize));
	}
	SECTION("Empty Greater"){
		node* head = ARRtoLL(new int[9]{8, 6, 9, 4, 7, 3, 5, 1, 0}, 9);
		node *less = nullptr, *more = nullptr;
		split_list(head, less, more, 10);
		size_t oLSize = 0, oMSize = 0;
		int *oLArr = nullptr, *oMArr  = nullptr;
		LLtoARR(less, oLArr, oLSize);
		LLtoARR(more, oMArr, oMSize);
		REQUIRE(arrEquals(new int[9]{8, 6, 9, 4, 7, 3, 5, 1, 0}, 9, oLArr, oLSize));
		REQUIRE(arrEquals(new int[0], 0, oMArr, oMSize));
	}
}
TEST_CASE("Footer"){
	SECTION("Score") {
		std::cout << "\e[34m===============================================================================\e[0m\n";
		std::cout << "FOR ALL ERROR MESSAGES, THE FIRST VALUE IS THE ONE PROVIDED BY THE CLASS,\nAND THE SECOND VALUE IS THE DESIRED OUTPUT.\nSTART AT THE TOP AND WORK DOWNWARDS\n";
		std::cout << "\e[34m===============================================================================\e[0m\n";
	}
}