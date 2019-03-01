// pudu-zhang.c 普渡杖法

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N使一招"HIB"「黃牛轉角」"NOR"，手中$w自下而上，沉猛無比地向$n的小腹挑去。",
        "lvl" : 0,
        "skill_name" : "黃牛轉角"
]),
([        "action":"$N快步跨出，一招"HIW"「野馬追風」"NOR"，左手平托$w，右掌猛推杖端，頂向$n的胸口。",
        "lvl" : 9,
        "skill_name" : "野馬追風"
]),
([        "action":"$N高舉$w，一招"HIM"「猛虎跳澗」"NOR"，全身躍起，手中$w摟頭蓋頂地向$n擊去。",
        "lvl" : 18,
        "skill_name" : "猛虎跳澗"
]),
([        "action":"$N一招"HIY"「獅子搖頭」"NOR"，雙手持杖如櫓，對準$n猛地一攪，如同平地刮起一陣旋風。",
        "lvl" : 27,
        "skill_name" : "獅子搖頭"
]),
([        "action":"$N橫持$w，一招"HIR"「蒼龍擺尾」"NOR"，杖端化出無數個圓圈，凝滯沉重，把$n纏在其中。",
        "lvl" : 36,
        "skill_name" : "蒼龍擺尾"
]),
([        "action":"$N全身滾倒，$w盤地橫飛，突出一招"HIG"「大蟒翻身」"NOR"，杖影把$n裹了起來",
        "lvl" : 45,
        "skill_name" : "大蟒翻身"
]),
([        "action":"$N雙手和十，躬身一招"HIY"「胡僧托砵」"NOR"，$w自肘彎飛出，攔腰向$n撞去。",
        "lvl" : 53,
        "skill_name" : "胡僧托砵"
]),
([        "action":"$N一招"CYN"「慈航普渡」"NOR"，$w如飛龍般自掌中躍出，直向$n的胸口穿入。",
        "lvl" : 60,
        "skill_name" : "慈航普渡"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage=="parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<300 )
                return notify_fail("你的內力不夠，無法學習普渡杖法。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候太淺，無法學習普渡杖法。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("pudu-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的普渡杖法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<30 || query("neili", me)<10 )
                return notify_fail("你的內力或氣不夠練普渡杖法。\n");
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
        int d_e1 = -35;
        int d_e2 = 0;
        int p_e1 = 30;
        int p_e2 = 55;
        int f_e1 = 200;
        int f_e2 = 250;
        int m_e1 = 150;
        int m_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("pudu-zhang", 1);
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
                "damage_type" : "挫傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }
string perform_action_file(string action)
{
        return __DIR__"pudu-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n普渡杖法："NOR"\n");
        write(@HELP

    普渡杖法為少林七十二絕技之一。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
