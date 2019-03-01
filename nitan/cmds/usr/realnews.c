// realnews.c
// For Nt2
// Write by Hcifml

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
    return 1; 
    if(!arg)
        return help(me);
    if(arg == "list") 
        me->start_more(REALNEWS_D->read_news_list());
    else
        me->start_more(REALNEWS_D->read_news(arg));
    return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : realnews <list | 編號>
 
這個指令可以查看實時新聞，參數為list則顯示所有新聞列表。
 
HELP
    );
    return 1;
}
