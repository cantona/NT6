// jingshen.c 六脈驚神

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "六脈驚神"; }

int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int skill, skill2;
        int damage, n;

        int i;
        i = me->query_skill("six-finger", 1) - 50;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「六脈驚神」只能對戰鬥中的對手使用。\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("你沒有激發六脈神劍，無法施展「六脈驚神」。\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("你沒有準備使用六脈神劍，無法施展「六脈驚神」。\n");

        skill = me->query_skill("six-finger", 1);
        skill2 = me->query_skill("sun-finger", 1);
        if (skill < 200)
                return notify_fail("你的六脈神劍修為有限，無法使用「六脈驚神」！\n");

        if (skill2 < 200)
                return notify_fail("你的一陽指修為有限，無法使用「六脈驚神」！\n");

        if (me->query_skill("force") < 400)
                return notify_fail("你的內功火候不夠，難以施展「六脈驚神」！\n");

        if( query("max_neili", me)<5000 )
                return notify_fail("你的內力修為沒有達到那個境界，無法運轉內力形成「六脈驚神」！\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須是空手才能施展「六脈驚神」！\n");

        if( query("neili", me)<500 )
                return notify_fail("你的真氣不夠，現在無法施展「六脈驚神」！\n");

        msg = HIY "$N" HIY "十指連動，忽伸忽縮，或點或按，空中氣流激盪，劍氣自"
              HIY "$N" HIY "指中洶湧而出，驚震四方！！\n"
              HIR "六劍連出，劍氣回盪，直割得$n眉毛削落，臉面生通，再也不能前進半分！\n" NOR;

        message_combatd(msg, me,target);

        damage = skill + skill2;
        if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 ) 
        {
                damage += damage * n * 15 / 100;
                msg = HIM"$N"HIM"運用氣脈流轉的輔助，使得六脈驚神傷害更強。\n"NOR; 
                message_combatd(msg, me,target);
        }
        addn_temp("apply/attack", i, me);
        addn_temp("apply/unarmed_damage", damage, me);
        {
                msg =  HIC "-------------------------少沖劍 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


                msg =  HIW "-------------------------少澤劍 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


                msg =  HIY "------------------------ 中沖劍 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


                msg =  HIG "-------------------------關沖劍 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


                msg =  HIM "-------------------------商陽劍 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);


                msg =  HIR "-------------------------少商劍 \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
        }
        addn_temp("apply/attack", -i, me);
        addn_temp("apply/unarmed_damage", -damage, me);
        addn("neili", -800, me);
        me->start_busy(3);
        return 1;
}
