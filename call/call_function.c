void caller_func()
{
    callee_func(0xbeba);
}

int callee_func(int my_arg)
{
    return my_arg;
}
