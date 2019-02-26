#include <ansi.h>

inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N面帶微笑，一招"HIR"「烈火燒身」"NOR"，舉$w對着$n連砍了八八六十四刀，刀氣縱橫，迅雷不可擋",
        "lvl"    : 0,
        "skill_name"  : "烈火燒身",
]),
([        "action" : "$N運起內功一招"GRN"「點木生火」"NOR"，$w上帶着無比勁氣，劃了一個大弧，從上而下劈向$n的$l",
        "lvl"    : 20,
        "skill_name"  : "點木生火",
]),
([        "action" : "$N手臂一沉，一招"HIM"「張弓望月」"NOR"，雙手持$w劃出一道雪亮刀光，接着攔腰反切，砍向$n的$l",
        "lvl"    : 40,
        "skill_name"  : "張弓望月",
]),
([        "action" : "$N揮舞$w上劈下撩，左擋右開，使出一招"RED"「烈火騰雲」"NOR"，捲起陣陣刀風，齊齊罩向$n",
        "lvl"    : 60,
        "skill_name"  : "烈火騰雲",
]),
([        "action" : "$N一招"MAG"「火中取栗」"NOR"，左腳躍步落地，手中$w單刀往前，挾着炙熱的風聲劈向$n的$l",
        "lvl"    : 80,
        "skill_name"  : "火中取栗",
]),
([        "action" : "$N騰空而起，半空中一招"HIW"「玉石俱焚」"NOR"，手中$w揮出滿天流光般的刀影，向$n的全身捲去",
        "lvl"    : 100,
        "skill_name"  : "玉石俱焚",
]),
});

int valid_enable(string usage) { return  (usage =="parry")|| (usage =="blade"); }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你必須先找一把刀才能練燃木刀法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不足，沒有辦法練燃木刀法，多練些內力再來吧。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺，沒有辦法練燃木刀法。\n");

        if ((int)me->query_skill("blade", 1) < 100)
                return notify_fail("你的基本刀法火候太淺，沒有辦法練燃木刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("ranmu-daofa", 1))
                return notify_fail("你的基本刀法水平還不夠，無法領會更高深的燃木刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 30;
        int d_e2 = 10;
        int p_e1 = -20;
        int p_e2 = -40;
        int f_e1 = 100;
        int f_e2 = 250;
        int m_e1 = 190;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("ranmu-daofa", 1);

        if (random(me->query_skill("ranmu-daofa", 1)) > 120 &&
             me->query_skill("force") > 100 &&
             query("neili", me)>1000 &&
             query_temp("weapon", me) &&
             random(10) > 6)
        {
                addn("neili", -100, me);
                return ([
                "action": HIR "$N" HIR "忽然高宣一聲佛號，身體急速"
                          "旋轉，遍體通紅，袈裟鼓起。剎那間手中" +
                          query("name", query_temp("weapon", me) )
                          + HIR "一道火光閃過，迸\n出一股灼熱的氣流，"
                          "襲向$n" HIR "！" NOR,
                "dodge" : -110,
                "attack": 340,
                "force" : 302,
                "damage": 289,
                "parry" : -70,
                "damage_type": "割傷"]);
        }

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "擦傷",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練燃木刀法。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的內力不夠練燃木刀法。\n");

        me->receive_damage("qi", 75);
        addn("neili", -85, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;
        if (random(damage) > victim->query_str()/10)
        {
                result = ([ "damage": damage ]);
                result += (["msg" : HIW "$N手中的大刀頓時化作一團火焰，激盪的炙流竄入$n體內，$n" BLINK +
                                    HIR "鮮血" NOR + HIW "狂噴而出！\n" NOR ]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"ranmu-daofa/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n燃木刀法："NOR"\n");
        write(@HELP

    燃木刀法是少林頂級刀法。
    韋陀杵、日月鞭法和燃木刀法並列為南少林三絕技。
    三絕技不能同時修習。

        學習要求：
                易筋經150級
                修羅刀150級
                內力修為1500
HELP
        );
        return 1;
}
