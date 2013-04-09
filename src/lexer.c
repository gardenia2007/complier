/*
 * lexer.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */
#include "global.h"

int get_num(int i, int flag);

int state = 0, start = 0;

int lexan() {
	if (feof(fp))
		return DONE;

	char ch;
	int i = 0, flag = 0, lex = 0, p = 0;
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
		p = look_up(token);
		if (p == 0)
			p = insert(token, ID);
		tokenval = p;
		return symtable[p].token;
	} else if (isdigit(ch)) {
		token[i++] = ch;
		return get_num(i, flag);
	} else {
		token[i++] = ch;
		switch (ch) {
		case '=':
			ch = fgetc(fp);
			if (ch == '=') {
				token[i++] = ch;
				lex = EQ;
			} else {
				fseek(fp, -1L, SEEK_CUR);
				lex = ASG;
				//error_handle(lineno, "Missing '='");
			}
			break;
		case '|':
			ch = fgetc(fp);
			if (ch == '|') {
				token[i++] = ch;
				lex = OR;
			} else {
				fseek(fp, -1L, SEEK_CUR);
				error_handle(lineno, "Missing '|'");
			}
			break;
		case '&':
			ch = fgetc(fp);
			if (ch == '&') {
				token[i++] = ch;
				lex = AND;
			} else {
				fseek(fp, -1L, SEEK_CUR);
				error_handle(lineno, "Missing '&'");
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
		case '+':
			lex = PLUS;
			break;
		case '-':
			//if (lex != NUM) { // lex is previous token
			//	return get_num(i, flag);
			//}else{
				lex = MINUS;
			//}
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
		case '[':
			lex = BB_L;
			break;
		case ']':
			lex = BB_R;
			break;
		case '{':
			lex = BIGB_L;
			break;
		case '}':
			lex = BIGB_R;
			break;
		default:
			lex = ERROR;
			error_handle(lineno, "Unkonwn character");
			break;
		}
		token[i] = '\0';
		tokenval = NONE;
		return lex;
	}

//	printf("%s", ch);
	return lexan();
}

int get_num(int i, int flag)
{
	char ch;
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
	tokenval = atoi(token);
	//tokenval = 10;
	return NUM;
}

