#include <ansi.h>
#include <combat.h>

#define TAN "「" HIW "雲中探爪" NOR "」"
 
inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, damage;

        if( userp(me) && !query("can_perform/panlong-zhao/tan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(TAN "只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" TAN "。\n");

        skill = me->query_skill("panlong-zhao", 1);

        if (skill < 130)
                return notify_fail("你的越空盤龍爪等級不夠，難以施展" TAN "。\n");
 
        if (me->query_skill_mapped("claw") != "panlong-zhao") 
                return notify_fail("你沒有激發越空盤龍爪，難以施展" TAN "。\n");

        if (me->query_skill_prepared("claw") != "panlong-zhao") 
                return notify_fail("你沒有準備越空盤龍爪，難以施展" TAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" TAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "伸出兩掌，朝$n" HIW "拍去，待掌至中途，卻變掌為爪，幻作兩"
              "道金光襲向$n" HIW "各處要脈！\n" NOR;
 
        ap = me->query_skill("claw");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -150, me);
                damage = 60 + ap / 3 + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "$p" HIR "面對$P" HIR "這電光火石般"
                                           "的雙抓，更本無從招架，登時被抓得血肉飛"
                                           "濺！\n" NOR);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN
                       "的招式，巧妙的招架開來，沒露半點破綻！\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}