
#ifndef SHM_H
#define SHM_H

#include "messages.h"

boite_struct * open_shm();
boite_struct * create_shm();
void close_shm(boite_struct * boite);

#endif