// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "我必還之" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int per;

        /*
        if( query("family/family_name", me) != "血刀門" )
                return notify_fail("你不是血刀門弟子，無法使用" + name() + "。\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法使用" + name() + "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if( me->is_busy() )
                return notify_fail("你正忙着呢。\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 1000)
                return notify_fail("你的血刀大法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你沒有激發血刀大法為刀法，難以施展" + name() + "。\n");

        if( query("qi", me)<100 )
                return notify_fail("你目前氣血翻滾，難以施展" + name() + "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你目前真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        msg = HIR "$N" HIR "手中" + weapon->name() + "直指$n" HIR"，口中喝罵道：「灑傢什麼都吃就是不知虧！人若傷我！我必還之！」\n"
              HIR "只見" + weapon->name() + "泛出濃烈血光、腥味刺鼻，映的四周直若濃血地獄。\n";

        if (ap / 2 + random(ap) > dp)
        {
                target->set_weak(5);
                per=query("eff_qi", me)*100/query("max_qi", me);
                if (per > 60)
                {
                        damage = damage_power(me, "blade");
                        damage+= query("jiali", me);
                }
                else
                if (per < 20)
                        damage = -1;
                else
                        damage=query("max_qi", target)*per/100;

                addn("neili", -150, me);
                me->start_busy(2);

                if (damage > 0)
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           HIR "在$n" HIR "眼中，" + weapon->name() + "的刀尖越來越大、壓的自己幾乎透不過氣，"
                                           HIR "直至猛然一嘔血，卻發現" + weapon->name() + "已經在自己身上留下猙獰的軌跡。\n" NOR);
                else
                {
                        msg += HIR "在$n" HIR "眼中，" + weapon->name() + "的刀尖越來越大、壓的自己幾乎透不過氣，"
                               HIR "直至猛然一嘔血，卻發現" + weapon->name() + "已經在自己身上留下猙獰的軌跡。\n" NOR;
                        target->die(me);
                }
        } else
        {
                me->start_busy(2);
                msg += CYN "正當這刀要落在$n" CYN "身上，$N" CYN "渾身一顫，血光驟減，$n" CYN "順勢滾到一旁，已是不成招法，躲過了$N"
                       CYN "的必殺一刀。\n"NOR;
                addn("neili", -100, me);
        }

        message_combatd(msg, me, target);
        return 1;
}

