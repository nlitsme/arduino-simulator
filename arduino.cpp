extern void setup();
extern void loop();

int main(int, char**)
{
    printf("setup\n");
    setup();
    while(true) {
#ifdef VERBOSE
        printf("loop\n");
#endif
        loop();
    }
}
