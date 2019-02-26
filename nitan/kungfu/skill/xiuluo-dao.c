// xiuluo-dao.c 修羅刀

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N藏刀內收，一招"HIY"「割肉飼鷹」"NOR"，刀鋒自下而上劃了個半弧，向$n的
$l揮去",
        "lvl" : 0,
        "skill_name" : "割肉飼鷹",
]),
([        "action" : "$N左掌虛託右肘，一招"MAG"「投身餓虎」"NOR"，手中$w筆直划向$n的$l",
        "lvl" : 10,
        "skill_name" : "投身餓虎",
]),
([        "action" : "$N一招"BLU"「斫頭謝天」"NOR"，$w繞頸而過，刷地一聲自上而下向$n猛劈",
        "lvl" : 20,
        "skill_name" : "斫頭謝天",
]),
([        "action" : "$N右手反執刀柄，一招"HIW"「折骨出髓」"NOR"，猛一挫身，$w直向$n的頸中斬
去",
        "lvl" : 30,
        "skill_name" : "折骨出髓",
]),
([        "action" : "$N一招"GRN"「挑身千燈」"NOR"，無數刀尖化作點點繁星，向$n的$l挑去",
        "lvl" : 40,
        "skill_name" : "挑身千燈",
]),
([        "action" : "$N雙手合執$w，一招"BLU"「挖眼佈施」"NOR"，擰身急轉，刀尖直刺向$n的雙眼
",
        "lvl" : 50,
        "skill_name" : "挖眼佈施",
]),
([        "action" : "$N一招"CYN"「剝皮書經」"NOR"，手中$w劃出一個大平十字，向$n縱橫劈去",
        "lvl" : 60,
        "skill_name" : "剝皮書經",
]),
([        "action" : "$N反轉刀尖對準自己，一招"RED"「剜心決志」"NOR"，全身一個翻滾，$w向$n攔
腰斬去",
        "lvl" : 70,
        "skill_name" : "剜心決志",
]),
([        "action" : "$N一招"HIB"「燒身供佛」"NOR"，$w的刀光彷彿化成一簇簇烈焰，將$n團團圍繞
",
        "lvl" : 80,
        "skill_name" : "燒身供佛",
]),
([        "action" : "$N刀尖平指，一招"HIR"「刺血滿地」"NOR"，一片片切骨刀氣如颶風般裹向$n的
全身",
        "lvl" : 90,
        "skill_name" : "刺血滿地",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("xiuluo-dao", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的修羅刀法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練修羅刀。\n");
        me->receive_damage("qi", 35);
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
        int d_e1 = 40;
        int d_e2 = 20;
        int p_e1 = -10;
        int p_e2 = -30;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 130;
        int m_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("xiuluo-dao", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"xiuluo-dao/" + action;
}

int help(object me)
{
        write(HIC"\n修羅刀："NOR"\n");
        write(@HELP

    修羅刀為少林七十二絕技之一。

        學習要求：
                混元一氣功10級
                內力50
HELP
        );
        return 1;
}
