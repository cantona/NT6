#include <ansi.h>
#include <combat.h>

#define PO "「" HIC "破穹" HIW "雲" HIC "蛟" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if( userp(me) && !query("can_perform/qixing-shou/po", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PO "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" PO "。\n");

        if ((int)me->query_skill("qixing-shou", 1) < 150)
                return notify_fail("你七星分天手不夠嫻熟，難以施展" PO "。\n");

        if (me->query_skill_mapped("hand") != "qixing-shou")
                return notify_fail("你沒有激發七星分天手，難以施展" PO "。\n");

        if (me->query_skill_prepared("hand") != "qixing-shou")
                return notify_fail("你沒有準備七星分天手，難以施展" PO "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功修為不夠，難以施展" PO "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" PO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        damage = (int)me->query_skill("qixing-shou", 1) / 2;
        damage += random(damage);

        ap = me->query_skill("hand");
        dp = target->query_skill("parry");
        msg = HIC "$N" HIC "雙目圓睜，單手陡然一振，袖底頓時竄出一道" NOR + MAG
              "紫光" HIC "，直射$n" HIC "前胸。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "但見$P" HIR "這道氣勁來勢迅猛之極"
                                           "，$n" HIR "如何避得，頓時被紫勁震開了"
                                           "數尺！\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "見勢不妙，急忙向後縱開數尺，避開了$P"
                       CYN "這招。\n" NOR;
        }

        ap = me->query_skill("hand");
        dp = target->query_skill("dodge");
        msg += "\n" HIC "緊接着$N" HIC "左掌驀的一抬，憑空虛劃了道" HIY "弧芒" HIC
               "，至上而下反推$n" HIC "後頸。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 25,
                                           HIR "$p" HIR "只覺後頸一麻，已被$N" HIR
                                           "這招擊個正中，頓時全身癱軟，嘔出一口鮮"
                                           "血！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "絲毫不為$P"
                       CYN "所動，奮力格擋，穩穩將這一招架開。\n" NOR;
        }

        ap = me->query_skill("hand");
        dp = target->query_skill("force");
        msg += "\n" HIC "便在此時，卻見$N" HIC "雙掌猛然迴圈，平推而出，頓時層層"
               HIW "氣浪" HIC "直襲$n" HIC "。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$p" HIR "在$N" HIR "的猛攻之下，已"
                                           "再無餘力招架，竟被這一掌震得飛起，摔了"
                                           "出去！\n" NOR);
        } else
        {
                msg += CYN "然而$p" CYN "沉身聚氣，奮力一格，便將$P"
                       CYN "這掌驅於無形。\n" NOR;
        }
        me->start_busy(2 + random(3));
        addn("neili", -200, me);
        message_combatd(msg, me, target);
        return 1;
}