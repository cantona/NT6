// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"入 白 刃"NOR; }
int perform(object me, object target)
{
        int skill;
        object weapon;
        skill = (int)me->query_skill("super-strike", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("入白刃只能在戰鬥中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿著武器怎麼能使用「入白刃」！\n");   
        if( skill < 150 )
                return notify_fail("你的鐵掌掌法不夠嫻熟，使不出「入白刃」。\n");
        if(me->query_skill("force",1) < 150 )
                return notify_fail("你的歸元吐吶法不夠嫻熟，使不出「入白刃。\n");
        if(me->query_skill_mapped("strike") != "super-strike" )
               return notify_fail("你現在無法使用「入白刃」！\n");
        if( (int)me->query("max_neili") < 2000)
                return notify_fail("你現在內力太弱，使不出「入白刃」。\n");      
        if( (int)me->query("neili") < 1500 )
                return notify_fail("你現在真氣太弱，使不出「入白刃」。\n");
        weapon = target->query_temp("weapon");
        if (!weapon)
                return notify_fail("對手沒有兵器，你要奪他的手嗎？\n");      

        message_vision(HBBLU"\n$N左掌向他臉上拍去。$n忙舉起"NOR+weapon->name()+HBBLU"擋格。\n"NOR,me,target);
        if (random(me->query_str()) > target->query_str()/2) {
           message_vision(HIR"\n$N變招快極，左手下壓，已抓住"+weapon->name()+HIR"！\n"NOR,me,target);
           message_vision(HIR"$N掌緣甫觸"+weapon->name()+HIR"，尚未抓緊，已向裡奪！\n"NOR,me,target);
           if (random(me->query_str()) > target->query_str()/4) {
              message_vision(HIR"$n手中的"+weapon->name()+HIR"已被$N硬生生的奪去了！\n"NOR,me,target);
              weapon->move(me);
              target->reset_action();
           } else
              message_vision(HIR"只是$N力量不如$n，無法將$n的"+weapon->name()+HIR"奪過。\n"NOR,me,target);
           target->start_busy(2);
        } else
           message_vision(HIR"\n$n"+weapon->name()+HIR"陡然轉向，$N急忙收手。\n"NOR,me,target);
        me->start_perform(3,"「入白刃」");
        return 1;
}

