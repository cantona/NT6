// qilian-zhi.c 祁連五絕指

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N左手輕輕撥動，五指徐徐彈出撥，一式「絕經指」，拂向$n全身經脈",
        "force" : 90,
        "dodge" : 5,
        "damage": 15,
        "lvl"   : 0,
        "damage_type" : "點穴",
        "skill_name" : "絕經指"
]),
([      "action": "$N俯身掠向$n，一式「絕脈指」，化掌成指，洶湧襲向$n，正是其要脈所在",
        "force" : 140,
        "attack": 5,
        "parry" : 5,
        "dodge" : 5,
        "damage": 20,
        "lvl" : 40,
        "damage_type" : "點穴",
        "skill_name" : "絕脈指"
]),
([      "action": "$N雙手扭曲如靈蛇，一式「絕目指」施出，左右並用，陡然插向$n的雙目",
        "force" : 155,
        "attack": 10,
        "parry" : 7,
        "dodge" : 5,
        "damage": 30,
        "lvl"   : 40,
        "damage_type" : "點穴",
        "skill_name" : "絕目指"
]),
([      "action": "$N一式「絕髓指」，左手抽回，右手前探，戟指點向$n的腦後脊髓",    
        "force" : 170,
        "attack": 20,
        "parry" : 11,
        "dodge" : 9,
        "damage": 40,
        "lvl"   : 60,
        "damage_type" : "點穴",
        "skill_name" : "絕髓指"
]),
([      "action": "$N使一式「絕心指」，身影變幻不定地掠至$n身後，猛地拍向$n左前胸",
        "force" : 190,
        "attack": 30,
        "parry" : 12,
        "dodge" : 10,
        "damage": 50,
        "lvl"   : 80,
        "damage_type" : "點穴",
        "skill_name" : "絕心指"
]),
([      "action": "$N兩臂大開大闔，一式「天地絕滅」，勁力透徹，頓時激出數道勁氣逼向$n",
        "force" : 220,
        "attack": 40,
        "parry" : 21,
        "dodge" : 15,
        "damage": 55,
        "lvl"   : 100,
        "damage_type" : "點穴",
        "skill_name" : "天地絕滅"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練祁連五絕指必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學祁連五絕指。\n");

        if ((int)me->query_skill("finger", 1) < 40)
                return notify_fail("你的基本指法火候不夠，無法學祁連五絕指。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，無法練祁連五絕指。\n");

        if (me->query_skill("finger", 1) < me->query_skill("qilian-zhi", 1))
                return notify_fail("你的基本指法太差，無法領會更高深的祁連五絕指。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("qilian-zhi", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了，無法練祁連五絕指。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠，無法練祁連五絕指。\n");

        me->receive_damage("qi", 55);
        addn("neili", -51, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qilian-zhi/" + action;
}