// qishi-ji.c 聖騎士戟

inherit SKILL;

mapping *action = ({
([      "action": "$N雙目怒睜，手中$w猛然刺出，疾若閃電",
        "force" : 100,
        "attack": 35,
        "dodge" : 10,
        "parry" : 5,
        "lvl"   : 0,
        "damage": 85,
        "damage_type" : "刺傷"
]),
([      "action": "$N雙手所持的$w轉動不已，猛的疾刺向$n而去",
        "force" : 125,
        "attack": 42,
        "dodge" : 10,
        "parry" : 15,
        "damage": 100,
        "lvl"   : 10,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中的$w連續變換幾個方向，最後突然直刺$n的$l",
        "force" : 150,
        "attack": 45,
        "dodge" : 15,
        "parry" : 25,
        "damage": 100,
        "lvl"   : 30,
        "damage_type" : "刺傷"
]),
([      "action": "$N手中的$w猛然縮回，隨即刺向$n，去勢異常兇猛",
        "force" : 160,
        "attack": 50,
        "dodge" : 25,
        "parry" : 29,
        "damage": 110,
        "lvl"   : 50,
        "damage_type" : "刺傷"
]),
([      "action": "$N跨前一不，雙手將$w一壓，斜斜的挑向$n的$l",
        "force" : 180,
        "attack": 48,
        "dodge" : 20,
        "parry" : 31,
        "damage": 115,
        "lvl"   : 80,
        "damage_type" : "刺傷"
]),
([      "action": "$N大喝一聲，$w便如閃電般刺出，攜著一股旋風刺向$n",
        "force" : 240,
        "attack": 52,
        "dodge" : 25,
        "parry" : 37,
        "damage": 120,
        "lvl"   : 100,
        "damage_type" : "刺傷"
]),
([      "action": "$N跨前幾步，$w奮力前刺，義無反顧的攻向$n",
        "force" : 260,
        "attack": 55,
        "dodge" : 15,
        "parry" : 37,
        "damage": 125,
        "lvl"   : 120,
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; } 

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠。\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("qishi-ji", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的聖騎士戟。\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("qishi-ji", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的聖騎士戟。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("qishi-ji", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練聖騎士戟。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練聖騎士戟。\n");

        me->receive_damage("qi", 70);
        addn("neili", -40, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qishi-ji/" + action;
}