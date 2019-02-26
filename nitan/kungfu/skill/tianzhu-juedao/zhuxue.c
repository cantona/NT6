/*
由於劈斷對方武器的功能是這個perform最大的威力，但為了保持獨孤九劍在
這一方面的第一地位，特地對發揮這一威力的條件，在程序中做了如下限制
希望以後的巫師不要更改這些設定，畢竟在weapon武功中，不能超越lonely-sword的地位。
*/

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me)
{
        string msg;
        object weapon, weapon2,target,*inv;
        int skill, ap, dp, neili_wound, qi_wound,equip,skill1;
        int damage;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill  = me->query_skill("tianzhu-juedao",1);
        skill1 = me->query_skill("shaolin-xinfa",1);


        if( !(me->is_fighting() ))
            return notify_fail("「"+HIR"融雪逐日"NOR+"」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
            return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("buddhism",1) < 220)
                return notify_fail("你佛法修為不足，不能使用「"+HIR"融雪逐日"NOR+"」！\n");

        if( skill < 150)
            return notify_fail("你的天竺絕刀等級不夠, 不能使用「"+HIR"融雪逐日"NOR+"」！\n");
        if(me->query_skill("shaolin-xinfa",1)<150)
            return notify_fail("你的少林心法等級不夠, 不能使用「"+HIR"融雪逐日"NOR+"」！\n");
 
        if( query("neili", me)<400 )
            return notify_fail("你的內力不夠，無法運用「"+HIR"融雪逐日"NOR+"」！\n");

        msg = HIY "$N縱身躍起,使出"+HIR"「融雪逐日」"NOR+""+HIY"，揮舞"NOR""+weapon->name()+ 
              NOR+HIY"從半空中揮刀直劈下來，\n刀鋒離地尚有數尺，地下已是塵沙飛揚，敗草落葉被"
              "刀風激得團團而舞，\n將$n逃遁退避的空隙封的嚴嚴實實。\n"NOR;
        message_vision(msg, me, target);

        ap = random(me->query_skill("blade") + skill);
        dp = target->query_skill("dodge")/2;
        damage = ap / 2 + random(ap / 2);

        if( dp < 10 )
            dp = 10;
        if( random(ap) > dp )
        {
            if(userp(me))
                 addn("neili", -250, me);
            msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60, 
                                       HIC"$n避無可避,只覺一股剛猛之極的勁風撲面而來，使人直欲窒息。\n"
                                       "$n極力後退隔擋，卻只見"NOR""+weapon->name()+""HIC"刀光一閃，"
                                       "毫不停息，一刀正中面門。\n"NOR); 

            me->start_busy(2+random(2)); 

       if( query("str", me) >= 20
        && objectp(weapon2=query_temp("weapon", target) )
       && me->query_str() >= 45                              
        && query("max_neili", me)>2500
        && !query("betrayer", me )
       && skill > 200                                           
       && skill1 > 200      
        && !query("no_drop", weapon2 )
        && !query("no_get", weapon2 )
        && !query("no_put", weapon2 )
        && !query("no_beg", weapon2 )
        && !query("no_steal", weapon2 )
        && !query("no_give", weapon2 )
       && random(2) == 1)        
       {
                inv = all_inventory(target);
                for(equip=0; equip<sizeof(inv); equip++)
                {
                          if( query("weapon_prop", inv[equip]) && (query("equipped", inv[equip]) == "wielded") )

                          {
                                 msg += HIW "$N力道未盡，手中刀勢不絕，連帶$n手上"NOR+
                                 query("name", inv[equip])+HIW"一起劈斷。\n只聽當的一"
                                 "聲，$n手上的"NOR+query("name", inv[equip])+HIW"已"
                                 "被劈成兩半，掉在了地上！\n"NOR;
                                  message_vision(msg, me,target);

                                  inv[equip]->unwield();
                                  inv[equip]->reset_action();
                                  inv[equip]->move(environment(target));
                                  set("name", "斷掉的"+query("name", inv[equip]), inv[equip]);
                                  set("value", 0, inv[equip]);
                                  set("weapon_prop", 0, inv[equip]);
                                  set("long", "一把破爛武器，從中斷開，破口整齊，看來是被高手一刀劈開的。\n", inv[equip]);
                        }
                }

                return 1;
        }
        }
        else
        {
            if(userp(me))
                 addn("neili", -100, me);
            msg = HIW"可是$n輕輕往旁邊一閃,閉過了$N這必殺的一刀。\n"NOR;
            me->start_busy(2+random(2));
        }
        message_combatd(msg, me, target);

        return 1;
}

