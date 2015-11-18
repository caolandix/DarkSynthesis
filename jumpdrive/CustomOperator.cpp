#include "CustomOperator.h"

CustomOperator::CustomOperator(const string symbol, const bool leftAssociative, const int precedence) {
	m_leftAssociative = leftAssociative;
	m_symbol = symbol;
	m_precedence = precedence;
	m_operandCount = 2;
}
CustomOperator::CustomOperator(const string symbol, const bool leftAssociative, const int precedence, const int operandCount) {
	m_leftAssociative = leftAssociative;
	m_symbol = symbol;
	m_precedence = precedence;
	m_operandCount = operandCount == 1 ? operandCount : 2;
}

CustomOperator::CustomOperator(const string symbol) {
	m_leftAssociative = true;
	m_symbol = symbol;
	m_precedence = 1;
	m_operandCount = 2;
}

CustomOperator::CustomOperator(const string symbol, const int precedence) {
	m_leftAssociative = true;
	m_symbol = symbol;
	m_precedence = precedence;
	m_operandCount = 2;
}
