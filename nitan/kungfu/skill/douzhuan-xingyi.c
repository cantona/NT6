// douzhuan-xingyi.c 斗轉星移

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *parry_msg = ({
        YEL"驀地裏一股力道飛來，將$n一引一帶，$n身子輕輕越起，身行落在一旁。\n"NOR,
        BLU"$n當下一股內力衝向$l，$N擊向$n的$l的招數莫名奇妙的溜滑向一旁。\n"NOR,
        HIW"$n雙手前探，左臂搭上$N右臂，右臂使出$N的招數將$N此招化去。\n"NOR,
        HIY"$n星移斗轉，$N這招莫名其妙的在中途轉了方向，直奔自己襲來。\n"NOR,
        YEL"$n作壁上觀，雙手與對方相交數掌，談笑間竟使出$N成名技藝，使得$N不知如何是好。\n"NOR,
        BLU"$n凝神運氣向$N猛攻快打，使出的招數好似$N的成名絕技，把$N的招數化於無行。\n"NOR,
        HIW"只見$n身如飄風，恰似漫天星移，詭異地一式，雙掌動向無定不可捉摸地拍向$N的$l。\n"NOR,
        HIY"$n身行飄忽不定，在星移斗轉之間反用$N的招數擊向$N，卻令人$N百思不得其解。\n"NOR,
        HIY"$n輕輕一帶，$N發現自己招數回擊過來，嚇得往後倒退幾步。\n"NOR,
        HIY"$n手臂迴轉，在$N手肘下輕輕一推，$N招數落空。\n"NOR,
        HIY"$n右手伸出，在$N手腕上輕輕一拉，$N收勢不住，直往前撲去。\n"NOR,
        HIY"$n雙手迴圈，$N只覺得前面好像有一堵牆，再也攻不進去。\n"NOR,
});

string *unarmed_parry_msg = ({
        "但是被$p雙掌一推，$N的攻勢頓時變了方向。\n",
        "$n身形一轉，$N只覺得的所有的力道全部都落到了空處。\n",
        "但是$N感覺像打到棉花上一樣，説不出的怪異。\n",
});

int valid_enable(string usage) { return usage=="parry"; }
string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}
int valid_learn(object me)
{
        object ob;
        int d_lvl = (int) me->query_skill("douzhuan-xingyi",1);
        //int s_lvl = (int) me->query_skill("shenyuan-gong",1);
        int s_lvl = (int) me->query_skill("force",1);
        int l_lvl = (int) me->query_skill("literate",1);

        if ((int)me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本招架技巧掌握的還不夠熟練，無法學習斗轉星移。\n");
        if( (int)me->query_int() < 40 )
                return notify_fail("你仔細地想了一會，還是沒明白借力用力的道理。\n");
        if( query("max_neili", me)<600 )
                return notify_fail("你的內力不夠，沒有辦法練斗轉星移。\n");
        if( s_lvl < 100)
                return notify_fail("斗轉星移必須先學好神元功才能練習。\n");
        if( s_lvl + 30 < d_lvl)
                return notify_fail("你的內功級別不夠你真正領會更高級的斗轉星移。\n");
        if( l_lvl + 50 < d_lvl)
                return notify_fail("你的讀書寫字水平不夠你領會更高級的斗轉星移。\n");
        return 1;
}
int practice_skill(object me)
{
        return notify_fail("斗轉星移只能通過學習來提高。\n");
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1; }

mixed valid_damage(object ob, object me, int damage, object weapon)
{
         mixed result;
         int ap, dp, mp, apr, opr, app, opp, rantemp;
         int lvl, ran;
         string msg;

         if ((int) me->query_skill("douzhuan-xingyi", 1) < 100 ||
          ! living(me) || me->query_skill("shenyuan-gong",1) < 100)
              return;
        
          // 移星換月效果
          if (query_temp("yixinghuanyue", me)) 
          {
                me->stop_busy(); 
                me->clear_weak(); 
          }
                
          mp = ob->query_skill("count", 1);
          ap = me->query_skill("force", 1);
          dp = me->query_skill("parry", 1);

          lvl = me->query_skill("douzhuan-xingyi", 1);

          // 特殊反傷害機率
          if (lvl > 280)ran = 50;
          if (lvl > 300)ran = 45;
          if (lvl > 320)ran = 35;
          if (lvl > 350)ran = 30;
          if (lvl > 380)ran = 20;
          if (lvl > 400)ran = 10;
          if (lvl > 450)ran = 8;
          if (lvl > 500)ran = 6;
          if (lvl > 550)ran = 4;
          if (lvl > 600)ran = 2;

          apr = me->query_skill("force", 1) + me->query_skill("dodge", 1) +
          me->query_skill("martial-cognize", 1);
          opr = ob->query_skill("force", 1) + ob->query_skill("parry", 1) +
          ob->query_skill("martial-cognize", 1);

          app = apr - opr;

          if (app > 0)
          {
             if (app > 1500)app=1500;

             //等級差別特殊反傷害機率調整係數

                opp = 10;
             if (lvl > 280)opp = 30;
             if (lvl > 300)opp = 34;
             if (lvl > 320)opp = 43;
             if (lvl > 350)opp = 50;
             if (lvl > 380)opp = 75;
             if (lvl > 400)opp = 150;
             if (lvl > 450)opp = 188;
             if (lvl > 500)opp = 250;
             if (lvl > 550)opp = 375;
             if (lvl > 600)opp = 750;

             rantemp = ran;
             ran = ran - (app / opp);

             if (ran < 2)ran = 2;
             if (ran > rantemp)ran = rantemp;
           }

              // 斗轉星移反傷效果

              if (query_temp("yixinghuanyue", me) || (lvl > 280 &&
               me->query_skill("zihui-xinfa", 1) > 300 &&
               ! me->is_busy() &&
               //me->query("max_neili") * 2 / 3 > ob->query("max_neili") &&
               query("neili", me)>500 &&
               mp < 100)
               //random(ran) == 1 )
               )
               {
                     set_temp("xingyi/"+query("id", ob), 1, me);
                     me->start_call_out((: call_other, __FILE__, "xingyi",
                                 ob, me :), 1);
                     
                     //if( !query_temp("yixinghuanyue", me) )
                     //   me->start_busy(2);

                     result = ([ "damage" : -damage ]);
                     result += ([ "msg" : msg ]);

                     return result;

                } else

                if (ap / 2 + random(ap) < dp)
                {
                     result = ([ "damage" : -damage ]);

                     switch (random(3))
                      {
                          case 0:
                             result += ([ "msg" : HIC "$n" HIC "身形忽然轉個不停，$N"
                                                  HIC "這一招竟然無從下手。\n" NOR ]);
                          break;
                          case 1:
                             result += ([ "msg" : HIC "$n" HIC "單掌一託，$N"
                                                  HIC "登時拿捏不準力道，不禁"
                                                  "泛起一陣有心無力的感覺。\n" NOR ]);
                          break;

                          default:
                             result += ([ "msg" : HIC "$N" HIC "一招眼看擊中了$n"
                                                  HIC "，然而$n" HIC "輕輕一卸，"
                                                  "將$N" HIC "的攻擊化解於無形。\n" NOR ]);
                          break;
                        }
                     return result;
                  } else

                  if (mp >= 100)
                  {
                        switch (random(3))
                         {
                             case 0:
                               result = HIY "$n" HIY "身形忽然轉個不停，然而$N"
                                        HIY "早已看穿其中奧妙，絲毫不受影響，揮招直入。\n" NOR;
                               break;

                              case 1:
                               result = HIY "$n" HIY "單掌一託，$N"
                                        HIY "忽感拿捏不準力道，驀然警醒，登時變化招式。\n" NOR;
                               break;

                              default:
                               result = HIY "$n" HIY "輕輕一卸力，但是$N"
                                        HIY "已然看出其中四兩撥千金的變化，左右騰挪，讓$n"
                                        HIY "如意算盤就此落空。\n" NOR;
                               break;
                           }
                          COMBAT_D->set_bhinfo(result);
                    }
}

void xingyi(object ob, object me)
{
        string msg;
        int ap, dp, damage;
        object weapon;
        string menpai;

        if (! ob
        || ! me->is_fighting(ob)
         || !query_temp("xingyi/"+query("id", ob), me) )
                  return;

        menpai=query("family/family_name", ob);
        weapon=query_temp("weapon", me);
        ap = me->query_skill("force");
        dp = ob->query_skill("parry");

        if (dp / 2 + random(dp) < ap)
        {
           damage = ap+random(ap) / 2;

           msg = HIY "\n$N" HIY "施展起絕學「斗轉星移」  " HIR "----以彼之道，還施彼身----\n" NOR;

              switch (menpai)
               {
                  case "少林派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,
                                HIC "$N" HIC "使出達摩劍的絕技「達摩三絕劍」，身法陡然加快！\n"
                                HIR "$n" HIR "大吃一驚，$N" HIR "竟將使出"
                                "$p" HIR"的成名招式。\n"
                                "$n" HIR "一聲慘呼，已然閃避不及。\n" NOR);
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIB "$N" HIB "忽然面露兇光，身形變的異常飄渺，在$n"
                                HIB "的四周遊走個不停，\n$n" HIB "正迷茫時，$N"
                                HIB "突然近身，毫無聲息的一指少林「修羅絕命指」戳"
                                    "出！\n" NOR );
                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "段氏皇族" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,
                                HIY "$N" HIY "深吸一口氣，腳下步步進擊，穩重之極，手中的" +
                                weapon->name() + HIY "使得猶如飛龍一般，纏繞向$n" HIY "！\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/5, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, 0, 0,
                                HIY "$N" HIY "陡然使出「" HIR "一指乾坤" HIY "」絕技，單指勁"
                                "點$n" HIY "檀中要穴，招式變化精奇之極！\n" NOR );
                         msg += HIR "$n" HIR "只覺胸口一麻，已被$N"
                                HIR "一指點中，頓時氣血上湧，全身痠軟"
                                "。\n" NOR;
                         ob->start_busy(5+random(2));

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "武當派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,
                                HIC "$N" HIC "使出柔雲劍法「三環套月」，一招之中另藴三招，鋪天"
                                "蓋地罩向$n" HIC "！\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIW "$N" HIW "使出太極拳「震」字訣，左手高，右手低，陡然"
                                "迴圈，企圖以內力震傷$n" HIW "。\n" NOR );

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "峨嵋派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIY "$N" HIY "跨步上前，手中" + weapon->name() +
                                HIY "將峨嵋劍法運轉如飛，劍光霍霍徑直逼向$n"
                                HIY "。\n" NOR );
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, 0, 0,
                                HIC "$N" HIC "使出天罡指穴法絕技「凌空指穴」，左手"
                                "一連七指向着$n" HIC "胸前大穴接連戳出。\n" NOR );
                         msg += HIR "結果$p" HIR "不及攻敵，拼力躲避$P"
                                HIR "指力頓時動作大亂！\n" NOR;
                         ob->start_busy(3+random(3));

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "逍遙派" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIY "$N" HIY "一聲清嘯，劍法忽變，手中" + weapon->name() + HIY
                                "輕輕劃出，帶出一條無比絢麗的劍芒，遙指$n" HIY "而去。\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(2+random(2));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIR "只聽$N" HIR "一聲斷喝，雙掌紛飛，一式「攀陽邀月」接"
                                "二連三向$n" HIR "攻去。\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(2);
                       }
                       break;

                  case "星宿派" :
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 100,
                                HIR "$N" HIR "悄然遊走至$n" HIR "跟前，陡然使出"
                                "三陰手絕技「損筋訣」，單掌輕輕拂過$n" HIR "太陽"
                                "穴，不着半點力道。\n" NOR );
                         msg += HIY "$n大吃一驚，卻又突然發現，雖然招式套路完全一樣，"
                                "但自己卻未中半分毒，不禁舒了口長氣。\n" NOR;
                         addn("neili", -500, me);
                         me->start_busy(2+random(2));

                       break;

                  case "血刀門" :
                      if( objectp(query_temp("weapon", me)) )
                      {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,
                                HIW "$N" HIW "嗔目大喝，將手中武器橫握做刀" HIW "一勢「"
                                HIR "赤煉神刀" HIW "」迸出漫天血光，鋪天蓋地灑向$n"
                                HIW "。\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/3, 100,"");

                         addn("neili", -500, me);
                         me->start_busy(3+random(3));
                       } else
                       {
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIR "$N" HIR "目睚俱裂，一聲爆喝，全身骨骼劈啪作響，拳"
                                "頭如閃電般擊向$n" HIR "的要害！\n" NOR );
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage/2, 100,
                                HIR "$N" HIR "大喝一聲，面色赤紅，全身骨骼劈啪作響，又"
                                "一拳如閃電般擊向$n \n" NOR );

                         addn("neili", -500, me);
                         me->start_busy(5);
                       }
                       break;

                       default :
                         msg = HIM "\n$N" HIM "默運紫徽心法，施展起絕學「斗轉星移」，\n"
                               HIM "一股真氣在體內迅速慣行，巧妙地牽引着$n \n"
                               HIM "的招式。\n" NOR;
                         msg += COMBAT_D->do_damage(me, ob, REMOTE_ATTACK, damage, 200,
                               HIR "\n$n" HIR "大吃一驚，不料$N" HIR "竟將"
                               "$p" HIR"先前的招式盡數折回反攻向自己。\n猛"
                               "然間$n" HIR "一聲慘呼，已然閃避不及。\n" NOR);

                         addn("neili", -500, me);
                         me->start_busy(2);

                  }

        } else
        {
               msg = HIC "$n" HIC "眼見$P來勢洶湧，不敢"
                      "大意，施出渾身解數化解開來。\n" NOR;
        }
           delete_temp("xingyi", me);
           message_combatd(msg, me, ob);
}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}
int help(object me)
{
        write(HIC"\n斗轉星移："NOR"\n");
        write(@HELP

    姑蘇慕容家最拿手的絕技，乃是一門借力打力之技，叫做“鬥
轉星移”。外人不知底細，見到慕容氏“以彼之道，還施彼身”神
乎其技，凡在致人死命之時，總是以對方的成名絕技加諸其身，顯
然天下各門各派的絕技，姑蘇慕容氏無一不會，無一不精。其實武
林中絕技千千萬萬，任他如何聰明淵博，決難將每一項絕技都學會
了，何況既是絕技，自非朝夕之功所能練成。但慕容氏有了這一門
巧妙無比的“斗轉星移”之術，不論對方施出何種功夫來，都能將
之轉移力道，反擊到對方自身。出手的人武功越高，死法就越是巧
妙。慕容氏若非單打獨鬥，若不是有把握定能致敵死命，這“鬥轉
星移”的功夫便決不使用，是以姑蘇慕容氏名震江湖，真正的功夫
所在，卻是誰也不知。將對手的兵刃拳腳轉換方向，令對手自作自
受，其中道理，全在“反彈”兩字。便如有人一拳打在石牆之上，
出手越重，拳頭上所受的力道越大，輕重強弱，不差分毫。只不過
轉換有形的兵刃拳腳尚易，轉換無形無質的內力氣功，那就極難。

        學習要求：
                不叛師
                慕容復的嫡傳弟子
                後天悟性40
                神元功100級
                神元功不能低於斗轉星移30級
                讀書寫字不能低於斗轉星移50級
                內力600
HELP
        );
        return 1;
}
