// hun.c 無間輪回

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

        skill = me->query_skill("liudaolunhui-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("無間輪回只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("cuff") != "liudaolunhui-cuff") 
                return notify_fail("你沒有用六道輪回拳法，無法使用無間輪回絕招！\n");

        if( me->query_skill_prepared("cuff") != "liudaolunhui-cuff" ) 
                return notify_fail("你所備的並非六道輪回拳法，不能使用無間輪回絕招！\n"); 

        if (skill < 100)
                return notify_fail("你的六道輪回拳法等級不夠，練好了再來！\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你拿著武器如何使用拳法絕招？\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "$N" HIY "左手斜指天際，右手沉掌向地，嘴中低沉吟唱：『天上地下，惟我獨尊』\n" 
              "$n" HIY "只覺一股渾厚的勁氣旋繞而來，頓時胸口鬱悶，口鼻難于呼吸。\n\n" NOR;

        msg += HIY "$N" HIY "突然騰身而起，身形幻化出眾生相，翻滾沉浮，如地獄魔煞撲向$n" HIY "，閃電般發出數招。\n\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = HIW "\n在$n" HIW "踉蹌後退時，$N" HIW "口中輕誦『" HIC "天" HIW "、" HIG "人" HIW  "、" HIB "阿修羅" HIW "、" HIY "畜牲" HIW "、" HIM "餓鬼" HIW "、" HIR "地獄" HIW "』"
              HIW "\n每念一字便有重重" NOR BLU "鬼影" HIW "閃現，待到念完，無數鬼影遁入往生輪回。\n\n"NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "心膽俱裂，迷惘失神下已被無數鬼魂糾纏，渾身血柱四射！\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "閉目靜神，憑借思感左右閃避，終于躲過這驚怖一擊。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

