// sanshou.c 岳家散手
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *msg = ({
"$N飛身躍起，半空中一腳踢向$n面門，卻是個虛招。 \n説時遲那時快，只見$N一個倒翻，一招「過眼煙雲」，雙掌已到了$n的$l",
"$N使一招「塵土雲月」，左拳虛晃右掌斜飛，擊向$n的$l",
"$N一招「朝天闕」，斜步扭身，手肘猛地向$n的胸口撞去",
"$N左掌斜穿，右手前探做虎爪，一招「壯志飢餐」抓向$n的$l",
"$N的左手虛引額前，驀地進步跟身，右手並指如劍，一招「笑談渴飲」刺向$n的$l",
"$N提步上前，一記「莫等閒」，雙掌緩緩推出，擊向$n的前胸",
"$N腳踩七星方位，雙掌翻飛施出「瀟瀟雨歇」，無數掌影擊向$n的$l",
"$N大喝一聲，一招「怒髮衝冠」，雙掌帶着天罡正氣，迅捷無比的擊向$n的$l",
"$N左手遞出，長臂竟如殘月般彎轉，一招「從頭收拾舊山河」右手反手對準$n$l扎去",
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo=="changquan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練岳家散手必須空手。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("jing", me)<30 )
                return notify_fail("你的精神無法集中了，休息一下再練吧。\n");
        if( query("qi", me)<30 )
                return notify_fail("你現在手足痠軟，休息一下再練吧。\n");
        if( query("neili", me)<10 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 30);
        addn("neili", -10, me);

        return 1;
}
mapping query_action(object me, object weapon)
{
        return ([
                "action" : msg[random(sizeof(msg))],
                "dodge"  : -30+random(30),
                "parry"  : 30+random(30),
                "force"  : 50+random(100),
                "damage_type" : random(2)?"內傷":"瘀傷",
        ]);
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n岳家散手："NOR"\n");
        write(@HELP

    【岳家散手】又稱岳氏散手、岳氏散掌，屬於岳家拳。據考證，
宋代著名抗金將領岳飛曾創編子母拳，後其子嶽震、嶽霆隱居於湖北
黃梅，傳下了岳家拳。金元時期，禁止練武，傳統武術受到摧殘，嶽
家拳也難倖免。降至明清，武術鼎盛，岳家拳才得以發展。史料記載，
明末清初的武術家訪名師於終南山，得嶽武穆拳譜，據其拳理創編形
意拳而自成一派。後來岳家拳主要流行於河北一帶。清末河北雄縣人
劉侍俊任宮廷護衞神機軍營教官，曾教授“岳氏散手”。岳氏散手共三
十二路一百七十三手，主要特點為以靜待動，以快制勝，出手兇猛，
見縫插針。強調心雄膽大，勇猛果斷，出手狠毒，迅疾飛快。平常對
指頭功夫要求很嚴，交手時不講情面，人稱一毒，二狠，三快。岳家
散手的主要方法，有刁卡擠靠、劈打捆肘等，每一手法都有一連串的
接應手法，“手起足要落，足落手要起”，或手打，或肘頂肩撞，一環
扣一環，隨機生變，貼身進步，見縫插針。


        學習要求：
                無
HELP
        );
        return 1;
}