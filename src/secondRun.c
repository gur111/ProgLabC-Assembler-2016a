/*
 * secondRun.c
 *
 *  Created on: Jan 18, 2016
 *      Author: Gur Telem
 */
#include <string.h> /*strlen*/
#include "assembler.h"
#include "dataTable.h"
#include "cmdTable.h"
#include "symbolTable.h"
#include "errorHandler.h"
#include <math.h>

static bool handleLine2(input_line*);
static addressing getArgWord(const char *str, word *wrd);

FLAG secondRun(FILE *src) {
	input_line *line;
	int lineIndex;
	fseek(src, 0L, SEEK_SET);
	relocate(cmd_list.length);
	for (lineIndex = 1; true; lineIndex++) { /* Runs through all the lines. */
		if ((line = getLine(src))) {
			if (line->isEOF) {
				freeLine(line);
				break; /* End when EOF is encountered */
			}
			if (line->isEffectless) {
				continue;
			}
			if (!handleLine2(line)) {
				if (cmd_list.length + data_list.length > MAX_MEMORY_SIZE) {
					error(sprintf(errMsg, OUT_OF_STORAGE));
					report(lineIndex);
					return flag;
				}
				report(lineIndex);
			}
		} else {
			report(lineIndex);
		}
		freeLine(line);
	}
	return flag;
}/* End secondRun */

/* Analyses an line of code and operates accordingly */
static bool handleLine2(input_line* line) {
	switch (line->cmd) {
	/* Two operands group */
	case MOV:
	case CMP:
	case ADD:
	case SUB:
	case LEA:
		if (line->args != NULL && line->args[1] != NULL && line->args[2] == NULL) { /* Two args */
			addressing srcAdders, destAdders;
			word srcArg, destArg;
			int rnd = 0;
			/* Handle source arg  */
			switch (srcAdders = getArgWord(line->args[0], &srcArg)) {
			case REG:
				srcArg.reg.srcOperand = srcArg.reg.destOperand;
				srcArg.reg.destOperand = 0;
			case IMD:
				if (line->cmd == LEA) {
					error(sprintf(errMsg, WRONG_ARG_FOR_FUNC));
					return false;
				}
				break;
			case RND:
				rnd = strlen(line->args[0]);
				if (line->cmd == LEA && rnd != 3) {
					error(sprintf(errMsg, WRONG_ARG_FOR_FUNC));
					return false;
				}
				break;
			case DIR:
				break;
			default:
				return false;
				break;
			}
			/* handle dest arg  */
			switch (destAdders = getArgWord(line->args[1], &destArg)) {
			case IMD:
				if (line->cmd != CMP) {
					error(sprintf(errMsg, WRONG_ARG_FOR_FUNC));
					return false;
					break;
				}
			case DIR:
			case REG:
				break;
			case RND:
			default:
				return false;
				break;
			}

			addCmd(ABS, destAdders, srcAdders, line->cmd, TWO_ARGS, rnd);
			if (destAdders == REG && (srcAdders == REG || rnd == 1)) {
				word multiReg;
				multiReg.reg.destOperand = destArg.reg.destOperand;
				multiReg.reg.srcOperand = srcArg.reg.srcOperand;
				multiReg.reg.decode = ABS;
				multiReg.reg.zeroBit = 0;
				addArg(multiReg);
			} else {
				destArg.reg.zeroBit = 0;
				srcArg.reg.zeroBit = 0;
				if (srcAdders == DIR && srcArg.num.value == 0) {/* If the arg is external */
					if (!addExt(line->args[0], getCmdLength() + 1)) {
						return false;
					}
				}
				addArg(srcArg);
				if (destAdders == DIR && destArg.num.value == 0) {/* If the arg is external */
					if (!addExt(line->args[1], getCmdLength() + 1)) {
						return false;
					}
				}
				addArg(destArg);
			}
		} else {
			error(sprintf(errMsg, WRONG_ARG_COUNT));
			return false;
			/* Expected 2 arg error */
		}
		break;
		/* One operands group */
	case NOT:
	case CLR:
	case INC:
	case DEC:
	case JMP:
	case BNE:
	case RED:
	case PRN:
	case JSR:
		if (line->args != NULL && line->args[1] == NULL) { /* Only one arg*/
			addressing adders;
			word arg;
			switch (adders = getArgWord(line->args[0], &arg)) {
			case IMD:
				if (line->cmd != PRN) {
					error(sprintf(errMsg, WRONG_ARG_FOR_FUNC));
					return false;
					break;
				}
			case DIR:
			case REG:
				addCmd(ABS, adders, IMD, line->cmd, ONE_ARG, 0/*no rnd*/);
				if (adders == DIR && arg.num.value == 0) {/* If the arg is external */
					if (!addExt(line->args[0], getCmdLength() + 1)) {
						return false;
					}
				}
				addArg(arg);
				break;
			case RND:
			default:
				return false;
				break;
			}
		} else {
			error(sprintf(errMsg, WRONG_ARG_COUNT));
			return false;
			/* Expected 1 arg error */
		}
		break;
		/* No operands group */
	case RTS:
	case STOP:
		if (line->args == NULL) { /*no args*/
			addCmd(0, IMD, IMD, line->cmd, NO_ARGS, 0);
		} else {
			error(sprintf(errMsg, WRONG_ARG_COUNT));
			return false;
		}
		break;

	case DOT_ENTRY:
		if (line->args != NULL && line->args[1] == NULL) {
			label* entLable;
			/* TODO: check*/
			if ((entLable = getLabel(line->args[0])) != NULL) {
				if (!(addEnt(entLable))) {
					return false;
				}
			} else {
				/* TODO:  */
				error(sprintf(errMsg, ENT_TO_UNDEF, line->args[0]));
				return false;
			}
		}
		break;
	case DOT_DATA:
	case DOT_STRING:
	case DOT_EXTERN:
		/* do nothing */
		break;
	default:
		/* Not a command error. Probably impossible to reach. */
		error(sprintf(errMsg, UNKNOWN_ERR));
		return false;
		break;
	}
	return true;
}/* End handleLine2 */

static addressing getArgWord(const char *str, word *wrd) {
	int num, i;
	label *lbl;

	if (str[0] == RND_FLAG) {/* Is random */
		i = 0;
		while (str[++i]) {
			if (str[i] != RND_FLAG) {
				i = -1;
				break;
			}

		};
		switch (i) {
		case 1:/* Random register */
			wrd->reg.zeroBit = 0;
			wrd->reg.decode = ABS;
			wrd->reg.srcOperand = rand() % REG_AMOUNT;
			wrd->reg.destOperand = 0;
			return RND;
			break; /* Just in case for future changes */
		case 2:/* Random number */
			wrd->num.decode = ABS;
			wrd->num.value = rand() % (int) pow(2, VALUE_SIZE);
			return RND;
			break; /* Just in case for future changes */
		case 3:/* Random address */
			wrd->num.decode = RLC;
			num = getRandomAddress();
			if (num == -1) {
				error(sprintf(errMsg, CANNOT_GET_RND));
				return -1;
			}
			wrd->num.value = num;
			return RND;
			break; /* Just in case for future changes */
		default:
			break;
		}
	} else if (str[0] == IMD_FLAG) {/* Is immediate number */
		if (!strToInt(str + 1, &num)) {
			error(sprintf(errMsg, SYNTAX_ERROR UNKNOWN_ARG_TYPE));
			return -1;
		}
		wrd->num.decode = ABS;
		wrd->num.value = num % (int) pow(2, VALUE_SIZE);
		return IMD;
	} else if (validReg(str)) {/* Is register name */
		wrd->reg.zeroBit = 0;
		wrd->reg.decode = ABS;
		wrd->reg.destOperand = str[1] - '0';
		wrd->reg.srcOperand = 0;
		return REG;
	} else if (validLabel(str)) {/* Is label name */
		if (!(lbl = getLabel(str))) {
			error(sprintf(errMsg, UNKNOWN_LABEL, str));
			return -1;
		}
		wrd->num.value = lbl->address;
		wrd->num.decode = lbl->isExt ? EXT : RLC;
		return DIR;
	}
	error(sprintf(errMsg, SYNTAX_ERROR INVALID_ARG, str));/* Syntax error */
	return -1;
}
