// qiankun-except.c

#include <ansi.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int limit;

        if (! living(me) && (me->query("eff_qi") < 100 || me->query("eff_jing") < 50))
        {
                me->set_temp("die_reason", "因為強自修煉逆九陰心法，走火入魔而死");
                me->die();
                return 0;
        } else
        {
                me->receive_wound("qi", 100);
                me->receive_wound("jing", 50);
                tell_object(me, HIR "你覺得丹田陣陣寒冷，可是臉上卻"
                            "好像發燒一樣火熱之極。\n" NOR);
                message("vision", me->name() + "臉色忽青忽紅，強忍著運功抗爭。\n",
                        environment(me), me);
        }

        return 1;
}
