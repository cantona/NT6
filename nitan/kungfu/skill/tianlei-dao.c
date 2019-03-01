inherit SKILL;

mapping *action = ({
([      "action" : "$N手持$w一刀劈下，迅即無比，勢不可當",
        "force"  : 160,
        "dodge"  : 20,
        "parry"  : 25,
        "lvl"    : 0,
        "damage" : 44,
        "damage_type" : "割傷",
]),
([      "action" : "$N刀鋒自下而上劃了個半弧，$w忽深忽吐，刺向$n的頸部",
        "force"  : 180,
        "dodge"  : 30,
        "parry"  : 40,
        "lvl"    : 25,
        "damage" : 58,
        "damage_type" : "割傷",
]),
([      "action" : "$N忽然將$w舞得天花亂墜，閃電般壓向$n",
        "force"  : 200,
        "dodge"  : 35,
        "parry"  : 50,
        "lvl"    : 50,
        "damage" : 56,
        "damage_type" : "割傷",
]),
([      "action" : "$N一橫$w，刀鋒像門板一樣向$n推去，封住$n所有的退路",
        "force"  : 230,
        "dodge"  : 45,
        "parry"  : 55,
        "lvl"    : 70,
        "damage" : 62,
        "damage_type" : "內傷",
]),
([      "action" : "$N轉身躍起，手舞$w，身與刀進合做一道電光射向$n",
        "force"  : 265,
        "dodge"  : 50,
        "parry"  : 75,
        "lvl"    : 90,
        "damage" : 70,
        "damage_type" : "割傷",
]),
([      "action" : "$N揮舞$w，亂砍亂殺，$w化作道道白光，上下翻飛罩向$n",
        "force"  : 270,
        "dodge"  : 55,
        "parry"  : 85,
        "lvl"    : 110,
        "damage" : 75,
        "damage_type" : "割傷",
]),
([      "action" : "$N將$w使得毫無章法，不守半點規矩，偏生快得出奇，$w挾風聲劈向$n的$l",
        "force"  : 290,
        "dodge"  : 52,
        "parry"  : 90,
        "lvl"    : 130,
        "damage" : 80,
        "damage_type" : "割傷",
]),
([      "action" : "$N大喝一聲，手中的$w就如長虹一般向$n直劈而下",
        "force"  : 310,
        "dodge"  : 61,
        "parry"  : 95,
        "lvl"    : 150,
        "damage" : 85,
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < 60)
                return notify_fail("你的基本刀法火候不夠，無法學習天雷絕刀。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("tianlei-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的天雷絕刀。\n");

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
        level   = (int) me->query_skill("tianlei-dao", 1);
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

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠，練不了天雷絕刀。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，練不了天雷絕刀。\n");

        me->receive_damage("qi", 45);
        addn("neili", -68, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianlei-dao/" + action;
}