inherit SKILL;

mapping *action = ({
([      "action" : "$N施展出一招「雷風指」，右手拇指直刺$n$l處的要穴所在",
        "force" : 30,
        "dodge" : 10,
        "damage": 5,
        "skill_name" : "雷風指",
        "lvl" : 0,
        "damage_type" : "刺傷"
]),
([      "action" : "$N使一招「山澤指」，左手輕輕一揮，右手刺向$n的檀中大穴",
        "force" : 60,
        "dodge" : 18,
        "damage": 10,
        "skill_name" : "山澤指",
        "lvl" : 20,
        "damage_type" : "刺傷"
]),
([      "action" : "$N雙掌翻飛，一招「乾坤指」，暗藏玄機，中指戳向$n的$l",
        "force" : 110,
        "dodge" : 16,
        "damage": 12,
        "skill_name" : "乾坤指",
        "lvl" : 40,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一聲大喝，一式「太陰指」，雙指齊出，攻向$n的胸口和$l",
        "force" : 150,
        "dodge" : 14,
        "damage": 15,
        "skill_name" : "太陰指",
        "lvl" : 60,
        "damage_type" : "刺傷"
]),
([      "action" : "$N連上數步，一招「少陽指」，左掌劈向$n，右手卻暗襲$n的$l",
        "force" : 170,
        "dodge" : 22,
        "damage": 25,
        "skill_name" : "少陽指",
        "lvl" : 80,
        "damage_type" : "刺傷"
]),
([      "action" : "$N雙手不住晃動，緩緩逼近$n，一招「少陰指」，籠罩了$n的$l",
        "force" : 190,
        "dodge" : 25,
        "damage": 20,
        "skill_name" : "少陰指",
        "lvl" : 90,
        "damage_type" : "刺傷"
]),
([      "action" : "$N一招「太陽指」，手指不住晃動，不離$n的$l方寸之間",
        "force" : 210,
        "dodge" : 30,
        "damage": 20,
        "skill_name" : "太陽指",
        "lvl" : 100,
        "damage_type" : "刺傷"
])
});

int valid_enable(string usage)
{
        return usage == "finger" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練乾天指法必須空手。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的內力不夠，無法學乾天指法。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，無法學乾天指法。\n");

        if ((int)me->query_skill("finger") < 20)
                return notify_fail("你的基本指法太淺，無法學乾天指法。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("qiantian-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的乾天指法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("qiantian-zhi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];

}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練習乾天指法。\n");

        me->receive_damage("qi", 35);
        addn("neili", -11, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qiantian-zhi/" + action;
}