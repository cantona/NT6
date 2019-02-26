// yanfly.c 燕雙飛
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

/* 輕功信息 */
string *dodge_msg = ({
        "$n一個"HIW"「比翼雙飛」"NOR"，隨着$N的攻勢飄起，從容躲過這一招。\n",
        "$n使出一招"HIC"「巧燕穿雲」"NOR"，猛然縱起丈餘，結果$N撲了個空。\n",
        "$n身形一搖，幻出幾個人影，一招"HIW"「望穿秋水」"NOR"躲過了$N的攻勢。\n",
        "$n一招"MAG"「飛鳥投林」"NOR"縱身躍起，倏忽已落至$N身後。\n",
        "$n左一搖，右一晃，一招"HIM"「紫燕呢喃」"NOR"已輕鬆閃過。\n",
});

/* 可激發的武功類型 */
int valid_enable(string usage) { return usage=="dodge" || usage=="move"; }

/* 學習的條件。practice也要檢測本函數，所以，在這裏限制內功和內力就夠了。 */
int valid_learn(object me)
{
        return 1;
}

/* 練習的條件 */
int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太差了，不能練燕雙飛。\n");
        if (me->query_skill("yanfly", 1) < 30)
                me->receive_damage("qi", 10);

        me->receive_damage("qi", 20);
        return 1;
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
int practice_bonus() { return 5; }

/* 對師傅傳授產生誤解的比率。random(success()) == 0的時候誤解。暫時不用。
數值越大越不容易誤解。誤解引起倒退或停滯，僅體現在learn & teach */
int success() { return 10; }

/* 威力參數，參照門派參數，限制範圍1到1.5。嚴禁超標！目前僅用於輕功。 */
int power_point(object me) { return 1.5; }

/* 絕招文件目錄 */
string perform_action_file(string action)
{
        return __DIR__"yanfly/" + action;
}

/* 幫助信息 */
int help(object me)
{
        write(HIC"\n燕雙飛："NOR"\n");
        write(@HELP

        學習要求：
                帝王神功20級
                內力修為10
HELP
        );
        return 1;
}
