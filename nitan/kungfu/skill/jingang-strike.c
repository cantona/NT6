// Last Modified by Winder on May. 29 2001
// jingang-strike.c 大金剛神掌 和多羅葉指互備 取自《天龍八部》等。

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
 
mapping *action = ({
([        "action" : "$N藹然微笑，一式"HIY"「禮敬如來」"NOR"，雙手合十向前微微一拜，一股暗勁蓄勢而發，擊向$n的$l",
         "lvl"   : 0,
         "skill_name" : "禮敬如來"
]),
([        "action" : "$N面色恭敬，一式"HIY"「遇佛傳法」"NOR"，閃到$n的身後，左手單拳在胸前一立，右手成掌直擊$n的後腦",
         "lvl"   : 10,
         "skill_name" : "遇佛傳法"
]),
([        "action" : "$N一聲冷笑，一式"HIY"「幽冥搜魂」"NOR"雙拳快速交替擊出十數掌，掌帶風聲呼呼作響，令$n不住倒退，疲於招架",
         "lvl"   : 20,
         "skill_name" : "幽冥搜魂"
]),
([        "action" : "$N暴雷般大喝聲中，一式"HIY"「引火煉妖」"NOR"，雙掌相搓，一前一後，挾着一股熱浪推向$n",
         "lvl"   : 30,
         "skill_name" : "引火煉妖"
]),
([        "action" : "$N一式"HIY"「魂散心魔」"NOR"，低眉垂目之間，突然雙掌直上直下，不成章法，猶如瘋魔一般攻向$n的身前身後",
         "lvl"   : 40,
         "skill_name" : "魂散心魔"
]),
([        "action" : "$N一式"HIY"「無相法相」"NOR"，右掌虛晃，身形一變，已化出數十個幻影，齊齊印向$n的全身各處要穴",
         "lvl"   : 60,
         "skill_name" : "無相法相"
]),
([        "action" : "$N騰身躍起，半空中出現巨大身影，突然一式"HIY"「攀天祥雲」"NOR"，頭下腳上，旋轉着俯衝下來，雙掌兜住$n",
         "lvl"   : 80,
         "skill_name" : "攀天祥雲"
]),
([        "action" : "$N莊嚴佇立，深深吸了一口氣，全身衣服微微漲起，低喝一聲，一式"HIY"「超度極樂」"NOR"，內力澎湃而出，擊向$n的前胸",
         "lvl"   : 100,
         "skill_name" : "超度極樂"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo){ return combo=="duoluoye-finger"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大金剛神掌必須空手。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 50)
                return notify_fail("你的站樁功火候不夠，無法學大金剛神掌。\n");
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練大金剛神掌。\n");
        if ((me->query_skill("boluomi-hand", 1) < 50) ||
                (me->query_skill("sanhua-strike", 1) < 50))
                return notify_fail("你的波羅蜜手和散花掌火候不夠，無法學大金剛神掌。\n");
        return 1;
}
int practice_skill(object me)
{
         if( query("qi", me)<50 )
                 return notify_fail("你的體力太低了。\n");
         if( query("neili", me)<20 )
                 return notify_fail("你的內力不夠練大金剛神掌。\n");
         me->receive_damage("qi", 45);
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
        int d_e2 = -25;
        int p_e1 = -5;
        int p_e2 = 20;
        int f_e1 = 210;
        int f_e2 = 320;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jingang-strike", 1);
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
         return __DIR__"jingang-strike/" + action;
}

int help(object me)
{
        write(HIC"\n大金剛神掌："NOR"\n");
        write(@HELP

    大金剛神掌是南少林掌法，和多羅葉指互備。

        學習要求：
                站樁功50級
                散花掌50級
                如來千葉手50級
                內力修為500
HELP
        );
        return 1;
}
