vkb-client: vkb_client.o
	g++ -g -o $@ $^ -Wl,-rpath $(PATH_BIN)/ -ldl -lpthread

vkb_client.o: vkb_client.cpp
	g++ -c -g -fshort-wchar -std=c++14 -Wfatal-errors --all-warnings $(addprefix -I, $(INCS_XPCOM)) $(addprefix -D, $(DEFS_XPCOM)) -o $@ vkb_client.cpp

clean:
	rm -f vkb-client vkb_client.o
