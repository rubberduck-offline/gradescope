# Target library
lib := libuthread.a

MAKEFLAGS += -rR
all: $(lib)


## TODO: Phase 1

objs := queue.o uthread.o context.o sem.o

CC := gcc
CFLAGS := -Wall -Wextra -Werror -pipe -MMD

AR := ar

ifneq ($(V),1)
Q = @
endif

deps := $(patsubst %.o,%.d,$(obs))
-include $(deps)

%.a: $(objs)
	@echo "AR $@"
	$(Q)$(AR) rcs $@ $^

%.o: %.c
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "CC	$@"
	$(Q)rm -rvf $(targets) $(objs) $(deps) *.d

.PHONY: clean
.PRECIOUS: $(objs)
