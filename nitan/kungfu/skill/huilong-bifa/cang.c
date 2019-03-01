#include <ansi.h>
#include <combat.h>

#define CANG "「" HIY "掌藏龍" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object anqi;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/huilong-bifa/cang", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(CANG "只能在戰鬥中對對手使用。\n");

        if( !objectp(anqi=query_temp("handing", me)) || 
            query("skill_type", anqi) != "throwing" )
                return notify_fail("你現在手中並沒有拿著暗器。\n");

        if ((int)me->query_skill("huilong-bifa", 1) < 120)
                return notify_fail("你的回龍璧法不夠嫻熟，難以施展" CANG "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" CANG "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你內力不夠了。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "一聲輕喝，單手一揚，袖底頓時迸出一股氣勁，袖中" +
              query("name", anqi)+NOR+HIY"便如蛟龍般射向$n"HIY"！\n"
              NOR;

        ap = me->query_skill("force") + me->query_skill("throwing");
        dp = target->query_skill("dodge") + target->query_skill("parry");
        me->start_busy(3);

        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap / 2 + random(ap / 2);
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 40,
                                           HIR "$n" HIR "只覺勁風襲體，低頭間，發"
                                           "現"+query("name", anqi)+NOR+HIR
                                           "正端端插在自己胸口，頓時驚怒交集，嘔"
                                           "出一口鮮血。\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，飛"
                       "身一躍而起，躲避開來。\n" NOR;
        }

        if( query("id", anqi) == "huilongbi" )
        {
                msg += HIC "霎時卻見回龍璧凌空一個盤旋，又飛回到$N"
                       HIC "手中。\n" NOR;
        }
        message_combatd(msg, me, target);

        if( objectp(anqi) && query("id", anqi) != "huilongbi" )
                destruct(anqi);

        return 1;
}