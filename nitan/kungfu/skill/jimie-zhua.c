// jimie-zhua.c 寂滅爪

inherit SKILL;

mapping *action = ({
([        "action" : "$N全身拔地而起，一式「眾生無我」，雙爪迅猛地抓向$n的$l",
        "force" : 100,
        "parry" : 5,
        "lvl" : 0,
        "skills_name" : "眾生無我",
        "damage_type" : "內傷"
]),
([        "action" : "$N大吼一聲，接連發出四抓，一式「苦樂隨緣」，雙爪抓向$n的頭部和胸部",
        "force" : 120,
        "parry" : 10,
        "lvl" : 10,
        "skills_name" : "苦樂隨緣",
        "damage_type" : "內傷"
]),
([        "action" : "$N一式「烈火騰雲」，雙掌化指，霎時間，一股咄咄逼人的內力逼向$n",
        "force" : 80,
        "parry" : 10,
        "lvl" : 20,
        "skills_name" : "烈火騰雲",
        "damage_type" : "內傷"
]),
([        "action" : "$N雙爪交錯，一式「普度眾生」，身行上揚，分別襲向$n左右腋空門",
        "force" : 220,
        "parry" : 15,
        "lvl" : 30,
        "skills_name" : "普度眾生",
        "damage_type" : "內傷"
]),
([        "action" : "$N一式「七星聚會」，右爪突出，左爪跟進，雙爪相疊，抓向$n的胸口",
        "force" : 180,
        "parry" : 20,
        "lvl" : 40,
        "skills_name" : "七星聚會",
        "damage_type" : "內傷"
]),
([        "action" : "$N原地不動，一式「以逸待勞」，只待$n襲來，雙爪襲向$n膻中大穴和襠部",
        "force" : 230,
        "parry" : 25,
        "lvl" : 50,
        "skills_name" : "以逸待勞",
        "damage_type" : "內傷"
]),
([        "action" : "$N的雙爪無數道勁氣破空而出，，一式「天衣無縫」，迅疾無比地擊向$n",
    "force" : 260,
        "parry" : 30,
        "lvl" : 55,
        "skills_name" : "天衣無縫",
        "damage_type" : "內傷"
]),
([        "action" : "$N騰空高飛數丈，一式「佛門善地」，一時間空中出現無數$N的身影罩向$n",
    "force" : 190,
        "parry" : 40,
        "lvl" : 60,
        "skills_name" : "佛門善地",
        "damage_type" : "內傷"
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }

int valid_combine(string combo) { return combo=="mohe-zhi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練寂滅爪必須空手。\n");
 if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練習寂滅爪。\n");
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
        level   = (int) me->query_skill("jimie-zhua",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("jingli", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練寂滅爪。\n");
        addn("jingli", -30, me);
        addn("neili", -10, me);
        return 1;
}
