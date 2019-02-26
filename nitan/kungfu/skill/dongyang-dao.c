// dongyang-dao 東洋刀法

inherit SKILL;

mapping *action = ({
([      "action": "$N大喝一聲，手中$w直劈下來，帶起一陣風",
        "force" : 40,
        "attack": 30,
        "dodge" : 32,
        "parry" : 5,
        "lvl"   : 0,
        "damage": 95,
        "damage_type" : "割傷"
]),
([      "action": "$N突然橫切，划向$n的$l",
        "force" : 80,
        "attack": 35,
        "dodge" : 33,
        "parry" : 8,
        "damage": 110,
        "lvl"   : 10,
        "damage_type" : "割傷"
]),
([      "action": "$N手中的$w連續變換幾個方向，最後突然直刺$n的$l",
        "force" : 110,
        "attack": 40,
        "dodge" : 37,
        "parry" : 12,
        "damage": 110,
        "lvl"   : 30,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中的$w猛然旋轉，舞起一團刀影，直逼$n",
        "force" : 130,
        "attack": 45,
        "dodge" : 45,
        "parry" : 15,
        "damage": 125,
        "lvl"   : 50,
        "damage_type" : "割傷"
]),
([      "action": "$N手中$w一沉，雙手持刃攔腰反切，砍向$n的$l",
        "force" : 140,
        "attack": 40,
        "dodge" : 47,
        "parry" : 18,
        "damage": 125,
        "lvl"   : 80,
        "damage_type" : "割傷"
]),
([      "action": "$N長嘯一聲，手中的$w不住的晃動，宛若三把刀劈向$n",
        "force" : 180,
        "attack": 45,
        "dodge" : 55,
        "parry" : 25,
        "damage": 135,
        "lvl"   : 100,
        "damage_type" : "割傷"
]),
([      "action": "$N一轉身，把背後全被賣給$n，突然雙手一轉，$w從$N腰側刺了出來",
        "force" : 200,
        "attack": 45,
        "dodge" : 55,
        "parry" : 31,
        "damage": 140,
        "lvl"   : 120,
        "damage_type" : "刺傷"
]),
([      "action": "$N猛然前襲，手中$w化作一道刀芒閃電般的刺向$n",
        "force" : 210,
        "attack": 50,
        "dodge" : 60,
        "parry" : 33,
        "damage": 160,
        "lvl"   : 150,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("dongyang-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的東洋刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("dongyang-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的東洋刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("dongyang-dao",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<75 )
                return notify_fail("你的體力不夠練東洋刀法。\n");

        if( query("neili", me)<55 )
                return notify_fail("你的內力不夠練東洋刀法。\n");

        me->receive_damage("qi", 60);
        addn("neili", -42, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dongyang-dao/" + action;
}