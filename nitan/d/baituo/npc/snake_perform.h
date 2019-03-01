// Code of JHSH

#include <ansi.h>

int auto_perform_duwu()
{
        object me = this_object();
        object *target;
        int damage, poison, i;

        poison=query("snake_poison", me);
        target = all_inventory(environment(me));

        if( me->is_busy() ) return 0;

        if( query("jingli", me)<poison)return 0;
        
        message_vision(HIR"祗見$N血紅的舌頭一伸一縮，形狀可怖，忽然張口，口中噴出一陣紅霧。\n\n"NOR,me);

        for(i=0; i<sizeof(target); i++) {

                if( !living(target[i]) || target[i] == me || query("race", target[i]) == "蛇類")continue;

                if( random(poison) > target[i]->query_skill("force") || !living(target[i]) )
        {
                        damage=random(poison*10-query("neili", target[i]));
                        if(damage > 800) damage = 800;
                        if(damage < 100) damage = 100;

                     target[i]->affect_by("snake_poison",
                              ([ "level" : poison + random(poison),
                                 "id":query("id", me),
                                 "duration" :  poison]));

                        target[i]->receive_damage("qi", damage,  me);
                        target[i]->receive_wound("qi", random(damage), me);
                        target[i]->start_busy(1+random(2));
                        message("vision", target[i]->name() + "的身子微微一晃，有點立足不定。\n", environment(me), target[i]);
                        tell_object(target[i], RED"你突然感到一陣頭暈，原來"+me->name()+"噴出來的紅霧是劇毒之物，在空中彌散開來，以致中了蛇毒！\n"NOR);
                }
                else {
                        tell_object(target[i], WHT"你立刻屏住呼吸，以免吸入蛇毒。\n"NOR);
                }
        }
        me->start_busy(1);
        addn("jingli", -(random(50)+poison/3), me);

        return 1;
}

int auto_perform_chan()
{
        object me = this_object();
        object target = me->select_opponent();
        object owner;
        object here = environment(me);
        int damage;

        if( query("jingli", me)<500)return 0;

        if( query("race", target) == "昆蟲")return 0;
        if( me->is_busy() || query_temp("snake_chan", target))return 0;

        set_temp("try_chan", 1, me);
        set("default_actions", (:call_other,__FILE__,"query_action":), me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        set("default_actions", (:call_other,"/adm/daemons/race/snake.c","query_action":), me);
        delete_temp("try_chan", me);
        return 1;
}

int auto_perform_double()
{
        object me = this_object();
        object target = me->select_opponent();

        if( me->is_busy() || !living(me) ) return 0;

        set("default_actions", (:call_other,__FILE__,"query_action":), me);
        set_temp("double_hit", 1, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        set_temp("double_hit", 2, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me));
        delete_temp("double_hit", me);
        set("default_actions", (:call_other,"/adm/daemons/race/snake.c","query_action":), me);

        return 1;
}

mapping query_action()
{
       object me = this_object();
        string msg1, msg2;
        msg1 = HIR"祗聽簌簌聲響，$N蜿蜒竄前，"+(random(2)?"右":"左")+"邊的蛇頭嘶嘶吐信，猛然咬向$n的$l"NOR;
        msg2 = RED"一口才剛咬過，卻見$N另一個頭也轉過了來，緊跟著咬向$n$l"NOR;

        if( query_temp("double_hit", me) )
        return ([
        "action":query_temp("double_hit", me) == 1?msg1:msg2,
        "force" : 400,
        "dodge" : 10,
        "parry" : 10,
        "damage" : 400,
        "weapon" :"毒牙",
        "damage_type":"咬傷"]);

        else return ([
        "action": HIR"祗見$N兩丈多長的身子一撲，猛然朝$n身上卷到！"NOR,
        "force" : 400,
        "dodge" : 0,
        "parry" : 0,
        "damage" : 400,
        "weapon" :"蛇身",
        "damage_type":"內傷"]);
}