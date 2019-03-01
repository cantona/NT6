#include <ansi.h>

inherit F_CLEAN_UP;

void dest_sword(object me);

int exert(object me, object target)
{
        object weapon;

        if (target != me)
                return notify_fail("呵氣成劍只能對自己使用。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你手中已經有武器了。\n");

        if (present("jian qi", me))
                return notify_fail("你身上已經有一束劍氣了。\n");

        addn("neili", -30, me);

        message_combatd(HIW "$N" HIW "食指虛點，指尖頓時生出半尺吞吐不定的"
                        "青芒，宛若一束無形劍氣。\n" NOR, me);

        weapon = new("/clone/weapon/jianqi");
        weapon->move(me);
        weapon->wield();

        me->start_call_out((: call_other, __FILE__, "dest_sword",
                              me :), 50);

        if (me->is_fighting())
                me->start_busy(1);

        return 1;
}

void dest_sword(object me)
{
        object weapon;

        if( objectp(weapon=query_temp("weapon", me) )
            && query("skill_type", weapon) == "sword"
            && query("id", weapon) == "jianqi" )
        {
                if (me->is_fighting())
                        me->start_call_out((: call_other, __FILE__, "dest_sword",
                                              me :), 2);
                else
                        destruct(weapon);
        }
}