#---LET START MAKE---
CC = gcc

DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
OBJT = EscapeTechnion.o company.o  escaper.o room.o order.o common_functions.o

TESTS =./tests
TEST_H = $(TESTS)/test_utilities.h

# -----EXE-----
mtm_escape : room.o parser.o EscapeTechnion.o escaper.o company.o order.o main.o common_functions.o
	$(CC) $(DEBUG_FLAG) room.o parser.o EscapeTechnion.o escaper.o company.o order.o main.o common_functions.o -o $@ -L. -lmtm

room.o : room.c room.h mtm_ex3.h set.h common_functions.h 
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

parser.o : parser.c parser.h mtm_ex3.h list.h set.h EscapeTechnion.h company.h escaper.h room.h common_functions.h order.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

EscapeTechnion.o : EscapeTechnion.c EscapeTechnion.h mtm_ex3.h list.h set.h  company.h escaper.h room.h order.h common_functions.h 
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

escaper.o : escaper.c escaper.h mtm_ex3.h common_functions.h common_functions.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

company.o : company.c company.h mtm_ex3.h common_functions.h common_functions.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

order.o : order.c order.h mtm_ex3.h common_functions.h common_functions.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

main.o : main.c $(TEST_H) mtm_ex3.h list.h parser.h EscapeTechnion.h set.h company.h escaper.h common_functions.h room.h order.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
common_functions.o  :  mtm_ex3.h common_functions.c common_functions.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

#  ----- TEST OBJS ------
tests : room_test company_test order_test list_mtm1_test escaper_test

room_test.o : $(TESTS)/room_test.c room.h order.h mtm_ex3.h escaper.h list.h EscapeTechnion.h  $(TEST_H)
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG)  $(TESTS)/$*.c -o $(TESTS)/$@ -L. -lmtm

#escape_technion_test.o : $(TESTS)/escape_technion_test.c EscapeTechnion.h parser.h  company.h mtm_ex3.h list.h escaper.h
#	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(TESTS)/$*.c -o $(TESTS)/$@ -L. -lmtm

escaper_test.o : $(TESTS)/escaper_test.c escaper.h company.h EscapeTechnion.h mtm_ex3.h list.h $(TEST_H)
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(TESTS)/$*.c -o $(TESTS)/$@ -L. -lmtm

company_test.o : $(TESTS)/company_test.c company.h escaper.h EscapeTechnion.h mtm_ex3.h list.h $(TEST_H)
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(TESTS)/$*.c -o $(TESTS)/$@ -L. -lmtm

order_test.o : $(TESTS)/order_test.c order.h mtm_ex3.h list.h EscapeTechnion.h escaper.h  $(TEST_H)
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(TESTS)/$*.c -o $(TESTS)/$@ -L. -lmtm

# -----TEST LIST-----
list_mtm1_test.o : $(TESTS)/list_mtm1_test.c  ./list_mtm/list_mtm1.h  $(TEST_H)
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $(TESTS)/$*.c -o $(TESTS)/$@

list_mtm1.o: ./list_mtm/list_mtm1.c ./list_mtm/list_mtm1.h
	$(CC) $(COMP_FLAG)  -c ./list_mtm/$*.c 

list_mtm1_test : list_mtm1_test.o list_mtm1.o 
	$(CC) $(TESTS)/list_mtm1_test.o list_mtm1.o -o $@   

### -----TESTS ADT----- 
room_test : room_test.o $(OJBT)
	$(CC) $(TESTS)/room_test.o $(OBJT) -o $@ -L. -lmtm

escape_technion_test : escape_technion_test.o $(OBJT) parser.o
	$(CC) $(TESTS)/escape_technion_test.o $(OBJT) parser.o  -o $@ -L. -lmtm


escaper_test : escaper_test.o $(OBJT)
	$(CC) $(TESTS)/escaper_test.o $(OBJT) -o $@ -L. -lmtm


company_test : company_test.o $(OBJT)
	$(CC) $(TESTS)/company_test.o $(OBJT) -o $@ -L. -lmtm


order_test : order_test.o $(OBJT)
	$(CC) $(TESTS)/order_test.o $(OBJT) -o $@ -L. -lmtm

	