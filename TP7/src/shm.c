#include "shm.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

boite_struct * open_shm()
{
	boite_struct * boite;
	int fd;
	fd = shm_open("/oss0612",  O_RDWR | O_CREAT, 0644);
	if(fd == -1) {
		fprintf(stderr, "Error while opening mem shared\n");
	}
	if(ftruncate(fd, sizeof(boite)) == -1) {
		fprintf(stderr, "Error while loading memory\n");
		exit(-1);
	}
	boite = (boite_struct *) mmap(&boite,
	 sizeof(boite), 
	 PROT_READ | PROT_WRITE, 
	 MAP_SHARED,
	 fd, 
	 0);

	if (boite == (void *) -1) {
		printf("Error allocating shared memory using mmap!\n");
		exit(1);
	}
	return boite;
}
boite_struct * create_shm()
{
	int fd;
	boite_struct * boite;
	
	fd = shm_open("/oss0612",  O_RDWR, 0644);

	if(fd == -1) {
		fprintf(stderr, "Error while opening mem shared\n");
	}
	 boite = (boite_struct*) mmap(&boite,
	 sizeof(boite), 
	 PROT_READ | PROT_WRITE, 
	 MAP_SHARED,
	 fd, 
	 0);
	 
	if (boite == (void *) -1) {
		printf("Error allocating shared memory using mmap!\n");
		exit(1);
	}
	return boite;
}

void close_shm(boite_struct * boite)
{
	munmap(boite, sizeof(boite));
}