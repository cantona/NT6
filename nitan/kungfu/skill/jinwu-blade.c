// This program is a part of NT MudLIB
// jinwu-blade.c 金烏刀法

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *mjj = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([        "action" : "$N手中$w直劈，一招"+(mjj[random(13)])+"「開門揖盜」"NOR"，挾著勁風萬丈之式，向$n當頭而下",
        "lvl"    : 0,
        "skill_name" : "開門揖盜"
]),
([        "action" : "$N一招"+(mjj[random(13)])+"「梅雪逢夏」"NOR"，卷起一片光幕，只見刀光漫天，向$n疾卷而去",
        "lvl"    : 10,
        "skill_name" : "梅雪逢夏"
]),
([        "action" : "$N橫刀直揮，一招"+(mjj[random(13)])+"「漢將當關」"NOR"，刀身疾下，攏起一陣勁飆，向$n$l劈去",
        "lvl"    : 20,
        "skill_name" : "漢將當關"
]),
([        "action" : "$N一招"+(mjj[random(13)])+"「赤日金鼓」"NOR"，$w左右連劈六刀，一陣金芒自刀上疾射而出，映的$n\n雙眼緊閉，$N乘機趨步上前，揮刀力斬$n$l",
        "lvl"    : 30,
        "skill_name" : "赤日金鼓"
]),
([        "action" : "$N手中$w一沉，一招"+(mjj[random(13)])+"「千鈞壓駝」"NOR"，$w看似沉滯不堪，實則似緩實快，自下挽了一個刀花，\n直劈$n$l",
        "lvl"    : 40,
        "skill_name" : "千鈞壓駝"
]),
([        "action" : "$N將$w往後一帶，使出一招"+(mjj[random(13)])+"「大海沉沙」"NOR"，$w頓時消失得無影無蹤，$n正驚疑間，\n只見刀光一閃，$w已迅如閃電般斬往$l",
        "lvl"    : 50,
        "skill_name" : "大海沉沙"
]),
([        "action" : "$N一招"+(mjj[random(13)])+"「鮑魚之肆」"NOR"，揮舞$w狂劈十八刀，看似混亂不堪，實則刀刀劈向$n要害",
        "lvl"    : 60,
        "skill_name" : "鮑魚之肆"
]),
([        "action" : "$N踏步上前，使出"+(mjj[random(13)])+"「赤日炎炎」"NOR"，手中$w倒提橫揮，化成一簇簇烈燄，向$n劈頭蓋臉的斬去",
        "lvl"    : 70,
        "skill_name" : "赤日炎炎"
]),
([        "action" : "$N一招"+(mjj[random(13)])+"「旁敲側擊」"NOR"，手中$w劃出一個大平十字，向$n縱橫劈去",
        "lvl"    : 80,
        "skill_name" : "旁敲側擊"
]),
([        "action" : "$N反轉刀尖對準自己，一招"+(mjj[random(13)])+"「長者折枝」"NOR"，全身一個翻滾，$w向$n攔腰斬去",
        "lvl"    : 90,
        "skill_name" : "長者折枝"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }
int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不到，無法學習金烏刀法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太差，無法學習金烏刀法。\n");

        if ((int)me->query_skill("blade", 1) < 30)
                return notify_fail("你的基本劍法火候太淺，無法學習金烏刀法。\n");

        if (me->query_skill("blade", 1) < me->query_skill("jinwu-blade", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的金烏刀法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練金烏刀法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練金烏刀法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -70, me);

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
        int d_e2 = 15;
        int p_e1 = -15;
        int p_e2 = -30;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 150;
        int m_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("jinwu-blade", 1);
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"jinwu-blade/" + action;
}

int help(object me)
{
        write(HIC"\n金烏刀法："NOR"\n");
        write(@HELP

    金烏刀法為雪山派掌門夫人史小翠所創。史小翠與其夫白自在
鬥氣，創此刀法專為克制雪山劍法，並傳授給石破天，試圖籍石破
天打敗白萬劍之勢，以壓過乃夫的氣燄，出一口自己數十年被欺壓
的悶氣。此刀法專為克制雪山劍法而創，與雪山劍法聯手，卻能盡
補其漏失，威力無儔。

        學習要求：
                冰雪心法50級
                雪山劍法80級
                內力100
HELP
        );
        return 1;
}
