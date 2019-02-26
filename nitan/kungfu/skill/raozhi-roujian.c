// raozhi-roujian.c 武當繞指柔劍

inherit SKILL;

mapping *action = ({
([      "action" : "$N使出一招「天外流星」，手中$w如一條銀蛇般刺向$n的$l",
        "force"  : 120,
        "dodge"  :-20,
        "parry"  :-14,
        "damage" : 25,
        "lvl"    : 0,
        "damage_type": "刺傷"
]),
([      "action" : "$N一式「落花滿天」，手中$w化做滿天劍影直刺向$n的$l",
        "force"  : 120,
        "dodge"  :-20,
        "parry"  :-15,
        "damage" : 20,
        "lvl"    : 10,
        "damage_type": "刺傷"
]),
([      "action" : "$N使出一招「窗含柔月」，手中$w揮舞，舞出數個劍花圈向$n的$l",
        "force"  : 140,
        "dodge"  :-15,
        "parry"  :-16,
        "damage" : 25,
        "lvl"    : 20,
        "damage_type": "刺傷"
]),
([      "action" : "$N輕輕一躍，一招「乘風歸去」，卻在轉身之際對準$n$l斜斜揮出一劍",
        "force"  : 150,
        "dodge"  :-15,
        "parry"  :-18,
        "damage" : 35,
        "lvl"    : 30,
        "damage_type": "刺傷"
]),
([      "action" : "$N神態悠閒，手中$w憑空一指，一招「白雲千載」輕妙地划向$n的$l",
        "force"  : 130,
        "dodge"  :-25,
        "parry"  :-21,
        "damage" : 25,
        "lvl"    : 40,
        "damage_type": "刺傷"
]),
([      "action" : "$N使出一招「星河影動」，劍光閃爍不定，若有若無地刺向$n$l",
        "force"  : 120,
        "dodge"  :-25,
        "parry"  :-22,
        "damage" : 25,
        "lvl"    : 50,
        "damage_type": "刺傷"
]),
([      "action" : "$N手中$w向外一分，一招「柳暗花明」反手對準$n$l一劍刺去",
        "force"  : 110,
        "dodge"  :-15,
        "parry"  :-35,
        "damage" : 38,
        "lvl"    : 60,
        "damage_type": "刺傷"
]),
([      "action" : "$N身形轉個不停，突然一招「一點靈犀」使出，手中$w劃出一道銀弧，徑刺$n$l",
        "force"  : 150,
        "dodge"  :-35,
        "parry"  :-45,
        "damage" : 43,
        "lvl"    : 70,
        "damage_type": "刺傷"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("raozhi-roujian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的繞指柔劍。\n");

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
        level = (int) me->query_skill("raozhi-roujian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<40 )
                return notify_fail("你的體力不夠練繞指柔劍。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練繞指柔劍。\n");

        me->receive_damage("qi", 35);
        addn("neili", -30, me);

        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"raozhi-roujian/" + action;
}