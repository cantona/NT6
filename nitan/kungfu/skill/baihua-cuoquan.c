// Cuff：  查拳、燕青拳、太祖長拳、六合拳、少林長拳、八極拳
// Claw：  大擒拿手、小擒拿手、鷹爪功、虎爪手
// Strike：八卦掌、武當綿掌、遊身八卦掌

#include <ansi.h>
inherit SKILL;

string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N單手上抬，一招查拳的「沖天炮」，對準$n的$l猛擊下去",
        "force" : 420,
        "attack": 130,
        "dodge" : 45,
        "parry" : 45,
        "damage": 80,
        "damage_type":  "砸傷"
]),
([      "action": "$N一招燕青拳的「白鶴亮翅」，身子已向左轉成弓箭步，兩臂向後成鈎手，呼\n"
                  "的一聲輕響，反擊$n$l",
        "force" : 512,
        "attack": 145,
        "dodge" : 10,
        "parry" : 75,
        "damage": 85,
        "damage_type":  "瘀傷"
]),
([      "action": "$N往後一縱，施展小擒拿手的手法，雙手對着$n$l處的關節直直抓去",
        "force" : 410,
        "attack": 170,
        "dodge" : 35,
        "parry" : 35,
        "damage": 178,
        "damage_type":  "抓傷"
]),
([      "action": "$N左拳拉開，右拳轉臂回擾，一招少林的少林長拳突然擊出，帶着許許風聲貫向$n",
        "force" : 460,
        "attack": 150,
        "dodge" : 62,
        "parry" : 60,
        "damage": 90,
        "lvl"   : 30,
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N運足氣力，使出八極拳中的「八極翻手式」，雙掌對着$n的$l平平攻去",
        "force" : 480,
        "attack": 160,
        "dodge" : 40,
        "parry" : 40,
        "damage": 85,
        "damage_type":  "瘀傷"
]),
([      "action": "$N大喝一聲，左手往$n身後一抄，右掌往$n反手擊去，正是八卦掌的招式",
        "force" : 510,
        "attack": 155,
        "dodge" : 30,
        "parry" : 30,
        "damage": 95,
        "damage_type":  "瘀傷"
]),
([      "action": "$N提氣遊走，左手護胸，右手一招遊身八卦掌的「遊空探爪」，迅速拍向$n$l",
        "force" : 510,
        "attack": 150,
        "dodge" : 45,
        "parry" : 45,
        "damage": 110,
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N拉開架式，雙手將武當派的綿掌使得密不透風，招招不離$n的$l",
        "force" : 460,
        "attack": 155,
        "dodge" : 160,
        "parry" : 160,
        "damage": 105,
        "damage_type":  "瘀傷"
]),
([      "action": "$N突然飛身一躍而起，雙手握做爪狀，朝着$n的$l猛然抓去，凜然是鷹爪功的招式",
        "force" : 470,
        "attack": 185,
        "dodge" : 60,
        "parry" : 60,
        "damage": 155,
        "damage_type":  "抓傷"
]),
([      "action": "只見$N身形一矮，雙手翻滾，合抱為圈，一招太極拳「雲手」直拿$n的$l",
        "force" : 350,
        "attack": 90,
        "dodge" : 210,
        "parry" : 230,
        "damage": 65,
        "damage_type":  "瘀傷"
]),
([      "action": "只見$N跨前一步，左手一記大擒拿手護住上盤，右手順勢一帶，施一招摔碑手擊向$n",
        "force" : 520,
        "attack": 155,
        "dodge" : 41,
        "parry" : 37,
        "damage": 103,
        "damage_type":  "瘀傷"
]),
([      "action": "$N一個轉身，趁$n不備，反手將$n牢牢抱住猛的朝地面摔去，竟然是蒙古的摔角招式",
        "force" : 560,
        "attack": 185,
        "dodge" : 75,
        "parry" : 60,
        "damage": 125,
        "damage_type":  "摔傷"
]),
});

string main_skill() { return "baihua-cuoquan"; }

mapping sub_skills = ([
                "cha-quan"      : 100,          // 查拳
                "baji-quan"     : 100,          // 八極拳
                "changquan"     : 100,          // 太祖長拳
                "liuhe-quan"    : 100,          // 六合拳法
                "yanqing-quan"  : 100,          // 燕青拳
                "shaolin-quan"  : 100,          // 少林長拳
                "bagua-zhang"   : 100,          // 八卦掌
                "bazhen-zhang"  : 100,          // 八陣八卦掌
                "wudang-zhang"  : 100,          // 武當棉掌
                "huzhao-shou"   : 100,          // 虎爪手
                "yingzhao-shou" : 100,          // 鷹爪手
                "xiao-qinna"    : 100,          // 小擒拿手
                "da-qinna"      : 100,          // 大擒拿手
        ]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if( query("int", me)<28 )
        {
                tell_object(me, "你演練完畢，覺得各種拳法毫無牽連，看來依你的悟"
                                "性，無法貫通百花錯拳。\n");
                return 0;
        }

        if( query("dex", me)<23 )
        {
                tell_object(me, "你演練完畢，只覺自己的身法靈動性太差，無法貫通"
                                "百花錯拳。\n");
                return 0;
        }

        if ((int)me->query_skill("unarmed", 1) < 150)
        {
                tell_object(me, "你覺得自己的拳腳功夫還有待提高，暫且無法貫通百"
                                "花錯拳。\n");
                return 0;
        }

        if (me->query_skill("force") < 250)
        {
                tell_object(me, "你覺得自己內功火候尚淺，無法貫通百花錯拳。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 80)
        {
                tell_object(me, "你覺得自己武學修養太低，無法貫通百花錯拳。\n");
                return 0;
        }

        if( query("max_neili", me)<3000 )
        {
                tell_object(me, "你覺得自己真氣不繼，無法貫通百花錯拳。\n");
                return 0;
        }

        if (random(10) < 7)
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通。\n");
                return 0;
        }

        tell_object(me, HIY "你一氣呵成，將各家各派的數十種拳法連續施展演練了一"
                            "片，突然間心中頓悟，通曉了百花錯拳的奧\n妙精髓，融"
                            "會貫通各家拳術中的精微之處，匯百家之長而成了這套百"
                            "花錯拳。\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練百花錯拳必須空手。\n");

        if( query("int", me)<28 )
                return notify_fail("你的先天悟性太差，無法學習百花錯拳。\n");

        if( query("dex", me)<23 )
                return notify_fail("你的先天身法孱弱，無法學習百花錯拳。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為遠遠不足，難以練習百花錯拳。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候尚淺，無法學習百花錯拳。\n");

        if ((int)me->query_skill("unarmed", 1) < 150)
                return notify_fail("你的拳腳根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("cuff", 1) < 100)
                return notify_fail("你的拳法根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("claw", 1) < 100)
                return notify_fail("你的爪法根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("strike", 1) < 100)
                return notify_fail("你的掌法根基有限，無法體會百花錯拳要詣。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("baihua-cuoquan", 1))
                return notify_fail("你的拳腳根基火候不足，無法領會更高深的百花錯拳。\n");

        return 1;
}

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"; }
int valid_combine(string combo) { return combo=="benlei-shou"; }

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
        int d_e1 = 25;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -15;
        int f_e1 = 130;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("baihua-cuoquan", 1);
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
                "damage_type" : "瘀傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point() { return 1.0; }

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 80);
        addn("neili", -120, me);

        return 1;
}

/*
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}
*/

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        mixed result;

        lvl = me->query_skill("baihua-cuoquan", 1);

        if (damage_bonus < 150 || lvl < 150) return 0;

        if (damage_bonus / 6 > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 100) / 3, me);
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "只聽$n" HIR "前胸「咔嚓」一聲脆響，竟像是"
                                     "肋骨斷折的聲音。\n" NOR ]);
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"baihua-cuoquan/" + action;
}

int help(object me)
{
        write(HIM"\n百花錯拳："NOR"\n");
        write(@HELP

    百花錯拳是天池怪俠袁士霄所創。袁士霄痛悔當年錯過大好因緣，
以世上萬物多錯，創出此拳。此拳取眾家之長，往往似是而非，誘敵
入彀，故稱錯拳。
    紅花會總舵主陳家洛為袁士霄入室弟子，得傳此拳。

        學習要求：
                紅花神功20級
                內力修為100
HELP
        );
        return 1;
}