void main()
{
    char *video_memory = (char *)0xb8000;

    *video_memory = 'X';
    video_memory[1] = 'x';
    video_memory[2] = 'd';
}