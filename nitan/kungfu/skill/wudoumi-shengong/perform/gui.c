#include <ansi.h>
#include <combat.h>

#define GUI "「" HIR "歸去來兮" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if( userp(me) && !query("can_perform/wudoumi-shengong/gui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(GUI "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" GUI "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功修為不夠，難以施展" GUI "。\n");

        if ((int)me->query_skill("wudoumi-shengong", 1) < 140)
                return notify_fail("你的五鬥米神功不夠嫻熟，難以施展" GUI "。\n");

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣不夠，難以施展" GUI "。\n");

        if (me->query_skill_mapped("force") != "wudoumi-shengong")
                return notify_fail("你沒有激發五鬥米神功為內功，難以施展" GUI "。\n");

        if (me->query_skill_mapped("unarmed") != "wudoumi-shengong")
                return notify_fail("你沒有激發五鬥米神功為拳腳，難以施展" GUI "。\n");

        if (me->query_skill_prepared("unarmed") != "wudoumi-shengong")
                return notify_fail("你現在沒有準備使用五鬥米神功，難以施展" GUI "。\n");

        if( !query_temp("powerup", me) )
                return notify_fail("你未將全身功力盡數提起，難以施展" GUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        damage = damage_power(me, "force");
        
        ap=attack_power(me,"force")+query("con", me)*10;
        dp=defense_power(target,"dodge")+query("dex", target)*10;

        msg = HIR "$N" HIR "一聲斷喝，雙掌施出五鬥米神功「歸去來兮」絕技，頓時掌"
              "勁澎湃，湧向$n" HIR "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$p" HIR "急忙奮力格擋，可只一瞬間"
                                           "，$P" HIR "的掌勁已透體而入，接連震斷"
                                           "數根肋骨！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "見$P" CYN "來勢洶湧，不敢硬接"
                       "，只得小巧騰挪，躲閃開來。\n" NOR;
        }

        ap = attack_power(me, "force") + me->query_con();
        dp = defense_power(target, "dodge") + target->query_dex();

        msg += "\n" HIR "緊接著只見$N" HIR "雙手陡然回圈，竟使已襲出的掌勁倒回"
               "，從$n" HIR "身後再度席卷而歸。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$p" HIR "大驚之下，竟然僵直而立，$P"
                                           HIR "澎湃的掌勁頓時穿透胸膛，盡傷五臟六"
                                           "腑！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "大驚之下急忙飛身躍起，終于躲開"
                       "了這神鬼莫測的一擊。\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -600, me);
        message_combatd(msg, me, target);
        return 1;
}