// yong.c 玄黃連環掌

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("玄黃連環掌只能對戰鬥中的對手使用。\n");
 
        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法施展玄黃連環掌！\n");

        if ((lvl = me->query_skill("bluesea-force", 1)) < 150)
                return notify_fail("你的南海玄功火候不夠，無法施展玄黃連環掌！\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("你沒有激發南海玄功為掌法，無法施展玄黃連環掌！\n");

        if (me->query_skill_prepared("strike") != "bluesea-force")
                return notify_fail("你沒有準備好使用南海玄功，無法施展玄黃連環掌！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "輕輕劃了個圈子，身形忽然變快，合數招為一擊攻向$n"
              HIC "！\n" NOR;
        i = 5;
        if (lvl + random(lvl) > (int)target->query_skill("force") * 2 / 3)
        {
                msg += HIY "內力激盪之下，$n" HIY "登時覺得呼吸"
                       "不暢，渾身有如重壓，萬分難受，只見$N"
                       HIY "一掌接一掌的攻到，有如海浪。\n" NOR;
                count = me->query_skill("bluesea-force", 1) / 5;
                addn_temp("apply/attack", count, me);
                i += random(5);
        } else
        {
                msg += CYN "$n" CYN "見來掌奇快，只好振作精神勉力抵擋。\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        addn("neili", -i*20, me);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 4 && ! target->is_busy())
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        addn_temp("apply/attack", -count, me);
        me->start_busy(1 + random(7));
        return 1;
}