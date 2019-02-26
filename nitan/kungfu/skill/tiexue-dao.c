inherit SKILL;

mapping *action = ({
([      "action": "$N一招「黑龍現身」，$w有如黑龍在$n的周身旋遊，勿快勿慢，變化若神",
        "force" : 40,
        "attack": 10,
        "dodge" : 10,
        "parry" : 5,
        "lvl"   : 0,
        "damage": 5,
        "skill_name"  : "黑龍現身",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「萬水千山」，左右腿一前一後，$w亂披風勢向$n的$l斬去",
        "force" : 90,
        "attack": 20,
        "dodge" : 10,
        "parry" : 8,
        "damage": 5,
        "lvl"   : 10,
        "skill_name"  : "萬水千山",
        "damage_type" : "割傷"
]),
([      "action":  "$N縱身躍落，一招「橫掃千里」，$w帶着疾風呼的一聲便向$n橫掃過去",
        "force" : 140,
        "attack": 25,
        "dodge" : 5,
        "parry" : 12,
        "damage": 15,
        "lvl"   : 30,
        "skill_name"  : "橫掃千里",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「左右開弓」，$w大開大闔，左右並進，左右兩刀向$n的兩肩砍落",
        "force" : 190,
        "attack": 30,
        "dodge" : 5,
        "parry" : 15,
        "damage": 25,
        "lvl"   : 50,
        "skill_name"  : "左右開弓",
        "damage_type" : "割傷"
]),
([      "action": "$N手中$w自上而下，一招「百丈飛瀑」刀光流瀉，如瀑布般砍向$n的頭部",
        "force" : 240,
        "attack": 35,
        "dodge" : 10,
        "parry" : 25,
        "damage": 30,
        "lvl"   : 80,
        "skill_name"  : "百丈飛瀑",
        "damage_type" : "割傷"
]),
([      "action": "$N使出一招「直摧萬馬」，上劈下撩，左擋右開，如千軍萬馬般罩向$n",
        "force" : 280,
        "attack": 40,
        "dodge" : 15,
        "parry" : 32,
        "damage": 35,
        "lvl"   : 100,
        "skill_name"  : "直摧萬馬",
        "damage_type" : "割傷"
]),
([      "action": "$N帶得刀風勁疾，一招「怪蟒翻身」，轉身連刀帶人往$n的$l的劈去",
        "force" : 290,
        "attack": 45,
        "dodge" : 5,
        "parry" : 35,
        "damage": 50,
        "lvl"   : 120,
        "skill_name"  : "怪蟒翻身",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「上步劈山」，$w直直的劈出，一片流光般的刀影向$n的全身罩去",
        "force" : 320,
        "attack": 50,
        "dodge" : 20,
        "parry" : 45,
        "damage": 60,
        "lvl"   : 150,
        "skill_name"  : "上步劈山",
        "damage_type" : "割傷"
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為不夠，難以修煉鐵血刀法。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，難以修煉鐵血刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("tiexue-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的鐵血刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("tiexue-dao", 1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練鐵血刀法。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練鐵血刀法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -58, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tiexue-dao/" + action;
}