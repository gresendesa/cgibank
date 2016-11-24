####################
####  Makefile  ####
####################

GPP = g++ --std=c++11

fw_out_dir = build/framework/
fw_in_dir = src/framework/
fw_hpp_dir = include/framework/
fw_units = Controller.o Core.o Helper.o Model.o Route.o Storage.o View.o

all: $(fw_units:%=$(fw_out_dir)%)

$(fw_units:%=$(fw_out_dir)%): $(fw_out_dir)%.o: $(fw_in_dir)%.cpp $(fw_hpp_dir)%.hpp
	$(GPP) -c $< -o $@

clear:
	rm -f build/framework/*.o 
