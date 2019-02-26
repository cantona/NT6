inherit SKILL;

#include <ansi.h>

mapping *action = ({
([      "action" : "$N一招「"HIW"杞人憂天"NOR"」抬頭向天，渾若不見，呼的一掌"
                   "向自己頭頂空空拍出，手掌斜下，掌力化成弧\n"
                   "形，四散落下拍向$n的$l",
        "force"  : 250,
        "attack" : 40,
        "dodge"  : 40,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "杞人憂天",
        "damage_type": "內傷"
]),
([      "action" : "$N一招「"HIG"無中生有"NOR"」手臂下垂，絕無半點防禦姿式，"
                   "突然間手足齊動，左掌右袖、雙足頭錘、連得\n"
                   "胸背腰腹盡皆有招式發出撞向$n",
        "force"  : 260,
        "attack" : 45,
        "dodge"  : 45,
        "damage" : 25,
        "lvl"    : 10,
        "skill_name" : "無中生有",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"HIB"拖泥帶水"NOR"」右手雲袖飄動，宛若流水，左掌"
                   "卻重滯之極，便似帶着幾千斤泥沙一般，左右\n"
                   "齊攻$n",
        "force"  : 280,
        "attack" : 50,
        "dodge"  : 50,
        "damage" : 30,
        "lvl"    : 20,
        "skill_name" : "拖泥帶水",
        "damage_type": "內傷"
]),

([      "action" : "$N一招「"HIY"力不從心"NOR"」含胸收腹，頭緩緩低下，腳步沉"
                   "重，右掌軟綿綿的拍向$n的$l",
        "force"  : 300,
        "attack" : 55,
        "dodge"  : 55,
        "damage" : 35,
        "lvl"    : 40,
        "skill_name" : "力不從心",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"HIR"行屍走肉"NOR"」踢出一腳。這一腳發出時恍恍惚"
                   "惚，隱隱約約，若有若無的踢向$n",
        "force"  : 330,
        "attack" : 60,
        "dodge"  : 60,
        "damage" : 40,
        "lvl"    : 60,
        "skill_name" : "行屍走肉",
        "damage_type": "瘀傷"
]),
([      "action" : "$N雙掌平託，一招「"HIM"庸人自擾"NOR"」沒精打采的拍向$n的$l",
        "force"  : 360,
        "attack" : 70,
        "dodge"  : 65,
        "damage" : 45,
        "lvl"    : 80,
        "skill_name" : "庸人自擾",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"RED"倒行逆施"NOR"」突然縱起丈餘，頭下腳上，倒過"
                   "身子，一掌拍向$n的$l",
        "force"  : 390,
        "attack" : 80,
        "dodge"  : 70,
        "damage" : 50,
        "lvl"    : 100,
        "skill_name" : "倒行逆施",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"YEL"心驚肉跳"NOR"」凝目遠眺，腳下虛浮，胸前門户"
                   "洞開，全身姿式與武學中各項大忌無不吻合",
        "force"  : 420,
        "attack" : 90,
        "dodge"  : 75,
        "damage" : 55,
        "lvl"    : 120,
        "skill_name" : "心驚肉跳",
        "damage_type": "內傷"
]),
([      "action" : "$N一招「"BLU"廢寢忘食"NOR"」腳下虛浮，有如幾天不吃不睡後"
                   "的腳步朗艙的襲到$n的身旁，左掌和右拳攻\n"
                   "向$n的$l",
        "force"  : 460,
        "attack" : 100,
        "dodge"  : 80,
        "damage" : 60,
        "lvl"    : 140,
        "skill_name" : "廢寢忘食",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"HIC"徘徊空谷"NOR"」左攻右打，虛虛實實的攻向$n的$l",
        "force"  : 490,
        "attack" : 110,
        "dodge"  : 85,
        "damage" : 65,
        "lvl"    : 160,
        "skill_name" : "徘徊空谷",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"CYN"飲恨吞聲"NOR"」左手做飲酒狀，右掌斜斜劈向$n的$l",
        "force"  : 520,
        "attack" : 125,
        "dodge"  : 90,
        "damage" : 90,
        "lvl"    : 70,
        "skill_name" : "飲恨吞聲",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"MAG"六神不安"NOR"」身如陀螺急轉，展開輕功圍着$n"
                   "快速遊走，忽然飛身而起，拍向$n的$l",
        "force"  : 550,
        "attack" : 140,
        "dodge"  : 95,
        "damage" : 75,
        "lvl"    : 200,
        "skill_name" : "六神不安",
        "damage_type": "內傷"
]),
([      "action" : "$N一招「"WHT"窮途末路"NOR"」閃身到$n身旁，左掌舉到胸前平"
                   "推而出，接着右掌斜斜劈向$n的$l",
        "force"  : 570,
        "attack" : 150,
        "dodge"  : 100,
        "damage" : 80,
        "lvl"    : 220,
        "skill_name" : "窮途末路",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"HIY"呆若木雞"NOR"」雙目直直的盯着$n，身體動也不"
                   "動一下的飛向$n",
        "force"  : 590,
        "attack" : 155,
        "dodge"  : 105,
        "damage" : 85,
        "lvl"    : 240,
        "skill_name" : "呆若木雞",
        "damage_type": "內傷"
]),
([      "action" : "$N低頭冥想，一招「"HIB"若有所失"NOR"」右掌向外平平推向$n"
                   "的$l",
        "force"  : 620,
        "attack" : 160,
        "dodge"  : 110,
        "damage" : 90,
        "lvl"    : 260,
        "skill_name" : "若有所失",
        "damage_type": "瘀傷"
]),
([      "action" : "$N一招「"HIB"四通八達"NOR"」雙掌晃出千萬掌影將$n籠罩在掌"
                   "力之下",
        "force"  : 650,
        "attack" : 165,
        "dodge"  : 115,
        "damage" : 95,
        "lvl"    : 280,
        "skill_name" : "四通八達",
        "damage_type": "內傷"
]),
([      "action" : "$N錯步上前，一招「"HIB"鹿死誰手"NOR"」招招搶先，以快打慢，"
                   "一個轉身已經轉到了$n的身後，運指如風點\n"
                   "向$n的大椎穴",
        "force"  : 680,
        "attack" : 170,
        "dodge"  : 120,
        "damage" : 100,
        "lvl"    : 300,
        "skill_name" : "鹿死誰手",
        "damage_type": "內傷"
]),
});

int valid_enable(string usage) { return usage == "unarmed" || usage == "parry"; }

int valid_learn(object me)
{
        // 無天性限制 ---- 黯然銷魂者，唯別而已矣

        if( query("gender", me) != "男性" )
                return notify_fail("你體會不到男人思念一個人的心情，無法領悟黯然銷魂掌。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想殺盡敵人，結果沒能進入黯然銷魂的境界。\n");

        if( query("character", me) == "陰險奸詐" )
                return notify_fail("你一心想去害人，結果沒能進入領悟黯然銷魂的境界。\n");

        if( query("str", me)<28 )
                return notify_fail("你先天臂力不足，無法修煉黯然銷魂掌。\n");

        if( query("int", me)<24 )
                return notify_fail("你先天悟性不足，無法修煉黯然銷魂掌。\n");

        if ((int)me->query_str() < 45)
                return notify_fail("你的膂力太弱，無法練黯然銷魂掌。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練黯然銷魂掌必須空手。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，無法練黯然銷魂掌。\n");

        if (me->query_skill("force") < 320)
                return notify_fail("你內功修為不足，無法修煉黯然銷魂掌。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳腳不夠嫻熟，無法練黯然銷魂掌。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("sad-strike", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的黯然銷魂掌。\n");

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
        int p_e1 = -45;
        int p_e2 = 25;
        int f_e1 = 300;
        int f_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("sad-strike", 1);
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

int practice_skill(object me)
{
        int cost;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");

        if( query("qi", me)<101 )
                return notify_fail("你的體力太低了。\n");

        cost = me->query_skill("sad-strike", 1) / 5 + 100;
        if( query("neili", me)<cost )
                return notify_fail("你的內力不夠練黯然消魂掌。\n");

        me->receive_damage("qi", 100);
        addn("neili", -cost, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string msg;
        mixed result;
        int j;

        j = me->query_skill("sad-strike", 1);
        if (damage_bonus < 50) return 0;

        if (random(20) >= 10 && ! victim->is_busy() && j > 140)
        {
                switch(random(3))
                {
                case 0 :
                        msg = YEL"$N抬頭向天，渾若不見，呼的一掌向頭頂空空拍出，手掌斜下，掌力化成弧形，四散落下！\n"NOR;
                        msg += HIR"結果$n被這一招「杞人憂天」帶得別説掙扎，竟連站定腳步也是不能。\n"NOR;
                        victim->start_busy(2 + random(2));
                        break;
                case 1 :
                        msg = HIB"$N右手雲袖飄動，宛若流水，左掌卻重滯之極，便似帶着幾千斤泥沙一般！\n"NOR;
                        msg += HIR"結果$n被這一招「拖泥帶水」帶得猶如身陷洪濤巨浪，跌跌撞撞。\n"NOR;
                        victim->start_busy(3 + random(2));
                        break;
                case 2 :
                        msg = HIG"突然間$N手足齊動，左掌右袖、雙足頭錘、連得胸背腰腹盡皆有招式發出！\n"NOR;
                        msg += HIR"結果$n被這一招「無中生有」帶得自身全然身不由主的境地。\n"NOR;
                        victim->start_busy(4 + random(2));
                        break;
                }
                return msg;
        } else
        {
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "只聽到“哇”的一聲，$n" HIR "噴出了一大口鮮血！\n" NOR]);

                return result;
        }

}

string perform_action_file(string action)
{
        return __DIR__"sad-strike/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("sad-strike", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }
int help(object me)
{
        write(HIC"\n黯然銷魂掌："NOR"\n");
        write(@HELP

    楊過自和小龍女在絕情谷斷腸崖前分手，不久便由神鵰帶着在
海潮之中練功，數年之後，除了內功循序漸進之外，別的無可再練，
心中整日價思念小龍女，漸漸的形銷骨立，了無生趣。一日在海濱
悄然良久，百無聊賴之中隨意拳打腳踢，其時他內功火候已到，一
出手竟具極大威力，輕輕一掌，將海灘上一隻大海龜的背殼打得粉
碎。他由此深思，創出了一套完整的掌法，出手與尋常武功大異，
厲害之處，全在內力，一共是一十七招。
    楊過生平受過不少武學名家的指點，自全真教學得玄門正宗內
功的口訣，自小龍女學得【玉女心經】，在古墓中見到【九陰真經
】，歐陽鋒以蛤蟆功和逆轉經脈，洪七公與黃蓉授以打狗棒法，黃
藥師授以彈指神通和玉簫劍法，除了一陽指之外，東邪、西毒、北
丐、中神通的武學無所不窺，而古墓派的武學又於五大高人之外別
創蹊徑，他依此融會貫通，卓然成家，創立此掌法。只因他單剩一
臂，是以不在招數變化取勝，反而故意與武學通理相反。將這套掌
法定名為“黯然銷魂掌”，取的是江淹【別賦】中那一句“黯然銷
魂者，唯別而已矣”之意。實飽含對小龍女的刻骨思念之情。

        學習要求：
                玉女心法100級
                內力1500
                只能向楊過學習
HELP
        );
        return 1;
}