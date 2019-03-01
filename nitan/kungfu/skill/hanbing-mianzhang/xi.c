// This program is a part of NITAN MudLIB
// xi.c 吸血青蝠

#include <ansi.h>

inherit F_SSERVER;

string name() { return "吸血青蝠"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("hanbing-mianzhang", 1);

        if (! (me->is_fighting(target)))
                return notify_fail("「吸血青蝠」只能對戰鬥中的對手使用。\n");

        if (objectp(weapon = query_temp("weapon", me)))
                return notify_fail("你使用了武器。\n");

        if (skill < 60)
                return notify_fail("你的「寒冰綿掌」等級不夠, 不能使用「吸血青蝠」！\n");

        if (me->query_skill("dodge", 1) < 200)
                return notify_fail("你的輕功基礎還沒有打好，無法運用「吸血青蝠」！\n");


        msg = HIR "$N" HIR "突然如同蝙蝠一樣，倏的欺近$n"
              HIR "的身前，張嘴便向$n" HIR "的嚥喉咬去。\n" NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                message_combatd(HIR"結果一下子咬在$n的頸側，猛吸起來，一股鮮血登時從$N的牙邊滲出，陰森可怖。\n\n"NOR,me,target);

                if ( query("combat_exp", me) > random(query("combat_exp", target)*10) )
                {
                        message_vision(HIR"只見$N的腹部微微鼓起，然後放開$n。再看時，$n已經血被吸幹，早已氣絕。\n"NOR,me,target);
                        me->receive_curing("qi",query("max_qi", target)+100);
                        addn("qi",query("max_qi", target)+100, me);
                        target->receive_damage("qi", query("max_qi", target)+100, me);
                        target->receive_wound("qi", query("max_qi", target)+100, me);
                        target->die(me);
                }
                else
                {
                        message_vision(HIW"$n拼死掙紮，終于掙脫$N的控制，但受傷極重，鮮血從頸部汩汩流出。\n"NOR,me,target);
                        me->receive_curing("qi",query("max_qi", target)/3);
                        addn("qi",query("max_qi", target)/3, me);
                        target->receive_wound("qi", query("max_qi", target)/3, me);
                        if( !target->is_busy() )
                                target->start_busy(2);
                }

                me->start_busy(1 + random(2));
        } else
        {
                msg = CYN "只見$n" CYN "不慌不忙，輕輕一閃，躲過了$N"
                      CYN "的利齒！\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
