// luohan-gun perform 羅漢棍陣

#include <ansi.h>

#define SHIBA HIY "【十八羅漢棍陣】" NOR

#define ME  "你現在不能使用" + SHIBA + "。\n"
#define TAR  "對方現在不能使用" + SHIBA + "。\n"

int check_fight(object me, object target, int amount);
private int remove_effect(object me, object target, int amount);

int perform(object me, object target)
{
        object *enemy;
        int i,j,k,amount;
        object wep1, wep2;
        wep1=query_temp("weapon", me);

        if( !target || target == me) return notify_fail("你要和誰組成棍陣?\n");

        if( query_temp("gunzhen", me))return notify_fail(ME);
        if( query_temp("gunzhen", target))return notify_fail(TAR);
        if( query("jingli", me)<200)return notify_fail(ME);
        if( query("jingli", target)<200)return notify_fail(TAR);
        if( query("neili", me)<1500)return notify_fail(ME);
        if( query("neili", target)<1500)return notify_fail(TAR);
        if (!me->is_fighting()) return notify_fail( SHIBA "只能在戰鬥中使用。\n");
        if (me->is_fighting(target)) return notify_fail("你已經在和對方打架，使用" + SHIBA + "作什麼?\n");
        if( (int)me->query_skill("luohan-gun", 1) < 120 ) return notify_fail(ME);
        if( (int)me->query_skill("club", 1) < 120 ) return notify_fail(ME);
        if( !wep1 || query("skill_type", wep1) != "club"
        || me->query_skill_mapped("club") != "luohan-gun")
                return notify_fail(ME);
        
        enemy = me->query_enemy();
        k = sizeof(enemy);
        while (k--)
        if (target->is_fighting(enemy[k])) break;
        if (k<0) return notify_fail(target->name()+"並沒有和你的對手在交戰。\n");

        if( (int)target->query_skill("luohan-gun", 1) < 120 )
                return notify_fail(TAR);
        if( (int)target->query_skill("club", 1) < 120 )
                return notify_fail(TAR);
        wep2=query_temp("weapon", target);
        if( target->is_busy() || !wep2 || query("skill_type", wep2) != "club"
        || target->query_skill_mapped("club") != "luohan-gun")
                return notify_fail(TAR);
                
        message_vision(HIY "\n只見他們幾人，動作協調，陣行嚴謹，攻守一體，"+
                           "一招一式，都似發自同一人，威力大增。"+
                           "$n不由看的呆了......\n" NOR, me, target);
        set_temp("gunzhen", 1, me);
        set_temp("bunzhen", 1, target);
        me->receive_damage("jingli", 100);
        target->receive_damage("jingli", 100);
        me->receive_damage("neili", 300);
        target->receive_damage("neili", 300);
        me->start_busy(1);
        target->start_busy(1);
        i = (int)me->query_skill("luohan-gun", 1);
        j = (int)target->query_skill("luohan-gun", 1);
        amount = ((i + j)/10 + (int)me->query_str() + (int)target->query_str())/5;
        if( amount > 20 ) amount = 20;
        addn_temp("apply/dex", amount, me);
        addn_temp("apply/str", amount, me);
        addn_temp("apply/dex", amount, target);
        addn_temp("apply/str", amount, target);
        enemy[k]->start_busy(amount/3);
        check_fight(me, target, amount);
        return 1;
}

int check_fight(object me, object target, int amount)
{  
        object wep1, wep2;
        if(!me && !target) return 0;
        if(!me && target){
           addn_temp("apply/dex", -amount, target);
           addn_temp("apply/str", -amount, target);
           delete_temp("gunzhen", target);
           return 0;
        }
        if( me && !target){
           addn_temp("apply/dex", -amount, me);
           addn_temp("apply/str", -amount, me);
           delete_temp("gunzhen", me);
           return 0;
        }
        wep1=query_temp("weapon", me);
        wep2=query_temp("weapon", target);
        if(!me->is_fighting()
         || !living(me)
         || me->is_ghost()
         || !wep1
         || !target->is_fighting()
         || !living(target)
         || target->is_ghost() 
         || !wep2
         || me->query_skill_mapped("club") != "luohan-gun" 
         || target->query_skill_mapped("club") != "luohan-gun"
         || environment(me) != environment(target))
              remove_effect(me, target, amount);
        else {
              call_out("check_fight", 1, me, target, amount);
        }
        return 1;
}

private int remove_effect(object me, object target, int amount)
{
        if(living(me)
         && !me->is_ghost()
         && living(target)
         && !target->is_ghost())
           message_vision(HIY "\n各僧眾將陣法施展完畢，各自收招。\n" NOR, me, target);

        addn_temp("apply/dex", -amount, me);
        addn_temp("apply/str", -amount, me);
        addn_temp("apply/dex", -amount, target);
        addn_temp("apply/str", -amount, target);
        delete_temp("gunzhen", me);
        delete_temp("gunzhen", target);
        return 0;
}