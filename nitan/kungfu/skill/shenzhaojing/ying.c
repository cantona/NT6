#include <ansi.h>
#include <combat.h>

#define YING "「" HIR "無影神拳" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/shenzhaojing/ying", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(YING "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能施展" YING "。\n");

        if (me->query_skill_mapped("unarmed") != "shenzhaojing")
                return notify_fail("你沒有激發神照經神功為空手技能，無法施展" YING "。\n");

        if (me->query_skill_prepared("unarmed") != "shenzhaojing")
                return notify_fail("你現在沒有準備使用神照經神功，無法施展" YING "。\n");

        if ((int)me->query_skill("shenzhaojing", 1) < 200)
                return notify_fail("你的神照經神功火候不夠，無法施展" YING "。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳腳火候不夠，無法施展" YING "。\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為不足，無法施展" YING "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，無法施展" YING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "倏然躍近，無聲無影擊出一拳，去勢快極，拳影重"
              "重疊疊，直襲$n" HIR "而去。\n"NOR;

        lvl = me->query_skill("shenzhaojing", 1);

        ap=me->query_skill("force")+query("con", me)*5;
        dp=target->query_skill("force")+query("con", target)*5;

        me->start_busy(4);
        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                addn("neili", -400, me);
                target->affect_by("shenzhao", ([
                        "level":query("jiali", me)+random(query("jiali", me)),
                        "id":query("id", me),
                        "duration" : lvl / 50 + random(lvl / 20) ]));
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                               damage, 90, HIR "$n" HIR "見拳勢變換莫測，只是"
                               "微微一愣，已被$N" HIR "一拳正中胸口，神照經內"
                               "勁頓\n時便如山洪爆發一般，透體而入。\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "來勢洶湧，急忙提氣躍開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
