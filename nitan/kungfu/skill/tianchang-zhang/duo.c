// duo.c 空手奪白刃

#include <ansi.h>

inherit F_SSERVER;

string name() { return "空手奪白刃"; }

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill;
        int comb1,comb2;
        mixed exp1, exp2;
        int skill1,skill2,neili1,neili2,str1,str2;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("tianchang-zhang",1);

        if( !(me->is_fighting() ))
                return notify_fail("空手奪白刃只能對戰鬥中的對手使用。\n");

        if( objectp(weapon2=query_temp("weapon", me)) )
                return notify_fail("你必須空手。\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("對方沒有兵刃，你不用擔心。\n");

        if( skill < 100)
                return notify_fail("你的天長掌法等級不夠, 不能使用空手奪白刃！\n");

        if ((int)me->query_skill("lengyue-shengong", 1)<100)
                return notify_fail("你的冷月神功火候不夠。\n");

        if ( me->query_skill_mapped("force") != "lengyue-shengong")
                return notify_fail("你沒有運用冷月神功！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠，無法使用空手摺梅！\n");

        if( !living(target))
                return notify_fail("對方都已經這樣了，還奪什麼，去撿好了！\n");

        message_combatd(CYN"\n$N閃電般伸出右手，瞅準$n武功破綻之處，抓向$n手中的"+query("name", weapon)+CYN"。\n\n"NOR,me,target);

        exp1=query("combat_exp", me);
        exp2=query("combat_exp", target);
        skill1 = me->query_skill("tianchang-zhang");
        skill2 = target->query_skill("parry");
        neili1=query("neili", me);
        neili2=query("neili", target);
        str1 = me->query_str();
        str2 = target->query_str();

        if (exp1 < exp2/3)
        {
                message_combatd("誰知$n露出此破綻乃是誘敵，一個變招反而向$N猛攻而至。\n",me,target);
                me->start_busy(1+random(3));
                addn("neili", -50, me);
                COMBAT_D->do_attack(target,me,query_temp("weapon", me));
                return 1;
        }

        if (exp1/ 100 > random(exp2/ 100))
        {
                message_combatd(HIR"$n眼睛一花，手中"+query("name", weapon)+HIR"已被$N反手抓到。\n\n"NOR,me,target);
                comb1 = str1*neili1*skill1;
                comb2 = str2*neili2*skill2;

                if (comb1 > comb2 * 3/5 )
                {
                        message_combatd(HIW"$n只覺一股寒氣自"+query("name", weapon)+HIW"傳了過來，整個手臂一陣冰涼，手中"+query("name", weapon)+HIW"脱手而出！\n"NOR,me,target);
                        weapon->unequip();
                        weapon->move(me);
                        addn("neili", -50, me);
                        return 1;
                }
                message_combatd(HIW"$N默運冷月寒氣，催動寒冷真氣注入"+query("name", weapon)+HIW"，$n見狀趕緊催動體內真氣與其相抗。\n\n"NOR,me,target);
                message_combatd(HIG"$N只覺$n手中的"+query("name", weapon)+HIG"傳來一陣炎熱的氣勁，將自己的冷月寒氣消弭於無形，只好放手，飄身退開。\n"NOR,me,target);
                me->start_busy(1+random(2));
                addn("neili", -150, me);
                return 1;

        }
        message_combatd("可是$n的看破了$N的企圖，立刻採取守勢，飄身躲開$N的攻擊。\n",me,target);
        addn("neili", -50, me);
        me->start_busy(1+random(2));
        return 1;
}