
avatars: main.c connection.c pool.c lib/threadpool/src/threadpool.c client.c
	gcc -o main main.c connection.c pool.c lib/threadpool/src/threadpool.c client.c -I. `pkg-config --cflags --libs MagickWand` -lcurl
