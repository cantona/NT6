// hun.c 羣魔亂舞

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("diyushajie-strike", 1);

        if (! me->is_fighting(target))
                return notify_fail("羣魔亂舞只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("strike") != "diyushajie-strike") 
                return notify_fail("你沒有用地獄殺劫掌法，無法使用「羣魔亂舞」絕招！\n");

        if (me->query_skill_prepared("strike") != "diyushajie-strike")
                return notify_fail("你沒有準備使用地獄殺劫掌法，無法施展「羣魔亂舞」絕招。\n");

        if (skill < 100)
                return notify_fail("你的地獄殺劫掌法等級不夠，練好了再來！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空着雙手才能使用掌法絕招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("strike") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIG "$N" HIG "雙手合結“" HIY "十八層地獄輪迴印" HIG "”，"
              "腳踏陰陽八卦陣,方圓十里羣魔亂舞。\n" HIG "陣陣奇異的聲音，猶如鬼吟，"
              "令$n" HIG "心神不定，神情恍惚。\n"
              "突然間一圈圈碧芒圍向$n" HIG "，震得$n" HIR "吐血" HIG "連連！\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIG "\n$n" HIG "尚未回過心神，結果發現被“" HIY "十八層地獄輪迴殺劫" HIG "”的強大魔氣衝入體內，登感呼吸不暢。\n"
              "乘此良機，$N" HIG "十八股極大的力道如同排山倒海一般奔向$n" HIG "，周遭狂風大作，飛砂走石！\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIM "$n" HIM "再也抵擋不住，身子被高高拋起，口中" HIR "鮮血" HIM "狂噴，生死不明。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIM "$n" HIM "拼力縱身後躍，險險避過此致命一擊，心有餘悸。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}

