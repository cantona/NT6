// shedao-qigong  蛇島奇功
#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

/*
mapping *action = ({
([        "action" : "$N一立一個翻身，一式「烏龍盤樹」，杖尾霍地橫捲過來，掃擊$n的$l",
        "lvl"    : 0,
        "skill_name" : "烏龍盤樹"
]),
([        "action" : "$N大喝一聲，手中$w化成一片銀光，一招「夜戰八方」，向$n的$l猛掃過去",
        "lvl"    : 10,
        "skill_name" : "夜戰八方"
]),
([        "action" : "$N驀然一聲長嘯，一招「流星趕月」，手中$w幻成三道白光，分襲$n胸腹要穴",
        "lvl"    : 15,
        "skill_name" : "流星趕月"
]),
([        "action" : "$N身形陡然飛起三丈多，一式「千斤壓頂」，手中$w帶着呼嘯破空聲從天而降",
        "lvl"    : 20,
        "skill_name" : "千斤壓頂"
]),
([      "action" : "$N趁着$n腳步未穩，攆杖向前進招，驟然一指，杖尾起處，「毒蛇尋穴」，直取白$n丹田下“血海穴”",
        "lvl"    : 25,
        "skill_name" : "毒蛇尋穴"
]),
([      "action" : "$N杖頭一轉，迅即一招「橫掃千軍」，剛猛迅捷，如雷霆疾發向$n下三路猛掃過去",
        "lvl"    : 30,
        "skill_name" : "橫掃千軍"
]),
([        "action" : "陡然間，$N手中杖光華大盛，$w宛似「蛟龍出海」，登時把$n圈在當中",
        "lvl"    : 35,
        "skill_name" : "蛟龍出海"
]),
([        "action" : "$N手中$w盤旋，左右飛舞宛如銀龍入海，十蕩十決，一式「橫雲斷峯」向$n的$l橫掃過去",
        "lvl"    : 40,
        "skill_name" : "橫雲斷峯",
]),
([      "action" : "$N高高躍起，揮舞着手中的$w一招「一柱擎天」猶如一條黑蟒般向$n當頭直落而下",
        "lvl"    : 50,
        "skill_name" : "一柱擎天",
]),
([        "action" : "$N一聲暴喝「蛟龍橫空」！將$w由下往上一撩，雙手握住$w尾，轉身猛得橫掃打向$n的$l",
        "lvl"    : 60,
        "skill_name" : "蛟龍橫空",
]),
([      "action" : "$N忽然招數一變，使出「靈蛇出洞」，杖法顯得靈巧之極，手中$w化作條條蛇影纏向$n",
        "lvl"    : 70,
        "skill_name" : "靈蛇出洞"
]),
([      "action" : "$N以杖代劍，$w中宮直進，夾着一陣狂風刺出，逼向$n的$l，正是招「長蛟化龍」",
        "lvl"    : 80,
        "skill_name" : "長蛟化龍"
]),
([        "action" : "$N一式「一杖定海」，當頭一$w擊將下來，杖頭未至，一股風已將$n逼得難以喘氣",
        "lvl"    : 90,
        "skill_name" : "一杖定海"
]),
([        "action" : "$N變招「羣蛇狂舞」，$w掃出一道道灰影從四面八方圍向$n，要將$n淹沒吞食",
        "lvl"    : 100,
        "skill_name" : "羣蛇狂舞"
]),
});
*/

mapping *action = ({
([        "action" : "$N使一招「仙鶴梳翎」手中$w一提，插向$n的$l",
        "damage" : 25,
        "dodge": -30,
        "parry": -40,
        "force": 90,
        "damage_type" : "挫傷",
        "skill_name" : "仙鶴梳翎"
]),
([        "action": "$N使出「靈蛇出洞」，身形微弓，手中$w倏的向$n的$l戳去",
        "damage" : 30,
        "dodge": -20,
        "parry": -10,
        "force": 140,
        "lvl"  : 30,
        "damage_type": "刺傷",
        "skill_name" : "靈蛇出洞"
]),
([        "action": "$N身子微曲，左足反踢，乘勢轉身，使一招「貴妃回眸」，右手$w已戳向$n$l",
        "damage" : 40,
        "dodge": -30,
        "parry": -20,
        "force": 190,
        "lvl"  : 70,
        "damage_type": "刺傷",
        "skill_name" : "貴妃回眸"
]),
([        "action" : "$N使一式「飛燕迴翔」，背對着$n，右足一勾，順勢在$w上一點，$w陡然向自己咽喉疾射，接着$N身子往下一縮，$w掠過其咽喉，急奔$n急射而來",
        "damage" : 50,
        "force" : 230,
        "dodge" : -45,
        "parry" : -40,
        "lvl" : 40,
        "lvl"  : 100,
        "damage_type" : "刺傷",
        "skill_name" : "飛燕迴翔"
]),
([        "action": "$N忽的在地上一個筋斗，使一招「小憐橫陳」，從$n胯下鑽過，手中$w直擊$n",
        "damage" : 55,
        "dodge": -40,
        "parry": -30,
        "force": 270,
        "lvl"  : 120,
        "damage_type": "刺傷",
        "skill_name" : "小憐橫陳"
]),
([        "action": "$N大吼一聲，使一招「子胥舉鼎」，反手擒拿$n極泉要穴，欲將$n摔倒在地",
        "dodge": -45,
        "parry": -50,
        "damage" : 60,
        "force": 330,
        "lvl"  : 140,
        "damage_type": "內傷",
        "skill_name" : "子胥舉鼎"
]),
([        "action": "$N雙腿一縮，似欲跪拜，一招「魯達撥柳」左手抓向$n右腳足踝，右手$w直擊$n小腹",
        "dodge": -50,
        "damage" : 65,
        "parry": -50,
        "force": 370,
        "lvl"  : 160,
        "damage_type": "內傷",
        "skill_name" : "魯達撥柳"
]),
([        "action": "$N突然一個倒翻筋斗，一招「狄青降龍」，雙腿一分，跨在肩頭，雙掌直擊$n",
        "dodge": -70,
        "damage" : 75,
        "parry": -30,
        "force": 400,
        "lvl"  : 180,
        "damage_type": "內傷",
        "skill_name" : "狄青降龍"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" ||
               usage == "sword"||
               usage == "staff"||
               usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法學蛇島奇功.\n");

        if ((int)me->query_skill("shenlong-bashi", 1) < 100)
                return notify_fail("你的神龍八式火候不夠，無法學蛇島奇功。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，無法學蛇島奇功。\n");

        /*
        if ((int)me->query_skill("shenlong-bashi", 1) < (int)me->query_skill("shedao-qigong", 1))
                return notify_fail("你的神龍八式水平有限，無法繼續學蛇島奇功。\n");
        */

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -30;
        int d_e2 = -60;
        int p_e1 = 0;
        int p_e2 = -30;
        int f_e1 = 300;
        int f_e2 = 400;
        int m_e1 = 220;
        int m_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shedao-qigong", 1);
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

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練蛇島奇功。\n");

        me->receive_damage("qi", 55);
        addn("neili", -67, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shedao-qigong/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }