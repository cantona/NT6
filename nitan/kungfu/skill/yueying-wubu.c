// yueying-wubu.c 月影舞步
// Last Modified by sir on 10.18.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
"$n身形一晃，纖腰一扭，一招"HIY"「星河鷺起」"NOR"，彈地而起。\n",
"$n一招"HIM"「歌盡桃花扇底風」"NOR"，$N只覺眼前一花，不見了$n的身影。\n",
"$n一招"HIC"「掃盡浮雲風不定」"NOR"，身形微晃，有驚無險地避開了$N這一招。\n",
"只見$n身子向後一翻，一招"MAG"「縹渺孤鴻影」"NOR"，後盪而起，掠向一旁。\n" ,
"$n一招"HIG"「起舞弄清影」"NOR"，長袖翻飛，躲過$N這一招。\n",
"卻見$n"GRN"「萬頃江田一鷺飛」"NOR"，沖天而起，一波三折，端是美觀。\n",
"可是$n一個"HIR"「流水落花春去也」"NOR"，側身一讓，$N這一招撲了個空。\n",
"只見$n一招"HIW"「月輪穿沼水無痕」"NOR"，倒掠身形，凌空兩個翻轉，退出兩丈開外。\n",
"$n提氣上升，意存玉枕，一招"HIB"「月在青天影在波」"NOR"，身子飄然而起。\n",
"$n面露淡淡的微笑，柳腰一轉，一招"HIM"「月兒倒鉤」"NOR"，不慌不忙的輕輕閃過$N的殺著。\n",
"$n口中輕□"HIM"「輕問清風聲，聞聲不見人」"NOR"，一雙金蓮猶如幻化千百雙，$N的眼前瞬間出現好
幾個人的身影，不知道哪個才是真的。\n",
"只見$n裙角一擺，$n的身影已轉到$N身後，並對著$N露出淺淺的一笑。\n",
"$n輕輕的原地旋轉，舞出了"HIM"「落花散月，流水耀星」"NOR"，身子忽快忽慢，忽前忽後，實在是美
不勝收，只見$N呆呆站立，不曉得在想什麼。\n",
"$n袖子輕掩嘴角，左手輕捻，一招"HIM"「麒麟天地行，鳳凰開天際」"NOR"，舞出了月影舞步的精義
，$n身影輕輕地從$N的身邊飄過。\n",
"但是$n不慌不忙，左腳輕抬，一式"HIM"「天馬追月」"NOR"，$n的身影已出現在半空中，有如蝴蝶般，輕輕地飄落在$N身影的一丈外。\n",
"月影微步的奧義，"HIM"「行者莫不住一腳，聽君輕唱仕女音」"NOR"，在$n的舞動下，有如一朵盛開的
鮮花，鮮艷的彩蝶。\n"
});

int valid_enable(string usage) { return (usage=="dodge") || (usage=="move"); }
int valid_learn(object me)
{
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<10 || query("neili", me)<2 )
                return notify_fail("你的體力太差了，不能練月影舞步。\n");
        me->receive_damage("qi", 10);
        addn("neili", -2, me);
        return 1;
}
string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
string perform_action_file(string action)
{
        return __DIR__"yueying-wubu/" + action;
}

int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) {
        if( query("class", me) == "dancer")return 1.5;
        else return 1.0;
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("yueying-wubu", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
int help(object me)
{
        write(HIC"\n月影舞步："NOR"\n");
        write(@HELP

    月影舞步天山靈鷲宮輕功身法。

        學習要求：
        八荒六合唯我獨尊功10級
HELP
        );
        return 1;
}
