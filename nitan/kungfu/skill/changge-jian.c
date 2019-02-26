// changge-jian.c
// Last Modified by winder on May. 15 2001

#include <ansi.h>
inherit SKILL;
/* 武功類型，分knowledge、martial martial分force、dodge和skill */
string type() { return "martial"; }
string martialtype() { return "skill"; }

/* 攻擊信息 */
mapping *action = ({
([        "action"     : "$N一聲長歎，$w輕點一招"MAG"「醉拍春衫惜舊香」"NOR"向着$n的$l疾刺而去",
        "skill_name" : "醉拍春衫惜舊香",
        "lvl"        : 0,
]),
([      "action"     : "$N緊縮眉頭，心中似有很深的怨氣$w一閃而隱，一招" MAG"「天將離恨惱梳狂」"NOR"刺向$n的$l",
        "skill_name" : "天將離恨惱梳狂",
        "lvl"        : 10,
]),
([      "action"     : "$N仰天不語，臉上掠過一絲憂愁，$w暫緩，一招" HIG"「年年陌上生青草」"NOR"遙遙刺向$n的$l",
        "skill_name" : "年年陌上生青草",
        "lvl"        : 20,
]),
([      "action"     : "$N怔怔而望，若有所思，忽然變招，驀然有驟風席捲，劍招凌烈撒向$n的$l，好一招"RED"「日日樓中到夕陽」"NOR,
        "skill_name" : "日日樓中到夕陽",
        "lvl"        : 30,
]),
([      "action"     : "$N衣袂飛舞，身形舒緩如舞，輕歌曼妙，一招" HIC"「雲渺渺，水茫茫」"NOR"，$w划向$n的$l",
        "skill_name" : "雲渺渺，水茫茫",
        "lvl"        : 40,
]),
([      "action"     : "$N微閉雙目，一股落寞的神情佈於臉上，劍意凝重，空氣頓時壓力大增一招"YEL"「徵人歸路許多長」"NOR"飛刺$n的$l",
        "skill_name" : "徵人歸路許多長",
        "lvl"        : 60,
]),
([      "action"     : "$N斜倚長劍，輕嘯而歌卻充滿了枯澀的意味，$w自肋下翻刺而出一招"HIM"「相思本是無憑語」"NOR"刺向$n的$l",
        "skill_name" : "相思本是無憑語",
        "lvl"        : 80,
]),
([      "action"     : "$N緩緩搖頭，雙目中似有淚光閃動$w輝映着蒼白的光芒若隱若現的閃現而出，一招"YEL"「莫向花箋費淚行」"NOR+"刺向$n的$l",
        "lvl"        : 100,
        "skill_name" : "莫向花箋費淚行",
]),
});

/* 招架信息 */
string *parry_msg = ({
        HIY"卻見$n踏前一步，劍式斜指$P的右臂，想要使$P閃身而退。\n"NOR,
        HIY"$n突然一劍點向$P的$l，雖一劍卻暗藏無數後着，$P手足無措，攻勢不由自主停了下來！\n"NOR,
});

/* 輕功信息 */
string *dodge_msg = ({
        HIC"$n一個"HIG"「江上弄春笛」"HIC"，平飛後躍，躲過了$N這一招。\n",
        HIC"$n一個"HIY"「大漠孤煙直」"HIC"，飛身縱起，身型曼妙，避開了$N的這一招。\n",
        HIC"$n一個"HIB"「海上生明"HIY"月"HIB"」"HIC"，身形恍惚，$N只覺眼前一花，招數落空。\n",
        HIC"$n手臂一轉，順勢一側身，一式"HIM"「長安市上酒家眠」"HIC"閃到一旁。\n",
        HIC"$n右手一揮，轉身就走，馬上又"HIG"「天涯涕淚一身遙」"HIC"，回身欺到$N身前。\n",
});

/* 可激發的武功類型 */
int valid_enable(string usage)
{
        return usage=="sword" || usage=="parry" || usage == "dodge";
}

/* 可與互備的武功 */
int valid_combine(string combo) { return combo=="king-of-dragon"; }

/* 招數效力的條件，目前我們沒限制 */
int valid_effect(object me, object weapon, string name, int skill) { }

/* 學習的條件。practice也要檢測本函數，所以，在這裏限制內功和內力就夠了。 */
int valid_learn(object me)
{
        object ob;

        if( (int)me->query_skill("king-of-dragon", 1) < 200 )
                return notify_fail("你的帝王神功不夠精熟，沒法練長歌劍法。\n");
        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠，沒有辦法練長歌劍法。\n");
        if( !(ob=query_temp("weapon", me)) || 
                query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");
        return 1;
}

/* 練習的條件 */
int practice_skill(object me)
{
        if( query("qi", me)<30 || query("neili", me)<3 )
                return notify_fail("你內力或氣不夠，沒有辦法練習長歌劍法。\n");
        me->receive_damage("qi", 30);
        addn("neili", -3, me);
        write("你按着所學練了一遍長歌劍法。\n");
        return 1;
}

/* 學習的招數表現 */
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

/* 升級的信息及副作用 */
void skill_improved(object me)
{
        tell_object(me, HIR "你輕輕一彈劍鋒，聲如龍吟。\n" NOR );
        addn("shen", 200, me);
}

/* 擊中對方的副作用 */
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/2)>query_temp("apply/armor", victim) )
        {
                victim->receive_wound("qi", (damage_bonus - 20) / 2 );
                victim->apply_condition("xx_poison", 10 );
                return HIR "你聽到「噗」地一聲輕響，鮮血飛濺！\n" NOR;
        }
}

/* 被擊中對方的副作用，目前主要用在內功上 factor= 加力 damage_bonus=臂力 */
mixed be_hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int ap, dp;

        ap=me->query_skill("force");
        dp=victim->query_skill("force");
        if( random(ap/2)>dp && query("neili", me)>2000 )
        {

                tell_object(me, HIY"你只覺得盡力襲體，急忙運起金鐘罩神功，一股真氣瀰漫全身！\n"NOR);
                addn("neili", -2*damage_bonus, me);
                return -damage_bonus;
        }
        return 0;
}

/* 激發成攻擊武功的信息 */
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -30;
        int d_e2 = 30;
        int p_e1 = -30;
        int p_e2 = 30;
        int f_e1 = 150;
        int f_e2 = 230;
        int m_e1 = 250;
        int m_e2 = 350;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("changge-jian", 1);
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

/* 激發成招架武功的信息 */
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

/* 激發成輕功的打鬥信息 */
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

/* 武功難度係數 = 100 / (learn_bonus+parctice_bonus+10) 在skill.c命令中體現 */
/* 每點潛能所能學到的本技能點數 = random(query_int()/2+query("int")/2+bonus) */
/* 限制範圍 0 - 30 */
int learn_bonus() { return 10; }

/* 每次練習獲得技能點數 = (random(基本武功*基本武功/(skill+1)))/5+bonus */
/* 限制範圍 0 - 30 */
int practice_bonus() { return 15; }

/* 對師傅傳授產生誤解的比率。random(success()) == 0的時候誤解。暫時不用。
數值越大越不容易誤解。誤解引起倒退或停滯，僅體現在learn & teach */
int success() { return 10; } 

/* 威力參數，參照門派參數，限制範圍1到1.5。嚴禁超標！目前僅用於輕功。 */
int power_point() { return 1; }

/* 絕招文件目錄 */
string perform_action_file(string action)
{
        return __DIR__"changge-jian/" + action;
}

/* 內功應用文件目錄 */
string exert_function_file(string func)
{
        return __DIR__"changge-jian/" + func;
}

/* 幫助信息 */
int help(object me)
{
        write(HIC"\n長歌劍法："NOR"\n");
        write(@HELP

    長歌劍法不對玩家開放。
    長歌劍法可激發成劍法、招架和輕功。用於NPC製作。
    
HELP
        );
        return 1;
}