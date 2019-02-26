// hujia-daofa.c 胡家刀法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N手中$w橫推，一招"HIM"「推波助瀾」"NOR"，由上至下向$nl砍去",
        "lvl"    : 0,
        "skill_name" : "推波助瀾",
]),
([        "action" : "$N一招"HIC"「沙鷗掠波」"NOR"，刀鋒自下而上劃了個半弧，$w一提一收，平刃
揮向$n的頸部",
        "lvl"    : 8,
        "skill_name" : "沙鷗掠波",
]),
([        "action" : "$N使出一招"HIB"「天設牢籠」"NOR"，將$w舞得如白霧一般壓向$n ",
        "lvl"    : 16,
        "skill_name" : "天設牢籠",
]),
([        "action" : "$N一招"HIG"「閉門鐵扇」"NOR"，$w緩緩的斜着向$n推去 ",
        "lvl"    : 24,
        "skill_name" : "閉門鐵扇",
]),
([        "action" : "$N手拖$w，轉身躍起，一招"RED"「翼德闖帳」"NOR"，一道白光射向$n的胸口",
        "lvl"    : 32,
        "skill_name" : "翼德闖帳",
]),
([        "action" : "$N揮舞$w，使出一招"HIW"「白鶴舒翅」"NOR"，上劈下撩，左擋右開，齊齊罩向$n",
        "lvl"    : 40,
        "skill_name" : "白鶴舒翅",
]),
([        "action" : "$N一招"GRN"「春風送暖」"NOR"，左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "lvl"    : 48,
        "skill_name" : "春風送暖",
]),
([        "action" : "$N募的使一招"HIM"「八方藏刀」"NOR"，頓時劍光中無數朵刀花從四面八方湧向
$n全身",
        "lvl"    : 56,
        "skill_name" : "八方藏刀",
]),
});

string main_skill() { return "daojian-guizhen"; }
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("con", me)<30 )
                return notify_fail("你研究了半天，只覺得根骨有些差，始終無法理解其中的真諦。\n");

        if( query("str", me)<30 )
                return notify_fail("你研究了半天，感覺膂力有些低，始終無法隨意施展。\n");

        /*
        if ((int)me->query_skill("daojian-guizhen", 1))
                return notify_fail("你已經將苗家劍法和胡家刀法二者合一了。\n");
        */
        if( query("max_neili", me)<1400 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < 120)
                return notify_fail("你的基本刀法火候不夠，無法學習胡家刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("hujia-daofa", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的胡家刀法。\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        /*
        if ((int)me->query_skill("daojian-guizhen", 1))
                return notify_fail("你已經將苗家劍法和胡家刀法二者合一了。\n");
        */

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠，練不了胡家刀法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，練不了胡家刀法。\n");

        me->receive_damage("qi", 50);
        addn("neili", -80, me);
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 50;
        int d_e2 = 30;
        int p_e1 = 0;
        int p_e2 = -20;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 70;
        int m_e2 = 180;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("hujia-daofa",1);
        if (random(me->query_skill("blade")) > 80
        &&  me->query_skill("force") > 100
         && query("neili", me)>500
         && objectp(weapon=query_temp("weapon", me) )
         && query("id", weapon) == "lengyuedao" )
        {
                addn("neili", -100, me);
                return ([
                        "action": "$N使出一招" HIM "「大雪紛紛」" NOR "，$w發出萬長白芒，寒光四射，直劈向$n",
                        "damage": 400,
                        "dodge" : -100,
                        "parry" : -100,
                        "attack": 200,
                        "damage_type": "割傷"
                ]);
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
                "damage_type" : "割傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1; }

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("hujia-daofa", 1)) < 100 ||
            ! objectp(query_temp("weapon", me)))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("hujia-daofa", 1);

        if (ap * 2 / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIC "$n" HIC "突然使出一招「大雪紛紛」，發出萬長白芒，寒光四射，直劈向$N"
                            "化守勢為攻勢，對$N發動進攻！\n" NOR]);
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        if (damage < 100) return 0;

        if (damage > victim->query_str())
        {
                result = ([ "damage" : damage ]);
                result += ([ "msg" : HIW "你聽到「喀嚓」一聲輕響，已被$N的刀氣挫傷，$n頓時血冒三丈！！！\n" NOR ]);

                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"hujia-daofa/" + action;
}

int help(object me)
{
        write(HIC"\n胡家刀法："NOR"\n");
        write(@HELP

    胡家刀法為胡家始祖飛天狐狸所創。胡斐據家傳刀譜練成後與
金面佛苗人鳳的苗家劍齊名天下。

        學習要求：
                基本內功20級
                內力50
HELP
        );
        return 1;
}
