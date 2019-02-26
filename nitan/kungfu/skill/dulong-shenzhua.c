//dulong-shenzhua for xuanming gu
//create by rcwiz 2003


inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N全身骨骼暴響，一式「天邪爪」，迅猛地抓向$n的$l",
        "force" : 100,
        "attack": 20,
        "dodge" : 5,
        "parry" : 15,
        "damage": 10,
        "lvl" : 0,
        "skills_name" : "天邪爪",
        "damage_type" : "內傷"
]),
([      "action": "$N單腿直立，雙臂平伸，一式「蛟龍爪」，雙爪一前一後攏向$n的$l",
        "force" : 120,
        "attack": 40,
        "dodge" : 10,
        "parry" : 22,
        "damage": 15,
        "lvl" : 30,
        "skills_name" : "蛟龍爪",
        "damage_type" : "內傷"
]),
([      "action": "$N一式「毒龍爪」，全身向斜裏平飛，右腿一繃，雙爪搭向$n的肩頭",
        "force" : 150,
        "attack": 50,
        "dodge" : 10,
        "parry" : 28,
        "damage": 20,
        "lvl" : 60,
        "skills_name" : "毒龍爪",
        "damage_type" : "內傷"
]),
([      "action": "$N雙爪翻騰而出，使一式「雙龍戲」，分別襲向$n左右腋空門",
        "force" : 180,
        "attack": 55,
        "dodge" : 15,
        "parry" : 35,
        "damage": 35,
        "lvl" : 80,
        "skills_name" : "雙龍戲",
        "damage_type" : "內傷"
]),
([      "action": "$N飛身而起，一式「飛龍爪」，自天而下，抓向$n的胸口",
        "force" : 220,
        "attack": 65,
        "dodge" : 20,
        "parry" : 38,
        "damage": 45,
        "lvl" : 100,
        "skills_name" : "飛龍爪",
        "damage_type" : "內傷"
]),
([      "action": "$N一式「地蛇爪」，上手襲向膻中大穴，下手反抓$n的襠部",
        "force" : 250,
        "attack": 60,
        "dodge" : 25,
        "parry" : 45,
        "damage": 60,
        "lvl" : 120,
        "skills_name" : "地蛇爪",
        "damage_type" : "內傷"
]),
([      "action": "$N左右手掌爪齊出，一式「劃長空」，雙爪劃空而過，抓向$n",
        "force" : 290,
        "attack": 75,
        "dodge" : 25,
        "parry" : 52,
        "damage": 85,
        "lvl" : 140,
        "skills_name" : "劃長空",
        "damage_type" : "內傷"
]),
([      "action": "$N騰空而起，一式「萬里神爪」，天空中頓時顯出一個巨靈爪影，罩向$n",
        "force" : 320,
        "attack": 80,
        "dodge" : 40,
        "parry" : 60,
        "damage": 80,
        "lvl" : 160,
        "skills_name" : "萬里神爪",
        "damage_type" : "內傷"
])
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練毒龍神爪功必須空手。\n");

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的內功火候不夠，無法學毒龍神爪功。\n");

        if( query("max_neili", me)<550 )
                return notify_fail("你的內力修為不足，無法學毒龍神爪功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("dulong-shenzhua", 1))
                return notify_fail("你的基本抓法火候水平有限，無法領會更高深的毒龍神爪功。\n");

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
        level = (int) me->query_skill("dulong-shenzhua",1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練鷹爪功。\n");

        me->receive_damage("qi", 60);
        addn("neili", -67, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dulong-shenzhua/" + action;
}