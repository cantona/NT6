// hanxing-fada/lastrisk.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int i, skill;
        string msg;
        object *ob;
        object weapon;
        string pmsg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("孤注一擲只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" || 
            weapon->query_amount() < 1)
                return notify_fail("你手中必須先有暗器。\n");

        if ((skill = me->query_skill("hanxing-bada", 1)) < 60)
                return notify_fail("你的寒星八打修為太淺，無法施展孤注一擲。\n");

        msg = CYN "$N" CYN "孤注一擲，發出所有暗器攻向$n" CYN "！\n" NOR;
        me->start_busy(2);
        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/200 )
        {
                msg += HIR "結果$p" HIR "被$P" HIR "攻了個措手不及，中了數枚暗器！\n" NOR;
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+120);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
        } else
        {
                msg += CYN "可是$p" CYN "從容不迫的躲過了$P"
                       CYN "的最後一擊。\n" NOR;
        }

        message_combatd(msg, me, target);
        destruct(weapon);
        me->reset_action();
        return 1;
}