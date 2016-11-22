BIN_PATH ?= ./bin

.PHONY: all create_dir fwprofile master slave1 slave2 run-demo

all: create_dir fwprofile master slave1 slave2

create_dir:
	@mkdir -p $(BIN_PATH)

fwprofile: create_dir
	./CompileAndLinkFw.sh ./lib/cordetfw/lib/fwprofile/src $(BIN_PATH)

master: create_dir
	./CompileAndLinkMa.sh ./lib/cordetfw/lib/fwprofile/src ./lib/cordetfw/src ./src/ $(BIN_PATH)

slave1:
	./CompileAndLinkS1.sh ./lib/cordetfw/lib/fwprofile/src ./lib/cordetfw/src ./src $(BIN_PATH)

slave2:
	./CompileAndLinkS2.sh ./lib/cordetfw/lib/fwprofile/src ./lib/cordetfw/src ./src $(BIN_PATH)

run-demo:
	./RunDemoApp.sh $(BIN_PATH)


clean:
	@rm bin -rdf

print-%: ; @echo $*=$($*)
