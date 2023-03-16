ifndef LIB_BUILD_DIR
$(error "LIB_BUILD_DIR must be passed")
endif

OUT=${LIB_BUILD_DIR}
SRC_OUT=../src/
OBJCOPY=objcopy

.DEFAULT_GOAL=$(SRC_OUT)compile_time_request.c

################ Compile time requests


$(OUT)%.o.ctr: $(OUT)%.o
	$(OBJCOPY) -j '.compile_time_request' -O binary $^ $@

OBJ_FILES=$(wildcard $(OUT)klipper/*.o)
CTR_FILES=$(patsubst %.o,%.o.ctr,${OBJ_FILES})

$(SRC_OUT)compile_time_request.c: ${CTR_FILES} buildcommands.py
	@echo "  Building $@"
	cat ${CTR_FILES} | tr -s '\0' '\n' > $(OUT)compile_time_request.txt
	python3 buildcommands.py -d $(OUT)klipper.dict -t "$(CC);$(AS);$(LD);$(OBJCOPY);$(OBJDUMP);$(STRIP)" $(OUT)compile_time_request.txt $(SRC_OUT)compile_time_request.c

