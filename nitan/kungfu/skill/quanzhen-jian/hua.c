// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "一氣化三清" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;
        int is_yunv = 0;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 200)
                return notify_fail("你全真劍法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("你的先天功不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("你沒有激發全真劍法，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你沒有激發先天功，難以施展" + name() + "。\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "一聲長吟，將內力全然運到劍上，" + weapon->name() +
              HIW "劍脊頓時" HIM "紫芒" HIW "閃耀，化作數道劍氣勁逼$n"
              HIW "。\n" NOR;

        ap = attack_power(me, "sword") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (stringp(target->query_skill_mapped("sword")) &&
            target->query_skill_mapped("sword") == "yunv-jian" &&
            query_temp("weapon", target) &&
            query("skill_type", query_temp("weapon", target)) == "sword")
        {
                dp += target->query_skill("yunv-jian", 1);
                is_yunv = 1;
        }

        me->start_busy(3);
        addn("neili", -200, me);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "頓時只聽$n" HIR "一聲慘叫，劍氣及"
                                           "身，身上接連射出數道血柱。\n" NOR);
                message_combatd(msg, me, target);

                if (ap / 2 + random(ap) > dp)
                {
                        count = me->query_skill("xiantian-gong", 1) / 2;
                        addn_temp("apply/attack", count, me);
                        message_combatd(HIY "$N" HIY "見$n" HIY "在這一擊之下破"
                                        "綻迭出，頓時身形前躍，唰唰唰又是三劍。"
                                        "\n" NOR, me, target);

                        for (i = 0; i < 3; i++)
                        {
                                if (! me->is_fighting(target))
                                        break;
                                COMBAT_D->do_attack(me, target, weapon, 0);
                        }
                        addn_temp("apply/attack", -count, me);
                }
        } else
        {
                if (is_yunv)
                        msg += CYN "卻見$n" CYN "微微一笑，反手一招“玉女劍法”，輕鬆地檔住了$N的劍招。\n" NOR;
                else
                        msg += CYN "可是$n" CYN "看破了$N" CYN "的企圖，斜躍避開。\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}
