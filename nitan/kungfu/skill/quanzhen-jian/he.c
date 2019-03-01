// This program is a part of NT MudLIB
// hebi.c 全真劍之與玉女劍合璧

#include <ansi.h>

inherit F_SSERVER;

string name() { return "雙劍合璧"; }

void check_fight(object me, object target, object victim, int amount);
private int remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill, skill1, skill2;
        object victim;
        object weapon;

        if( !victim ) victim = offensive_target(me);

        if( !victim || !victim->is_character() || !me->is_fighting(victim) )
                return notify_fail("雙劍合璧只能對戰鬥中的對手使用。\n");

        if( !target )
                return notify_fail("你想與誰進行雙劍合璧？\n");

        if( query("id", victim) == query("id", target) )
                return notify_fail("不能與敵人進行雙劍合璧！\n");

        if( !target->is_fighting(victim) )
                return notify_fail("你想與其雙劍合璧的對象並未與你的敵人搏鬥！\n");

        if( target->query_skill_mapped("sword") != "yunv-jian" )
                return notify_fail("你想與其雙劍合璧的對象所使用的並非玉女劍法！\n");

        if( !objectp(weapon=query_temp("weapon", target) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你想與其雙劍合璧的對象並沒有用劍！\n");

        if( query_temp("hebi", me) )
                return notify_fail("你正與"+target->name()+"進行雙劍合璧。\n");

        if( query_temp("hebi", target) )
                return notify_fail("你想與其雙劍合璧的對象正與他人合壁戰鬥中，無暇與你合璧！\n");

        if( query_temp("yunv_hebi", target) )
                return notify_fail("你想與其雙劍合璧的對象正獨自運用玉女、全真劍法交錯中，無力與你合璧！\n");

        skill1 = me->query_skill("sword");
        skill2 = target->query_skill("sword");
        skill =  ( skill1 + skill2 ) / 4;

        if( mapp(query("couple", me)) &&
            query("couple/couple_id", me) == query("id", target) )
        skill += skill/2;

        message_combatd(
        HIR "\n$N與$n突然間雙劍一交，全真劍法與玉女劍法配合得天衣無縫，攻勢及守勢驟然大增！\n\n" NOR, me, target);

        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/damage", skill, me);
        addn_temp("apply/dodge", skill/2, me);
        addn_temp("apply/parry", skill/2, me);
        set_temp("hebi", 1, me);

        addn_temp("apply/attack", skill/2, target);
        addn_temp("apply/damage", skill, target);
        addn_temp("apply/parry", skill/2, target);
        addn_temp("apply/dodge", skill/2, target);
        set_temp("hebi", 1, target);

        addn_temp("apply/damage", skill, me);
        addn_temp("apply/damage", skill, target);
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(target,victim,query_temp("weapon", target));

        addn_temp("apply/damage", -skill, me);
        addn("neili", -150, me);
        addn_temp("apply/damage", -skill, target);
        addn("neili", -150, target);


        me->start_call_out( (: call_other, __FILE__, "check_fight", me, target, victim, skill/2 :), 1);

        return 1;
}

void check_fight(object me, object target, object victim, int amount)
{
        object weapon;
        if( !query_temp("hebi", me) || !query_temp("hebi", target))return ;

       if( !living(victim) || !present(query("id",victim), environment(me)) || 
                query("qi", victim) <= 50 && me->is_fighting(victim) && target->is_fighting(victim) )
        {
                remove_effect(me, amount);
                remove_effect(target, amount);
                message_vision(HIY"$N與$n個自收招，相視一笑。\n\n"NOR, me, target);
                                return;
        }
        else if( (!present(query("id", victim),environment(me)) && target->is_fighting(victim) )
         || (!present(query("id", target),environment(me)) && me->is_fighting(victim))){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"雙劍合璧已然瓦解，壓力頓減，你不由然地鬆了一口氣。\n"NOR);
                                return;
        }
         else if( !present(query("id", target),environment(me) )
        || !target->is_fighting() || !me->is_fighting() || !living(target)
        || !living(me) || target->is_ghost() || me->is_ghost() ) {
                remove_effect(me, amount);
        remove_effect(target, amount);
                tell_object(me, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"雙劍合璧已然瓦解，壓力頓減，你不由然地鬆了一口氣。\n"NOR);
                                return;
        }
        else if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"雙劍合璧已然瓦解，壓力頓減，你不由然地鬆了一口氣。\n"NOR);
                                return;
        }
        else if( !objectp(weapon=query_temp("weapon", target) )
         || query("skill_type", weapon) != "sword"){
                remove_effect(me, amount);
                remove_effect(target, amount);
                tell_object(me, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(target, HIR"雙劍合璧已然瓦解！\n"NOR);
                tell_object(victim, HIY"雙劍合璧已然瓦解，壓力頓減，你不由然地鬆了一口氣。\n"NOR);
                                return;
        }
        else if( me->query_skill_mapped("sword") != "quanzhen-jian")
        {
                remove_effect(me, amount);
                remove_effect(target,amount);
                message_vision(HIR"$N"HIR"突然劍招一轉，不再使用全真劍法，雙劍合璧頃刻瓦解。\n"NOR,me);
                return;
        }
        else if( target->query_skill_mapped("sword") != "yunv-jian")
        {
                remove_effect(me, amount);
                remove_effect(target,amount);
                message_vision(HIR"$N"HIR"突然劍招一轉，不再使用玉女劍法，雙劍合璧頃刻瓦解。\n"NOR,target);
                return;
        }
        call_out("check_fight", 1, me, target, victim, amount);
}

private int remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/damage", -amount*2, me);
        addn_temp("apply/parry", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        delete_temp("hebi", me);

        return 0;
}
