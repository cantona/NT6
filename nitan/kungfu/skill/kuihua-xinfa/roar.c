// roar.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

/*
  if ( userp(me) && !wizardp(me) && 
  !query("perform/roar", me) && 
  !query("can_perform/kuihua-xinfa/roar", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");
*/

        if( (query("neili", me)<500) || (query("max_neili", me)<500) || (me->query_skill("kuihua-xinfa",1)<100) )
                return notify_fail("你鼓足真氣＂喵＂的吼了一聲, 結果嚇走了幾隻老鼠。\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裏不能攻擊他人。\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);
        me->receive_damage("qi", 10);

        me->start_busy(5);
        message_combatd(
                HIY"$N深深地吸一囗氣，真力迸發，運起葵花心法，發出一聲尖利的長嘯：“"HIR"日出東方，唯我不敗！"HIY"”\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++)
        {
                if( !living(ob[i]) || query_temp("noliving", ob[i]) || ob[i] == me)continue;

                if( skill/2+random(skill/2)<query("con", ob[i])*2)continue;

                if (!userp(ob[i]) && !ob[i]->accept_hit(me)) continue;

                damage=skill-(query("max_neili", ob[i])/10);

                if( damage > 0 )
                {
                        ob[i]->receive_damage("jing", damage * 2 );
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage);
                        tell_object(ob[i], "你覺得一陣天昏地暗，耳朵如針扎一般疼痛欲裂！\n");
                }

                if( userp(ob[i]) ) ob[i]->fight_ob(me);
                else if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);
        }
        return 1;
}

int help(object me)
{
        write(WHT"\n葵花心法之東方不敗："NOR"\n");
        write(@HELP

        使用功效：
                傷害自己周圍的所有生物的精氣

        出手要求：
                葵花心法100級
                內力500
HELP
        );
        return 1;
}
