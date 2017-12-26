PROJECT_DIR=$(shell pwd)
TODAY=$(shell date '+%Y_%m_%d')
GPP=g++
NVCC=nvcc

ifeq "$(DISTRIB)" ""
	DISTRIB=debug
endif
	
ifeq "$(DISTRIB)" "debug"
NVCC_FLAGS= -gencode arch=compute_35,code=sm_35\
	-gencode arch=compute_52,code=sm_52 \
	-std=c++11 -G -rdc=true -lcudadevrt -lcudart -lcublas_device
COMPILER_OPTIONS=-ggdb -msse4.2 -DDEBUG 
GPP_FLAGS= -Wall -ggdb -msse4.2 -DDEBUG -std=c++11
endif

ifeq "$(DISTRIB)" "release"
NVCC_FLAGS= --optimize 2 \
	-gencode arch=compute_35,code=sm_35 \
	-gencode arch=compute_52,code=sm_52 \
	-std=c++11  -rdc=true  -lcudadevrt -lcudart -lcublas_device
	
	
COMPILER_OPTIONS= -msse4.2 -O2
GPP_FLAGS=-O2 -msse4.2 -ftree-vectorize -funroll-loops -std=c++11
endif


CUDA_COMPILER_OPTIONS = $(foreach option, $(COMPILER_OPTIONS), --compiler-options $(option))

# -------------------------------------------------------------------
# files
# -------------------------------------------------------------------
	
CPP_SRCS = $(shell ls src/*.cpp)
CUDA_SRCS  = $(shell ls src/*.cu)

SRCS = $(CPP_SRCS) $(CUDA_SRCS)
OBJS = $(subst src,obj/$(DISTRIB),$(subst .cpp,.o,$(subst .cu,.o,$(SRCS))))

BINARIES = bin/$(DISTRIB)/satisfy_para.exe


all: info make_dirs $(BINARIES)

info:
	@echo "========================================================"
	@echo "DISTRIB          = $(DISTRIB)"
	@echo "GPP_FLAGS        = $(GPP_FLAGS)"
	@echo "NVCC_FLAGS       = $(NVCC_FLAGS)"
	@echo "COMPILER_OPTIONS = $(CUDA_COMPILER_OPTIONS)"
	@echo "BINARIES         = $(BINARIES)"
	@echo "OBJECTS          = $(OBJS)"

	@echo "========================================================"

make_dirs:
	@mkdir -p bin/$(DISTRIB)
	@mkdir -p obj/$(DISTRIB)
	


debug:
	@make --no-print-directory DISTRIB=debug

release:
	@make --no-print-directory DISTRIB=release


bin/$(DISTRIB)/satisfy_para.exe:  obj/$(DISTRIB)/cpu_timer.o obj/$(DISTRIB)/gpu_timer.o obj/$(DISTRIB)/satisfy_para.o
	@echo "generate binary $@"
	@$(NVCC) --link  -o $@ $^ $(NVCC_FLAGS) $(CUDA_COMPILER_OPTIONS)

obj/$(DISTRIB)/%.o: src/%.cu
	@echo "compile $<"
	@$(NVCC) -o $@ --compile $< $(NVCC_FLAGS) $(CUDA_COMPILER_OPTIONS)

obj/$(DISTRIB)/%.o: src/%.cpp
	@echo "compile $<"
	@$(GPP) -o $@ -c $< $(GPP_FLAGS)  

# -------------------------------------------------------------------
# clean
# -------------------------------------------------------------------

clean:
	rm -rf bin/$(DISTRIB)/*.exe obj/$(DISTRIB)/*.o

deep_clean:
	rm -rf bin/* obj/*


