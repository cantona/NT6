// 血海魔刀
#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";;

mapping *action = ({
([      "action" : CYN"$N一招「"HIR"磨牙吮血"CYN"」，將$w"CYN"銜在嘴裏，等$n走近了，突然間左手抓住刀柄，順手一揮，砍向$p$l"NOR,
        "skill_name" : "磨牙吮血",
        "force" : 200,
        "dodge" : 15,
        "lvl" : 0,
        "damage" : 150,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N嘿嘿一笑，一式「"MAG"批紙削腐"CYN"」，一刀橫削過去，$n只覺眼前紅光閃動，$l上微微一涼"NOR,
        "skill_name" : "批紙削腐",
        "force" : 240,
        "dodge" : 25,
        "lvl" : 20,
        "damage" : 175,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N銜$w"CYN"在口，空手在$n身旁穿來插去，驀地裏右手從口中抽出刀來，「"HIR"血海茫茫"CYN"」一揮之下，刀鋒直劈$p$l"NOR,
        "skill_name" : "血海茫茫",
        "force" : 280,
        "dodge" : 30,
        "lvl" : 30,
        "damage" : 160,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N嘿嘿冷笑聲中，一招「"HIR"血洗天河"CYN"」，突見那$w"HIR"紅影"CYN"閃閃，迎頭彎轉，竟如一根軟帶一般曲了下來，刀頭削向$n$l"NOR,
        "skill_name" : "血洗天河",
        "force" : 320,
        "dodge" : 55,
        "lvl" : 50,
        "damage" : 190,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N身子向前一探，一招「"HIR"血蛇逐電"CYN"」，$w"CYN"顫動，刀刃便如一條赤練蛇一般，迅速無倫地在$n身上爬行而過，隨即收刀入鞘，哈哈大笑"NOR,
        "skill_name" : "血蛇逐電",
        "force" : 350,
        "dodge" : 75,
        "lvl" : 70,
        "damage" : 200,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N低吼一聲，凜然生威，將手中$w"CYN"刀柄反拿，一式「"HIR"血痕累累"CYN"」，捲起片片刀風斬向$n的$l"NOR,
        "skill_name" : "血痕累累",
        "force" : 380,
        "dodge" : 60,
        "lvl" : 90,
        "damage" : 260,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N氣透刀尖，捲起刺骨寒風，一招「"BLU"血風刺骨"CYN"」向前直劈而下，一道紅光從上至下剖向$n的$l"NOR,
        "skill_name" : "血風刺骨",
        "force" : 500,
        "dodge" : 55,
        "lvl" : 100,
        "damage" : 380,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N一式「"HIR"血雨空鳴"CYN"」，一口$w"CYN"越使越快，一團團紅影籠罩了全身，向$n連砍數刀，都是隻攻不守，極其凌厲的招數"NOR,
        "skill_name" : "血雨空鳴",
        "force" : 620,
        "dodge" : 10,
        "lvl" : 120,
        "damage" : 320,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N略略側身，一招「"MAG"斬頭式"CYN"」反手從背後橫劈出一刀，直奔$n的項頸。\n  "NOR,
        "skill_name" : "斬頭式",
        "force" : 200,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "damage" : 130,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N突然橫卧於地，$n目瞪口呆之際，一招「"GRN"破膛刀"CYN"」，手中$w"CYN"由下而上直劈$n的小腹。  "NOR,
        "skill_name" : "破膛刀",
        "force" : 240,
        "dodge" : 5,
        "parry" : 15,
        "lvl" : 8,
        "damage" : 150,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N足尖一點，一個倒翻頭頂着地，一招「"YEL"去魂電"CYN"」，$w"CYN"一閃，自左而右，由右到左連出十刀。  "NOR,
        "skill_name" : "去魂電",
        "force" : 280,
        "dodge" : 10,
        "parry" : 15,
        "lvl" : 16,
        "damage" : 165,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N怪叫一聲，飛騰空中，一招「"BLU"流星經天"CYN"」，手中$w"CYN"脱手而出，疾射$n的$l  "NOR,
        "skill_name" : "流星經天",
        "force" : 320,
        "dodge" : 0,
        "parry" : 5,
        "lvl" : 23,
        "damage" : 170,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N臉色詭異，喉中“"BLU"呵呵"CYN"”低吼，一招「"YEL"蛇行"CYN"」，$w"CYN"靈動異常的在$n的$l遊走過去  "NOR,
        "skill_name" : "蛇行",
        "force" : 350,
        "dodge" : 35,
        "parry" : 25,
        "lvl" : 30,
        "damage" : 180,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N一招「"HIW"三界咒"CYN"」，手中$w"CYN"微微一抖，“"HIW"嗤嗤嗤"CYN"”三聲輕響，向$n頭、胸、腹連劈三刀。  "NOR,
        "skill_name" : "三界咒",
        "force" : 320,
        "dodge" : 10,
        "parry" : 25,
        "lvl" : 40,
        "damage" : 210,
        "damage_type" : "割傷",
]),
([      "action" : CYN"$N炸雷般大喝一聲，一式「"HIR"魔分身"CYN"」$w"CYN"照$n摟肩帶背斜劈下來，力道兇猛，勢不可擋。  "NOR,
        "skill_name" : "魔分身",
        "force" : 500,
        "dodge" : 15,
        "parry" : 10,
        "lvl" : 60,
        "damage" : 230,
        "damage_type" : "割傷",
]),
([      "action": CYN"$N高高躍起，揮舞着手中的$w"CYN"一招「"BLU"一柱擎天"CYN"」猶如一條黑蟒般向$n當頭直落而下"NOR,
        "dodge": 10,
        "force": 310,
        "damage" : 250,
        "lvl" : 0,
        "damage_type": "割傷"
]),

([  "action": CYN"$N一聲暴喝「"YEL"橫掃千軍"CYN"」！將$w"CYN"由下往上一撩，雙手握住$w，轉身猛得橫掃打向$n的$l"NOR,
        "dodge": 15,
        "force": 350,
        "lvl" : 0,
        "damage": 260,
        "damage_type": "割傷"
]),
([      "action": CYN"$N忽然招數一變，使出「"HIC"靈蛇出洞"CYN"」，刀法顯得靈巧之極，手中$w"CYN"化作條條黑影纏向$n"NOR,
        "dodge": 50,
        "force": 400,
        "lvl" : 29,
        "damage": 330,
        "damage_type": "割傷"
]),
([  "action": CYN"$N以刀代劍，$w"CYN"中宮直進，夾着一陣狂風刺出，逼向$n的$l，正是招「"HIB"蛟蛇化龍"CYN"」"NOR,
        "dodge": 15,
        "force": 400,
        "lvl" : 59,
        "damage": 370,
        "damage_type": "刺傷"
]),
([  "action": CYN"$N一式「"HIW"一刀定海"CYN"」，當頭一$w"CYN"擊將下來，刀頭未至，一股風已將$n逼得難以喘氣"NOR,
        "dodge": 50,
        "force": 440,
        "lvl" : 79,
        "damage": 380,
        "damage_type": "割傷"
]),
([  "action": CYN"$N變招「"HIR"羣魔狂舞"CYN"」，$w"CYN"掃出一道道灰影從四面八方圍向$n，要將$n淹沒吞食"NOR,
        "dodge": 100,
        "force": 540,
        "lvl" : 89,
        "damage": 390,
        "damage_type": "割傷"
]),
});

string *parry_msg = ({
"$n反手一刺，$w象一條盤蛇，直撲$N的手腕.",
"$n向左側進一步，手中的$w順勢滑下，急削$N握的手指。\n",
"$n刀法一變，將手中的$w向上一撩,將$N的攻勢引偏出去.",
});
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("xiangfu-lun") > 100)
		return notify_fail("你有雪山開山祖師的功力?\n");
	if ((int)me->query_skill("longxiang-boruo", 1) < 150)
		return notify_fail("需要有第五層以上龍象般若功火候,才能修煉血海魔刀。\n");
          return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        object target, weapon; 
        int i, level, lvl;     
        
        target = offensive_target(me);    
        if (target->query_temp("weapon"))
             weapon = target->query_temp("weapon");
    
        lvl = random((int)me->query_skill("xuehai-modao",1));
      
        if (me->query_skill("xuehai-modao",1) > 100 &&
            me->query("neili") > 1000 && random(5) > 3 &&
            random(me->query("combat_exp")) > (int)target->query("combat_exp")/2){
            me->add("neili", -20);            
//            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
            return ([
                "action": HIC"不等招式用老，$N把手中$w順勢一晃，刀尖直劃而下，夾起一股陰風劈向$n！"NOR,
                "force" : 600,
                "dodge" : 200,
                "damage": 510,
                "damage_type":  "割傷"]);  
           } 
            

        level   = (int) me->query_skill("xuehai-modao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("你使用的武器不對。\n");
	if ((int)me->query_skill("xiangfu-lun") > 100)
		return notify_fail("你有雪山開山祖師的功力?\n");
	
	if ((int)me->query("jingli") < 60)
		return notify_fail("你的精力不夠練血海魔刀。\n");
	me->receive_damage("jingli", 50);
	return 1;
}

int double_attack(object me)
{	
   	if ( me->query_skill("xuehai-modao", 1) >= 80
     	&& me->query_skill_mapped("blade") == "xuehai-modao"
     	&& me->query("zhou/hubo"))
             	return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuehai-modao/" + action;
}
