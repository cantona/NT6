#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *dodge_msg = ({
        "$n身形微微一晃，雙足連環踢出，將$N硬生生迫退。\n",
        "$n錯步上前，單足忽的一抬，將$N的攻勢全部擋回，只能自保。\n",
        "$n雙足輕輕點地，猛的拔地而起，躲開了$N的招式。\n",
});

mapping *action = ({
([        "action" : "$N雙手虛晃，左腳猛地飛起，一式"HIC"「風起雲湧」"NOR"，腳尖晃動，踢向$n的屁股",
        "lvl" : 0,
        "skill_name" : "風起雲湧"
]),
([        "action" : "$N左腳頓地，別轉身來抽身欲走，只一剎那間一回身，右腳一式"HIB"「空谷足音」"NOR"，猛踹$n的$l",
        "lvl" : 0,
        "skill_name" : "空谷足音"
]),
([        "action" : "$N左手一掙，反手扭搭住$n的右手，右腳同時踹出，既猛且準，一式"GRN"「碧淵騰蛟」"NOR"，踢中的$n的胸口",
        "lvl" : 10,
        "skill_name" : "碧淵騰蛟"
]),
([        "action" : "$N突然躍起，雙足連環圈轉，一式"HIY"「秋風落葉」"NOR"，足帶風塵，攻向$n的全身",
        "lvl" : 10,
        "skill_name" : "秋風落葉"
]),
([        "action" : "$N兩手護胸，雙腳交叉踢起，一式"HIW"「風掃殘雲」"NOR"，腳腳不離$n的面門左右",
        "lvl" : 20,
        "skill_name" : "風掃殘雲"
]),
([        "action" : "$N突然側身，卻步後退，一個前空翻，右腳自上而下一式"HIM "「流星墜地」"NOR"，照$n的面門直劈下來",
        "lvl" : 30,
        "skill_name" : "流星墜地"
]),
([        "action" : "$N使一式"HIW"「朔風吹雪」"NOR"，全身突然飛速旋轉，雙足忽前忽後，迅猛無極踹向$n的胸口",
        "lvl" : 40,
        "skill_name" : "朔風吹雪"
]),
([        "action" : "$N抽身躍起，開聲吐氣，大喝一聲：嗨！一式"MAG"「雷動九天」"NOR"，雙腳如旋風般踢向$n的$l",
        "lvl" : 30,
        "skill_name" : "雷動九天"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" ||  usage == "parry" ||  usage == "dodge";
}

int valid_combine(string combo)
{
        return combo == "luoying-shenzhang";
}

int valid_learn(object me)
{
            if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學習旋風掃葉腿必須空手。\n");

            if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法學旋風掃葉腿。\n");

            if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練旋風掃葉腿。\n");

            if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("xuanfeng-tui", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的旋風掃葉腿。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("xuanfeng-tui", 1))
                return notify_fail("你的基本輕功水平有限，無法領會更高深的旋風掃葉腿。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 5;
        int d_e2 = 25;
        int p_e1 = -45;
        int p_e2 = 30;
        int f_e1 = 350;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xuanfeng-tui", 1);
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

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
            if( query("qi", me)<60 )
                       return notify_fail("你的體力太低了。\n");

            if( query("neili", me)<60 )
                       return notify_fail("你的內力不夠練旋風掃葉腿。\n");

            me->receive_damage("qi", 45);
            addn("neili", -51, me);
            return 1;
}

string perform_action_file(string action)
{
            return __DIR__"xuanfeng-tui/" + action;
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n旋風掃葉腿："NOR"\n");
        write(@HELP

    旋風掃葉腿是東海桃花島主黃藥師所創武功。
    可與落英神劍掌互備。

        學習要求：
                碧波神功15級
                內力100
HELP
        );
        return 1;
}
