#include <combat.h>
#include  <ansi.h>

#define HUI "「" HIW "毀天" HIR "滅地" NOR "」"

string final1(object me, object target, int damage);
string final2(object me, object target, int damage);

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, lvl;
        object weapon;
         int attack_type;

        if( userp(me) && !query("can_perform/kuihua-mogong/hui", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("kuihua-mogong", 1) < 320)
                return notify_fail("你葵花魔功修為不夠，難以施展" HUI "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你內力修為不夠，難以施展" HUI "。\n");

        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("你沒有激發葵花魔功為內功，無法施展" HUI "。\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("你使用的武器不對！\n");

                attack_type = WEAPON_ATTACK;
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("你並沒有準備使用葵花魔功，無法施展" HUI "！\n");

                attack_type = UNARMED_ATTACK;
        }

        
        if( query("neili", me)<800 )
                return notify_fail("你現在真氣不夠，難以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        lvl = me->query_skill("kuihua-mogong", 1);

        message_vision("\n\t\t" + BBLU + HIR "毀    天    " HIW "滅    地\n" NOR, me);

        // 第一式-----毀天
        ap = me->query_skill("force") + me->query_skill("dodge");
        dp=target->query_skill("force")+query("dodge", target);

        message_combatd(sort_msg(HIW "\n忽然間$N" HIW "身形猛轉，剎時狂風如潮，遮雲蔽"
                     "日，天地為之變色，這正是《葵花寶典》所記載絕學「" HIR "毀天"
                     "式" HIW "」。轉眼間$N" HIW "已不見了蹤影，只聽得一聲尖嘯，一"
                     "道白光從天而下將$n" HIW "籠罩！" NOR), me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 130,
                                           (: final1, me, target, damage :));

                if( !query("can_perform/kuihua-mogong/hui2", me) )
                {
                       addn("can_perform/kuihua-mogong/hui1", 1, me);
                       if( query("can_perform/kuihua-mogong/hui1", me) >= 200 )
                       {
                            tell_object(me, HIR "你的「毀天式」已經運用得非常熟練了！\n" NOR);
                       }
                }
        } else
        {
                msg = HIC "$p" HIC "眼明身快，縱身向旁一跳，竟躲過這招。。\n" NOR;
        }
        message_combatd(msg, me, target);

        if( query("can_perform/kuihua-mogong/hui2", me) )
        {
        // 第二式-----滅地式        
        message_combatd(sort_msg(HIM "\n緊跟着$N" HIM "身形一晃，已沒了蹤跡，剎那間，$n" HIM "只覺得地動"
                     "山搖，風起雲湧，正猶豫間，$N" HIM "已躥至$n" HIM "身後，一招"
                     "「" HIR "滅地訣" HIM "」使出 ……\n" NOR), me, target);

        ap = me->query_skill("force") + me->query_skill("dodge");
        dp=target->query_skill("force")+query("dodge", target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 130,
                                          (: final2, me, target, damage :));

                                           
        } else
        {
                msg = HIC "$p" HIC "只覺身後風聲呼呼，猛地提氣躍開，躲過了這招。\n" NOR;
        }
        message_combatd(msg, me, target);
        }

        me->start_busy(2 + random(3));
        addn("neili", -200-random(300), me);
        return 1;
}

string final1(object me, object target, int damage)
{
        target->receive_wound("qi", damage / 16, me);

        return HIR "$n" HIR "心中大驚，只見$N" HIR "一道"
               "耀眼白光一閃，已晃至自己跟前，躲閃不及，被擊"
               "個正中。\n:內傷@?";

}
string final2(object me, object target, int damage)
{
        target->receive_wound("jing", damage / 20, me);
        target->receive_wound("qi", damage / 20, me);
        return  HIR "只聽$n" HIR "一聲慘嚎，被$N" HIR
                "擊中背心，“喀嚓喀嚓”肋骨已震斷。\n:內傷@?";
}