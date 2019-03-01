//kuangfeng-blade 狂風刀法
// Made by deaner
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$N手中$w輕揮，一招"+HIW"「風平浪靜」"NOR+"，看似平緩實則迅速地向
$n的$l撩去",
    "force" : 150,
    "dodge" : 10,
    "lvl" : 0,
    "skill_name" : "風平浪靜",
    "damage_type" : "割傷"
]),
([  "action" : "$N一招"+HIW"「風起雲湧」"NOR+"，右腳一點，$w寒光閃閃，快速湧$n的
$l",
    "force" : 170,
    "dodge" : 35,
    "damage" : 20,
    "lvl" : 3,
    "skill_name" : "風起雲湧",
    "damage_type" : "割傷"
]),
([  "action" : "$N一招"+HIY"「風卷殘雲」"NOR+"，手臂一掄，刀鋒一卷，自上而下斬向
$n",
    "force" : 190,
    "dodge" : 25,
    "damage" : 25,
    "lvl" : 5,
    "skill_name" : "風卷殘雲",
    "damage_type" : "割傷"
]),
([  "action" : "$N一招"+HIC"「風流雲散」"NOR+"，側身而退，$w卻在胸前劃出一道圓弧
，橫劈$n的$l",
    "force" : 210,
    "dodge" : 15,
    "damage" : 35,
    "lvl" : 10,
    "skill_name" : "風流雲散",
    "damage_type" : "割傷"
]),
([  "action" : "$N側身滑步而上，一招"+HIW"「風聲鶴唳」"NOR+"，欺至$n身前，$w猛砍
$n的$l",
    "force" : 230,
    "dodge" : 20,
    "damage" : 50,
    "lvl" : 20,
    "skill_name" : "風聲鶴唳",
    "damage_type" : "割傷"
]),
([  "action" : "$N快速揮舞$w，使出一招"+RED"「風中殘燭」"NOR+"，幻起一片刀花罩向
$n的$l",
    "force" : 260,
    "dodge" : 15,
    "damage" : 65,
    "lvl" : 30,
    "skill_name" : "風中殘燭",
    "damage_type" : "割傷"
]),
([  "action" : "$N一招"+HIC"「風刀霜劍」"NOR+"，只見漫天刀光閃爍，重重刀影向$n的
全身湧去",
    "force" : 290,
    "dodge" : 20,
    "damage" : 85,
    "lvl" : 40,
    "skill_name" : "風刀霜劍",
    "damage_type" : "割傷"
]),
([  "action" : "$N使一招"+HIW"「風馳電掣」"NOR+"，$w舞出陣陣光影向$n的$l湧去",  
    "force" : 320,
    "dodge" : 40,
    "damage" : 105,
    "lvl" : 60,
    "skill_name" : "風馳電掣",
    "damage_type" : "割傷"
]),
([  "action" : "$N一招"+HIB"「風雨飄搖」"NOR+"，$w刀光閃爍不定，似幻似真地逼$n的
$l",
    "force" : 350,
    "dodge" : 10,
    "damage" : 125,
    "lvl" : 80,
    "skill_name" : "風雨飄搖",
    "damage_type" : "割傷"
]),
([  "action" : "$N挪步小退，一招"+HIC"「風花雪月」"NOR+"，手中$w輕描淡寫地揮出一
刀，隨即又“唰唰”連
劈出兩刀，後發先至，洒向$n的$l",
    "force" : 400,
    "dodge" : 20,
    "damage" : 150,
    "lvl" : 100,
    "skill_name" : "風花雪月",
    "damage_type" : "割傷"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
   if(level >= action[i]["lvl"])
      return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("kuang-blade",1);
    for(i = sizeof(action); i > 0; i--)
   if(level > action[i-1]["lvl"])
      return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if( !objectp(weapon=query_temp("weapon", me) )
     || query("skill_type", weapon) != "blade" )
    return notify_fail("你使用的武器不對。\n");
    if( query("qi", me)<100 )
    return notify_fail("你的體力不夠練狂風刀法。\n");
    me->receive_damage("qi", 80);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"kuang-blade/" + action;
}