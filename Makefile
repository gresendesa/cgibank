####################
####  Makefile  ####
####################

GPP = g++ --std=c++11

src_dir = src/
include = include/
build = build/

fw_out_dir = $(build)framework/
fw_in_dir = $(src_dir)framework/
fw_hpp_dir = $(include)framework/

models_out_dir = $(build)app/
models_in_dir = $(src_dir)app/
models_hpp_dir = $(include)app/

controllers_out_dir = $(build)app/controllers/
controllers_in_dir = $(src_dir)app/controllers/
controllers_hpp_dir = $(include)app/controllers/

views_out_dir = $(build)app/views/
views_in_dir = $(src_dir)app/views/
views_hpp_dir = $(include)app/views/

fw_sources = $(shell ls $(fw_in_dir) | grep '\.cpp')
app_models_sources = $(shell ls $(models_in_dir) | grep '\.cpp')
app_controllers_sources = $(shell ls $(controllers_in_dir) | grep '\.cpp')
app_views_sources = $(shell ls $(views_in_dir) | grep '\.cpp')

fw_units = $(fw_sources:%.cpp=%.o)
route_file = routes.o
credential_file = credentials.o
app_models = $(app_models_sources:%.cpp=%.o)
app_controllers = $(app_controllers_sources:%.cpp=%.o)
app_views = $(app_views_sources:%.cpp=%.o)

all: $(fw_units:%=$(fw_out_dir)%) $(route_file:%=$(fw_out_dir)%) $(credential_file:%=$(fw_out_dir)%) $(app_models:%=$(models_out_dir)%) $(app_controllers:%=$(controllers_out_dir)%) $(app_views:%=$(views_out_dir)%) link

#Framework objects
$(fw_units:%=$(fw_out_dir)%): $(fw_out_dir)%.o: $(fw_in_dir)%.cpp $(fw_hpp_dir)%.hpp
	$(GPP) -c $< -o $@

#Routes file
$(route_file:%=$(fw_out_dir)%): $(fw_out_dir)%.o: $(src_dir)%.cpp $(fw_hpp_dir)%.hpp
	$(GPP) -c $< -o $@

#Credentials file
$(credential_file:%=$(fw_out_dir)%): $(fw_out_dir)%.o: $(src_dir)%.cpp $(fw_hpp_dir)%.hpp
	$(GPP) -c $< -o $@

#App models
$(app_models:%=$(models_out_dir)%): $(models_out_dir)%.o: $(models_in_dir)%.cpp $(models_hpp_dir)%.hpp
	$(GPP) -c $< -o $@

#App controllers
$(app_controllers:%=$(controllers_out_dir)%): $(controllers_out_dir)%.o: $(controllers_in_dir)%.cpp $(controllers_hpp_dir)%.hpp
	$(GPP) -c $< -o $@

#App views
$(app_views:%=$(views_out_dir)%): $(views_out_dir)%.o: $(views_in_dir)%.cpp $(views_hpp_dir)%.hpp
	$(GPP) -c $< -o $@

#Brings everything together
link:
	$(GPP) -o public/index.cgi $(fw_units:%=$(fw_out_dir)%) $(route_file:%=$(fw_out_dir)%) $(credential_file:%=$(fw_out_dir)%) $(app_models:%=$(models_out_dir)%) $(app_controllers:%=$(controllers_out_dir)%) $(app_views:%=$(views_out_dir)%)

clear:
	rm -f $(fw_out_dir)*.o $(models_out_dir)*.o $(controllers_out_dir)*.o $(views_out_dir)*.o

see:
	echo $(fw_sources)

permissions:
	sudo chmod 777 -R data/
	sudo chmod 777 -R src/app/views/html