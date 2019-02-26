inherit SKILL;

mapping *action = ({
([      "action":"$N右手托住杖端，一招「攔鵲式」，左掌居中一擊，令其憑慣性倒向$n的肩頭",
        "force" : 65,
        "attack": 12,
        "dodge" : -10,
        "parry" : 5,
        "damage": 35,
        "lvl"   : 0,
        "damage_type":"挫傷"
]),
([      "action":"$N雙眼發紅，將手中$w舞成千百根相似，根根砸向$n全身各處要害",
        "force" : 89,
        "attack": 20,
        "dodge" : -10,
        "parry" : 8,
        "damage": 44,
        "lvl"   : 30,
        "damage_type":"挫傷"
]),
([      "action":"$N快步跨出，左手平託$w，右掌猛推杖端，頂向$n的胸口",
        "force" : 128,
        "attack": 35,
        "dodge" : -5,
        "parry" : 10,
        "damage": 52,
        "lvl"   : 60,
        "damage_type":"挫傷"
]),
([      "action":"$N大喝一聲，手中$w如飛龍般自掌中躍出，直向$n的胸口穿入",
        "force" : 150,
        "attack": 34,
        "dodge" : -5,
        "parry" : 12,
        "damage": 66,
        "lvl"   : 80,
        "damage_type":"挫傷"
]),
([      "action":"$N橫持$w，杖端化出無數個圓圈，凝滯沉重，把$n纏在其中",
        "force" : 200,
        "attack": 46,
        "dodge" : -15,
        "parry" : 18,
        "damage": 70,
        "lvl"   : 100,
        "damage_type":"挫傷"
]),
([      "action":"橫持$w，一招「蒼龍擺尾」，杖端化出無數個圓圈，凝滯沉重，把$n纏在其中",
        "force" : 240,
        "attack": 67,
        "dodge" : 5,
        "parry" : 22,
        "damage": 78,
        "lvl"   : 120,
        "damage_type":"挫傷"
]),
([      "action":"$N全身滾倒，$w盤地橫飛，突出一招「大蟒翻身」，杖影把$n裹了起來",
        "force" : 270,
        "attack": 89,
        "dodge" : -5,
        "parry" : 28,
        "damage": 100,
        "lvl"   : 140,
        "damage_type":"挫傷"
]),
([      "action":"$N單腿獨立，$w舞成千百根相似，根根砸向$n全身各處要害",
        "force" : 310,
        "attack": 102,
        "dodge" : -5,
        "parry" : 35,
        "damage": 120,
        "lvl"   : 160,
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage)
{
        return usage == "staff" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力修為不足，無法學習鹿頭杖法。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候太淺，無法學習鹿頭杖法。\n");

        if ((int)me->query_skill("staff", 1) < 20)
                return notify_fail("你的基本杖法太淺，無法學習鹿頭杖法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("lutou-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的鹿頭杖法。\n");

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
        level = (int)me->query_skill("lutou-zhang", 1);

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練鹿頭杖法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練鹿頭杖法。\n");

        me->receive_damage("qi", 75);
        addn("neili", -78, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lutou-zhang/" + action;
}