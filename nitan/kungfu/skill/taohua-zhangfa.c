// taohua-zhangfa.c 桃花掌法
inherit SKILL;

mapping *action = ({
([      "action" : "$N右手五指緩緩一收，一式「春風拂面」，五指忽然遙遙拂向$n，$n只覺得五"
                   "股疾風襲向自己五處大穴",
        "force"  : 40,
        "dodge"  : 20,
        "damage_type" : "瘀傷",
        "lvl" : 0,
        "skill_name" : "春風拂面"
]),
([      "action" : "$N突然縱身躍入半空，一式「落花無情」，雙掌向下，疾撲$n的頭頂",
        "force"  : 60,
        "dodge"  : 25,
        "damage_type" : "內傷",
        "lvl" : 10,
        "skill_name" : "落花無情"
]),
([      "action" : "$N伸出右手並攏食指中指，捻個劍決，一式「尋花探柳」，直指$n的中盤",
        "force"  : 80,
        "dodge"  : 20,
        "damage_type" : "內傷",
        "lvl" : 20,
        "skill_name" : "尋花探柳"
]),
([      "action" : "$N突然抽身而退，接著一式「隨風而逝」，平身飛起，雙掌向$n的$l"
                   "連拍數掌",
        "force"  : 100,
        "dodge"  : 35,
        "damage_type" : "內傷",
        "lvl" : 30,
        "skill_name" : "隨風而逝"
]),
([      "action" : "$N使一式「狂風卷葉」，全身突然飛速旋轉，雙掌忽前忽後，猛地拍向$n"
                   "的胸口",
        "force"  : 110,
        "dodge"  : 30,
        "damage_type" : "內傷",
        "lvl" : 40,
        "skill_name" : "狂風卷葉"
]),
([      "action" : "$N前後一揉，一式「寸草不生」，雙掌推出一股陰柔之力襲向$n的$1 ",
        "force"  : 130,
        "dodge"  : 35,
        "damage_type" : "內傷",
        "lvl" : 50,
        "skill_name" : "寸草不生"
]),
([      "action" : "$N雙手食指和中指迅速和在一起，一式「摧花斷葉」，一股強烈的氣"
                   "流湧向$n的全身",
        "force"  : 150,
        "parry"  : 25,
        "dodge"  : 20,
        "damage_type" : "內傷",
        "lvl" : 60,
        "skill_name" : "摧花斷葉"
]),
([      "action" : "$N使一式「天女散花」，雙掌舞出無數圈勁氣，一環環向$n的$l斫去 ",
        "force" : 170,
        "parry" : 25,
        "dodge" : 35,
        "damage_type" : "劈傷",
        "lvl" : 70,
        "skill_name" : "天女散花"
]),
([      "action" : "$N兩掌在胸前合什，施展出「推波助瀾」，雙掌驟然分開，祭出兩團光"
                   "球飛速攻向$n",
        "force" : 190,
        "parry" : 25,
        "dodge" : 30,
        "damage_type" : "內傷",
        "lvl" : 80,
        "skill_name" : "推波助瀾"
]),
([      "action" : "$N一式「落英繽紛」，雙掌在胸前疾轉數圈，不急不緩地推向$n。$n只"
                   "見漫天掌花逼向自己，早已為此招所折服，根本不知躲避。",
        "force" : 210,
        "parry" : 30,
        "dodge" : 35,
        "damage_type" : "內傷",
        "lvl" : 90,
        "skill_name" : "落英繽紛"
])
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; }  

int valid_learn(object me)
{
    if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("練桃花掌法必須空手。\n");

    if( query("max_neili", me)<100 )
        return notify_fail("你的內力太弱，無法練桃花掌法。\n");

    if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("taohua-zhangfa", 1))
        return notify_fail("你的基本掌法水平有限，無法領會更高深的桃花掌法。\n");

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
    level = (int)me->query_skill("taohua-zhangfa", 1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if( query("qi", me)<40 )
        return notify_fail("你的體力太低了。\n");

    if( query("neili", me)<20 )
        return notify_fail("你的內力不夠練桃花掌法。\n");

    me->receive_damage("qi", 30);
    addn("neili", -5, me);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"taohua-zhangfa/" + action;
}