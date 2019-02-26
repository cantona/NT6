#include <ansi.h>
#include <combat.h>

#define SHI "「" HIR "噬血穹蒼" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int i, count;

        if( userp(me) && !query("can_perform/xuedao-dafa/shi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHI "只能對戰鬥中的對手使用。\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" SHI "。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候不夠，難以施展" SHI "。\n");

        if ((int)me->query_skill("xuedao-dafa", 1) < 180)
                return notify_fail("你的血刀大法還不到家，難以施展" SHI "。\n");

        if (me->query_skill_mapped("force") != "xuedao-dafa")
                return notify_fail("你沒有激發血刀大法為內功，難以施展" SHI "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-dafa")
                return notify_fail("你沒有激發血刀大法為刀法，難以施展" SHI "。\n");

        if( query("qi", me)<100 )
                return notify_fail("你目前氣血翻滾，難以施展" SHI "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你目前真氣不足，難以施展" SHI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap=attack_power(me,"blade")+query("str", me)*10;
        dp=defense_power(target,"dodge")+query("dex", target)*10;

        msg = HIY "$N" HIY "陡然施出「" HIR "噬血穹蒼" HIY "」，手中" +
              weapon->name() + HIY "騰起無邊殺意，攜着風雷之勢向$n" HIY
              "劈斬而去！\n"NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
                                           HIR "$n" HIR "只覺眼前一蓬血雨噴灑而出"
                                           "，已被$N" HIR "這一刀劈了個正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "只見$P" CYN "來勢洶湧，難以抵擋，當"
                       "即飛身朝後躍出數尺。\n" NOR;
        }

        msg += HIY "\n緊接着$N" HIY "嗔目大喝，手中" + weapon->name() +
               HIY "一振，迸出漫天血光，鋪天蓋地灑向$n" HIY "！\n"NOR;

        if (random(me->query_skill("blade")) > target->query_skill("parry") / 2)
        {
                msg += HIR "霎時間$n" HIR "只覺周圍殺氣瀰漫，全身氣血翻"
                       "滾，甚難招架。\n" NOR;
                count = me->query_skill("xuedao-dafa", 1) / 4;
        } else
        {
                msg += HIY "霎時間$n" HIY "只覺周圍殺氣瀰漫，心底微微一"
                       "驚，連忙奮力招架。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        addn_temp("apply/attack", count, me);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->receive_wound("qi", 80);
        addn_temp("apply/attack", -count, me);
        me->start_busy(3 + random(5));
        addn("neili", -200-random(300), me);
        return 1;
}