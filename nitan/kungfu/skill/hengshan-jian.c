// hengshan-jian.c 恆山劍法
/// Last Modified by sir on 5/17/2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N意帶神閒，一式"HIG"「蒼松迎客」"NOR"，$w輕輕飛動，幻起一片劍光，圍掠$n全身",
        "lvl" : 0,
        "skill_name" : "蒼松迎客"
]),
([        "action":"$N使一招"HIR"「撥雲見日」"NOR"，身形向上飄起，手中$w虛虛實實幻出點點寒光射向$n$l",
        "lvl" : 20,
        "skill_name" : "撥雲見日"
]),
([        "action":"$N身形一轉，猛然一式"HIY"「日入空山」"NOR"，舞出滿天劍影，挾着勁風向$n的$l掃去",
        "lvl" : 40,
        "skill_name" : "日入空山"
]),
([        "action":"$N仰天長笑，身形飄然而起，在半空中身子一旋，一式"HIB"「輕雲蔽
月」"NOR"狂風般地擊向$n",
        "lvl" : 50,
        "skill_name" : "輕雲蔽月"
]),
([        "action":"$N左手捏着劍訣，右足踏開一招"HIC"「星劃長空」"NOR"向上斜刺，長劍鏘然躍出倏的化作幾點星光射向$n的$l",
        "lvl" : 80,
        "skill_name" : "星劃長空"
]),
([        "action":"$N向前邁去一大步，使出"HIW"「織女穿梭」"NOR"，手中$w舞成一個光球，迅若奔雷擊向$n的$l",
        "lvl" : 100,
        "skill_name" : "織女穿梭"
]),
([        "action":"$N運力一抖$w，一時"MAG"「飄然出塵」"NOR"，$w幻出點點劍花，飄然刺向$n的$l",
        "lvl" : 110,
        "skill_name" : "飄然出塵"
]),
([        "action":"$N大喝一聲，一招"GRN"「曲徑通幽」"NOR"，$w閃電般劃出一道大圓弧劈向$n的$l",
        "lvl" : 130,
        "skill_name" : "曲徑通幽"
]),
([        "action":"$N身形向上飄起，突然一轉身，頭下腳上，手握$w，一招"HIM"「雲霞
無聲」"NOR"，無聲無息地攻向$n的$l",
        "lvl" : 150,
        "skill_name" : "雲霞無聲"
]),
([        "action":"$N手中$w一抖，一招"BLU"「日照高林」"NOR"，$w逼出耀眼光芒，奮力擊向$n的$l",
        "lvl" : 160,
        "skill_name" : "日照高林"
]),
([        "action":"$N忽然身形高高躍起，使出"RED"「雲裏乾坤」"NOR"，$w幻出漫天花瓣，迅如雷霆射向$n的$l",
        "lvl" : 180,
        "skill_name" : "雲裏乾坤"
])
});

int valid_enable(string usage) { return (usage=="sword") || (usage=="parry") ; }

int valid_learn(object me)
{
        if( query("max_neili", me)<150 )
                return notify_fail(HIC"你的內力不夠。\n"NOR);

        if( query("force", me)<30 )
                return notify_fail(HIC"你的內功火候不夠。\n"NOR);

        if( query("gender", me) != "女性" )
                return notify_fail(HIY"這種陰柔的劍法只有女子才適合學。\n"NOR);
        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠練恆山劍法。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
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
        int d_e1 = 10;
        int d_e2 = 30;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 100;
        int m_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("hengshan-jian", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"hengshan-jian/" + action;
}

int help(object me)
{
        write(HIC"\n恆山劍法："NOR"\n");
        write(@HELP

    恆山劍法為恆山武功。

        學習要求：
                身具白雲心法的女性
                內力100
HELP
        );
        return 1;
}
