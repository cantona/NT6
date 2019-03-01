// hun.c 悲歡離合

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

        skill = me->query_skill("canyue-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("悲歡離合只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("sword") != "canyue-sword") 
                return notify_fail("你沒有用殘月劍法，無法使用悲歡離合絕招！\n");

        if (skill < 100)
                return notify_fail("你的殘月劍法等級不夠，練好了再來！\n");

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

        msg = HIG "$N" HIG "輕輕抖動" + weapon->name() + HIG "，劍花飛揚中依次展現新月、殘月、半月、滿月等幻影。\n" 
              "$n" HIG "只覺神情恍惚，思緒擁動，悲歡離合百般滋味一一泛顯，手腳逐漸緩慢下來。\n" NOR;

        msg += HIY "$N" HIY "乘$n" HIY "思緒混亂，步履蹣跚之際，手中" + weapon->name() + HIY
              "劍芒爆射，星星劍光籠罩$n" HIY "全身，順勢連出數招。\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = YEL "\n$N" YEL "的劍勢忽然變慢了，很慢。一劍揮出，似乎永遠沒有終點。 \n"
              "$n" YEL "終于從先前的狂風暴雨中解脫出來，兀自心有余悸，驚恐不定。\n"
              "不料未及$n" YEL "喘過氣來，這笨拙而遲鈍的一劍忽然化作了滿天月光籠罩下來。 \n\n" NOR; 

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "始料不及，慌亂之中四處躲閃，剎那間已經身中數劍！\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "大驚之下呆若木雞，不料這恰好正是殘月劍法唯一生門，竟僥幸逃過一劫。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}
