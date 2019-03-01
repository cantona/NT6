// chongling-sword.c

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N手中$w輕輕點擊，使一招"GRN"「青梅如豆」"NOR"，向$n的$l刺去",
        "lvl"    : 0,
        "skill_name" : "青梅如豆"
]),
([        "action" : "$N手中$w輕輕掠過，斜斜削向$n額間。$n一呆，低聲道：“"GRN "「柳葉似眉」"NOR"”",
        "lvl"    : 10,
        "skill_name" : "柳葉似眉"
]),
([        "action" : "$N舞動$w，一招"HIW"「霧中初見」"NOR"挾著無數劍光刺向$n的$l",
        "lvl"    : 20,
        "skill_name" :  "霧中初見"
]),
([        "action" : "$N手中$w輕輕揮洒，一招"HIB"「雨後乍逢」"NOR"直刺向$n的雙眼",
        "lvl"    : 30,
        "skill_name" :   "雨後乍逢"
]),
([        "action" : "$N使一招"HIC"「一見鐘情」"NOR"，手中$w劍光暴長，向$n的$l刺去",
        "lvl"    : 40,
        "skill_name" :   "一見鐘情"
]),
([        "action" : "$N劍隨身轉，一招"HIM"「兩小無猜」"NOR"罩向$n的$l",
        "lvl"    : 50,
        "skill_name" : "兩小無猜"
]),
([        "action" : "$N手中$w劍光暴長，飛身而起，一招"MAG"「同生共死」"NOR"往$n嚥喉刺去",
        "lvl"    : 60,
        "skill_name" :  "同生共死"
]),
([        "action" : "$N手中$w化成一道光弧，直指$n$l，一招"HIG"「難舍難分」"NOR"發出虎哮龍吟刺去",
        "lvl"    : 70,
        "skill_name" :   "難舍難分"
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力不夠，沒有辦法練沖靈劍法。\n");
        if( (string)me->query_skill_mapped("force")!= "zixia-shengong")
                return notify_fail("沖靈劍法必須配合紫霞神功才能練。\n");
        if( !(ob=query_temp("weapon", me)) ||
                query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<10 )
                return notify_fail("你的內力或氣不夠，無法練習沖靈劍法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
        write("你按著所學練了一遍沖靈劍法。\n");
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
        int d_e2 = 60;
        int p_e1 = 10;
        int p_e2 = 25;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 20;
        int m_e2 = 110;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("chongling-sword", 1);
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
int power_point() { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"chongling-sword/" + action;
}

int help(object me)
{
        write(HIC"\n沖靈劍法："NOR"\n");
        write(@HELP

    這是令狐沖和小師妹岳靈珊兩人在華山練劍時共創的“沖靈劍
法”。“沖”是令狐沖，“靈”是岳靈珊，是二人好玩而共同鑽研
出來的劍術。令狐沖的天份比師妹高得多，不論做甚麼事都喜不拘
成法，別創新意，這路劍法雖說是二人共創，十之八九卻是令狐沖
想出來的。當時二人武功造詣尚淺，這路劍法中也並沒甚麼厲害的
招式，只是二人常在無人處拆解，練得卻十分純熟。


        學習要求：
                紫霞神功1級
                內力修為50
HELP
        );
        return 1;
}
