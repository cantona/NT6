inherit SKILL;

mapping *action = ({
([      "action":"$N使一式「虛式分金」，手中$w由左至右橫掃向向$n的$l",
        "force" : 126,
        "parry" : 3,
        "dodge" : 5,
        "damage": 21,
        "lvl"   : 0,
        "skill_name" : "虛式分金",
        "damage_type":  "割傷"
]),
([      "action":"$N踏上一步，「荊軻刺秦」，手中$w盤旋飛舞出一道金光劈向$n的$l",
        "force" : 149,
        "parry" : 13,
        "dodge" : 10,
        "damage": 25,
        "lvl"   : 30,
        "skill_name" : "荊軻刺秦",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w一抖，一招「九品蓮台」，斜斜反腕撩出，攻向$n的$l",
        "force" : 167,
        "parry" : 12,
        "dodge" : 15,
        "damage": 31,
        "lvl"   : 50,
        "skill_name" : "九品蓮台",
        "damage_type":  "割傷"
]),
([      "action":"$N手中$w連繞數個大圈，一式「剛柔並濟」，一道光飛向$n的$l",
        "force" : 187,
        "parry" : 23,
        "dodge" : 19,
        "damage": 45,
        "lvl"   : 70,
        "skill_name" : "剛柔並濟",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w斜指蒼天，一式「日月無華」，對準$n的$l斜斜擊出",
        "force" : 197,
        "parry" : 31,
        "dodge" : 27,
        "damage": 56,
        "lvl"   : 90,
        "skill_name" : "日月無華",
        "damage_type":  "刺傷"
]),
([      "action":"$N一式「天罡匯聚」，$w飛斬盤旋，如疾電般射向$n的胸口",
        "force" : 218,
        "parry" : 49,
        "dodge" : 35,
        "damage": 63,
        "lvl"   : 110,
        "skill_name" : "天罡匯聚",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w一沉，一式「行影相隨」，無聲無息地滑向$n的$l",
        "force" : 239,
        "parry" : 52,
        "dodge" : 45,
        "damage": 72,
        "lvl"   : 130,
        "skill_name" : "行影相隨",
        "damage_type":  "刺傷"
]),
([      "action":"$N手中$w斜指蒼天，劍芒吞吐，一式「歲月無聲」，對準$n的$l斜斜擊出",
        "force" : 287,
        "parry" : 55,
        "dodge" : 51,
        "damage": 88,
        "lvl"   : 150,
        "skill_name" : "歲月無聲",
        "damage_type":  "刺傷"
]),
([      "action":"$N左指凌空虛點，右手$w逼出丈許雪亮光芒，一式「流水無情」刺向$n的嚥喉",
        "force" : 342,
        "parry" : 63,
        "dodge" : 55,
        "damage": 105,
        "lvl"   : 170,
        "skill_name" : "流水無情",
        "damage_type":  "刺傷"
]),
([      "action":"$N合掌跌坐，一式「刀光劍影」，$w自懷中躍出，如疾電般射向$n的胸口",
        "force" : 381,
        "parry" : 76,
        "dodge" : 65,
        "damage": 122,
        "lvl"   : 190,
        "skill_name" : "刀光劍影",
        "damage_type":  "刺傷"
])
});

int valid_enable(string usage)
{ 
       return usage == "sword" || usage == "parry" || usage == "blade";
}

int valid_learn(object me)
{
        object weapon;
        int lv = me->query_skill("yinyang-ren", 1);

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade") )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，不能學習陰陽刃法。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你的內力修為不夠，不能學習陰陽刃法。\n");

        if (me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，不能學習陰陽刃法。\n");

        if (me->query_skill("blade", 1) < 100)
                return notify_fail("你的基本刀法火候不夠，不能學習陰陽刃法。\n");

        // 180 級之前受 sword 及 blade 兩種基本技能限制
        if (lv <= 180 && (int)me->query_skill("sword", 1) < lv)
                return notify_fail("你的基本劍法水平有限，無法領會更高深的陰陽刃法。\n");

        if (lv <= 180 && (int)me->query_skill("blade", 1) < lv)
                return notify_fail("你的基本刀法水平有限，無法領會更高深的陰陽刃法。\n");

        if ((int)me->query_skill("sword", 1) < lv
           && (int)me->query_skill("blade", 1) < lv)
                return notify_fail("你的基本刀劍水平有限，無法領會更高深的陰陽刃法。\n");

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
        level = (int) me->query_skill("yinyang-ren", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || (query("skill_type", weapon) != "sword"
            && query("skill_type", weapon) != "blade") )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力不夠練陰陽刃法。\n");

        if( query("neili", me)<130 )
                return notify_fail("你的內力不夠練陰陽刃法。\n");

        me->receive_damage("qi", 80);
        addn("neili", -100, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yinyang-ren/" + action;
}