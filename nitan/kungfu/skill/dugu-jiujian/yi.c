// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define YI "「" HIY "劍意" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, skill;
        int damage;

        skill = me->query_skill("dugu-jiujian", 1);

        if (skill < 90)
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if( userp(me) && !query("can_perform/dugu/yi", me) )
                return notify_fail("你還沒有受過高人指點，無法施展" YI "。\n"); 
                
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(YI "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" YI "。\n");

        if (me->query_skill_mapped("sword") != "dugu-jiujian") 
                return notify_fail("你沒有激發獨孤九劍，難以施展" YI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        switch (random(3))
        {
        case 0:
                msg = HIY "$N" HIY "隨手一劍指向$n" HIY "，落點正是$n"
                      HIY "破綻所在，神劍之威，當真人所難測。\n" NOR;
                break;

        case 1:
                msg = HIY "$N" HIY "劍招大開大闔，看似雜亂無章，但招"
                      "招皆擊$n" HIY "攻勢中破綻，有如神助。\n" NOR;
                break;

        default:
                msg = HIY "$N" HIY "反手橫劍刺向$n" HIY "，這似有招似"
                      "無招的一劍竟然威力奇大，令人匪夷所思。\n" NOR;
                break;
        }

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry") +
             target->query_skill("dugu-jiujian");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = damage_power(me, "sword") * 3 / 2;
                target->receive_damage("jing", damage / 2, me);
                target->receive_wound("jing", damage / 3, me);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 100,
                                           HIR "$n" HIR "全然無法領會$N" HIR "劍"
                                           "招中的奧妙，一個疏神，登遭重創！\n" NOR);
                if (! target->is_busy())
                target->start_busy(3 + random(2)); 
                me->start_busy(2);
        } else 
        {
                msg += CYN "可$n" CYN "淡然處之，並沒將$N"
                       CYN "此招放在心上，隨手架開，不漏半點破綻。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
