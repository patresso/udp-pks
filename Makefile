dev: source/lib/common/misc/intro.c source/app.c source/lib/common/misc/messages.c source/lib/server/server.c source/lib/client/client.c source/lib/common/protocol/connection_threads.c source/lib/common/misc/control.c source/lib/common/misc/crc.c source/lib/common/protocol/message_processing.c source/lib/common/protocol/send.c source/lib/common/protocol/recieve.c source/lib/common/file_handling/recievefile.c source/lib/common/file_handling/sendfile.c
	gcc source/app.c source/lib/server/server.c source/lib/client/client.c source/lib/common/protocol/message_processing.c source/lib/common/protocol/connection_threads.c source/lib/common/misc/control.c source/lib/common/misc/crc.c source/lib/common/misc/messages.c source/lib/common/misc/intro.c source/lib/common/protocol/send.c source/lib/common/protocol/recieve.c source/lib/common/file_handling/recievefile.c source/lib/common/file_handling/sendfile.c -odev -g -lpthread

clean:
	rm dev
	rm downloads/*.*