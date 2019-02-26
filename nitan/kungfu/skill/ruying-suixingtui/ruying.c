// gladiator

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int i; 

        i = me->query_skill("ruying-suixingtui", 1) / 4;

        if( userp(me) && !query("can_perform/ruying-suixingtui/ruying", me) )
                return notify_fail("你所使用的外功中沒有這樣的功能。\n");
        
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「如影隨形」只能在戰鬥中對對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("使用「如影隨形」時雙手必須空着！\n");

        if( (int)me->query_skill("ruying-suixingtui", 1) < 160 )
                return notify_fail("你的如影隨形腿不夠嫻熟，不會使用「如影隨形」。\n");

        if( (int)me->query_skill("force", 1) < 160 )
                return notify_fail("你的內功等級不夠，不能使用「如影隨形」。\n");

        if( (int)me->query_dex() < 30 )
                return notify_fail("你的身法不夠強，不能使用「如影隨形」。\n");

        if (me->query_skill_prepared("unarmed") != "ruying-suixingtui"
        || me->query_skill_mapped("unarmed") != "ruying-suixingtui")
                return notify_fail("你現在無法使用「日月同輝」進行攻擊。\n");
 
        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為太弱，不能使用「如影隨形」！\n");

        if( query("neili", me)<700 )
                return notify_fail("你現在內力太少，不能使用「如影隨形」。\n"); 

        addn("neili", -500, me);
      
        msg = YEL "\n你猛吸一口真氣，體內勁力瞬時爆發！\n" NOR;
        message_vision(msg, me, target); 
       
        addn_temp("apply/str", i, me);
        addn_temp("apply/dex", i, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i, me);

        if( random(query("combat_exp", me))>query("combat_exp", target)/2
        &&  random((int)me->query_skill("force")) > (int)target->query_skill("force") / 2)
       { 
             msg = HIY "$N忽然躍起，左腳一勾一彈，霎時之間踢出一招「如」字訣的穿心腿，直襲$n前胸！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        
             msg = HIY "緊接着$N左腿勾回，將腰身一扭，那右腿的一招「影」字訣便緊隨而至，飛向$n！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),1,msg);
 
             msg = HIY"只見$N右腳勁力未消，便凌空一轉，左腿順勢掃出一招「隨」字訣，如影而至！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

             msg = HIY"半空中$N腳未後撤，已經運起「形」字訣，內勁直透腳尖，在$n胸腹處連點了數十下！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

             msg = HIR"這時$N雙臂展動，帶起一股強烈的旋風，雙腿霎時齊並，「如影隨形」一擊重炮轟在$n胸膛之上！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        } else 
       {
             msg = HIY"$N忽然躍起，左腳一勾一彈，霎時之間踢出一招「如」字訣的穿心腿，直襲$n前胸！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);
        
             msg = HIY"緊接着$N左腿勾回，將腰身一扭，那右腿的一招「影」字訣便緊隨而至，飛向$n！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),1,msg);
 
             msg = HIY"只見$N右腳勁力未消，便凌空一轉，左腿順勢掃出一招「隨」字訣，如影而至！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_QUICK,msg);

             msg = HIY"半空中$N腳未後撤，已經運起「形」字訣，內勁直透腳尖，在$n胸腹處連點了數十下！"NOR;
             COMBAT_D->do_attack(me,target,query_temp("weapon", me),1,msg);
        }
 
             msg = YEL "\n你連環飛腿使完，全身一轉，穩穩落在地上。\n" NOR;
               
             addn("neili", -400, me);
             addn_temp("apply/dex", -i, me);
             addn_temp("apply/damage", -i, me);
             addn_temp("apply/str", -i, me);
             addn_temp("apply/attack", -i, me);
             me->start_busy(2+random(2));

        return 1;
}
