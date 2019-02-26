//longxing-jian.c
inherit SHAOLIN_SKILL;

mapping *action = ({
([        "action" : "$N使一招「蒼龍無形」手中$w一提，插向$n的$l",
        "damage" : 40,
        "parry": 40,
        "force": 150,
        "damage_type" : "挫傷",
        "skill_name" : "蒼龍無形"
]),
([        "action": "$N使出「飛龍擎天」，身形微弓,手中$w倏的向$n的$l戳去",
        "damage" : 50,
        "dodge": 80,
        "parry": 10,
        "force": 250,
        "damage_type": "刺傷",
        "skill_name" : "飛龍擎天"
]),
([        "action": "$N身子微曲，左足反踢，乘勢轉身，使一招「龍形萬裂」，右手$w已戳向$n$l",
        "damage" : 60,
        "dodge": 80,
        "parry": 20,
        "force": 250,
        "damage_type": "刺傷",
        "skill_name" : "龍形萬裂"
]),
([        "action" : "$N使一式「神龍初現」，身子往下一縮,$w掠過其咽喉,急奔$n急射而來",
        "damage" : 170,
        "force" : 450,
        "dodge" : 90,
        "lvl" : 100,
        "damage_type" : "刺傷",
        "skill_name" : "神龍初現"
]),
([        "action": "$N忽的在地上一個筋斗,使一招「金龍騰空」,從$n胯下鑽過,手中$w直擊$n",
        "damage" : 180,
        "dodge": 80,
        "parry": 70,
        "force": 350,
        "damage_type": "刺傷",
        "skill_name" : "金龍騰空"
]),
([        "action": "$N雙腿一縮，似欲跪拜，一招「龍飛鳳舞」左手抓向$n右腳足踝，右手$w直擊$n小腹",
        "dodge": 80,
        "damage" : 80,
        "parry": -10,
        "force": 400,
        "damage_type": "內傷",
        "skill_name" : "龍飛鳳舞"
]),
([        "action": "$N突然一個倒翻筋斗，一招「狄青降龍」，雙腿一分，跨在肩頭，雙掌直擊$n",
        "dodge": 90,
        "damage" : 90,
        "parry": 30,
        "force": 400,
        "damage_type": "內傷",
        "skill_name" : "狄青降龍"
]),
});

int valid_enable(string usage) { return usage=="sword"|| usage=="staff"|| usage=="parry"; }

int valid_learn(object me)
{
        if( query("str", me)<24 )
                return notify_fail("你先天臂力不足。\n");

        if( query("int", me)<26 )
                return notify_fail("你先天悟性不足。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為不夠，難以修煉龍形劍法。\n");

        if ((int)me->query_skill("force") < 280)
                return notify_fail("你的內功火候太淺，難以修煉龍形劍法。\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("你的劍法根基不足，難以修煉龍形劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("longxing-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的龍形劍法。\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練龍形劍法。\n");
        addn("qi", -30, me);
        addn("neili", -40, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"longxing-jian/" + action;
}