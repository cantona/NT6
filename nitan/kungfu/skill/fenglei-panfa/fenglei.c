#include <ansi.h>
#include <combat.h>

#define FENG "「" HIR "風雷四擊" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if( userp(me) && !query("can_perform/fenglei-panfa/fenglei", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FENG "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "hammer" )
                return notify_fail("你目前所裝備的武器無法使用出" FENG "。\n");

        if (me->query_skill_mapped("hammer") != "fenglei-panfa")
                return notify_fail("你沒有激發風雷盤法，不能使用" FENG "。\n");

        if ((int)me->query_skill("fenglei-panfa", 1) < 150)
                return notify_fail("你的風雷盤法不夠嫻熟，還使不出" FENG "。\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" FENG "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在真氣不夠，難以施展" FENG "。\n"NOR);

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        wname = weapon->name();

        damage = (int)me->query_skill("fenglei-panfa", 1) / 2;
        damage += random(damage / 2);

        // 風起雲湧
        ap = me->query_skill("hammer");
        dp = target->query_skill("dodge");
        msg = "\n" HIW "$N" HIW "喝道：“風起雲湧！”身形陡然加快，單手高舉"
               + wname + HIW "，便如狂風一般襲向$n" HIW "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$p" HIR "一楞，只見$P" HIR "身形"
                                           "一閃，已晃至自己跟前，躲閃不及，被這"
                                           "招擊個正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷靜非凡，絲毫不為這奇幻的招數"
                       "所動，凝神抵擋，不漏半點破綻！\n" NOR;
        }

        // 狂風驟雨
        ap = me->query_skill("hammer");
        dp = target->query_skill("dodge");
        msg += "\n" WHT "$N" WHT "喝道：“狂風驟雨！”手中" + wname + WHT "一"
               "陣狂舞，氣勢如虹，鋪天蓋地連續向$n" HIW "攻去。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 32,
                                           HIR "$p" HIR "一楞，只見$P" HIR "身形"
                                           "一閃，已晃至自己跟前，躲閃不及，被這"
                                           "招擊個正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷靜非凡，絲毫不為這奇幻的招數"
                       "所動，凝神抵擋，不漏半點破綻！\n" NOR;
        }

        // 雷霆萬鈞
        ap = me->query_skill("hammer");
        dp = target->query_skill("force");
        msg += "\n" HIM "$N" HIM "喝道：“雷霆萬鈞！”躍至半空，手中" + wname
               + HIM "一個盤旋，攜着萬鈞之勁凌空貫向$n" HIM "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 33,
                                           HIR "$p" HIR "一楞，只見$P" HIR "身形"
                                           "一閃，已晃至自己跟前，躲閃不及，被這"
                                           "招擊個正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷靜非凡，絲毫不為這奇幻的招數"
                       "所動，凝神抵擋，不漏半點破綻！\n" NOR;
        }

        // 電閃雷鳴
        ap = me->query_skill("hammer");
        dp = target->query_skill("parry");
        msg += "\n" HIY "$N" HIY "喝道：“電閃雷鳴！”猛地向前直衝數尺，手中"
               + wname + HIY "幻出一道黃芒，閃電一般射出。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "$p" HIR "一楞，只見$P" HIR "身形"
                                           "一閃，已晃至自己跟前，躲閃不及，被這"
                                           "招擊個正中。\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "冷靜非凡，絲毫不為這奇幻的招數"
                       "所動，凝神抵擋，不漏半點破綻！\n" NOR;
        }

        me->start_busy(2 + random(5));
        addn("neili", -400-random(100), me);
        message_combatd(msg, me, target);
        return 1;
}