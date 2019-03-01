// jianqi.c 六道輪回

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        string *learned;
        object weapon, weapon2;
        string type,perform_type;
        mapping prepare;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("liudaolunhui-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("六道輪回劍氣只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("sword") != "liudaolunhui-sword") 
                return notify_fail("你沒有用六道輪回劍法，無法使用劍氣絕招！\n");

        if (skill < 100)
                return notify_fail("你的六道輪回劍法等級不夠，練好了再來！\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIG "$N" HIG "凝神靜氣，默運神通，周圍寒氣漸生，手中" + weapon->name() + HIG
              "通體碧寒，仿佛周圍一切都已經被凍結了。\n" NOR;

        msg += HIY "$N" HIY "乘$n" HIY "氣血僵硬，無法動彈之際，手中" + weapon->name() + HIY
              "劍走偏鋒，籠罩$n" HIY "全身各處大穴，順勢連出數招。\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg = HIW "忽然$N" HIW "大喝一聲，" + weapon->name() + HIW
                      "遙遙指向$n。\n" HIW "一道劍氣如白色蛟龍般洶湧噴薄，帶著周圍刺骨的寒氣襲向$n" HIW "的全身。\n" + 
                      "待得$n" HIW "猛然驚覺，卻為時已晚。" HIR "劍氣" HIW "已透體而過，全身氣血凝固，仿佛被凍僵了！\n" NOR;

                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg = HIW "$N" HIW "抖動著手中的" + weapon->name() + HIW "尋找著機會，"
                      "可是$n" HIW "拼命躲閃，$N" HIW "一時竟也無機可乘。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

