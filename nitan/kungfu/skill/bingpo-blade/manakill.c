// made by cii for snow
#include <command.h>
#include <ansi.h>
inherit F_SSERVER;
int perform(object me, object target)
{
       string msg;
       int ski_value, max_lv;
       ski_value= random(me->query_skill("bingpo-blade",1));
       max_lv=me->query_skill("bingpo-blade",1);

        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("『魔氣殺』只能對戰鬥中的對手使用。\n");
  
/*
        if( me->query_skill_mapped("blade")!="bingpo-blade" )
         return notify_fail("你沒有裝備冰破寒刀。 \n");
*/
   if( me->query_skill("bingpo-blade",1)<100 )
         return notify_fail("你的冰破寒刀技巧不足。 \n");

   if( me->query_skill("blade",1)<100 )
         return notify_fail("你的刀法不夠好。 \n");
   if( query("neili", me)<1000 )
         return notify_fail("你的內力不夠。\n");
   if( target->is_busy() )
      return notify_fail(target->name() + "為了躲避你的殺氣,目前正自顧不暇!\n");
msg = HIY "$N自殘己身,以血氣轉換成殺氣。\n
            ……$N身上發出一股強大的殺氣……\n
    ■$N身上殺氣逐漸地聚集在雙手,在雙手上形成兩團魔氣■\n
            $N倏地大喝一聲－－魔 氣 殺－－\n\n" NOR;

     if( ski_value+50<random(max_lv) && query("combat_exp", me)>2000000){
     msg += HIR BLINK "$N突然喉頭一動～～　只見$N口中噴出一道血柱往$n射去～～\n
此乃魔氣殺之
            最終殺招 『魔 血 氣 殺』\n\n
$n遭到前所未有的打擊,但$N也受傷不輕。\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") / 20 + 3);
     target->receive_damage("qi",query("max_qi", target)*70/100);
     me->receive_damage("qi",query("qi", me)*30/100);
     addn("neili", -50, me);
     }
   else if( ski_value < 20 ){
      msg +="$N真氣所轉換的殺氣不夠大,對敵人毫無影響。\n";
      me->receive_damage("qi",query("qi", me)*1/100);
      addn("neili", -50, me);}
     
    
    else if( ski_value <  70 ){
     msg += HIM "第一招 『魔氣無常』\n\n$n受到傷害,動彈不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);

     addn("neili", -query("max_neili", me)*2/10, me);}
    
    else if( ski_value <  90 ){
     msg += HIG "第二招 『火魔煞神』\n\n$n受到傷害,動彈不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);
 
     addn("neili", -query("max_neili", me)*3/10, me);}
     
     else  if( ski_value < 100 ){
     msg += HIC "第三招 『商魂魔身』\n\n$n受到傷害,動彈不得。\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);

     addn("neili", -query("max_neili", me)*4/10, me);}

     else if( ski_value <  120 ){
     msg += HIB "第四招 『劍魔滅世』\n\n$n受到傷害,動彈不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 1);

     addn("neili", -query("max_neili", me)*5/10, me);}

     else if( ski_value <  140 ){
     msg += HIW "第五招 『狂魔破空』\n\n$n受到傷害,動彈不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*6/10, me);}


     else if( ski_value <  160 ){
     msg += CYN "第六招 『群魔亂舞』\n\n$n受到傷害,動彈不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*7/10, me);}

     else if( ski_value <  180 ){
     msg +=  YEL "第七招 『天極魔殺』\n\n$n受到傷害,動彈不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*8/10, me);}

     else if( ski_value <  200 ){
     msg += BLU "第八招 『鬥魔無生魂』\n\n$n受到傷害,動彈不得！\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);

     addn("neili", -query("max_neili", me)*9/10, me);}

     else                    {
     msg += RED "第九招 『風魔狂轉業』\n\n$n受到傷害,動彈不得。\n" NOR;
     target->start_busy( (int)me->query_skill("bingpo-blade") /100 + 2);
 
     addn("neili", -query("max_neili", me)*9/10, me);}

     message_vision(msg, me, target);
        return 1;
}