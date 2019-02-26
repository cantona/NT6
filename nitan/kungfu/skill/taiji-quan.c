// taiji-quan.c 太極拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *taijin = ({ "「陰陽訣」", "「動靜訣」", "「兩儀訣」", "「剛柔訣」", "「沾黏訣」",  "「引字訣」","鑽翻", "螺旋","靜恆","開合","軟手","虛靈"});
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
         "$p眼見$P$w攻到，當即使出一招「攬雀尾」，右腳實，左腳虛，運起“擠”字訣，粘連粘隨，右掌已搭住$P左腕，橫勁發出。$N身不由主的向前一衝，跨出兩步，方始站定。\n",
         "不料$p雙手一圈，如抱太極，一股雄渾無比的力道組成了一個旋渦，只帶得$P在原地急轉七八下。\n",
         "$p「雙風貫耳」，連消帶打，雙手成圓形擊出，隨即左圈右圈，一個圓圈跟着一個圓圈，大圈、小圈、平圈、立圈、正圈、斜圈，一個個太極圓圈發出，登時便套得$P跌跌撞撞，身不由主的立足不穩。\n",
         "$p使出一招「雲手」，左手高，右手低，一個圓圈已將$P$w套住。\n",
         "$p覺氣息微窒，當下一招「斜飛勢」，將$P$w引偏。\n",
         "$p吸一口氣，體內真氣流轉，右掌揮出，一拒一迎，將$P的力道盡行碰了回去。\n",
         "$p雙掌一翻，使出一招「雲手」，雙掌柔到了極處，空明若虛，將$P$w的急勁盡數化去。\n",
        "$p當即雙掌一揚，迎着$w接去，待得手掌與$P$w將觸未觸之際，施出「攬雀尾式」，將$w輕輕攏住，腳下“金雞獨立式”，左足關地，右足懸空，全身急轉，宛似一枚陀螺。\n",
         "就在這電光石火的一瞬之間，$p身子一弓，正是「白鶴亮翅」的前半招，$P的勁力登時落空。\n",
});

mapping *action = ({
([      "action" : "$N使一招"+(order[random(13)])+"「攬雀尾」"NOR"，雙手劃了個半圈，按向$n的$l",
        "skill_name" : "攬雀尾",
        "lvl" : 0
]),
([      "action" : "$N使一招"+(order[random(13)])+"「單鞭」"NOR"，右手收置肋下，左手向外揮出，劈向$n的$l",
        "skill_name" : "單鞭",
        "lvl" : 5
]),
([      "action" : "$N左手回收，右手由鈎變掌，由右向左，使一招"+(order[random(13)])+"「提手上式」"NOR"，向$n的$l打去",
        "skill_name" : "提手上式",
        "lvl" : 10
]),
([      "action" : "$N雙手劃弧，右手向上，左手向下，使一招"+(order[random(13)])+"「白鶴亮翅」"NOR"，分擊$n的面門和$l",
        "skill_name" : "白鶴亮翅",
        "lvl" : 15
]),
([      "action" : "$N左手由胸前向下，身體微轉，劃了一個大圈，使一招"+(order[random(13)])+"「摟膝拗步」"NOR"，擊向$n的$l",
        "skill_name" : "摟膝拗步",
        "lvl" : 20
]),
([      "action" : "$N左手由下上挑，右手內合，使一招"+(order[random(13)])+"「手揮琵琶」"NOR"，向$n的$l打去",
        "skill_name" : "手揮琵琶",
        "lvl" : 25
]),
([      "action" : "$N左手變掌橫於胸前，右拳由肘下穿出，一招"+(order[random(13)])+"「肘底看錘」"NOR"，錘向$n的$l",
        "skill_name" : "肘底看錘",
        "lvl" : 30
]),
([      "action" : "$N左腳前踏半步，右手使一招"+(order[random(13)])+"「海底針」"NOR"，指由下向$n的$l戳去",
        "skill_name" : "海底針",
        "lvl" : 35
]),
([      "action" : "$N招"+(order[random(13)])+"「閃通臂」"NOR"，左腳一個弓箭步，右手上舉向外撇出，向$n的$l揮去",
        "skill_name" : "閃通臂",
        "lvl" : 40
]),
([      "action" : "$N兩手由相對，轉而向左上右下分別揮出，右手使一招"+(order[random(13)])+"「斜飛式」"NOR"，揮向$n的$l",
        "skill_name" : "斜飛式",
        "lvl" : 45
]),
([      "action" : "$N左手虛按，右手使一招"+(order[random(13)])+"「白蛇吐信」"NOR"，向$n的$l插去",
        "skill_name" : "白蛇吐信",
        "lvl" : 50
]),
([      "action" : "$N雙手握拳，向前向後劃弧，一招"+(order[random(13)])+"「雙峯貫耳」"NOR"打向$n的$l",
        "skill_name" : "雙風貫耳",
        "lvl" : 55
]),
([      "action" : "$N左手虛劃，右手一記"+(order[random(13)])+"「指襠錘」"NOR"擊向$n的襠部",
        "skill_name" : "指襠錘",
        "lvl" : 60
]),
([      "action" : "$N施出"+(order[random(13)])+"「伏虎式」"NOR"，右手擊向$n的$l，左手攻向$n的襠部",
        "skill_name" : "伏虎式",
        "lvl" : 65
]),
([      "action" : "$N由臂帶手，在面前緩緩劃過，使一招"+(order[random(13)])+"「雲手」"NOR"，揮向$n的$l",
        "skill_name" : "雲手",
        "lvl" : 70
]),
([      "action" : "$N左腿收起，右手使一招"+(order[random(13)])+"「金雞獨立」"NOR"，向$n的$l擊去",
        "skill_name" : "金雞獨立",
        "lvl" : 75
]),
([      "action" : "$N右手由鈎變掌，雙手掌心向上，右掌向前推出一招"+(order[random(13)])+"「高探馬」"NOR"",
        "skill_name" : "高探馬",
        "lvl" : 80
]),
([      "action" : "$N右手使一式招"+(order[random(13)])+"「玉女穿梭」"NOR"，撲身向$n的$l插去",
        "skill_name" : "玉女穿梭",
        "lvl" : 85
]),
([      "action" : "$N右手經腹前經左肋向前撇出，使一招"+(order[random(13)])+"「反身撇錘」"NOR"，向$n的$l錘去",
        "skill_name" : "反身撇錘",
        "lvl" : 90
]),
([      "action" : "$N左手虛按，右腿使一招"+(order[random(13)])+"「轉身蹬腿」"NOR"，向$n的$l踢去",
        "skill_name" : "反身蹬腿",
        "lvl" : 95
]),
([      "action" : "$N左手向上劃弧攔出，右手使一招"+(order[random(13)])+"「搬攔錘」"NOR"，向$n的$l錘去",
        "skill_name" : "白蛇吐信",
        "lvl" : 100
]),
([      "action" : "$N使一招"+(order[random(13)])+"「栽錘」"NOR"，左手摟左膝，右手向下錘向$n的$l",
        "skill_name" : "栽錘",
        "lvl" : 120
]),
([      "action" : "$N雙手先抱成球狀，忽地分開右手上左手下，一招"+(order[random(13)])+"「野馬分鬃」"NOR"，向$n的$l和麪門打去",
        "skill_name" : "野馬分鬃",
        "lvl" : 150
]),
([      "action" : "$N左手由胸前向下，右臂微曲，使一招"+(order[random(13)])+"「抱虎歸山」"NOR"，向$n的$l推去",
        "skill_name" : "抱虎歸山",
        "lvl" : 180
]),
([      "action" : "$N雙手經下腹劃弧交於胸前，成十字狀，一式"+(order[random(13)])+"「十字手」"NOR"，向$n的$l打去",
        "skill_name" : "十字手",
        "lvl" : 210
]),
([      "action" : "$N左腳踏一個虛步，雙手交叉成十字拳，一招"+(order[random(13)])+"「進步七星」"NOR"，向$n的$l錘去",
        "skill_name" : "進步七星",
        "lvl" : 240
]),
([      "action" : "$N身體向後騰出，左手略直，右臂微曲，使一招"+(order[random(13)])+"「倒攆猴」"NOR"，向$n的$l和麪門打去",
        "skill_name" : "倒攆猴",
        "lvl" : 270
]),
([      "action" : "$N雙手伸開，以腰為軸，整個上身劃出一個大圓弧，\n一招"+(order[random(13)])+"「轉身擺蓮」"NOR"，將$n渾身上下都籠罩在重重掌影之中",
        "skill_name" : "轉身擺蓮",
        "lvl" : 300
]),
([      "action" : "$N雙手握拳，右手緩緩收至耳際，左手緩緩向前推出，\n拳意如箭，一招"+(order[random(13)])+"「彎弓射虎」"NOR"，直奔$n心窩而去",
        "skill_name" : "彎弓射虎",
        "lvl" : 400
]),
([      "action" : "$N雙手在胸前翻掌，由腹部向前向上推出，一招"+(order[random(13)])+"「如封似閉」"NOR"，一股勁風直逼$n",
        "skill_name" : "如封似閉",
        "lvl" : 500
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }
int valid_combine(string combo)
{
        return combo == "wudang-zhang" || combo == "paiyun-shou";
}

int valid_learn(object me)
{
        if( query("int", me)<26 )
                return notify_fail("你先天悟性太差，難以領會太極拳的要詣。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練太極拳必須空手。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功火候不夠，無法學太極拳。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力太弱，無法練太極拳。\n");

        if ((int)me->query_skill("cuff", 1) < 100)
                return notify_fail("你的基本拳法火候不夠，無法學太極拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("taiji-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的太極拳。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練太極拳。\n");
        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -50;
        int p_e1 = -70;
        int p_e2 = -60;
        int f_e1 = 400;
        int f_e2 = 600;
        int i, lvl, seq, ttl = sizeof(action);
        string msg;
        lvl = (int) me->query_skill("taiji-quan", 1);
/////////yun taiji/////////
        if( query_temp("taiji", me) && query("neili", me)>100 )
        {
                addn_temp("taiji_fight", 1, me);
                msg = random(2)==1?
                        HIW"只見$N虛靈頂勁、涵胸拔背、鬆腰垂臀、沉肩墜肘，雙手抱了個太極式的圓圈，純以意行太極，\n已達形神合一，心動氣動的境界，結果使出了太極拳中的"NOR:
                        HIW"剎時間$N悟到了太極拳旨中“似鬆非鬆，將展未展，勁斷意不斷”的精微奧妙之處，\n使出一招猶如行雲流水，瀟灑無比。結果使出了太極拳中的"NOR;
                msg = msg + order[random(sizeof(order))] + taijin[random(sizeof(taijin))] + NOR;
        if ( lvl > 250
        && random(lvl) > 200
        && random(10)>3)
        {
                addn("neili", -10, me);
                return ([
                        "action" : msg,
                        "force" :  600,
                        "dodge":   -180,
                        "damage":   500,
                        "parry":   -180,
                        "damage_type" : random(2)==1?"瘀傷":"內傷",
                ]);
        }
  }
  //////普通出招////////
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

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("taiji-quan", 1) < 100 ||
            !living(me) || query_temp("weapon", me) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("taiji-quan", 1);

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "面含微笑，雙手齊出，劃出了"
                                            "一個圓圈，竟然讓$N" +
                                            HIC "的攻擊全不着力。\n" NOR]);
                        break;

                case 1:
                        result += (["msg" : HIC "$n" HIC "左右格檔，使出四兩撥千斤的手法，"
                                            "化解$N" HIC "的攻勢於無形。\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "慢慢出拳"
                                            HIC "，動作雖然緩慢，卻讓$N"
                                            HIC "感到渾身粘滯，甚不舒暢。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "面含微笑，雙手齊出，劃出了"
                                 "一個圓圈，然而$N" +
                                 HIY "理也不理，隨手揮招直入，進襲$n"
                                 HIY "！\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "左右格檔，使出四兩撥千斤的手法，"
                                 "可是$N" HIY "攻勢卻是變化無方，不遵循常理。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "慢慢出拳"
                                 HIY "，動作緩慢卻讓$N"
                                 HIY "感到粘滯，可是$N"
                                 HIY "立刻變化節奏，出奇招快速進擊$n"
                                 HIY "！\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("taiji-quan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
string perform_action_file(string action)
{
        return __DIR__"taiji-quan/" + action;
}
string query_description()
{
        return
        "太極拳，為宋末元初武當張三丰真人所創，合道家之説，沖虛自然，主以慢"
        "打快，以靜制動，後發制人，無為至虛之念的上乘武學。拳出時雙手圓轉，"
        "每一招都含着太極式的陰陽變化，精微奧妙，實是開闢了武學中從所未有的"
        "新天地。訣竅為「虛靈頂勁、涵胸拔背、鬆腰垂臀、沉肩墜肘」十六個字，"
        "純粹以意行，最忌用力。形神合一，是這路拳法的要旨。"
        "太極拳勁首要在於似鬆非鬆，將展未展，勁斷意不斷，其接力打力為武林一絕。";
}

int help(object me)
{
        write(WHT"\n太極拳："NOR"\n");
        write(@HELP

    太極拳，為宋末元初武當張三丰真人所創，合道家之説，沖虛
自然，講究以柔克剛、四兩撥千斤。主以慢打快，以靜制動，後發
制人，無為至虛之念的上乘武學。拳出時雙手圓轉，每一招都含着
太極式的陰陽變化，精微奧妙，實是開闢了武學中從所未有的新天
地。訣竅為「虛靈頂勁、涵胸拔背、鬆腰垂臀、沉肩墜肘」十六個
字，純以意行，最忌用力。形神合一，是這路拳法的要旨。
    太極拳勁首要在似鬆非鬆，將展未展，勁斷意不斷，其接力打
力為武林一絕。

        學習要求：
                太極神功20級
                內力100
HELP
        );
        return 1;
}
