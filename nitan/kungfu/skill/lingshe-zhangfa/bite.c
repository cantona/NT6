// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>
#define SNAKE_STAFF query_temp("weapon", this_player())

inherit F_SSERVER;

string name() { return "驅蛇咬人"; }
//void remove_bite(object);

int perform(object me, object target)
{
        string type, snake_path, msg;
        object weapon, snake;
        int t, lv, poison, poi_amount, train_lv, snake_lv, damage, dp, i;

        t=query_temp("baituo/bite", me);
        lv = (int)me->query_skill("lingshe-zhangfa", 1);
        poison = (int)me->query_skill("poison", 1);
        train_lv = (int)me->query_skill("training", 1);

        poi_amount = lv + poison;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("你只能縱蛇偷襲戰鬥中的對手。\n");

        if (lv < 200 )
                return notify_fail("你的靈蛇杖法不夠嫻熟，無法在使杖攻敵之余縱蛇傷人。\n");

        if (poison < 200 )
                return notify_fail("你對使毒的法門所知有限。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                 return notify_fail("你手上沒有盤蛇的兵器。\n");

        type=query("snake_type", weapon);

        if( !type && query("id", weapon) != "she zhang" )
                return notify_fail("你的"+weapon->name()+"上並沒有蛇。\n");

        if( t && (time() - t) < 5 )
                return notify_fail("你剛剛已經縱蛇傷人，這麼快就故技重施，祗怕難以奏效。\n");

        if( me->query_skill("training",1) < 100 )
               return notify_fail("你的馭獸術無法順利驅使毒蛇傷人。\n");

        if( query("neili", me)<poi_amount )
                return notify_fail("你的內力不夠，難以在縱蛇襲擊時穩控"+weapon->name()+"。\n");

        if( query("jingli", me)<300 )
                return notify_fail("你的精力不夠，難以在縱蛇襲擊時穩控"+weapon->name()+"。\n");

        if(( me->query_skill_mapped("force") != "hama-gong") && ( me->query_skill_mapped("force") != "jiuyin-hamagong"))
                return notify_fail("你所用的內功與「靈蛇杖法」氣路相悖！\n");

        addn("neili", -(poi_amount/2+50), me);
        addn("jingli", -200, me);

        switch (type) {
        case "怪蛇" :
        snake_path = "/d/baituo/npc/guaishe";
        break;
        case "靈蛇" :
        snake_path = "/d/baituo/npc/lingshe";
        break;
        default:
        snake_path = "/d/baituo/npc/snake";
        type = "毒蛇";
        }

        seteuid(getuid());

        snake = new(snake_path);

        snake_lv = (train_lv + lv)*2/3;

        set("bite_busy", 1, snake);
        set("env/invisible", 10, snake);
        set("owner", me, snake);
        snake->move(environment(me));
        set("default_actions", (:call_other,__FILE__,"query_action":), snake);
        set("combat_exp",query("combat_exp",  me), snake);

        addn_temp("apply/speed", 2, snake);
        addn_temp("apply/attack", snake_lv, snake);
        addn_temp("apply/damage", snake_lv, snake);
        set("neili",query("neili",  me), snake);
        set("jingli",query("max_jingli",  me)*2, snake);
        set("max_jingli",query("max_jingli",  me), snake);
        set("snake_poison", poi_amount*5, snake);
        snake->kill_ob(target);

        message_combatd(HIB"\n$N將"+weapon->name()+HIB"一抖，杖上金環當啷啷一陣亂響，一條"+type+HIB"從杖底直盤上來。\n"NOR,me);

        me->start_busy(1);

        COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
        COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));

        if( query("snake", weapon) == 2){
                set("second_attack", 1, snake);
                COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
                COMBAT_D->do_attack(snake,target,query_temp("weapon", snake));
        }

        destruct(snake);
        damage = lv +  poison + train_lv + me->query_skill("staff",1);
        damage += (damage);
        dp=target->query_skill("dodge")+target->query_skill("training",1);
        if (damage/2+random(damage)>dp)
        {
                addn("neili", -200, me);
                message_combatd(HIB"\n$N忽然將"+weapon->name()+HIB"當頭打了下來，$n因為防備毒蛇而躲閃不及。\n"NOR,me,target);
                COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100);
        }

        target->kill_ob(me);
        set_temp("baituo/bite", time(), me);

        call_out("remove_bite", 5, me, type);

        return 1;
}

void remove_bite(object me, string type)
{
        if (! objectp(me)) return;
        delete_temp("baituo/bite", me);
        tell_object(me, type+"昂起了頭，嘶地一吐舌頭。\n");
}

mapping query_action(object me)
{
        string msg1, msg2;
        msg1 = HIR"祗見"+SNAKE_STAFF->name()+HIR"從$n眼前掠過，纏杖盤旋的一條$N吞吐伸縮，猛然張口咬向$n$l，猙獰詭異之極！"NOR;
        msg2 = HIW BLK"一條$N才剛竄出，冷不防"+SNAKE_STAFF->name()+HIW BLK"上另一條$N也已悄沒聲息地昂首而起，一口向$n$l咬去！"NOR;
        return ([
        "action":query("second_attack", me)?msg2:msg1,
        "force" : 400,
        "dodge" : 0,
        "parry" : 0,
        "damage" : 400,
        "weapon" :"毒牙",
        "damage_type":"咬傷"]);
}