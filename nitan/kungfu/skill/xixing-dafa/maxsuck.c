// maxsuck.c
// Last Modified by winder on Apl. 10 2000

#include <ansi.h>

inherit F_SSERVER;
int exert(object me, object target)
{
        int sp, dp;
        int my_max, tg_max;

/*  if ( userp(me) && !wizardp(me) && 
  !query("perform/maxsuck", me) && 
  !query("can_perform/xixing-dafa/maxsuck", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("你所使用的內功中沒有這種功能。");
*/
        if( !target || !target->is_character() || target == me )
         target = offensive_target(me);

        if( query("no_fight", environment(me)) )
                return notify_fail("在這裡不能攻擊他人。\n");

        if( !objectp(target) ||
                query("id", target) == "zhangmen" || 
                query("id", target) == "gongpingzi" || 
                query("id", target) == "jinren" || 
                query("id", target) == "muren" || 
                query("id", target) == "shiren" || 
                query("id", target) == "jiguanren" || 
                query("id", target) == "xiangpiren" || 
                query("id", target) == "dujiangshi" )
                return notify_fail("你要吸取誰的丹元？\n");

        notify_fail("不是你要抓的人，湊什麼熱鬧！\n");
        if (!userp(target) && !target->accept_hit(me)) return 0;

        if( query("race", target) != "人類" )
                return notify_fail("搞錯了！只有人才能有丹元！\n");

        my_max=query("max_neili", me);
        tg_max=query("max_neili", target);

        if( query_temp("sucked", me) )
                return notify_fail("你剛剛吸取過丹元！\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能施用吸星大法吸人丹元！\n");

        if( !me->is_fighting() || !target->is_fighting())

        if( (int)me->query_skill("xixing-dafa",1) < 90 )
                return notify_fail("你的吸星大法功力不夠，不能吸取對方的丹元！□n");
        if( (int)me->query_skill("kuihua-xinfa",1) < 90 )
                return notify_fail("你的葵花心法不夠，不能運取吸星大法！\n");

        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠，不能使用吸星大法。\n");

        if( query("neili", me)>2*query("max_neili", me) )
                return notify_fail(HIR"你只覺全身真氣亂闖，看來要調理內息了。\n"NOR);

        if( me->query_skill("force")<query("max_neili", me)/10 )
                return notify_fail("你的內功太低了，再吸取也是徒勞。\n");

        if( query("max_neili", target)<100 )
                return notify_fail( target->name() +
                        "丹元渙散，功力未聚，你無法從他體內吸取任何東西！\n");

        if( query("max_neili", target)<query("max_neili", me)/10 )
                return notify_fail( target->name() +
                        "的內功修為遠不如你，你無法從他體內吸取丹元！\n");

        message_combatd(
                HIY"$N手臂猛地長出正抓在$n右手腕上。突然之間，$n猛覺右腕“內關”“外關”兩處穴道中內力源源外泄！\n\n" NOR, me, target );

        if( living(target) && !query_temp("noliving", target) )
        {
                if( !target->is_killing(me) ) target->kill_ob(me);
        }

        sp = me->query_skill("force") + me->query_skill("dodge");
        dp = target->query_skill("force") + target->query_skill("dodge");

        set_temp("sucked", 1, me);

        if (( random(sp) > random(dp) ) ||
                !living(target) || query_temp("noliving", target) )
        {
                tell_object(target, HIR"你只覺得手腕上“內關”“外關”兩處穴道便如開了兩個大缺口，立時全身內力急瀉而出，有如河水決堤，再也難以堵截！\n" NOR);
                tell_object(me, HIG"你覺得" + target->name() + "的丹元自手掌源源不絕地流了進來。\n" NOR);

                addn("max_neili", -1*(1+(me->query_skill("xixing-dafa",1)-90)/5), target);
                addn("max_neili", 1*(1+(me->query_skill("xixing-dafa",1)-90)/5), me);
                if( query("max_neili", target)<1)set("max_neili", 0, target);

                addn("potential", 3, me);
                addn("combat_exp", 10, me);

                me->start_busy(7);
                target->start_busy(random(7));
                addn("neili", -10, me);

                call_out("del_sucked", 10, me);
        }
        else
        {        
                message_combatd(HIY"可是$p看破了$P的企圖，內力猛地一震，借勢溜了開去。\n" NOR, me, target);
                me->start_busy(7);
                call_out("del_sucked", 20, me);
        }

        return 1;
}

void del_sucked(object me)
{
        if( query_temp("sucked", me) )
        delete_temp("sucked", me);
}

int help(object me)
{
        write(WHT"\n吸星大法之吸取丹元："NOR"\n");
        write(@HELP

        使用功效：
                吸取對方丹元
                增強自己內力上限

        出手要求：
                葵花心法90級
                吸星大法90級
                內力20
HELP
        );
        return 1;
}
