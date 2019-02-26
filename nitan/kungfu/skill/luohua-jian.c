// luohua-jian.c 落花十三劍
// Last Modified by winder on Sep. 12 2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N凌空飛起，挽了一個劍花，一招"GRN"「水面風回聚落花」"NOR"，劍光四射就如同千萬點寒星，向$n當頭灑下",
        "lvl"    : 0,
        "skill_name"  : "水面風回聚落花"
]),
([        "action" : "$N驀的向前一縱身，左手單掌護胸，右手手腕一沉，$w向上反撩，一式"HIY"「閒敲棋子落燈花」"NOR"划向$n的$l",
        "lvl"    : 20,
        "skill_name"  : "閒敲棋子落燈花"
]),
([        "action" : "$N口中輕叱一聲，手中$w向下一點，身形向上拔起丈餘，一招"BLU"「駿馬行橋踏落花」"NOR"$w居高臨下如閃電般刺向$n的$l",
        "lvl"    : 30,
        "skill_name"  : "駿馬行橋踏落花"
]),
([        "action" : "$N雙腳不丁不八，身形穩如泰山，左手微屈捏成劍決，右手$w輕顫，一式"MAG"「江城五月落梅花」"NOR"，只見滿天銀光紛紛點點罩向$n的$l",
        "lvl"    : 70,
        "skill_name"  : "江城五月落梅花"
]),
([        "action" : "$N長吸一口真氣，一招"RED"「銀燭光搖半夜花」"NOR"，右手$w搖曳不定，似有似無地刺向$n",
        "lvl"    : 80,
        "skill_name"  : "銀燭光搖半夜花"
]),
([        "action" : "$N雙目直視$n，左手疾伸，與右手同時握住$w，劍隨意動，一招"HIC"「猶為離人照落花」"NOR"，$w大開大闔，向$n的$l直劈過去",
        "lvl"    : 90,
        "skill_name"  : "猶為離人照落花"
]),
([        "action" : "只見$N左穿右插，劍光閃爍不定，一招"HIM"「更持紅燭賞殘花」"NOR"，$w極快地劃出一個光圈，“嗚..嗚..”作響，奔向$n的$l",
        "lvl"    : 100,
        "skill_name"  : "更持紅燭賞殘花"
]),
([        "action" : "$N身形稍挫，一招"HIG"「春城無處不飛花」"NOR"反手擊出，只聽“嗤”的一聲，一道青光射向$n的$l",
        "lvl"    : 110,
        "skill_name"  : "春城無處不飛花"
]),
([        "action" : "$N一聲清叱，劍光暴長，一招"HIW"「光搖銀海眩生花」"NOR"，攻勢突發，手中$w有如長江大河，滾滾而上，湧向$n的$l",
        "lvl"    : 130,
        "skill_name"  : "光搖銀海眩生花"
]),
([        "action" : "$N一聲長嘯，右臂一振，一招"HIR"「長日臨池看落花」"NOR"，手中$w作龍吟之聲脱手而出，$n只覺一道凌厲的劍氣撲面而來",
        "lvl"    : 150,
        "skill_name"  : "長日臨池看落花"
]),
([        "action" : "$N身軀一轉，一招"HIW"「月明殘雪映梅花」"NOR"，內力急吐，$w上突地漲出尺餘長的劍芒呼呼作響,划向$n的$l",
        "lvl"    : 160,
        "skill_name"  : "月明殘雪映梅花"
]), 
([      "action" : "$N雙眉一揚，眼中殺氣大盛，一招"HIM"「化作春泥更護花」"NOR"，左腳腳尖點地，右腳迅速向前踏出一步，只見$N與手中$w合而為一，直奔$n而去",     
        "lvl"    : 170,
        "skill_name"  : "化作春泥更護花"
]),
([        "action" : "$N抱元守一，運力於臂，一招"HIR"「人間處處有紅花」"NOR"，只見劍光閃閃，四下裏劍氣縱橫，$n幾乎要透不過氣來",
        "lvl"    : 180,
        "skill_name"  : "人間處處有紅花"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if ((int)me->query_skill("honghua-shengong", 1) < 20)
                return notify_fail("你的紅花神功火候太淺。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<35 )
                return notify_fail("你的內力或氣不夠練落花十三劍。\n");
        me->receive_damage("qi", 45);
        addn("neili", -30, me);
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
        int d_e1 = -5;
        int d_e2 = 15;
        int p_e1 = -35;
        int p_e2 = -15;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 140;
        int m_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luohua-jian", 1);
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
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"luohua-jian/" + action;
}
int help(object me)
{
        write(HIM"\n落花十三劍："NOR"\n");
        write(@HELP

    落花十三劍又稱紅花十三劍，是紅花會本門劍法。

        學習要求：
                紅花神功20級
                內力修為100
HELP
        );
        return 1;
}