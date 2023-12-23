
# $1 - target name
# $2 - source files
# $3 - build flags
# $4 - dependency libraries
# $5 - source directory

define build_executable

$(eval TARGET = $(strip $1))
$(eval SRC = $(strip $2))
$(eval FLAGS = $(CFLAGS) $3)
$(eval DEPS = $(strip $4))
$(eval DIR = $(strip $5))
$(eval LDFL = $(LDFLAGS)

$(eval OBJ = $(addprefix $(BUILD)/,$(SRC:.c=.o)))
$(eval TARGETS = $(TARGETS) $(BUILD)/$(TARGET)))

$(BUILD)/%.o: $(DIR)/%.c
	@mkdir -p $$(dir $$@)
	@echo "CC $$@"
	@$(CC) $(FLAGS) -c $$< -o $$@

$(BUILD)/$(TARGET): $(DEPS) $(OBJ)
	@echo LD $(TARGET)
	@$(LD) $(LDFL) $(OBJ) -o $$@ $(DEPS)

endef

define build_library

$(eval TARGET = $(strip $1))
$(eval SRC = $(strip $2))
$(eval FLAGS = $(CFLAGS) $3)
$(eval DEPS = $(strip $4))
$(eval DIR = $(strip $5))

$(eval OBJ = $(addprefix $(BUILD)/,$(SRC:.c=.o)))

$(BUILD)/$(TARGET): $(DEPS) $(OBJ)
	@echo AR $(TARGET)
	@$(AR) $(BUILD)/$(TARGET) $(OBJ) $(DEPS)

$(BUILD)/%.o: $(DIR)/%.c
	@mkdir -p $$(dir $$@)
	@echo CC $$@
	@$(CC) $(FLAGS) -c $$< -o $$@

endef

#mkdir -p $$(dir $$@)
#	@echo LIB TARGET $(BUILD)/$(TARGET)
#	@echo 'sp>'$(TARGET)'<sp'
#	@echo TARGET $(TARGET)
#	@echo SRC $(SRC)
#	@echo FLAGS $(FLAGS)
#	@echo DEPS $(DEPS)
#	@echo DIR $(DIR)
#
#	@echo OBJ $(OBJ)
#	@echo
