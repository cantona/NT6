//tianmo-shou.c 天魔手
//By haiyan

inherit SKILL;

mapping *action = ({
([      "action":"$N一招「覆雨翻雲」，左手抓向$n的丹田，就在$n回身自防的一瞬間，右手卻已掐上了$n的$l。",
        "force" :95,
        "attack":15,
        "parry" :10,
        "dodge" :30,
        "damage":20,
        "lvl"   :0,
        "skill_name" :"覆雨翻雲",
        "damage_type":"瘀傷"
]),
([      "action":"$N雙手一錯，右手向外橫推而出，一招「風起雲湧」帶着一股勁風拍向$n的$l。",
        "force" :120,
        "attack":28,
        "parry" :40,
        "dodge" :60,
        "damage":35,
        "lvl"   :50,
        "skill_name" :"風起雲湧",
        "damage_type":"瘀傷"
]),
([      "action":"忽聽$N一聲怒吼，右手高高舉起，一式「高山流水」，砍向$n的$l。",
        "force" :160,
        "attack":40,
        "parry" :70,
        "dodge" :90,
        "damage":53,
        "lvl"   :80,
        "skill_name" :"高山流水",
        "damage_type":"砍傷"
]),
([      "action":"$N身子微斜，隨即跨出一步，左手忽掌忽爪使出「兩處茫茫」，拍向$n的$l。",
        "force" :190,
        "attack":56,
        "parry" :100,
        "dodge" :120,
        "damage":70,
        "lvl"   :130,
        "skill_name" :"兩處茫茫",
        "damage_type":"瘀傷"
]),
([      "action":"$N使出「出沒風波里」，雙手滑溜異常對準$n的$l抓去。",
        "force" :220,
        "attack":74,
        "parry" :130,
        "dodge" :150,
        "damage":90,
        "lvl"   :160,
        "skill_name" :"出沒風波里",
        "damage_type":"抓傷"
]),
([      "action":"$N右手在$n$l劃過，隨後一招「捕風捉影」左手又向同一方位抓去。",
        "force" :260,
        "attack":100,
        "parry" :180,
        "dodge" :200,
        "damage":150,
        "lvl"   :200,
        "skill_name" :"捕風捉影",
        "damage_type":"抓傷"
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練天魔手必須空手。\n");

        if ((int)me->query_skill("riyue-xinfa", 1) < 100)
                return notify_fail("你的內功心法火候太淺，不能學天魔手。\n");

        if ((int)me->query_skill("hand", 1) < 100)
                return notify_fail("你的基本手法火候不夠。\n");

        if( query("max_neili", me)<350 )
                return notify_fail("你的內力太低，無法學天魔手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("tianmo-shou", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的天魔手。\n");

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
        level = (int) me->query_skill("tianmo-shou", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練天魔手必須空手。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力不夠練天魔手。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的內力不夠練天魔手。\n");

        me->receive_damage("qi", 85);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianmo-shou/" + action;
}
