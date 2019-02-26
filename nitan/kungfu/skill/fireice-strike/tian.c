// This program is a part of NT MudLIB
// binghuo.c 烈焰寒冰掌--

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "冰火二重天"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage, ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character()
        ||  !me->is_fighting(target))
                return notify_fail("「冰火二重天」只能在戰鬥中使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展「冰火二重天」。\n");

        if( (int)me->query_skill("fireice-strike", 1) < 150 )
                return notify_fail("你的烈焰寒冰掌功夫還不夠嫻熟，不會使用「冰火二重天」。\n");

        if(me->query_skill("yunv-xinfa", 1) < 120)
                return notify_fail("以你現在的玉女心法還使不出「冰火二重天」。\n");

        if ( me->query_skill_mapped("strike") != "fireice-strike" )
                return notify_fail("你現在無法使用「冰火二重天」進行攻擊。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為太弱，不能使用「冰火二重天」！\n");

        if( query("neili", me)<800 )
                return notify_fail("你的真氣不夠！\n");

        if( !living(target) )
                return notify_fail("對方已經這樣了，用不着使這麼大力氣吧。\n");

        if ("jiuyang-shengong" == target->query_skill_mapped("force"))
        {
                msg = HIR"$N" HIR"左手手心隱隱透紅光，一股熾熱掌氣向" HIR"$n" HIR"迎臉撲來！\n" NOR;

                dp = target->query_skill("force",1) / 4;

                if (random(me->query_skill("force",1)) > dp)
                {
                       addn("neili", -100, me);
                       msg += HIY "$n一見之下，暗運九陽神功作出抵抗！！臉色轉了幾轉，安然無恙！\n"NOR;
                }  else
                {
                       me->start_busy(3);
                       addn("neili", -200, me);
                       msg += HIW"$p" HIW"大喝一聲“來的正好！”猛運九陽真氣，\n"
                              HIR"$N" HIR"的掌力竟被反震，血氣翻騰！連退數步！\n"NOR;
                }
        }  else
        {
                msg = HIR "\n$N" HIR "左手手心隱隱透紅光，一股熾熱掌氣直襲" HIR "$n" HIR "胸口！\n"NOR;

                ap = attack_power(me, "strike");
                dp = defense_power(target, "parry");
                if (ap / 2 + random(ap) > dp)
                {
                        //me->start_busy(1);
                        if( !target->is_busy() )
                                target->start_busy(1);

                        addn("neili", -300, me);
                        damage = damage_power(me, "strike");
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                HIR "$n" HIR" 頓時覺得胸口如被火燒，一口真氣難以繼回，!!\n"NOR);

                        if( me->query_skill("fireice-strike", 1) > 150 )
                                call_out("perform2", 0, me, target);
                }
                else
                {
                        me->start_busy(3);
                        addn("neili", -100, me);
                        msg += HIW"可是$p一個巧雲翻身，遠遠的躲了開去。\n"NOR;
                }
        }
        message_combatd(msg, me, target);
        return 1;
}

int perform2(object me, object target)
{
        string msg;
        int damage, ap, dp;

        if (!me || !target || environment(me) != environment(target)) return 0;
        if(!living(target))
                return notify_fail("對手已經不能再戰鬥了。\n");

        if( query("neili", me)<600 )
                return notify_fail("你待要再出第二掌，卻發現自己的內力不夠了！\n");

        msg = HIB "\n接着" HIB "$N" HIB "你揮出右手，手心竟是暗隱寒勁，以巧妙角度向" HIB "$n" HIB "拍過去!\n"NOR;
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);

                addn("neili", -300, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                HIW  "結果一掌擊中，" HIW "$n" HIW "只覺得全身氣脈通道如遭凍結，臉色一下變白！\n"NOR);
        }
        else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                msg += HIY "\n$p" HIY "眼看寒氣逼人，暗生警覺，順勢跳了開去。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
