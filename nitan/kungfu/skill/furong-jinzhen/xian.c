#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

#define XIAN "「" HIY "金針現影" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage, p;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/furong-jinzhen/xian", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿著暗器。\n");

        if ((int)me->query_skill("furong-jinzhen", 1) < 80)
                return notify_fail("你的芙蓉金針不夠嫻熟，難以施展" XIAN "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，難以施展" XIAN "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你內力不夠了。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -100, me);
        weapon->add_amount(-1);

        msg = HIY "只見$N" HIY "五指陡然箕張，$n" HIY "但覺眼前金光一"
              "閃，數股勁風隨即撲面而來！\n" NOR;

        me->start_busy(2);

        ap = me->query_skill("force") + me->query_skill("throwing");
        dp = target->query_skill("dodge") + target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 5 + random(ap / 5);

                msg += HIR "$n" HIR "微微一愣，卻已被$N" HIR
                       "那"+query("base_unit", weapon)+
                       weapon->name() + HIR "正中要穴，入肉"
                       "半寸之深。\n" NOR;

                target->receive_wound("qi", damage, me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+100);

                p=query("qi", target)*100/query("max_qi", target);

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);

        } else
        {
                msg += CYN "可是$p" CYN "早料得$P" CYN
                       "有此一著，急忙飛身躍起，躲閃開來。"
                       "\n" NOR;
                message_combatd(msg, me, target);
        }
        me->reset_action();
        return 1;
}