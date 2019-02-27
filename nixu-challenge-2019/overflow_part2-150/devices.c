#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define DEVICE_LIMIT 24

static uint64_t master = 0x8100ca33c1ab7dafLL;
static char flag[64];
static char flag2[64];

struct device {
    char name[32];
    char description[128];
    uint64_t id;
};

static struct device devices[DEVICE_LIMIT];
static int next;


char *input(char *buf, int size) {
    char *r = fgets(buf, size - 1, stdin); 	
    if (r) {
        if (r[strlen(r)-1] == '\n')
            r[strlen(r)-1] = '\0';
        }
    return r; 
}

uint64_t random_id() {
    uint64_t tmp = random();
    tmp = (tmp << 32) | random();
    return tmp;
}

int add_device() {
    char tmp_name[32];
    char tmp_description[256];
    uint64_t tmp_id = random_id();
    devices[next].id = tmp_id;

    printf("Add a new device\n");
    printf("Assigned device ID %lx\n", tmp_id);
    printf("Name:\n");
    input(tmp_name, sizeof(tmp_name));
    printf("Description:\n");
    input(tmp_description, sizeof(tmp_description));

    strcpy(devices[next].name, tmp_name);
    strcpy(devices[next].description, tmp_description);

    next++;
    return 0;
}


void menu() {
    printf("\n1) List devices\n"
    "2) Add device\n"
    "3) Process\n"
    "5) Quit\n");
}

void list_devices() {
    printf("\nListing devices:\n\n");
    for (int i = 0; i < DEVICE_LIMIT; i++) {
        if (!devices[i].id) {
            break;
        }
        printf("%i:\n"
                "ID: %lx\n"
                "Name: %s\n"
                "Description: %s\n\n"
                , i + 1, devices[i].id, devices[i].name,
                devices[i].description);
    }

}

void edit_device() {
    if (next == 0) {
        printf("No devices found\n");
        return;
    }
    if (next == 1) {
        printf("Select device to edit (1):\n");
    } else {
        printf("Select device to edit (1-%i):\n", next);
    }

    char choice[8];
    choice[0] = '\0';
    if (fgets(choice, 8, stdin) == NULL) return;
    int target = choice[0] - '0';
    if (target <= 0 || target - 1 >= next) {
        printf("Invalid device selection\n");
        return;
    }

    target = target - 1;
    char tmp_name[32];
    char tmp_description[256];

    printf("New name:\n");
    input(tmp_name, sizeof(tmp_name));
    printf("New description:\n");
    input(tmp_description, sizeof(tmp_description));

    strcpy(devices[target].name, tmp_name);
    strcpy(devices[target].description, tmp_description);

    return;

}

void process() {
    printf("Looking for master device id: %lx\n", master);
    for (int i = 0; i < DEVICE_LIMIT; i++) {
        if (!devices[i].id) {
            printf("Processing done, no master device found\n");
            break;
        }
        if (devices[i].id == master ) {
            printf("Device with master id found, here's the flag:\n");
            printf("%s\n", flag2);
            return;
        }
    }
}

void admin_menu() {
    printf("Admin functionality is not fully implemented but here's a flag:\n");
    printf("%s\n", flag);
    return;
}

void read_flags() {
    FILE *f;
    f = fopen("./flag1.txt", "rb");
    fgets(flag, sizeof(flag) - 1, f);
    flag[strlen(flag) - 1] = '\0';
    fclose(f);

    f = fopen("./flag2.txt", "rb");
    fgets(flag2, sizeof(flag2) - 1, f);
    flag2[strlen(flag2) - 1] = '\0';
    fclose(f);

    return;
}

void mainloop() {

    char choice[8];
    // TODO: implement authentication system. Default to 999999 while testing.
    int id = 999999;
    while (1) {
        printf("\n1) List devices\n"
        "2) Add device\n"
        "3) Edit device\n"
        "4) Process\n"
        "5) Quit\n");
        if (id == 0) {
            printf("8) Admin\n");
        }
        choice[0] = '\0';
        if (fgets(choice, 127, stdin) == NULL) return;
        switch(choice[0]) {
            case '1':
                list_devices();
                break;
            case '2':
                add_device();
                break;
            case '3':
                edit_device();
                break;
            case '4':
                process();
                break;
            case '5':
                printf("Leaving\n");
                return;
            case '8':
                if (id == 0) {
                    admin_menu();
                } else {
                    printf("You are not an admin!");
                }
                break;
            default:
                printf("Try again\n");
                break;
        }
    }
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Welcome to ACME corp control panel\n");
    read_flags();
    mainloop();
}
