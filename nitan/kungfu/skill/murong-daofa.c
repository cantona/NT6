// murong-daofa.c 慕容刀法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N凌空躍起，雙手握起$w，高舉過頭，一招"HIM"「劈天蓋地滿壯志」"NOR"，勢
如奔雷墜地，卷起漫天風塵，一刀向$n的$l劈了下來",
        "lvl"    : 0,
        "skill_name" : "劈天蓋地滿壯志",
]),
([        "action" : "$N左腿斜跨一步，右手握著$w，橫架前胸，猛地側身旋轉，以腰帶
臂，以臂扛刀，一招"HIR"「彎刀逆轉倒乾坤」"NOR"，平刃揮向$n的$l",
        "lvl"    : 20,
        "skill_name" : "彎刀逆轉倒乾坤",
]),
([        "action" : "$N手握$w，展開身形，使動"HIW"「遙看萬疆千裡雪」"NOR"，突然之間，四周中
白光閃動，丈余圈子之內，全是刀影",
        "lvl"    : 40,
        "skill_name" : "遙看萬疆千裡雪",
]),
([        "action" : "$N一招"HIG"「壯志豪氣滿江湖」"NOR"，$w聲勢大變，東砍一刀少林寺的降魔刀
法，西劈一刀廣西黎山洞黎老漢的柴刀十八路，回轉又是一刀江南史家的
回風拂柳刀，刀刀不離$n左右",
        "lvl"    : 60,
        "skill_name" : "壯志豪氣滿江湖",
]),
});

int valid_enable(string usage) { return (usage=="blade") || (usage=="parry"); }
int valid_learn(object me)
{
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力不夠。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練慕容刀法。\n");
        me->receive_damage("qi", 30);
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
        int d_e2 = 25;
        int p_e1 = -5;
        int p_e2 = -20;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 90;
        int m_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("murong-daofa", 1);
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
int learn_bonus() { return 15; }
int practice_bonus() { return 10; }
int success() { return 15; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"murong-daofa/" + action;
}

int help(object me)
{
        write(HIC"\n慕容刀法："NOR"\n");
        write(@HELP

    慕容刀法為江南姑蘇慕容祖傳刀法。以雄渾沉厚、氣勢凝重著
稱。

        學習要求：
                內力50
HELP
        );
        return 1;
}
