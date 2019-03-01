#include <ansi.h>
#include <combat.h>

#define LONG "「" HIC "天外玉龍" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int neili, hit_point, time;

        /*
        if( userp(me) && !query("can_perform/poyang-jian/long", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");
        */

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" LONG "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，難以施展" LONG "。\n");

        if (me->query_skill("poyang-jian", 1) < 180)
                return notify_fail("你的破陽冷光劍修為不夠，難以施展" LONG "。\n");

        if ((int)me->query_skill("dodge") < 200)
                return notify_fail("你的輕功火候不夠，難以施展" LONG "。\n"); 

        if( query("max_neili", me)<2700 )
                return notify_fail("你的內力修為不足，難以施展" LONG "。\n");

        if( query("neili", me)<350 )
                return notify_fail("你的真氣不夠，難以施展" LONG "。\n");

        if (me->query_skill_mapped("sword") != "poyang-jian")
                return notify_fail("你沒有激發破陽冷光劍，難以施展" LONG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");
        
        if( !query("real_perform/poyang-jian/long", me) )
        {
                msg = HIY "\n只見$N" HIY "手中" + weapon->name() + HIY
                      "橫掃而出，施出絕招「" HIC "天外玉龍" HIY "」，"
                      "劍勢縱橫，猶如一條長龍蜿蜒而出，刺向$n\n" HIY "。" NOR;
               
                neili = 220;
                hit_point = 55;
                time = 2 + random(2);
        }

        else
        {
                msg = HIW "\n但見$N" HIW "手中" + weapon->name() + HIW 
                      "自半空中橫過，劍身似曲似直，便如一件活物一般，正"
                      "是破陽冷光劍的精髓「" HIY "天外玉龍" HIW "」，一"
                      "柄死劍被$N" HIW "使得如靈蛇，如神龍，猛然劍刺向$n\n" 
                      HIW "。" NOR;

                neili = 300;
                hit_point = 80;
                time = 3 + random(4);
        }
        message_sort(msg, me, target);

        ap = me->query_skill("sword");

        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -neili, me);
                me->start_busy(time);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, hit_point,
                                           HIR "$n" HIR "見此招來勢兇猛， 阻擋不"
                                           "及， 頓時被" + weapon->name() + HIR 
                                           "所傷，苦不堪言。\n" NOR);
        } else
        {
                addn("neili", -150, me);
                me->start_busy(1 + random(2));
                msg = CYN "可卻見" CYN "$n" CYN "猛的拔地而起，避開了"
                      CYN "$N" CYN "來勢兇猛的一招。\n" NOR;
        }
        message_vision(msg, me, target);

        return 1;
}