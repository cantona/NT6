// ai.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string r;

        if( query("pigging", environment(me)) )
                return notify_fail("你還是安心的拱豬吧！\n");

        if (! objectp(ob = STORY_D->query_running_story())
            || base_name(ob) != STORY_DIR + "challenge")
                return notify_fail("現在沒有人來挑戰，你瞎動什麼？\n");

        if (me->is_in_prison())
                return notify_fail("好好的做你的牢吧。\n");

        if (me->is_ghost())
                return notify_fail("你還是等還了陽再説吧。\n");

        if (wizardp(me))
                return notify_fail("你一個巫師搗什麼亂？\n");

        if (me->is_busy())
                return notify_fail("你現在正忙，等有空了再説吧！\n");

        if (me->is_fighting())
                return notify_fail("你還是把眼前的敵人放倒再説吧！\n");

        if (r = ob->cannot_accept(me))
                return notify_fail(r);

        ob->accept_for_challenge(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : accept

接收來自挑戰者的挑戰。當然的有人向你挑戰才可以。

其他相關指令: fight, hit

HELP );
        return 1;
}
