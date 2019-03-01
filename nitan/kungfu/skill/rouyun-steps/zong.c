// zong.c「柔雲縱」

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;

        if (! me->is_fighting())
                return notify_fail("「柔雲縱」只能在戰鬥中使用。\n");

        if ((int)me->query_skill("rouyun-steps",1) < 50)
                return notify_fail("你的柔雲步法不夠熟練！\n");

        if( query("jingli", me)<50 )
                return notify_fail("你的精力不夠！\n");

        msg = HIC "$N" HIC "身形陡然縱起，十分優雅，天空中卻"
              "飄下一朵雲，非常奇怪！\n" NOR;
        me->receive_damage("jing", 10);
        addn("jingli", -20, me);
        set_temp("no_follow", 1, me);
        msg += HIC "原來$N" HIC "已使出「柔雲縱」，乘雲而去了！\n" NOR;
        message_combatd(msg, me, target);
        switch (random(3))
        {
                case 0:
                        me->move("/d/city/wumiao");
                        break;
                case 1:
                        me->move("/d/city/kedian");
                        break;
                case 2:
                        me->move("/u/deaner/test1");
                        break;
        }
        return 1;
}