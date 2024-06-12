#ifndef __PIRATE_H__
#define __PIRATE_H__

typedef struct _skill{
    char* skill; 
    int skillcount; 
} skill;

// Type of a pirate.
typedef struct _pirate {
    char* pirate_name;
    struct pirate* captain; 
    char* title;
    char* vessel;
    char* port; 
    int treasure;
    skill* skill_list; 
    int skill_length; 
    int skill_capacity;  
} pirate;

#endif
