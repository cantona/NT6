// hui.c 蛤蟆功回息

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

int exert(object me, object target)
{
        int skill;
        string msg;

        if( !(skill=query_temp("hmg_dzjm", me)) )
                return notify_fail("你並沒有倒轉經脈啊。\n");

        msg = HIB "$N" HIB "緩緩吐出一口氣，臉色變了變，陰陽不定。\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/dodge", -skill/4, me);
        addn_temp("apply/parry", -skill/4, me);
        addn_temp("apply/armor", -skill/2, me);
        addn_temp("apply/dispel_poison", -skill/2, me);
        delete_temp("hmg_dzjm", me);

        set("neili", 0, me);
        return 1;
}