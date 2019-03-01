#include <ansi.h>

#include <combat.h>

string name() { return HIC "天外清音" NOR; }

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yuxiao-jianfa")
                return notify_fail("你沒有激發玉簫劍法，難以施展" + name() + "。\n");

        skill = me->query_skill("yuxiao-jianfa", 1);

        if (skill < 120)
                return notify_fail("你玉簫劍法等級不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("bibo-shengong", 1) < 120)
                return notify_fail("你碧波神功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "一聲清嘯，手中" + weapon->name() +
              HIC "劍發琴音，閃動不止，劍影如夜幕般撲向$n" HIC "。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -120, me);
                qi_wound = damage_power(me, "sword");
                qi_wound+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, qi_wound, 70,
                                           HIR "$n" HIR "頓時覺得眼前金光亂閃動，雙耳嗡嗡"
                                           "內鳴，全身便如針紮一般！\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -50, me);
                msg += CYN "可是$n" CYN "寧心靜氣，隨手揮洒，將$N"
                       CYN "的招數撇在一邊。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}