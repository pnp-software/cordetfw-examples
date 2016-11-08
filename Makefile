BIN_PATH ?= ./bin

.PHONY: all create_dir fwprofile master slave1 slave2

all: create_dir fwprofile master slave1 slave2

create_dir:
	@mkdir -p $(BIN_PATH)

fwprofile: create_dir
	./CompileAndLinkFw.sh ./lib/cordetfw/lib/fwprofile/src ./bin

master: create_dir
	./CompileAndLinkMa.sh ./lib/cordetfw/lib/fwprofile/src ./lib/cordetfw/src ./src/ ./bin

slave1:
	./CompileAndLinkS1.sh ./lib/cordetfw/lib/fwprofile/src ./lib/cordetfw/src ./src ./bin

slave2:
	./CompileAndLinkS2.sh ./lib/cordetfw/lib/fwprofile/src ./lib/cordetfw/src ./src ./bin

clean:
	@rm bin -rdf
