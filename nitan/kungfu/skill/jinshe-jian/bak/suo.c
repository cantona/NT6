// This program is a part of NITAN MudLIB
// suo.c 鎖劍訣

#include <ansi.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2, target;
        int skill, ap, dp, damage;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("id", weapon) != "jinshejian" )
                return notify_fail("你沒用金蛇劍，不能使用絕招！\n");

        if( query("dex", me)<20 || query("str", me)<20 )
                return notify_fail("你的先天膂力身法孱弱, 不能使用「鎖劍訣」！\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("jinshe-jian", 1);

        if( !(me->is_fighting() ))
                return notify_fail("「鎖劍訣」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon2=query_temp("weapon", target)) )
                return notify_fail("對方沒有使用兵器，你用不了「鎖劍訣」。\n");

        if( skill < 150)
                return notify_fail("你的金蛇劍法等級不夠, 不能使用「鎖劍訣」！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的內力不夠，無法運用「鎖劍訣」！\n");

        msg = HIC "$N手中"YEL"金蛇劍"HIC"畫出一道金光，斜刺一拉，「鎖劍訣」！\n"
              YEL "金蛇劍"HIC"劍尖倒鈎正好掛在$n的"+weapon2->name()+"上。\n";
              
        message_combatd(msg, me, target);

        damage = 100 + random(skill / 2);
        
        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -50, me);
                msg = "$n頓時覺得眼前金光一閃，手腕一振，手中";
                msg += weapon2->name();
                msg += "脱手飛出！\n" NOR;
                me->start_busy(random(2));
                target->receive_damage("qi", damage);
                target->start_busy(2);
                weapon2->move(environment(me));
        }
        else
        {
                addn("neili", -30, me);
                msg = "$n急運內力，將手中" + weapon2->name()+ "斜斜順勢一送一搭，抽了回來。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}