// yunlong-jian.c 雲龍劍
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"\n$N使一式"GRN"「悠悠順自然」"NOR"，手中$w嗡嗡微振，幻成一條白光刺向$n的$l",
        "lvl" : 0,
        "skill_name" : "悠悠順自然"
]),
([        "action":"\n$N錯步上前，使出"HIC"「來去若夢行」"NOR"，劍意若有若無，$w淡淡地向$n的$l揮去",
        "lvl" : 8,
        "skill_name" : "來去若夢行"
]),
([        "action":"\n$N一式"HIB"「志當存高遠」"NOR"，縱身飄開數尺，運發劍氣，手中$w遙搖指向$n的$l",
        "lvl" : 15,
        "skill_name" : "志當存高遠"
]),
([        "action":"$N縱身輕輕躍起，一式"HIW"「表裏俱澄澈」"NOR"，劍光如水，一瀉千里，灑向$n全身",
        "lvl" : 20,
        "skill_name" : "表裏俱澄澈"
]),
([        "action":"$N手中$w中宮直進，一式"BLU"「隨風潛入夜」"NOR"，無聲無息地對準$n的$l刺出一劍",
        "lvl" : 30,
        "skill_name" : "隨風潛入夜"
]),
([        "action":"$N手中$w一沉，一式"HIG"「潤物細無聲」"NOR"，無聲無息地滑向$n的$l",
        "lvl" : 40,
        "skill_name" : "潤物細無聲"
]),
([        "action":"\n$N手中$w斜指蒼天，劍芒吞吐，一式"HIY"「雲龍聽梵音」"NOR"，對準$n的$l斜斜擊出",
        "lvl" : 50,
        "skill_name" : "雲龍聽梵音"
]),
([        "action":"$N左指凌空虛點，右手$w逼出丈許雪亮劍芒，一式"RED"「萬里一點紅」"NOR"刺向$n的咽喉",
        "lvl" : 60,
        "skill_name" : "萬里一點紅"
]),
([        "action":"$N合掌跌坐，一式"MAG"「我心化雲龍」"NOR"，$w自懷中躍出，如疾電般射向$n的胸口",
        "lvl" : 70,
        "skill_name" : "我心化雲龍"
]),
([        "action":"\n$N呼的一聲拔地而起，一式"HIY"「日月與同輝」"NOR"，$w幻出萬道光影，將$n團團圍住",
        "lvl" : 80,
        "skill_name" : "日月與同輝"
]),
([        "action":"$N隨風輕輕飄落，一式"GRN"「清風知我意」"NOR"，手中$w平指，緩緩拍向$n臉頰",
        "lvl" : 90,
        "skill_name" : "清風知我意"
]),
([        "action" : "$N劍尖微顫作龍吟，一招"HIW"「高處不勝寒」"NOR"，切骨劍氣如颶風般裹向$n全身",
        "lvl" : 100,
        "skill_name" : "高處不勝寒"
]),
([        "action" : "$N募的使一招"HIR"「紅葉舞秋山」"NOR"，頓時劍光中幾朵血花灑向$n全身",
        "lvl" : 110,
        "skill_name" : "紅葉舞秋山"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<900 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yunlong-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的雲龍劍法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if ((int)me->query_skill("yunlong-shengong", 1) < 20)
                return notify_fail("你的雲龍神功火候太淺。\n");
        if( query("qi", me)<55 || query("neili", me)<40 )
                return notify_fail("你的內力或氣不夠練雲龍劍法。\n");
        me->receive_damage("qi", 50);
        addn("neili", -35, me);
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
        int d_e1 = -15;
        int d_e2 = 5;
        int p_e1 = -45;
        int p_e2 = -25;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 180;
        int m_e2 = 270;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yunlong-jian", 1);
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
int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) {
        if ((int)me->query_skill("yunlong-xinfa",1) < 100)
        return 0.7;
        else if ((int)me->query_skill("yunlong-xinfa",1) > 200)
        return 1.4;
        else return ( ((int)me->query_skill("yunlong-xinfa",1)-100)/100*0.7+0.7 );
}
string perform_action_file(string action)
{
        return __DIR__"yunlong-jian/" + action;
}
int help(object me)
{
        write(HIC"\n雲龍劍法："NOR"\n");
        write(@HELP

    天地會看家本領，其特殊攻擊法威力奇大，堪稱武林一絕。

        學習要求：
                基本內功40級
                雲龍神功20級
                雲龍心法20級
                內力200
HELP
        );
        return 1;
}
