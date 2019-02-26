//Code of Shenzhou
//coding by Slow
#include <ansi.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_SSERVER;

void remove_effect(object me);
void checking(int del_time,object me);

int exert(object me, object target)
{
          int lv;

          if( !query("canewhua", me))return notify_fail("你還沒得到化功大法的真傳。\n");

          /*
          if( query("family/family_name", me) != "星宿派" )
                  return notify_fail("化功大法是星宿派的獨門絕學。\n");
          */

          if( query("no_fight", environment(me)) && file_name(environment(me)) != "/d/city/biwu_dating" )
                  return notify_fail("在這裏不能運用化功大法。\n");

          lv = (int)me->query_skill("huagong-dafa", 1);

          if( target == me) target=offensive_target(me);
          if( !target ) target = offensive_target(me);
          if( !target ) target = me->select_opponent();

          if( query_temp("newhua", me) )
                    return notify_fail("你已經施展出化功大法了！\n");


          if( me->query_skill("huagong-dafa", 1) < 360 )
                    return notify_fail("你的化功大法火候未到！\n");

          if( me->query_skill_mapped("force") != "huagong-dafa")
                    return notify_fail("你所運使的內功並非化功大法，無法施展開來！\n");

          if( query("neili", me) <= 3000 )
                  return notify_fail("你的內力不足以施展化功大法！\n");

          if( query("jingli", me) <= 900 )
                  return notify_fail("你的精力不足以施展化功大法！\n");

          if( me->query_skill_mapped("sword") == "pixie-jian" ||
              me->query_skill_mapped("parry") == "pixie-jian" ||
              me->query_skill_mapped("dodge") == "pixie-jian" )
          return notify_fail("辟邪劍法與化功大法的修煉方法相悖，無法同時施展化功大法和辟邪劍法！\n");
          if(me->is_busy())
                  return notify_fail("你正忙着呢,沒辦法施展化功大法! \n");

message_vision(
HIB"$N突然面色陰暗下來，乾笑幾聲，陡然加快身法，將一雙大袖舞得呼呼風響。\n"
HIG"只見$N越舞越快滿場遊走，化功大法激發出的真氣佈滿$N的兩隻袖袍，象鼓足的風帆。\n"
HIB"四處瀰漫的真氣將空氣擠成一股股洶湧澎湃的氣浪。\n" NOR, me, target );


          set_temp("newhua", me->query_skill("huagong-dafa",1)/20+10, me);
          call_out("checking", 1, 1, me);
          return 1;
}


void checking(int del_time,object me)
{
          int num,ap,dp,dmg,the_time;
         int exp_div;
          object target;

          if( !me || !query_temp("newhua", me))return ;
          target=query_temp("offensive_target", me);
          num=query_temp("newhua", me);

          if( me->query_skill_mapped("sword") == "pixie-jian" ||
              me->query_skill_mapped("parry") == "pixie-jian" ||
              me->query_skill_mapped("dodge") == "pixie-jian" )
          {
                  delete_temp("newhua", me);
                  message_vision(HIY "\n$N用辟邪劍法與化功大法的修煉方法相悖，不可同時施展化功大法和辟邪劍法！！\n"NOR, me);;
                  return;
          }
          set_temp("newhua",query_temp("newhua",  me)-del_time, me);
          if( wizardp(me) )  tell_object(me,sprintf("<持續時間還剩%d秒>\n",num));
          if( num<1 )
          {
                  message_vision(YEL"$N漸感內力不支，不得已將已發揮到極致的「化功大法」緩緩收回丹田。\n"NOR, me);
                  delete_temp("newhua", me);
                  return;
          }
          if( !target ) target = offensive_target(me);
          if( !target || !target->is_character() || !me->is_fighting(target) )
          {
                  call_out("checking", 1, 1, me);
                  return;
          }


          if( !living(me) || me->is_ghost()  )
          {
                  remove_effect(me);
                  return;
          }

        if( query("combat_exp", me)>10000000 )
                exp_div = 10000;
        else
                exp_div = 1000;
          ap=query("combat_exp", me)/exp_div;
          ap += me->query_skill("force");
          ap+=query("kar", me)*50;
          ap += me->query_skill("poison",1)*2;
          dp=query("combat_exp", target)/exp_div;
          dp += target->query_skill("force");
          dp+=query("kar", target)*50;
          dp += target->query_skill("dodge",1)*2;

          if (random(16)>7)
          {
                  if(ap > (dp/2 + random(dp)))
                  {
                          message_vision(
HIR "$n剛剛靠近$N，只覺得一股陰冷無比的氣浪撲來要將自己卷裹進去，連忙運功布氣。\n"
CYN "$N冷哼一聲，黑氣騰騰的雙手已抓住$n的脈門大穴，$n疼入骨髓不由發出淒厲慘叫。\n" NOR, me, target );
                          tell_object(target, HIR "你突然覺得全身真氣自手掌奔湧而出，四肢無力，再也使不出勁來！\n" NOR);
                          tell_object(me, HIG "你覺得" + target->name() + "的真氣自手掌源源不絕地流了進來。\n" NOR);
                        dmg=(int)me->query_skill("force")*3 +random(1+(int)me->query_skill("force"));
                          target->receive_damage("qi", dmg, me );
                          target->receive_wound("qi", dmg/2+random(dmg/2), me);
                          addn("qi", me->query_skill("force"), me);
                          COMBAT_D->report_status(target);
                          if (! target->is_busy())
                          target->start_busy(random(3));
                          if( !target->is_killing(me) ) target->kill_ob(me);
                  }
         }
         else
         {
                  message_vision(
HIB"忽見三條"+HIW+"銀線"+HIB+"從$N的百會、左右太陽穴如冰蠶延行般直入眉心。\n"
HIB"$N額頭已隱隱罩上一層殷藍之氣，突然身形一轉袖袍狂舞變化出重重身影，身影中似有無數利爪向$n抓去。\n"
HIB"$N臉色越發陰暗，身上的玉笛在真氣的鼓盪之下發出刺耳嗡鳴擾得$n心煩意亂，攻勢不由得減緩了下來。\n"
HIW"$N見$n略顯頹勢，長嘯一聲將鼓足真氣雙袖象兩堵高牆一般砸了過去，$n只得格架卻將膻中穴暴露無遺。\n" NOR,
                           me, target );
                  if(ap > (dp/2 + random(dp)))
                  {
                           message_vision(
                              HIR "$N頓覺膻中微痛，如同被尖針刺了個小孔，全身內力如水銀般循孔飛泄而出！\n\n" NOR,
                              target );
                           tell_object(me, HIG "你覺得" + target->name() + "的內力自手掌源源不絕地流了進來。\n" NOR);
                           if( query("neili", target)>me->query_skill("force")*2 )
                           {
                                   addn("neili", -me->query_skill("force")*2, target);
                                   addn("neili", (me->query_skill("force")), me);
                           }else{
                                   addn("neili", (me->query_skill("force"))/2, me);
                                   set("neili", 0, target);
                           }
                  }
                  if( !target->is_killing(me) ) target->kill_ob(me);
        }
        the_time = 3+random(3);
        call_out("checking", the_time, the_time, me);
        return;
}

void remove_effect(object me)
{
        if (!me) return;
        delete_temp("newhua", me);
        me->start_busy(1);
}