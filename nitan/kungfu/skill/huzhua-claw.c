// huzhua-gong.c 虎爪功

#include <combat.h>
#include <ansi.h>


inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N雙爪一張，斜身進步，腳踏中宮，一式「黑虎掏心」，疾如迅電，銳不可擋，向$n胸口猛拍過去",
        "force" : 100,
        "attack": 30,
        "dodge" : 25,
        "parry" : 5,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "黑虎掏心" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N身形驟起，雙臂箕張，向外一展，一招「猛虎下山」，雙爪翻飛，自上而下，罩向$n天靈",

        "force" : 120,
        "attack": 41,
        "dodge" : 30,
        "parry" : 5,
        "damage": 30,
        "lvl"   : 10,
        "skill_name" : "猛虎下山" ,
        "damage_type" : "內傷"
]),
([      "action": "$N讓過來勢，竟用一式「餓虎撲食」，合身撲上，如疾風般，欺到$n身前，罩向$n周身各處大穴",
        "force" : 120,
        "attack": 55,
        "dodge" : 45,
        "parry" : 30,
        "damage": 65,
        "lvl"   : 40,
        "skill_name" : "餓虎撲食" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N運足真氣，震聲長嘯，正是一式「虎嘯東山」，在$n一愕之間，已欺身進前，猛扳$n雙腕",
        "force" : 170,
        "attack": 64,
        "dodge" : 36,
        "parry" : 18,
        "damage": 70,
        "lvl"   : 60,
        "skill_name" : "虎嘯東山" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N微微一閃，一招「大蟲卷尾」，反圈到$n身後，疾如飄風，直朝$n肩後抓去",
        "force" : 180,
        "attack": 77,
        "dodge" : 58,
        "parry" : 5,
        "damage": 80,
        "lvl"   : 80,
        "skill_name" : "大蟲卷尾" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N如影隨形，跟蹤直上，正是一式「巨虎穿林」，身隨掌走，掌隨身轉，朝$n面門襲去",
        "force" : 220,
        "attack": 87,
        "dodge" : 42,
        "parry" : 22,
        "damage": 95,
        "lvl"   : 100,
        "skill_name" : "巨虎穿林" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N雙足一蹬，一躍而起，半空中使出一式「龍騰虎躍」，攜翻身搗海之勢，風雷夾擊之聲，向$n抓去",
        "force" : 250,
        "attack": 85,
        "dodge" : 40,
        "parry" : 29,
        "damage": 110,
        "lvl"   : 120,
        "skill_name" : "龍騰虎躍" ,
        "damage_type" : "抓傷"
]),
([      "action": "$N往後一閃，一式「病虎藏身」，讓過對方攻勢，右爪悄然探出，抓向$n腰眼",
        "force" : 300,
        "attack": 96,
        "dodge" : 75,
        "parry" : 45,
        "damage": 107,
        "lvl"   : 140,
        "skill_name" : "病虎藏身" ,
        "damage_type" : "抓傷"
])
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "qinna-shibada"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練虎爪功必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學虎爪功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，無法練虎爪功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("huzhua-claw"))
                return notify_fail("你的基本爪法火候水平有限，無法領會更高深的虎爪功。\n");

        if ((int)me->query_skill("jimie-zhua", 1) < (int)me->query_skill("huzhua-claw"))

                return notify_fail("你的寂滅爪火候水平有限，無法領會更高深的虎爪功。\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action); i > 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("huzhua-claw", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練虎爪功。\n");

        if ((int)me->query_skill("jiemie-zhua", 1) < (int)me->query_skill("huzhua-claw", 1))
                return notify_fail("你的寂滅爪火候水平有限，無法領會更高深的虎爪功。\n");

        me->receive_damage("qi", 60);
        addn("neili", -75, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huzhua-claw/" + action;
}
