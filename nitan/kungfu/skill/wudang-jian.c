// wudang-jian.c 武當劍法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" :  "飛燕入林",
        "action" : "$N身體左轉，左手劍指，兩腿屈膝，右前臂內旋，劍尖前端一寸處短促抖腕發力，一招"HIB"「飛燕入林」"NOR"，手中$w輕輕顫動，一劍自上而下扎向$n的$l",
        "lvl" : 0
]),
([        "skill_name" :  "青龍吐水",
        "action" : "$N身形不動，右前臂外旋，劍刃上崩，立馬左腿左弓步，一招"HIG"「青龍吐水」"NOR"，手中$w向前下反刺，一劍指向$n的$l",
        "lvl" : 10
]),
([        "skill_name" :   "鳳凰摯窩",
        "action" : "$N左腳向前一步，蹬地跳起，身體騰空疾速左轉，右手$w先向前刺，隨轉體變向，使出一式"MAG"「鳳凰摯窩」"NOR"，劍光如匹練般泄向$n的$l",
        "lvl" : 20
]),
([        "skill_name" :   "白蛇吐信",
        "action" : "$N碎步急進，提劍沿劍身方向疾速上崩，一招"HIW"「白蛇吐信」"NOR"直取$n的$l",
        "lvl" : 30
]),
([        "skill_name" :   "玉女穿梭",
        "action" : "$N平劍斜洗，臂圓劍直，雙腳交替弧形邁進，右手$w使出一式"HIC"「玉女穿梭」"NOR"，劍鋒往來運轉如梭，連綿不絕刺向$n的$l",
        "lvl" : 40
]),
([        "skill_name" :   "仙人指路",
        "action" : "$N屈腕抬臂，劍由前向後上方抽帶，挺起中平劍奮勇向前，右手$w使出一式"HIY"「仙人指路」"NOR"刺向$n的$l",
        "lvl" : 50
]),
([        "skill_name" :  "懷中抱月",
        "action" : "$N左撤步，抱劍當胸，揮劍做圓環形，正反攪動，右手$w一式"HIG"「懷中抱月」"NOR"，劍意圓潤，刺向$n的$l",
        "lvl" : 60
]),
([        "skill_name" :   "反身朝陽",
        "action" : "$N側身退步，左手劍指劃轉，腰部一扭，上體後仰，右手$w一記"HIM"「反身朝陽」"NOR"自下上撩指向$n的$l",
        "lvl" : 70
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wudang-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的武當劍法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<30 || query("neili", me)<10 )
                return notify_fail("你的內力或氣不夠練武當劍法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = 5;
        int p_e2 = 25;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 20;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wudang-jian", 1);
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
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"wudang-jian/" + action;
}

int help(object me)
{
        write(HIC"\n武當劍法："NOR"\n");
        write(@HELP

    武當劍法為武當派入門劍法。

        學習要求：
                太極神功10級
                基本劍法10級
                內力10
HELP
        );
        return 1;
}
