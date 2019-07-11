typedef struct{
    char  c1;
    short s; 
    char  c2; 
    int   i;
}T_FOO;

int main(void){  
    T_FOO a; 
    printf("c1 -> %d, s -> %d, c2 -> %d, i -> %d\n", 
            (unsigned int)(void*)&a.c1 - (unsigned int)(void*)&a,
            (unsigned int)(void*)&a.s  - (unsigned int)(void*)&a, 
            (unsigned int)(void*)&a.c2 - (unsigned int)(void*)&a, 
            (unsigned int)(void*)&a.i  - (unsigned int)(void*)&a); 
    return 0;
}
