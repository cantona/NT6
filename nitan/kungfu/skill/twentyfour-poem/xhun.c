// xhun.c 雄渾

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

        skill = me->query_skill("twentyfour-poem", 1);

        if (! me->is_fighting(target))
                return notify_fail("雄渾只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("cuff") != "twentyfour-poem") 
                return notify_fail("你沒有用詩經二十四品，無法使用「雄渾」絕招！\n");

        if (me->query_skill_prepared("cuff") != "twentyfour-poem")
                return notify_fail("你沒有準備使用詩經二十四品，無法施展「雄渾」絕招。\n");

        if (skill < 100)
                return notify_fail("你的詩經二十四品等級不夠，練好了再來！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空着雙手才能使用掌法絕招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIC "\n$N" HIC "身形忽轉，雙拳飄忽不定，真氣運轉全身，口吐真言，朗朗誦道：\n"
              HIW "大用外腓，真體內充。反虛入渾，積健為雄。具備萬物，橫絕太空。\n" 
              HIW "荒荒油雲，寥寥長風。超以象外，得其環中。持之非強，來之無窮。\n" 
              HIC "真氣激盪中，" HIG "詩經二十四品" HIC "至強式" HIY "「雄渾」" HIC "破碎虛空，呼嘯而至。\n\n" NOR; 

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "\n$N" HIW "萬拳歸一，緩慢向$n" HIW "擊出，卻又頃刻而至，端是奇妙！\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIW "$n" HIW "躲閃不急，慘叫一聲，已經被重重擊中。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIC "$n" HIC "見勢不妙，猛地向後一躍，躲避開來。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

