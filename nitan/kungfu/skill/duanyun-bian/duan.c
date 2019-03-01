#include <ansi.h>

inherit F_SSERVER;

int second_hit(object me, object target);
int duo(object me, object target);
int duo2(object me, object target);

string name() { return "斷雲助日"; }

int perform(object me, object target)
{
        object weapon;
        mapping myfam;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("「斷雲助日」只能對戰鬥中的對手使用。\n");

         /*
        if( (int)me->query_skill("xiantian-gong",1) < 150 )
                return notify_fail("你先天功修為不足！\n");
         */

        if( (int)me->query_skill("taoism",1) < 150 )
                return notify_fail("你道學修為修為不足！\n");

        if( me->query_skill("duanyun-bian",1) < 150 )
                return notify_fail("你的「斷雲鞭法」修為不足！\n");

        if( me->query_skill("whip",1) < 150 )
                return notify_fail("你的鞭法的基本功不紮實！\n");

        if( me->query_con() < 40 )
                return notify_fail("你的根骨太差！\n");

        if( query("neili", me) <= 300 )
                return notify_fail("你的內力不夠使用「斷雲助日」！\n");

        if( !query_temp("weapon", me) || query("skill_type", query_temp("weapon", me)) != "whip" )
                return notify_fail("你並沒有裝備鞭作為武器。\n");

        /*
        if( query("combat_exp", me)/100>query("shen", me) )
                return notify_fail("你的俠義正氣太低，無法控住心中的邪念，使此招無益有損。\n");
        */

        if( query_temp("duanyun", me) )
                return notify_fail("你正在使用「斷雲助日」絕招。\n");

        message_combatd(HIW"\n$N心中平和，漸漸將斷雲鞭法使得圓轉如意，手中"+(query("name", query_temp("weapon", me)))+HIW"在內力摧動下閃出點點銀光，有如雲彩將$n逐漸包圍在其中。\n\n"NOR,me,target);

        set_temp("duanyun", 1, me);

        addn("neili", -me->query_skill("whip")/2, me);

        call_out("second_hit", 1, me, target);

        return 1;
}

int second_hit(object me, object target){

        int ap, dp, damage;
        string str;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon",me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N已手中無鞭，無法將絕招繼續，只得運功收招。\n"NOR,me);
                return 1;
        }

        if(me->is_fighting()){

                message_vision(HIY"\n$N內力鼓盪，一聲清嘯聲中，向$n猛地發出三招，瞬時間鞭上銀光陡散，風聲大作。\n"NOR, me, target);

                addn("jiali", me->query_skill("whip",1)/5, me);
                addn_temp("apply/attack", me->query_skill("whip",1), me);
                addn_temp("apply/damage", me->query_skill("whip",1), me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                addn("jiali", -me->query_skill("whip",1)/5, me);
                addn_temp("apply/attack", -me->query_skill("whip",1), me);
                addn_temp("apply/damage", -me->query_skill("whip",1), me);

                ap=query("combat_exp")/100+me->query_skill("whip", me)+query("neili", me);
                if (living(target))
                      dp=query("combat_exp")/100+target->query_skill("whip", target)+query("neili", target);
                else  dp = 1;
                message_combatd(HIY"\n兩招過後，$N招數一變，手中"+query("name", query_temp("weapon", me))+HIY"在空中劃了一個弧線，向$n擊落。\n"NOR,me,target);

                if(random(ap)>dp/2){

                        message_combatd(HIR"\n只聽見$n一聲慘叫，"+query("name", query_temp("weapon", me))+HIR"已經打在$n肩頭，鮮血濺了一地。\n\n"NOR,me,target);

                        damage=me->query_skill("duanyun-bian",1)*(random(6)+3);

                        if (damage<500) damage=500;
                                if (damage>2000) damage=2000;

                        target->receive_damage("qi", damage, me);
                        target->receive_wound("qi", damage/2,me);

                        str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                        message_combatd("($N"+str+")\n", target);

                } else if(random(ap)>dp/3 && objectp(query_temp("weapon",target)) && me->is_fighting() && random(4)==1){

                        message_combatd(HIG"\n$n見敵人招勢兇猛，忙舉起手中"+query("name", query_temp("weapon", target))+HIG"招架。\n",me,target);
                        message_combatd(HIW"\n$N鞭梢微揚，已經將$n手中的"+query("name", query_temp("weapon", target))+HIW"卷住，兩人同時運力回奪。\n"NOR,me,target);

                        me->start_busy(3);
                        target->start_busy(3);

                        call_out("duo", 3, me, target);

                        return 1;

                } else if(random(ap)>dp/3 && !objectp(query_temp("weapon",target)) && me->is_fighting() && random(4)==1){

                        message_combatd(HIG"\n$n身隨意轉，微微一晃已經將鞭梢抓住，兩人同時運力回奪。\n"NOR,me,target);

                        me->start_busy(4);
                        target->start_busy(4);

                        call_out("duo2", 3, me, target);

                        return 1;

                } else if(random(ap)>random(dp)) {

                        message_combatd(HIY"\n$n見此招來勢兇猛，大駭之下向後跳開。\n"NOR, me, target);

                        message_combatd(HIG"\n$N一擊不中，身子一轉，反手又是一招，猛地向$n打去。\n"NOR,me,target);

                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                } else
                        message_combatd(HIY "\n$n見此招來勢兇猛，忙向後躍開。\n"NOR,me,target);

                me->start_busy(2+random(2));
        } else
                message_combatd(HIY "\n$N見戰勢已必，長長的吸了一口氣，將內力收回。\n"NOR, me);

        delete_temp("duanyun", me);
        return 1;
}

int duo(object me, object target)
{
        int amount1, amount2;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon", me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N已手中無鞭，無法將絕招繼續，只得運功收招。\n"NOR,me);
                return 1;
        }

        if( (query("neili", me)<(me->query_skill("force",1)*15) || query("neili", target)<(target->query_skill("force",1)*15))){

                if( query("neili", me)>query("neili", target)){

                        message_combatd(HIG"\n$N運足了氣力，猛地將"+query("name", query_temp("weapon", me))+HIG"向後一拉，將$n手中的"+query("name", query_temp("weapon", target))+HIG"拉得脫手而出，掉在了地上。\n"NOR,me,target);

                        message_combatd(HIG"\n$N順手就是一招，向$n擊去。"NOR,me,target);

                        addn("jiali", me->query_skill("whip",1), me);
                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

                        addn("jiali", -me->query_skill("whip",1), me);
                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                        query_temp("weapon", target)->move(environment(me));

                        target->start_busy(2+random(3));
                } else {

                        message_combatd(HIG"\n$n運足了氣力，猛地將"+query_temp("weapon",query("name",  target))+HIG"向後一拉，將$N手中的"+query("name", query_temp("weapon", me))+HIG"拉得脫手而出，掉在了地上。\n"NOR,me,target);

                        query_temp("weapon", me)->move(environment(me));

                        me->start_busy(2+random(3));
                }

        } else {

                message_combatd(WHT"\n只見$N和$n運足了內力用力回奪自己的兵刃，兩人的衣服在內力鼓盪下如遇驟風。\n"NOR, me, target);

                amount1=me->query_skill("force",1);
                amount2=target->query_skill("force",1);

                if(random(amount1)>random(amount2)){
                        message_combatd(YEL"\n只見$n身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount1, target);
                } else {

                        message_combatd(YEL"\n只見$N身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount2, me);
                }
                addn("neili", -100, me);
                addn("neili", -100, target);

                me->start_busy(4);
                target->start_busy(4);

                call_out("duo", 3, me, target);

                return 1;
        }
        delete_temp("duanyun", me);
        return 1;
}

int duo2(object me, object target){

        int amount1, amount2;

        if (!me) return 0;

        if( !target || !me->is_fighting(target) )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !living(me) || me->is_ghost() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if( !target || environment(me) != environment(target) || !me->is_fighting() )
        {
                delete_temp("duanyun", me);
                return 0;
        }

        if (!query_temp("weapon",me) || query("skill_type", query_temp("weapon", me)) != "whip")
        {
                delete_temp("duanyun", me);
                message_combatd (HIY"\n$N已手中無鞭，無法將絕招繼續，只得運功收招。\n"NOR,me);
                return 1;
        }

        if( (query("neili", me)<(me->query_skill("force",1)*15) || query("neili", target)<(target->query_skill("force",1)*15))){

                if( query("neili", me)>query("neili", target)){

                        message_combatd(HIG"\n$N運足了氣力，猛地將"+query("name", query_temp("weapon", me))+HIG"奪回，順手就是一招，向$n擊去。"NOR,me,target);

                        addn("jiali", me->query_skill("whip",1), me);
                        addn_temp("apply/attack", me->query_skill("whip",1), me);
                        addn_temp("apply/damage", me->query_skill("whip",1), me);

                        COMBAT_D->do_attack(me,target,query_temp("weapon", me));


                        addn("jiali", -me->query_skill("whip",1), me);
                        addn_temp("apply/attack", -me->query_skill("whip",1), me);
                        addn_temp("apply/damage", -me->query_skill("whip",1), me);

                        target->start_busy(random(3));

                } else {

                        message_combatd(HIG"\n$n運足了氣力，猛地將$N手中的"+query("name", query_temp("weapon", me))+HIG"拉得脫手而出，掉在了地上。\n"NOR,me,target);

                        query_temp("weapon", me)->move(environment(me));

                        me->start_busy(2+random(3));
                }

        } else {

                message_combatd(WHT"\n只見$N和$n運足了內力用力回奪，兩人的衣服在內力鼓盪下如遇驟風。\n"NOR, me, target);

                amount1=me->query_skill("force",1);
                amount2=target->query_skill("force",1);

                if(random(amount1)>random(amount2)){
                        message_combatd(YEL"\n只見$n身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount1, target);
                } else {

                        message_combatd(YEL"\n只見$N身子一晃，似乎有些支持不住。\n"NOR, me, target);
                        addn("neili", -amount2, me);
                }
                addn("neili", -100, me);
                addn("neili", -100, target);

                me->start_busy(4);
                target->start_busy(4);

                call_out("duo2", 3, me, target);

                return 1;
        }
        delete_temp("duanyun", me);
        return 1;
}
