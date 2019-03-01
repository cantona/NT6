#include <ansi.h>

void do_nothing(string nothing);

int main(object who,string arg)
{   
    write(REF);
    if(arg=="-l")
    input_to( (:do_nothing:) );
    return 1;
}

int help()
{
    write(@HELP
指令格式：cls [-l]
這個指令可以清除當前屏幕內容。
如果有-l這個參數就暫緩屏幕輸出。只至按回車健。
HELP );
    return 1;
}

void do_nothing(string nothing)
{
    return;
}