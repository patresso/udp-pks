dev: source/lib/common/misc/intro.c source/app.c source/lib/common/misc/messages.c source/lib/server/server.c source/lib/client/client.c 
	gcc source/app.c source/lib/common/misc/intro.c source/lib/common/misc/messages.c source/lib/server/server.c source/lib/client/client.c -odev -g

clean:
	rm dev