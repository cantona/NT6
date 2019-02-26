// fuqi-daofa.c　夫妻刀法
// By Alf, Last Update 2001.05

//　女貌郎才珠萬斛　天教麗質為眷屬　碧簫聲裏雙鳴鳳　清風引佩下瑤台
//　刀光掩映孔雀屏　明月照粧成金屋　喜結絲羅在喬木　千金一刻慶良宵

inherit SKILL;

mapping *action = ({
([  "action" : "$N輕輕一笑，手中$w斜指，一招「女貌郎才珠萬斛」，反身撩向$n的$l",
    "force" : 120,
    "dodge" : -10,
    "lvl" : 0,
    "skill_name" : "女貌郎才珠萬斛",
    "damage_type" : "割傷"
]),
([  "action" : "$N面帶微笑，一招「天教麗質為眷屬」，$w一提一收，平刃揮向$n的頸部",
    "force" : 130,
    "dodge" : -10,
    "damage" : 5,
    "lvl" : 8,
    "skill_name" : "天教麗質為眷屬",
    "damage_type" : "割傷"
]),
([  "action" : "$N展顏微笑，$w刀鋒左右開闔，一招「碧簫聲裏雙鳴鳳」，攔腰斬向$n",
    "force" : 140,
    "dodge" : -5,
    "damage" : 15,
    "lvl" : 16,
    "skill_name" : "碧簫聲裏雙鳴鳳",
    "damage_type" : "割傷"
]),
([  "action" : "$N使一招「清風引佩下瑤台」，$w自上而下劃出一個大弧，筆直劈向$n",
    "force" : 160,
    "dodge" : 5,
    "damage" : 25,
    "lvl" : 24,
    "skill_name" : "清風引佩下瑤台",
    "damage_type" : "割傷"
]),
([  "action" : "$N手中$w一沉，一招「刀光掩映孔雀屏」，雙手持刃反切，砍向$n胸口",
    "force" : 180,
    "dodge" : 10,
    "damage" : 30,
    "lvl" : 33,
    "skill_name" : "刀光掩映孔雀屏",
    "damage_type" : "割傷"
]),
([  "action" : "$N一招「明月照粧成金屋」，手中$w上劈下撩，左擋右開，齊齊罩向$n",
    "force" : 210,
    "dodge" : 15,
    "damage" : 35,
    "lvl" : 42,
    "skill_name" : "明月照粧成金屋",
    "damage_type" : "割傷"
]),
([  "action" : "$N躍步落地，$w順勢送出，一招「喜結絲羅在喬木」，斜斜劈向$n的$l",
    "force" : 240,
    "dodge" : 5,
    "damage" : 50,
    "lvl" : 51,
    "skill_name" : "喜結絲羅在喬木",
    "damage_type" : "割傷"
]),
([  "action" : "$N輕笑聲中，「千金一刻慶良宵」使出，一片流光般的刀影湧向$n全身",
    "force" : 280,
    "dodge" : 20,
    "damage" : 60,
    "lvl" : 60,
    "skill_name" : "千金一刻慶良宵",
    "damage_type" : "割傷"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
    if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
    return 1;
}

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
    level   = (int) me->query_skill("fuqi-daofa",1);
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
    if( query("qi", me)<50 )
      return notify_fail("你的體力不夠練夫妻刀法。\n");
    me->receive_damage("qi", 25);
    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"fuqi-daofa/" + action;
}

