//yinyang-shuangren.c  陰陽雙刃
//Jiuer /9/30/2001      絕情谷莊主 獨家功夫

inherit SKILL;

mapping *action = ({
([        "action" : "$N口中大喊一聲「看招」，一式「幽谷傳聲」，手中的$w劃了個圓圈直繞到$n的$l",
        "force" : 100,
        "dodge" : -5,
        "damage" : 15,
        "lvl" : 0,
        "skill_name" : "幽谷傳聲",
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w招勢越劃越大，一招「劃圈逼敵」，$w已繞到$n的$l，直逼下來",
        "force" : 120,
        "dodge" : -5,
        "damage" : 25,
        "lvl" : 5,
                "skill_name" : "劃圈逼敵",
        "damage_type" : "刺傷",
]),
([      "action" : "$N一招「漫天飛舞」，右手中的$w向前彎成弧形刺向$n的$l",
        "force" : 140,
        "dodge" : -10,
        "damage" : 55,
        "lvl" : 15,
                "skill_name" : "漫天飛舞",
        "damage_type" : "刺傷",
]),
([      "action" : "$N一式「蓮花吐蕊」，手中$w鬥地彎彎的繞著刺向$n的$l",
        "force" : 160,
        "dodge" : -10,
        "damage" : 85,
        "lvl" : 30,
                "skill_name" : "蓮花吐蕊",
        "damage_type" : "割傷",
]),
([      "action" : "$N$w胸前一橫，一招「僮子拜佛」，$w橫斫，斜刺$n",
        "force" : 180,
        "dodge" : -15,
        "damage" : 120,
        "lvl" : 45,
                "skill_name" : "僮子拜佛",
        "damage_type" : "割傷",
]),
([          "action" : "$N向後一閃，一招「陰陽倒亂」，右手$w左擊，立時劍法變刀法，$w隨即刺出",
            "force" : 200,
            "dodge" : -15,
            "damage" : 100,
            "lvl" : 60,
                "skill_name" : "陰陽倒亂",
            "damage_type" : "刺傷",
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        mapping a_action;
        int i, level;
        level = (int) me->query_skill("yinyang-shuangren",1);
        for( i = sizeof(action); i > 0; i-- )
                if( level > action[i-1]["lvl"] )
                {
                        a_action = action[NewRandom(i, 20, level/5)];
                        break;
                }
        a_action["dodge"] -= level / 10;
        a_action["parry"] = -level / 10;
        a_action["force"] += level / 10;
        a_action["damage"] += level / 10;
        return a_action;

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("jingli", me)<30 )
                return notify_fail("你的精力不夠練陰陽雙刃。\n");
        me->receive_damage("jingli", 20);
        return 1;
}
