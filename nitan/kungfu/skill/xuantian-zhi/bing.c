#include <ansi.h>
#include <combat.h>

#define BING "「" HIW "冰堅地獄" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/xuantian-zhi/bing", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(BING "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用" BING "。\n");         

        if (me->query_skill_mapped("finger") != "xuantian-zhi")
                return notify_fail("你沒有激發玄天指，不能使用" BING "。\n");

        if (me->query_skill_prepared("finger") != "xuantian-zhi")
                return notify_fail("你現在沒有準備使用玄天指，無法使用" BING "。\n");

        if ((int)me->query_skill("xuantian-wujigong", 1) < 180)
                return notify_fail("你的玄天無極功火候不夠，使不出" BING "。\n");

        if ((int)me->query_skill("xuantian-zhi", 1) < 180)
                return notify_fail("你的玄天指不夠熟練，不會使用" BING "。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不足，無法使用" BING "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法使用" BING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "默運玄天無極功，頓時一層寒霜籠罩全身，一聲冷"
              "笑，聚力於指，直戳$n" HIW "要穴！\n"NOR;  

        lvl = me->query_skill("xuantian-zhi", 1);

        ap=me->query_skill("finger")+query("con", me)*5;
        dp=target->query_skill("force")+query("con", target)*5;

        me->start_busy(4);
        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                addn("neili", -400, me);
                target->affect_by("xuantian_zhi",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));
                                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                         damage, 70, HIW "$n" HIW "稍不留神，已被$P" HIW
                                         "一指點中，陰寒之勁頓時侵入三焦六脈。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "來勢洶湧，急忙提氣躍開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}