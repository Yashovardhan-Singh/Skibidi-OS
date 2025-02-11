int strlen(char* msg) {
    int len = 0;
    if (msg == 0) return 0;
    while (msg[len] != '\0') len++;
    return len;
}