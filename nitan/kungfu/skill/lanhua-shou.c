// lanhua-shou.c -蘭花拂穴手

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N右手五指分開，微微一撥，再並攏向外一拂，一式" MAG"「花疏雲淡」"NOR"，拂向$n的膻中要穴",
        "lvl" : 0,
        "skill_name" : "花疏雲淡"
]),
([        "action" : "$N側身掠向$n，一式"CYN"「輕雲蔽月」"NOR"，左手五指暗暗運氣撥向$n的胸前大穴",
        "lvl" : 10,
        "skill_name" : "輕雲蔽月"
]),
([        "action" : "$N使一式"HIW"「雲破月來」"NOR"，左掌虛攻，右手並指斜前翻出，拍向$n的肩井穴",
        "lvl" : 20,
        "skill_name" : "雲破月來"
]),
([        "action" : "$N左掌護胸，微微側身，右掌勾上，一式"BLU"「幽蘭弄影」"NOR"，緩緩拂向$n的天突穴",
        "lvl" : 30,
        "skill_name" : "幽蘭弄影"
]),
([        "action" : "$N使一式"GRN"「芳蘭竟體」"NOR"，身影不定地掠至$n身後，猛地拍向$n的大椎穴",
        "lvl" : 42,
        "skill_name" : "芳蘭竟體"
]),
([        "action" : "$N兩臂左手下右手上地于胸前成蘭花指形翻上，微吸一口氣，一式"HIG"「蘭桂齊芳」"NOR"，雙手向外快速一撥，激出數道勁氣逼向$n的華蓋、璇璣、紫宮幾處大穴",
        "lvl" : 54,
        "skill_name" : "蘭桂齊芳"
]),
([        "action" : "$N衣袂飄飄，向上躍起，一式"RED"「月影花香」"NOR"，居高臨下，拂出一道勁力罩向$n的百會大穴",
        "lvl" : 66,
        "skill_name" : "月影花香"
]),
([        "action" : "$N凝神施展出"HIR"「花好月圓」"NOR"，雙手疾拂，一環環的勁氣逼向$n的上中下各大要穴",
        "lvl" : 80,
        "skill_name" : "花好月圓"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="tanzhi-shentong"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練蘭花拂穴手必須空手。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法學蘭花拂穴手。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太弱，無法練蘭花拂穴手。\n");

        if ((int)me->query_skill("hand", 1) < 100)
                return notify_fail("你的基本手法太差，無法學習蘭花拂穴手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("lanhua-shou", 1))
                return notify_fail("你的基本手法火候不夠，無法領會更高深的蘭花拂穴手。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了，無法練蘭花拂穴手。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練蘭花拂穴手。\n");
        me->receive_damage("qi", 35);
        addn("neili", -25, me);
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
        int d_e1 = -50;
        int d_e2 = -20;
        int p_e1 = 10;
        int p_e2 = 40;
        int f_e1 = 170;
        int f_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("lanhua-shou", 1);
        if (lvl > 100
           && random(10) == 1
           && me->query_skill("jingluo-xue", 1) > 100
            && query("neili", me)>1000 )
        {
                addn("neili", -300, me);
                return ([       "action" : HIW "$N" HIW "兩臂交叉置于胸前，指形作蘭花狀陡然翻上，疾點$n"
                                           HIW "胸前諸多要穴",
                                "attack" : 100,
                                "dodge"  : -300,
                                "parry"  : -300,
                                "damage" : 100,
                                "force"  : 300,
                                "weapon" : "蘭花指",
                                "damage_type": "點穴"
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"lanhua-shou/" + action;
}

int help(object me)
{
        write(HIC"\n蘭花拂穴手："NOR"\n");
        write(@HELP

    蘭花拂穴手是東海桃花島武功。出手五指狀如蘭花。
    可與彈指神通互備。

        學習要求：
                碧波神功20級
                內力200
HELP
        );
        return 1;
}
