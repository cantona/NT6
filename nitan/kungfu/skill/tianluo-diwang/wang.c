// This program is a part of NITAN MudLIB
// wang.c 天羅地網 「天羅地網」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "天羅地網" NOR; }

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, ap, dp;

        skill = me->query_skill("tianluo-diwang", 1);

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「天羅地網」只能在戰鬥中使用。\n");

        if((int)me->query_str() < 25)
                return notify_fail("你臂力不夠,不能使用這一絕技!\n");

        if((int)me->query_skill("yunv-xinfa",1) < 100)
                return notify_fail("你玉女心經的功力不夠不能使用天羅地網!\n");

        if((int)me->query_skill("strike") < 120)
                return notify_fail("你的掌法修為不夠,目前還不能使用天羅地網絕技!\n");

        if( query("neili", me)<300 )
                return notify_fail("你內力現在不夠, 不能使用天羅地網! \n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧□\n");

        if( query_temp("luowang", target) )
                return notify_fail("對手已在你的天羅地網勢之中！\n");

        msg = HIM "\n但見$N雙臂飛舞，出手擋擊回臂反撲發掌奇快，但一招一式清清楚楚自成" +
              "段落，兩只手掌宛似化成了千手千掌！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += CYN "\n$n心下大駭，飛滾翻撲，始終逃不出$N只掌所圍作的圈子! \n" NOR;

                target->start_busy( 3 + skill / 100 );
                addn_temp("apply/defense", -skill/8, target);
                set_temp("luowang", 1, target);
                addn("neili", -150, me);
                remove_call_out("checking");
                call_out("checking", 1, me, target,skill);
                if( userp(target)) call_out("remove_effect", skill/20, me, target, skill);
                else call_out("remove_effect", skill/30, me, target, skill);
        }
        else
        {
                msg += HIY "\n可是$p氣定神弦，看破了$P的誘惑，縱身一躍，跳了開去。\n" NOR;
                me->start_busy(1+random(3));
                addn("neili", -100, me);
                return 1;
        }
        message_combatd(msg, me, target);
        return 1;
}

void checking(object me, object target, int skill)
{
        if( !objectp(target) || !objectp(me) ) return;
        if( query_temp("luowang_finished", target) )
                delete_temp("luowang_finished", target);
        else
        {
                if( !living(me) || me->is_ghost() )
                {
                        delete_temp("luowang", target);
                        addn_temp("apply/defense", skill/8, target);
                        remove_call_out("remove_effect");
                        message_combatd(HIG"慢慢的，$n已不似初見時那麼詫異萬分。\n\n"NOR,me,target);
                        return ;
                }
                if( !me->is_fighting() )
                {
                        delete_temp("luowang", target);
                        addn_temp("apply/defense", skill/8, target);
                        remove_call_out("remove_effect");
                        message_combatd(HIG"慢慢的，$n已不似初見時那麼詫異萬分。\n\n"NOR,me,target);
                        return ;
                }

                if( me->query_skill_mapped("strike") != "tianluo-diwang"
                ||  me->query_skill_prepared("strike") != "tianluo-diwang" )
                {
                        message_combatd(HIM"\n$N驟然變換招數，不能再繼續用天羅地網牽制對手的攻擊！\n"NOR, me);
                        delete_temp("luowang", target);
                        addn_temp("apply/defense", skill/8, target);
                        remove_call_out("remove_effect");
                        message_combatd(HIG"慢慢的，$n已不似初見時那麼詫異萬分。\n\n"NOR,me,target);
                        return ;
                }

                else
                        call_out("checking", 1, me, target,skill);
                return;
        }
        return;
}

int remove_effect(object me, object target, int skill)
{
        if (! objectp(target))
                return 0;

        delete_temp("luowang", target);
        addn_temp("apply/defense", skill/8, target);
        set_temp("luowang_finished", 1, target);

        message_combatd(HIG"慢慢的，$N已不似初見時那麼詫異萬分。\n\n"NOR, target);
        return 1;
}