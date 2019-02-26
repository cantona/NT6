// parry.c 基本招架
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }
string *parry_msg = ({
        "只聽見「鏘」一聲，被$p格開了。\n",
        "結果「當」地一聲被$p擋開了。\n",
        "但是被$n用手中兵刃架開。\n",
        "但是$n身子一側，用手中兵刃格開。\n",
});
string *unarmed_parry_msg = ({
        "但是被$p格開了。\n",
        "結果被$p擋開了。\n",
});

/* 招架信息 $n的$W: 招架人的兵器 $P的$l和$w: 攻擊方的身體部位和兵器 */
string *axe_msg = ({
        "卻見$n踏前一步，舉起$W奮力一架，架開了$P的$w。\n",
        "$n側過頭，斜身舉起$W，向$P的$l虛劈一斧，迫得$P攻勢不由自主停下來！\n",
        "只聽見「鏘」一聲，$n舉起$W將$P的$w格開了。\n",
        "結果「當」地一聲，$n身子一側，用手中$W格開$P的$w。\n",
});
string *blade_msg = ({
        "卻見$n踏前一步，掄起$W奮力向上一架，架開了$P的$w。\n",
        "$n側過頭，斜身舉起$W，窺得$P的親切就是一刀，迫得$P不得不停下來！\n",
        "只聽見「鏘」一聲，$n舉起$W將$P的$w格開了。\n",
        "結果「當」地一聲，$n身子一側，用手中$W格開$P的$w。\n",
        "$n高舉手中$W，不管三七二十一，衝着$P當頭劈下，逼得$P手忙腳亂。\n",
});
string *club_msg = ({
        "卻見$n向前踏出一步，雙手橫過$W奮力一架，正好架開了$P的$w。\n",
        "$n側身一閃，舉起$W，向$P的下盤一棍挑去，迫得$P跳起躍開！\n",
        "$n豎起$W一隔，把$P的$w擋在了外門。\n",
        "$n手握$W往$P當胸一捅，逼得$P掄回$w自救不暇。\n",
});
string *dagger_msg = ({
        "卻見$n踏前一步，舉起$W奮力一格，架開了$P的$w。\n",
        "$n忙斜身躍前，手執$W奮不顧身向$P的$l就扎，$P只好跳開避免兩敗俱傷。\n",
        "$n側過頭，斜身舉起$W一架，正架在$P的$w上！\n",
});
string *hammer_msg = ({
        "卻見$n踏前一步，舉起$W奮力一砸，砸偏了$P的$w。\n",
        "$n側身立起$W在身前，一錘正好擋住了$P的$w。\n",
        "$n不管三七二十一，長身提起$W，自上而下一錘下去，迫得$P的$w一個收勢退了回去！\n",
});
string *hook_msg = ({
        "卻見$n踏前一步，舉起$W奮力一架，架開了$P的$w。\n",
        "$n舉起$W一鈎，正好鈎開了$P的$w！\n",
        "$n側過頭，斜身舉起$W，向$P的$l一鈎鈎去，迫得$P回勢自救不迭。\n",
        "$n立起$W一擋，堪堪把$P的$w擋在身外！\n",
});
string *spear_msg = ({
        "卻見$n向前踏出一步，雙手橫過$W奮力一架，正好架開了$P的$w。\n",
        "$n側身一閃，橫過槍尾，向$P的下盤掃去，迫得$P跳起閃避！\n",
        "$n豎起$W一隔，把$P的$w擋在了外門。\n",
        "$n手握$W，搶先向$P分心就刺，逼得$P掄回$w自救不暇。\n",
});
string *staff_msg = ({
        "卻見$n向前踏出一步，雙手橫過$W奮力一架，正好架開了$P的$w。\n",
        "$n側身一閃，橫過杖尾，向$P的下盤掃去，迫得$P跳起閃避！\n",
        "$n豎起$W一隔，把$P的$w擋在了外門。\n",
        "$n高舉$W，發力向$P全力砸下，逼得$P後躍急避不迭。\n",
});
string *stick_msg = ({
        "卻見$n向前踏出一步，雙手橫過$W奮力一架，正好架開了$P的$w。\n",
        "$n側身一閃，橫過棒尾，向$P的下盤掃去，迫得$P跳起閃避！\n",
        "$n豎起$W一隔，把$P的$w擋在了外門。\n",
        "$n手握$W往$P當胸一捅，逼得$P掄回$w自救不暇。\n",
});
string *sword_msg = ({
        "卻見$n踏前一步，$W斜指$P的右臂，想要使$P撤回$w閃身而退。\n",
        "$n手中$W疾點$P右手手腕，迫得$P收招撤回$w。\n",
        "$n手中$W橫過，劍尖劃過$P右臂，迫得$P掄回$w撤招。\n",
        "$n手中$W斜出，指向$P的$w來路，「當」地一聲，將它擋了開去。\n",
        "$n一個斜身，手中$W斜斜指向$P的$l，迫得$P回招自救。\n",
        "$n突然一劍點向$P的$l，雖一劍卻暗藏無數後着，$P手足無措，攻勢不由自主停了下來！\n",
});
string *whip_msg = ({
        "卻見$n踏前一步，$W在半空中化為一圈銀芒，落向$P的$l，迫使$P閃身而退。\n",
        "但見$n左腿提膝，手中$W斜指，橫向$P的$l，要使$P閃身而退。\n"NOR,
        "只見$n上身往左側一擰，右手$W反手抖動，向$P的$l鉸去，暗藏無數後着，$P手足無措，攻勢不由自主停了下來！\n",
        "可$n手中$W騰空一卷，一聲脆響入磬，猛地向$P劈頭打下，嚇得$P往後倒退幾步。\n",
        "卻見$n力貫鞭梢，手中$W舞出滿天鞭影，排山倒海般掃向$P的全身，$P一招擊下，有如石沉大海，不覺呆住了。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
        {
                switch(query("skill_type", weapon) )
                {
                case "axe"   :return axe_msg[random(sizeof(axe_msg))];break;
                case "blade" :return blade_msg[random(sizeof(blade_msg))];break;
                case "club"  :return club_msg[random(sizeof(club_msg))];break;
                case "dagger":return dagger_msg[random(sizeof(dagger_msg))];break;
                case "hammer":return hammer_msg[random(sizeof(hammer_msg))];break;
                case "hook"  :return hook_msg[random(sizeof(hook_msg))];break;
                case "spear" :return spear_msg[random(sizeof(spear_msg))];break;
                case "staff" :return staff_msg[random(sizeof(staff_msg))];break;
                case "stick" :return stick_msg[random(sizeof(stick_msg))];break;
                case "sword" :return sword_msg[random(sizeof(sword_msg))];break;
                case "whip"  :return whip_msg[random(sizeof(whip_msg))];break;
                default      :return parry_msg[random(sizeof(parry_msg))];break;
                }
        }
        else return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int help(object me)
{
        write(HIC"\n基本招架："NOR"\n");
        write(@HELP

    招架的基本功。幾乎所有技擊技能均能激發為招架。

        學習要求：
                無
HELP
        );
        return 1;
}
