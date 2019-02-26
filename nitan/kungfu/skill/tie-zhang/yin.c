#include <ansi.h>
#include <combat.h>

string name() { return HIR "陰陽磨" NOR; }

inherit F_SSERVER;

string finala(object me, object target, int damage);
string finalb(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp, dd;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tie-zhang", 1) < 220)
                return notify_fail("你鐵掌掌法火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你沒有激發鐵掌掌法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你沒有準備鐵掌掌法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "施出鐵掌絕技「" HIR "陰陽磨"
              HIW "」，左掌不着半點力道，攜着陰寒勁向$n"
              HIW "拂去。\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*15;
        dp=defense_power(target,"parry")+target->query_con()*15;
        dd=defense_power(target,"dodge")+target->query_dex()*15;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me,"strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                           (: finala, me, target :));
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "掌出如風，心知"
                       "此招後着極是凌厲，當即斜跳閃開。\n" NOR;
        }

        msg += HIR "\n緊接着$N" HIR "右掌一振，掌風過處，竟席"
               "捲起一股熱浪，向$n" HIR "胸前猛然拍落。\n" NOR;

        if (ap / 2 + random(ap) > dd)
        {
                damage = damage_power(me,"strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           (: finalb, me, target :));
        } else
        {
                msg += CYN "$n" CYN "忽聞呼嘯聲大至，眼見$N" CYN
                       "掌勢如虹，急忙縱躍躲避開來。\n" NOR;
        }
        me->start_busy(2 + random(2));
        addn("neili", -400, me);
        message_combatd(msg, me, target);
        return 1;
}

string finala(object me, object target, int damage)
{
        int lvl;
        lvl = me->query_skill("strike");

        target->affect_by("tiezhang_yin",
                       (["level":query("jiali", me)+random(query("jiali", me)/2),
                          "id":query("id", me),
                          "duration" : lvl / 50 + random(lvl / 50) ]));

        return HIW "霎那間$n" HIW "已被$N" HIW "陰寒掌勁拂中要"
               "害，不由得渾身一顫，難受之極。\n" NOR;
}

string finalb(object me, object target, int damage)
{
        int lvl;
        lvl = me->query_skill("strike");

        target->affect_by("tiezhang_yang",
                       (["level":query("jiali", me)+random(query("jiali", me)/2),
                          "id":query("id", me),
                          "duration" : lvl / 50 + random(lvl / 50) ]));

        return HIR "只聽嗤的一聲，$N" HIR "右掌如擊敗革，正中"
               "$n" HIR "胸口，震斷了數根肋骨。\n" NOR;
}