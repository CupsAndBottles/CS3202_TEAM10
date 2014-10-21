#pragma once

#include "Token.h"
#include <iostream>

using namespace std;

Token::Type Token::GetType() {
	return Identifier;
}

string Token::GetContent() {
	return "emptyString";
}
