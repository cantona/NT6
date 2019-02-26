#include <ansi.h>
inherit SKILL;

int is_ultimate_skill() { return 1; }

mapping *action = ({
([      "action" : "$N右腳立定、左腳虛點，一式" HIR "『赤火手』" NOR "，左右手一高一低，擊向$n的$l",
        "force" : 150,
        "dodge" : 5,
        "damage": 5,
        "lvl" : 0,
        "skill_name" : "赤火手",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左腳虛踏，全身右轉，一招" HIW "『行風腿』" NOR "，右腿攜着旋風勁猛地踢向$n的$l",
        "force" : 200,
        "dodge" : 10,
        "damage": 20,
        "lvl" : 20,
        "skill_name" : "行風腿",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N身形飄忽不定，猛然一招" HIC "『水龍抓』" NOR "連環擊出，無數爪影一齊抓向$n的$l",
        "force" : 200,
        "dodge" : 10,
        "damage": 20,
        "lvl" : 40,
        "skill_name" : "水龍抓",
        "damage_type" : "抓傷"
]),
([      "action" : "$N雙手大開大闔，寬打高舉，使一招" HIY "『爍金掌』" NOR "，雙掌變做兩道金光罩向$n$l",
        "force" : 220,
        "dodge" : 15,
        "damage": 25,
        "lvl" : 60,
        "skill_name" : "爍金掌",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左掌圈花揚起，屈肘當胸，右手虎口朝上，一招" WHT "『土霸拳』" NOR "呼嘯着打向$n的$l",
        "force" : 260,
        "dodge" : 20,
        "damage": 35,
        "lvl" : 80,
        "skill_name" : "土霸拳",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N凝神聚氣，一招" YEL "『神木指』" NOR "，上身前探，“颼”地一指直刺$n的$l",
        "force" : 300,
        "dodge" : 25,
        "damage": 30,
        "lvl" : 100,
        "weapon" : "手指",
        "skill_name" : "神木指",
        "damage_type" : "刺傷"
]),
([      "action" : "$N雙拳劃弧，一記" RED "『五行總訣』" NOR "，招出如電，幻出漫天掌影，鋪天蓋地襲向$n全身",
        "force" : 320,
        "dodge" : 0,
        "damage": 40,
        "lvl" : 120,
        "skill_name" : "五行總訣",
        "damage_type" : "內傷"
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練滅神拳必須空手。\n");

        if ((int)me->query_skill("force") < 10)
                return notify_fail("你的內功火候不夠，無法學滅神拳。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練滅神拳。\n");

        if ((int)me->query_skill("unarmed", 1) < 10)
                return notify_fail("你的拳腳根基有限，無法體會滅神拳要詣。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("mieshenquan", 1))
                return notify_fail("你的拳腳根基火候不足，無法領會更高深的滅神拳。\n");

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
        level   = (int) me->query_skill("mieshenquan",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練滅神拳。\n");

        me->receive_damage("qi", 45);
        addn("neili", -56, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"mieshenquan/" + action;
}
