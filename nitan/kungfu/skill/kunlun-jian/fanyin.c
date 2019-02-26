#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, jing_wound;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「域外梵音」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("tanqin-jifa", 1) < 120)
                return notify_fail("你的彈琴技法尚且不夠熟練, 發不出「域外梵音」！\n");

        if (me->query_skill("kunlun-jian", 1) < 120)
                return notify_fail("你的崑崙劍法等級不夠, 發不出「域外梵音」！\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為尚且無法達到使用「域外梵音」所需的境界！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，運足「域外梵音」所需的內力！\n");

        msg = MAG "$N微微一笑，左手橫握劍柄，右手五指對準" + weapon->name() + NOR + MAG"劍脊輕輕彈撥，劍身微顫，聲若龍吟。\n頓時發出一陣清脆的琴音......\n" NOR;

        skill = me->query_skill("kunlun-jian",1);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                jing_wound = damage_power(me, "sword") +
                           (int)me->query_skill("tanqin-jifa", 1) * 2;

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, jing_wound, 96,
                                           MAG "$n頓時只覺琴音猶如兩柄利劍一般刺進雙耳，剎那間頭暈目眩，全身刺痛！\n" NOR);
                me->start_busy(2 + random(2));
        } else
        {
                addn("neili", -50, me);
                msg += HIG "可是$n趕忙寧心靜氣，收斂心神，絲毫不受$N琴音的干擾。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}
