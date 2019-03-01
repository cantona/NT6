// jingxiu.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping fam;
        object where = environment(me);

        seteuid(getuid());

        if( query("family/family_name", me) != "少林派" )
                return 0;

        if( query("no_fight", environment(me)) && 
            (query("doing", me) != "scheme" || this_player(1)) )
                return notify_fail("這裡太紛雜，你沒法安心靜修。\n");

        if( query("jing", me)<50 )
                return notify_fail("你精神不濟，無法定心靜修。\n");

        if (me->is_busy())
                return notify_fail("你正忙著呢！\n");

        if (me->is_fighting())
                return notify_fail("戰鬥中怎麼靜修？\n");

        if (me->query_skill("buddhism", 1) < 200)
                return notify_fail("你的佛學還不夠深厚，難以通過靜修參悟禪理。\n");

        switch (random(3))
        {
        case 0:
                message_vision("$N盤膝坐下，冥思入定。\n", me);
                break;

        case 1:
                message_vision("$N緩緩坐下，魂遊天外。\n", me);
                break;

        default:
                message_vision("$N安坐不動，整個人似夢似醒。\n", me);
        }

        me->receive_damage("jing", 40 + random(10));
        me->improve_skill("buddhism", 50 + random(me->query_int()));
        me->start_busy(1 + random(3));
        write(HIC "你對禪宗心法有所心得。\n" NOR);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : jingxiu

這個指令是少林派弟子用以靜修參禪的命令.

HELP );
        return 1;
}