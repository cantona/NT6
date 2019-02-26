#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "一指乾坤" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("sun-finger", 1) < 100)
                return notify_fail("你一陽指訣不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 160)
                return notify_fail("你對經絡學瞭解不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("你沒有激發一陽指訣，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("你沒有準備一陽指訣，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "陡然使出「" HIR "一指乾坤" HIY "」絕技，單指勁"
              "點$n" HIY "檀中要穴，招式變化精奇之極！\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force") + me->query_skill("qiantian-zhi", 1);
        dp = defense_power(target, "parry") + me->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"運用氣脈流轉的輔助，使得一指乾坤傷害更強。\n"NOR;
                }
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "只覺胸口一麻，已被$N" HIR
                                           "一指點中，頓時氣血上湧，噴出數口鮮血"
                                           "。\n" NOR);
                addn("neili", -100, me);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "可是$n" CYN "看破了$N" CYN "的招"
                       "數，連消帶打擋開了這一指。\n" NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
