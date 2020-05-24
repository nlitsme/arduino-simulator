extern void setup();
extern void loop();

int main(int, char**)
{
    printf("setup\n");
    setup();
    while(true) {
        printf("loop\n");
        loop();
    }
}
