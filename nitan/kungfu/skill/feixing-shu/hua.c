// This program is a part of NITAN MudLIB
// huayu.c

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;
#define YU "「" HIG "滿天花雨" NOR "」"

int perform(object me, object target)
{
        int skill, i;
        int n, p;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/feixing-shu/hua", me) )
                return notify_fail("你還沒有受過高人指點，無法施展" YU "。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YU "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("你現在手中並沒有拿著暗器。\n");

        if (weapon->query_amount() < 10)
                return notify_fail("至少要有十枚暗器你才能施展" YU "。\n");

        if ((skill = me->query_skill("feixing-shu", 1)) < 100)
                return notify_fail("你的飛星術不夠嫻熟，不會使用" YU "。\n");
 
        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的內功火候不夠，不能使用" YU "。\n");

        if (me->query_skill_mapped("throwing") != "feixing-shu")
                return notify_fail("你沒有激發飛星術為基本暗器，無法施展" YU "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你內力不夠了。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        addn("neili", -100, me);
        weapon->add_amount(-10);

        msg= HIG "只聽一股勁風從$N" HIG "的右側發出，$N" HIG
             "手中的" + weapon->name() + HIG "如煙雨般向$n"
             HIG "籠罩過去！\n" NOR;

        me->start_busy(2);
        my_exp = attack_power(me, "throwing");
        ob_exp = defense_power(target, "dodge");
        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                addn("neili", -100, me);
                n = 1 + random(2);
 
                if (random(my_exp) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
                if (random(my_exp / 4) > ob_exp) n += 1 + random(2);
                msg += HIR "結果$n" HIR "反應不及，中了$N" HIR +
                       chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIR "！\n" NOR;

                target->receive_wound("qi", skill / 3 + random(skill / 3), me);
                p=query("qi", target)*100/query("max_qi", target);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me,target,query("jiali", me)+100+n*10);
                }
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                
                message_combatd(msg, me, target);
        } else
        {
                msg += NOR + CYN "可是$n" CYN  "身法靈動，躲過了$N" CYN  "發出的所有" +
                       weapon->name() + CYN  "。\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}