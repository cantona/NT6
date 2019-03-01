#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

#define JIA "「" HIY "掌中夾鏢" NOR "」"

inherit F_SSERVER;
int perform(object me, object target)
{
        int ap, dp, damage, p;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/bagua-zhang/jia", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIA "只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(JIA "只能空手施展。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿著暗器。\n");

        if (me->query_skill_mapped("strike") != "bagua-zhang") 
                return notify_fail("你沒有激發八卦掌，難以施展" JIA "。\n");

        if (me->query_skill_prepared("strike") != "bagua-zhang") 
                return notify_fail("你沒有準備八卦掌，難以施展" JIA "。\n");

        if (me->query_skill_mapped("throwing") != "bagua-biao") 
                return notify_fail("你沒有激發八卦鏢訣，難以施展" JIA "。\n");

        if ((int)me->query_skill("bagua-zhang", 1) < 120)
                return notify_fail("你的八卦掌不夠嫻熟，難以施展" JIA "。\n");

        if ((int)me->query_skill("bagua-biao", 1) < 120)
                return notify_fail("你的八卦鏢訣不夠嫻熟，難以施展" JIA "。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" JIA "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不足，難以施展" JIA "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -100, me);
        weapon->add_amount(-1);

        msg = HIY "$N" HIY "一聲暴喝，一掌重重擊向$n" HIY "，$p" HIY
              "正欲格擋，忽然只見眼前金光一閃，一股勁風已由$N" HIY
              "掌中激射而出！\n" NOR;

        me->start_busy(2);

        ap = me->query_skill("strike") + me->query_skill("throwing");
        dp = target->query_skill("dodge") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "throwing");
                msg += HIR "$n" HIR "果真始料不及，$N" HIR "那" +
                       query("base_unit", weapon)+weapon->name()+
                       HIR "正好打在$p" HIR "要穴上，頓時血氣上湧，"
                       "連退數步！\n" NOR;
                target->receive_damage("qi", damage * 3 / 2, me);
                target->receive_wound("qi", damage, me);
                p=query("qi", target)*100/query("max_qi", target);

                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+100);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);

        } else
        {
                msg += CYN "可是$p" CYN "早料得$P"
                       CYN "有此一著，哈哈一笑，斜跳閃開。\n" NOR;
                message_combatd(msg, me, target);
        }
        me->reset_action();
        return 1;
}