
avatars: router.c main.c connection.c pool.c parser.c lib/threadpool/src/threadpool.c lib/slre/slre.c client.c
	gcc -o main  router.c main.c connection.c pool.c parser.c lib/threadpool/src/threadpool.c lib/slre/slre.c client.c -I. `pkg-config --cflags --libs MagickWand` -lcurl
