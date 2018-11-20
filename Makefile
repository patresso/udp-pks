dev: source/lib/common/misc/intro.c source/app.c source/lib/common/misc/messages.c source/lib/server/server.c source/lib/client/client.c source/lib/common/protocol/actions.c source/lib/common/protocol/conn.c source/lib/common/misc/control.c
	gcc source/app.c source/lib/common/misc/intro.c source/lib/common/misc/messages.c source/lib/server/server.c source/lib/client/client.c source/lib/common/protocol/actions.c source/lib/common/protocol/conn.c source/lib/common/misc/control.c -odev -g -pthread

clean:
	rm dev