build: i6d_ucase_cl.c i6d_ucase_sv.c i6d_ucase.h
	mkdir -p build
	cc i6d_ucase_cl.c -o build/i6d_ucase_cl
	cc i6d_ucase_sv.c -o build/i6d_ucase_sv

seq: is_seqnum.h sockets/inet_sockets.h sockets/inet_sockets.c is_seqnum_sv.c is_seqnum_cl.c
	mkdir -p build
	cc is_seqnum_sv.c sockets/inet_sockets.c -g -o build/is_seqnum_sv
	cc is_seqnum_cl.c sockets/inet_sockets.c -g -o build/is_seqnum_cl

kv: kv.h sockets/inet_sockets.h hashtable.h hashtable.c sockets/inet_sockets.c command.c kv_server.c
	mkdir -p build
	cc command.c hashtable.c kv_server.c sockets/inet_sockets.c -g -o build/kv_server

clean:
	rm build/*

.PHONY: clean