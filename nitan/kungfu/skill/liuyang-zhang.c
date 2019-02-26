// liuyang-zhang.c 天山六陽掌

#include <ansi.h>;
#include <combat.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
void sun1(object me, object victim, object  weapon, int damage);
void sun2(object me, object victim, object  weapon, int damage);
void sun3(object me, object victim, object  weapon, int damage);
void sun4(object me, object victim, object  weapon, int damage);
void sun5(object me, object victim, object  weapon, int damage);
void sun6(object me, object victim, object  weapon, int damage);
int baihong(object me, object victim, int damage);
mapping *action = ({

([      "action" : "$N一招"RED"「落日熔金」"NOR"，左掌疊於右掌之上，劈向$n",
        "lvl" : 0,
        "skill_name" : "落日熔金"
]),
([      "action" : "$N一招"HIY"「安禪製毒龍」"NOR"，面色凝重，雙掌輕飄飄地拍向$n",
        "lvl" : 20,
        "skill_name" : "安禪製毒龍"
]),
([      "action" : "$N一招"HIR"「日斜歸路晚霞明」"NOR"，雙掌幻化一片掌影，將$n籠罩於內。",
        "lvl" : 30,
        "skill_name" : "日斜歸路晚霞明"
]),

//([    "action" : "$N一招"HIG"「陽關三疊」"NOR"，向$n的$l連擊三掌",
//      "lvl" : 40,
//      "skill_name" : "陽關三疊"
//]),
([      "action" : "$N一招"GRN"「陽春一曲和皆難」"NOR"，只見一片掌影攻向$n",
        "lvl" : 40,
        "skill_name" : "陽春一曲和皆難"
]),

([      "action" : "$N雙掌平揮，一招"BLU"「雲霞出海曙」"NOR"擊向$n",
        "lvl" : 60,
        "skill_name" : "雲霞出海曙"
]),
([      "action" : "$N一招"HIW"「白日參辰現」"NOR"，只見一片掌影攻向$n",
        "lvl" : 70,
        "skill_name" : "白日參辰現"
]),

([      "action" : "$N左掌虛晃，右掌一記"HIC"「雲霞出薛帷」"NOR"擊向$n的頭部",
        "lvl" : 80,
        "skill_name" : "雲霞出薛帷"
]),
([      "action" : "$N施出"HIB"「青陽帶歲除」"NOR"，右手橫掃$n的$l，左手攻向$n的胸口",
        "lvl" : 90,
        "skill_name" : "青陽帶歲除"
]),
//([    "action" : "$N施出"HIR"「陽歌天鈞」"NOR"，雙掌同時擊向$n的$l",
//      "lvl" : 100,
//      "skill_name" : "陽歌天鈞"
//])
  ([ "action":
HIY"$N使出"HBBLU+HIW"天山六陽掌"NOR+HIY"第一掌"HIR"「陽關三疊」"HIY"強勁的掌力以連綿不絕生生不息之力
有如排山倒海之勢朝$n擊去，一掌三式掌勁渾厚無匹。"NOR,
        "lvl" : 201,
                "force":                500,
     //           "damage":               300,
                 "post_action":               (:sun1:),
                "damage_type":  "內傷",
       ]),
//2
  ([ "action":
HIY"$N聚起全身的內力化勁成焰，一招"HIW"「烈陽普照」"HIY"全身上下發出巨大的光芒，刺
眼的光芒使$n無法張眼，$N身上發出強烈的温度使$n全身灼傷有如陷
入焚爐之中痛苦萬分。"NOR,
        "lvl" : 210,
        "force":        520,
     //   "damage":       350,
        "post_action":               (:sun2:),
        "damage_type":  "灼傷",
        ]),
//3
  ([ "action":
HIY"$N左手運勁內走奇經八脈化氣成焰，右手逆轉內勁氣走丹田化為霜，使出\n"
HBBLU+HIW"天山六陽掌"NOR+HIY"第三掌"HIC"「陽盛陰衰」"HIY"，強大的內勁催使$n左冷右熱兩極
交叉內息大亂受到嚴重的內傷狂吐鮮血。"NOR,
           "lvl" : 220,
           "force":       540,
       //    "damage":      400,
           "post_action":               (:sun3:),
           "damage_type":  "內傷",
      ]),
//4
  ([ "action":
HIC"$N身法如鷹府衝而下使出"HBBLU+HIW"天山六陽掌"NOR+HIC"第四掌"HIW"「陽歌天鈞」"HIC"以詭異的身法遊走$n的四方，趁其不備雙
手運勾朝$n的腦門撲擊而去。"NOR,
        "lvl" : 230,
          "force":        560,
      //    "damage":       450,
          "post_action":          (:sun4:),
          "damage_type":  "瘀傷",
        ]),
//5
  ([ "action":
HIM"$N使出"HBBLU+HIW"天山六陽掌"NOR+HIM"第五掌"HIC"「春陽白雪」"HIM"，$N身形飛舞全身散發寒勁成霜，當場雪
花漫天飛舞，$n完全看不見四周的情形，$N趁機發動攻勢偷襲使其受創。"NOR,
        "lvl" : 240,
           "force":        580,
     //      "damage":       500,
          "post_action":      (:sun5:),
           "damage_type":  "瘀傷",
        ]),
//6
  ([ "action":
HIR"$N聚勁雙臂運勁成焰，凝聚強大的熱量使出"HBBLU+HIW"天山六陽掌"NOR+HIR"第六掌"HIY"「驕陽似火」"HIR"，烈焰
掌勁侵入$n全身陣陣如火酷勁有如遭烈焰焚身。"NOR,
        "lvl" : 250,
           "force":        600,
     //      "damage":       600,
           "post_action":      (:sun6:),
           "damage_type":  "焚傷",
        ])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="zhemei-shou"; }

int valid_learn(object me)
{
        if( query("str", me)<30 )
                return notify_fail("你研究了半天，感覺膂力有些低，始終無法隨意施展。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練天山六陽掌必須空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候不夠，無法練六陽掌。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力太弱，無法練六陽掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("liuyang-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的天山六陽掌。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<30 )
                return notify_fail("你的內力不夠練天山六陽掌。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -30;
        int d_e2 = -10;
        int p_e1 = 10;
        int p_e2 = 40;
        int f_e1 = 160;
        int f_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("liuyang-zhang", 1);

        if( random(query_temp("lingjiu/baihong", me))>50 || query_temp("baihong_attack", me) )
        {
                string msg;
                switch(query_temp("baihong_attack", me) )
                {
                        case 1: msg = "不料$N左掌一帶，掌力繞過$N的身子，直拍向$p$l";
                                break;
                        case 2: msg = WHT"誰知$N一掌未竭第二掌又至，連催兩重勁，掌力便如長蛇之遊，奇詭不可設想"NOR;
                                break;
                        default: msg = WHT"突然間$N掌力破空，拍向$n，勁風撲面，鋒利如刀，轉而斜砍$p$l"NOR;
                                break;
                }

                addn_temp("lingjiu/baihong", -1, me);
                addn("neili", -30, me);

                return ([
                        "action": msg,
                        "force" : 380+random(120),
                        "dodge" : -60,
                        "parry" : -80,
                        "damage": 220+random(80),
                        "damage_type":"內傷",
                        "post_action": (: baihong :)
                        ]);
        }

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        if ( /*me->query_family() =="lingjiu" &&*/ (int)me->query_skill("bahuang-gong",1) >= 250)
        {
                        seq=sizeof(action)-6+random(6);
                        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : action[seq]["force"],
                "damage"      : action[seq]["damage"],
                "post_action"   : action[seq]["post_action"],
                "damage_type" : random(2) ? "內傷" : "瘀傷",
          ]);
        }
        if (seq > sizeof(action)-6)
                seq = sizeof(action)-6;
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"liuyang-zhang/" + action;
}
void sun1(object me, object victim, object weapon, int damage)
{
         if( ((query("combat_exp", me)+random(2000000))>(query("combat_exp", victim)+random(2000000)) )
         || random(50)>40)
         {
           message_combatd(HIR"陽關三疊之"HBRED+HIM"【毀山劈天】\n"NOR, me, victim);
           victim->receive_damage("qi",200);
           COMBAT_D->report_status(victim);
           message_combatd(HIR"陽關三疊之"HBBLU+HIC"【形合破滅】\n"NOR, me, victim);
           victim->receive_wound("qi",100);
           COMBAT_D->report_status(victim);
           message_combatd(HIR"陽關三疊之"HBGRN+HIG"【虛空無極】\n"NOR, me, victim);
           if( (query("neili", victim)-100)<0 )
             set("neili", 0, victim);
           else addn("neili", -100, victim);
           COMBAT_D->report_status(victim);
         }else message_combatd(HIW"$n順勢閃過了$N烈陽餘勁的攻擊。\n"NOR, me, victim);

}
void sun2(object me, object victim, object weapon, int damage)
{
        if(((me->query_skill("dodge")+random(100)) > (victim->query_skill("dodge")+random(100)))
         || random(50)>40)
        {
          message_combatd(HIR"\n$n一個不小心被$N的烈陽餘勁所傷。\n"NOR, me, victim);
          victim->receive_damage("qi",200);
          victim->apply_condition("hot_poison",random(10)+1);
          COMBAT_D->report_status(victim);
        }
}
void sun3(object me, object victim, object  weapon, int damage)
{
       if(((me->query_skill("force")+random(500)) > (victim->query_skill("force")+random(500)))
         || random(50)>30)
       {
         message_combatd(HIC"\n$n受不了忽冷忽熱的煎熬受了嚴重的內傷。\n"NOR, me, victim);
         victim->receive_damage("qi",300);
         victim->apply_condition("cuff_power",1);
         COMBAT_D->report_status(victim);
       }
}
void sun4(object me, object victim, object weapon, int damage)
{
       if(((me->query_skill("parry")+random(100)) > (victim->query_skill("parry")+random(100)))
         || random(50)>45)
       {
         message_combatd(HIY"\n$n閃躲不擊慘招$N凌厲攻勢所傷。\n"NOR, me, victim);
         victim->receive_wound("qi",200);
         victim->apply_condition("bleeding",random(10)+1);
         COMBAT_D->report_status(victim);
       }
}
void sun5(object me, object victim, object weapon, int damage)
{
       if( ((query("parry", me)+random(100))>(query("parry", victim)+random(100)) )
         || random(50)>40)
       {
         message_combatd(HIW"\n$N使出天山六陽掌之變招‘天山折梅手’，$n被此招牽制無法使力。\n"NOR, me, victim);
         victim->receive_damage("qi",200);
         victim->start_busy(me->query_skill("liuyang-zhang",1)/100);
         COMBAT_D->report_status(victim);
       }
}

void sun6(object me, object victim, object weapon, int damage)
{
       if( ((query("combat_exp", me)+random(2000000))>(query("combat_exp", victim)+random(2000000)) )
         || random(50)>45)
       {
         message_combatd(HIG"$N"HIY"驕陽似火"HIG"一出，$n運勁丹田竟感覺空空蕩蕩毫無內勁。\n"NOR, me, victim);
         if( query("neili", victim)<500 )
          set("neili", 0, victim);
         else
          addn("neili", -500, victim);
 //        COMBAT_D->report_status(victim);
       }
}

int baihong(object me, object victim, int damage)
{
        int level = (int)me->query_skill("liuyang-zhang", 1)/2;

        addn_temp("baihong_attack", 1, me);

        if( damage == RESULT_DODGE && query_temp("baihong_attack", me)<3 )
        {
                addn_temp("apply/attack", level, me);

                if( query_temp("baihong_attack", me) == 1 )
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me),TYPE_QUICK);
                else delete_temp("baihong_attack", me);

                addn_temp("apply/attack", -level, me);
                return 1;
        }
        else delete_temp("baihong_attack", me);
        return 1;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("liuyang-zhang", 1); 

        if( lvl >= 1000 && query("reborn/times", me) &&
            !query("can_perform/liuyang-zhang/zun", me) )  
        { 
                tell_object(me, HIC "你通曉了天山六陽掌「" HIR "八荒獨尊掌" HIC "」的奧祕。\n" NOR);     
                set("can_perform/liuyang-zhang/zun", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
}

int help(object me)
{
        write(HIC"\n天山六陽掌："NOR"\n");
        write(@HELP

    天山六陽掌為靈鷲宮武功絕技。

        學習要求：
                北冥神功20級或八荒六合唯我獨尊功20級
                內力50
HELP
        );
        return 1;
}
