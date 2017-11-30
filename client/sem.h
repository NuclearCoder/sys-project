//
// Created by nuclearcoder on 30/11/17
//

#ifndef SYS_PROJECT_SEM_H
#define SYS_PROJECT_SEM_H

// DON'T CALL init_sem MORE THAN ONCE!
void init_sem(pmmap_t *map);
void wait_sem(pmmap_t *map);

#endif // SYS_PROJECT_SEM_H
