
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N使出倚天屠龍掌中的一式"+HIY"『武林至尊』"NOR+"，一筆"
                   "一劃，暗含內勁，擊向$n的$l",
        "force" : 110,
        "dodge" : -5,
        "parry" : -7,
        "damage": 6,
        "damage_type" : "內傷",
        "lvl" : 0,
        "skill_name" : "武林至尊"
]),
([      "action" : "$N使出倚天屠龍掌中的一式"+HIY"『寶刀屠龍』"NOR+"，“龍"
                   "”字筆劃甚多，筆劃多的不覺其繁，擊向$n的$l",
        "force" : 148,
        "dodge" : -15,
        "parry" : -27,
        "damage": 15,
        "damage_type" : "內傷",
        "lvl" : 30,
        "skill_name" : "寶刀屠龍"
]),
([      "action" : "$N使出倚天屠龍掌中的一式"+HIY"『號令天下』"NOR+"，“下"
                   "”字筆劃甚少，筆劃少的不見其陋，擊向$n的$l",
        "force" : 195,
        "dodge" : -22,
        "parry" : -33,
        "damage": 19,
        "damage_type" : "內傷",
        "lvl" : 50,
        "skill_name" : "號令天下"
]),
([      "action" : "$N使出倚天屠龍掌中的一式"+HIY"『莫敢不從』"NOR+"，其縮"
                   "也凝重，似尺蠖之屈，其縱也險勁，如狡兔之脱，擊\n向$n的$l",
        "force" : 245,
        "dodge" : -32,
        "parry" : -41,
        "damage": 23,
        "damage_type" : "內傷",
        "lvl" : 80,
        "skill_name" : "莫敢不從"
]),
([      "action" : "$N使出倚天屠龍掌中的一式"+HIY"『倚天不出』"NOR+"，淋漓"
                   "酣暢，雄渾剛健，俊逸處如風飄，如雪舞，厚重處如\n虎蹲，"
                   "如象步，擊向$n的$l",
        "force" : 280,
        "dodge" : -37,
        "parry" : -46,
        "damage": 29,
        "damage_type" : "內傷",
        "lvl" : 120,
        "skill_name" : "倚天不出"
]),
([      "action" : "$N使出倚天屠龍掌中的一式"+HIY"『誰與爭鋒』"NOR+"，長嘯"
                   "一聲，右掌直劃下來，當真是星劍光芒，如矢應機，\n霆不暇"
                   "發，電不及飛，這一直乃是“鋒”字的最後一筆，直劈向$n的$l",
        "force" : 330,
        "dodge" : -45,
        "parry" : -57,
        "damage": 36,
        "damage_type" : "內傷",
        "lvl" : 160,
        "skill_name" : "誰與爭鋒"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "hujia-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練倚天屠龍掌必須空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，無法練倚天屠龍掌。\n");

        if( query("max_neili", me)<750 )
                return notify_fail("你的內力太弱，無法練倚天屠龍掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候不夠，無法練習倚天屠龍掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("yitian-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的倚天屠龍掌。\n");

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
        level = (int)me->query_skill("yitian-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練倚天屠龍掌。\n");

        me->receive_damage("qi", 55);
                addn("neili", -62, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yitian-zhang/" + action;
}
