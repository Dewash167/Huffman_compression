typedef struct anode
{
    int freq;
    char ch;
    struct anode *next;
} anode;

anode *frequency(int fr);
anode *sorting(anode *start);
