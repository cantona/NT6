// This program is a part of NITAN MudLIB
// yuxiao-jianfa.c 玉蕭劍法

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *xue_name = ({
        "勞宮穴","膻中穴","曲池穴","關元穴","曲骨穴","中極穴","承漿穴","天突穴","百會穴",
        "幽門穴","章門穴","大橫穴","紫宮穴","冷淵穴","天井穴","極泉穴","清靈穴","至陽穴",
});

string *parry_msg = ({
        "卻見$n身子微轉，輕描淡寫的以$w輕輕擋開，口唇未離簫邊，樂聲竟未有片刻停滯。\n",
});

string query_parry_msg(object weapon, object me)
{
        if( !me ) me = this_player();

        if (! objectp(weapon)
         || !query_temp("exercise/playing", me) )
                return SKILL_D("parry")->query_parry_msg(weapon);
        else
                return parry_msg[random(sizeof(parry_msg))];
}

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([        "action" : "$N漫步提腰，一招"+(order[random(13)])+"「英雄瀟洒我獨行」"NOR"，飄然來至$n面前，隨即手中$w微震，劍尖疾點向$n的$l",
        "lvl" : 0,
        "skill_name": "英雄瀟洒我獨行"
]),
([        "action" : "$N斜跨一步，使出一式"+(order[random(13)])+"「兒女情長只恨短」"NOR"，揮劍舞出兩道一長一短的光影直刺$n的$l",
        "lvl" : 10,
        "skill_name" : "兒女情長只恨短"
]),
([        "action" : "$N一招"+(order[random(13)])+"「翩然離去不思歸」"NOR"，$w驟然出鞘又立刻回到劍鞘中，隨即轉身翩然離去。$n這時才感覺到有一股勁氣逼向自己的$l",
        "lvl" : 20,
        "skill_name": "翩然離去不思歸"
]),
([        "action" : "$N雙手舉劍向天，一招"+(order[random(13)])+"「傲立群雄無所懼」"NOR"，$w帶起陣陣驚雷，自上而下向$n的頭顱剁去",
        "lvl" : 30,
        "skill_name": "傲立群雄無所懼"
]),
([        "action" : "$N施展出"+(order[random(13)])+"「傾城一笑萬人醉」"NOR"，手握$w頷首微微一笑，$n只看得一呆，卻見一道劍影猶如龍遊般襲向自己的$l，而自己卻沒看清$N何時出的手",
        "lvl" : 40,
        "skill_name" : "傾城一笑萬人醉"
]),
([        "action" : "$N左腳踏實，右腳虛點，一招"+(order[random(13)])+"「一曲奏畢愁腸結」"NOR"，$w帶著一團劍花，飄浮不定地逼向$n的$l",
        "lvl" : 50,
        "skill_name": "一曲奏畢愁腸結"
]),
([        "action" : "$N一招"+(order[random(13)])+"「處子弄簫亦多情」"NOR"，左手輕撫$w，隨即猛地一彈，右手向前一遞，只見一道閃爍不定的劍影迅速刺向$n的$l",
        "lvl" : 60,
        "skill_name" : "處子弄簫亦多情"
]),
([        "action" : "$N回身低首，神色黯然，一招"+(order[random(13)])+"「聞聲哀怨斷人腸」"NOR"，$w劍尖遊移不定地刺向$n的$l",
        "lvl" : 70,
        "skill_name" : "聞聲哀怨斷人腸"
]),
([        "action" : "$N坐手掩面，一招"+(order[random(13)])+"「彼將離兮淚漣漣」"NOR"，右手$w斜向下劃出，$n微覺奇怪，正遲疑間，卻見$N手中的$w已反挑而上，直刺自己的嚥喉",
        "lvl" : 80,
        "skill_name": "彼將離兮淚漣漣"
]),
([        "action" : "$N忽然面露微笑，一招"+(order[random(13)])+"「隨音而舞笑開顏」"NOR"，右手$w一閃，舞出三團劍花刺向$n的上中下三路",
        "lvl" : 90,
        "skill_name" : "隨音而舞笑開顏"
]),
([        "action" : "$N左手食指疾點$w，一招"+(order[random(13)])+"「簫音有情人無情」"NOR"，$w發出一聲龍吟，余音繚繞，$n只覺得胸前一悶，一陣剛猛的勁氣迫向自己",
        "lvl" : 100,
        "skill_name" : "簫音有情人無情"
]),
([        "action" : "$N右手微震，一招"+(order[random(13)])+"「簫聲響畢情兩斷」"NOR"，手中$w急顫，發出一陣震耳欲聾的轟鳴，剎那間飛沙走石，$n已在一團劍光的籠罩下，正勉力支撐著",
        "lvl" : 110,
        "skill_name" : "簫聲響畢情兩斷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不夠，無法學習玉蕭劍法。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法學習玉蕭劍法。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法火候不夠，無法學習玉蕭劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("yuxiao-jianfa", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的玉蕭劍法。\n");

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
        int d_e1 = -40;
        int d_e2 = -30;
        int p_e1 = -50;
        int p_e2 = -30;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 190;
        int m_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yuxiao-jianfa", 1);
        if (random(lvl) > 200 &&
            me->query_skill("force", 1) > 100 &&
            query("neili", me)>200 )
        {
                return ([
                        "action": HIC "$w" NOR + HIC "上的劍芒，猶似長蛇般伸縮不定......\n\n"
                                  HIG"$N丹田中猛提一口真氣，身子滴溜溜的打了半個圈子，手中$w"NOR+HIG"一挺，驀地劍芒突盛，青芒疾刺$n$l！"NOR,
                        "dodge" : -100,
                        "parry" : -100,
                        "attack": 200,
                        "force" : 400,
                        "damage": 400,
                        "damage_type":  "刺傷"
                ]);
        }
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

int practice_skill(object me)
{
        object weapon;

        if( !(weapon=query_temp("weapon", me)) )
                return notify_fail("空手時無法練玉簫劍法。\n");
        if( query("skill_type", weapon) != "sword" && query("skill_type", weapon) != "xsword" )
                return notify_fail("你使用的武器不對，無法練玉簫劍法。\n");
        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練玉簫劍法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的體力不夠練玉簫劍法。\n");

        me->receive_damage("qi", 70);
        addn("neili", -70, me);
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"yuxiao-jianfa/" + action;
}

mixed hit_ob(object me, object victim, int damage)
{
        mixed result;
        string name;
        object weapon;
        name = xue_name[random(sizeof(xue_name))];

        if( damage < 50 ) return 0;

        /*
        if( !objectp(weapon=query_temp("weapon", me) )
         || (query("id", weapon) != "yu xiao" &&
            query("id", weapon) != "xiao") )
                return;
        */
        result = ([ "damage" : damage ]);

        if (random(2) != 1)
                result += ([ "msg" : HIR "$n聽到耳邊傳來一陣陣蕭聲，頓時血氣翻滾，一股熱流穿心而過！\n" NOR]);
        else
                result += ([ "msg" : HIB "$n被$N劍上所附的一部分螺旋勁氣侵入" RED + name + NOR +
                                     HIB "，頓時經脈倒轉，痛苦萬分！\n" NOR]);
        return result;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yuxiao-jian", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n玉簫劍法："NOR"\n");
        write(@HELP

    玉簫劍法是東海桃花島主黃藥師的不傳之密。
    在桃花島竹林內“積翠亭”兩旁，懸著一副對聯：“桃花影裡
飛神劍，碧海潮生按玉簫”，隱然黃藥師生平兩大得意武功。落英
神劍之外就是玉簫劍法了。

        學習要求：
                碧波神功100級
                內力500
                機緣
HELP
        );
        return 1;
}
