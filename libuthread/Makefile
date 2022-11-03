# Target library
lib := libuthread.a

# SRCS = libuthread/queue.c libuthread/uthread.c libuthread/context.c

MAKEFLAGS += -rR
all: $(lib)


## TODO: Phase 1

# targets := queue uthread context
objs := queue.o uthread.o context.o

CC := gcc
CFLAGS := -Wall -Wextra -Werror -pipe -MMD

AR := ar

ifneq ($(V),1)
Q = @
endif

# all: $(targets)

deps := $(patsubst %.o,%.d,$(obs))
-include $(deps)

# queue: $(objs)
# 	@echo "CC	$@"
# 	$(Q)$(CC) $(CFLAGS) -o $@ $^
# 	@./queue

# uthread: $(objs)
# 	@echo "CC	$@"
# 	$(Q)$(CC) $(CFLAGS) -o $@ $^
# 	@./uthread

# context: $(objs)
# 	@echo "CC	$@"
# 	$(Q)$(CC) $(CFLAGS) -o $@ $^
# 	@./context

%.a: $(objs)
	@echo "AR $@"
	$(Q)$(AR) rcs $@ $^

%.o: %.c
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

# $(lib): $(SRCS) 
#     ar -rcs libuthread.a queue.c

clean:
	@echo "CC	$@"
	$(Q)rm -rvf $(targets) $(objs) $(deps) *.d


# gcc contexts_fixed_schedule.c -o demo_code in CSIF
# scp Makefile afong@pc16.cs.ucdavis.edu:/home/afong/libuthread
.PHONY: clean
.PRECIOUS: $(objs)
