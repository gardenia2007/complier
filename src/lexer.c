/*
 * lexer.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */
#include "global.h"

int state = 0, start = 0;

int lexan() {
	if (feof(fp))
		return DONE;

	char ch;
	int i = 0, flag = 0, lex = 0;
	ch = fgetc(fp);
	while (ch == ' ' || ch == '\t' || ch == '\n') {
		if (ch == '\n')
			lineno++;
		ch = fgetc(fp);
	}

	if (feof(fp))
		return DONE;

	if (ch == '#') { // comment
		while (ch != '\n') //skip this line
			ch = fgetc(fp);
		//fseek(fp, 1, SEEK_CUR);
		//ch = fgetc(fp);
		lineno++;
		return lexan();
	}
	if (isalpha(ch)) {
		token[i++] = ch;
		ch = fgetc(fp);
		while (isalnum(ch)) {
			token[i++] = ch;
			ch = fgetc(fp);
		}
		fseek(fp, -1L, SEEK_CUR);
		token[i] = '\0';
		//install_id(token);
		return ID;
	} else if (isdigit(ch)) {
		token[i++] = ch;
		ch = fgetc(fp);
		while (isdigit(ch) || ch == '.') {
			if (ch == '.' && flag == 1) {
				error_handle(lineno, "unexpected '.' ");
				ch = fgetc(fp);
				continue;
			}
			if (ch == '.')
				flag = 1;
			token[i++] = ch;
			ch = fgetc(fp);
		}
		fseek(fp, -1L, SEEK_CUR);
		token[i] = '\0';
		return NUM;
	} else {
		token[i++] = ch;
		switch (ch) {
		case ':':
			ch = fgetc(fp);
			if (ch == '=') {
				token[i++] = ch;
				lex = ASG;
			} else {
				error_handle(lineno, "Missing '='");
			}
			break;
		case '>':
			ch = fgetc(fp);
			if (ch == '=') {
				token[i++] = ch;
				lex = GE;
			} else {
				lex = GT;
			}
			break;
		case '<':
			ch = fgetc(fp);
			if (ch == '=') {
				token[i++] = ch;
				lex = LE;
			} else if (ch == '>') {
				token[i++] = ch;
				lex = NE;
			} else {
				lex = LT;
			}
			break;
		case '=':
			lex = EQ;
			break;
		case '+':
			lex = PLUS;
			break;
		case '-':
			lex = MINUS;
			break;
		case '*':
			lex = MUL;
			break;
		case '/':
			lex = DIV;
			break;
		case ';':
			lex = SEMICOLON;
			break;
		case ',':
			lex = COMMA;
			break;
		case '(':
			lex = BRACKET_L;
			break;
		case ')':
			lex = BRACKET_R;
			break;
		}
		token[i] = '\0';
		return lex;
	}

	error_handle(lineno, "Unkonwn character");

//	printf("%s", ch);
	return lexan();
}
