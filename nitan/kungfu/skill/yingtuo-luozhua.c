// 搜骨鷹爪功


inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N全身拔地而起，半空中一個筋鬥，一式「鷹飛式」，迅猛地抓向$n的$l",
        "force" : 200,
        "attack": 80,
        "dodge" : 20,
        "parry" : 30,
        "damage": 100,
        "lvl" : 0,
        "skills_name" : "鷹飛式",
        "damage_type" : "內傷"
]),
([      "action": "$N單腿直立，雙臂平伸，一式「雄鷹式」，雙爪一前一後攏向$n的$l",
        "force" : 220,
        "attack": 100,
        "dodge" : 50,
        "parry" : 50,
        "damage": 110,
        "lvl" : 100,
        "skills_name" : "雄鷹式",
        "damage_type" : "內傷"
]),
([      "action": "$N一式「鎖骨爪」，全身向斜裡平飛，右腿一繃，雙爪搭向$n的肩頭",
        "force" : 250,
        "attack": 150,
        "dodge" : 60,
        "parry" : 60,
        "damage": 180,
        "lvl" : 120,
        "skills_name" : "鎖骨爪",
        "damage_type" : "內傷"
]),
([      "action": "$N雙爪交錯上舉，使一式「奪魂勾」，一拔身，分別襲向$n左右腋空門",
        "force" : 280,
        "attack": 180,
        "dodge" : 15,
        "parry" : 35,
        "damage": 240,
        "lvl" : 140,
        "skills_name" : "奪魂勾",
        "damage_type" : "內傷"
]),
([      "action": "$N全身滾動上前，一式「神鷹式」，右爪突出，鬼魅般抓向$n的胸口",
        "force" : 400,
        "attack": 180,
        "dodge" : 60,
        "parry" : 80,
        "damage": 260,
        "lvl" : 150,
        "skills_name" : "神鷹式",
        "damage_type" : "內傷"
]),
([      "action": "$N伏地滑行，一式「血鷹爪」，上手襲向膻中大穴，下手反抓$n的襠部",
        "force" : 490,
        "attack": 160,
        "dodge" : 60,
        "parry" : 60,
        "damage": 260,
        "lvl" : 180,
        "skills_name" : "血鷹爪",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練因陀羅爪功必須空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候不夠，無法學因陀羅爪功。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的內力太弱，無法練因陀羅爪功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("yingtuo-luozhua", 1))
                return notify_fail("你的基本抓法火候水平有限，無法領會更高深的因陀羅爪功。\n");

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
        level = (int) me->query_skill("yingtuo-luozhua",1);

        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠因陀羅爪功。\n");

        me->receive_damage("qi", 60);
        addn("neili", -67, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yingtuo-luozhua/" + action;
}
