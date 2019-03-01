// kuihua-shengong.c

#include <ansi.h>
inherit FORCE;

string *parry_msg = ({
"$n左一撥，右一撥，上一撥，下一撥，將$N的招數盡數撥開。這四下撥擋，周身竟無半分破綻。\n",
"$n右手大拇指和食指捏住一根繡花針，向上一舉，擋住來勢，$N的招式便使不下去。\n",
"$n不擋不閃，左手食指顫動，向$N的左目急刺，竟是兩敗俱傷的打法。\n",
"$n左撥右擋，兀自好整以暇的嘖嘖對$N連讚：“好功夫，好功夫！”\n",
"$n從懷中取出一塊雪白的綢帕，輕輕抹了抹臉，簡直便如是戲台上的花旦。$N一呆，竟停住了自己的招式。\n"
});

string  *msg = ({
"$N身形一變，如閃電般欺到$n身前，相距不過一尺，手中$w已經刺到$n的$l",
"但見紅影閃處，$N手中的$w向$n的$l直戳而來，勢如奔雷，避不可避",
"$N欺身而上，左手在$n的肩上一拍再橫飛出去，而手中的$w卻指向$n的$l",
"$N突然躍起丈余，$n一抬頭，發現空中並無$N的身影，而一股寒氣卻從後襲來",
"$N左一撥，右一撥，上一撥，下一撥，將$n的招數盡數撥開，右手一轉，刺向$n",
"驀地裡$N空手猱身而上，雙手擒拿點拍，攻勢凌厲之極，乘$n驚駭之際彈出$w刺向$n",
"$N身形飄忽，有如鬼魅，轉了幾轉，移步向西，一劍刺向$n。出手之奇之快，直是匪夷所思",
"$N腳下一頓，站立片刻，忽向$n的左後方滑出丈余，跟著快速無倫的回到原處",
"$N潛運內力，忽進忽退，繞著$n身子亂轉，手中$w所使劍招也如狂風驟雨一般，越來越快",
"突然$N手中$w向上一撩，就在$n微一分神之際直取$n的$l，勢道勁急無倫"NOR,
"就在$n一呆之際，$N向右躍開兩尺，右足剛著地，身子跟著彈起，刷刷兩劍，向$n攻去",
"$N忽然化身為二，分出左右兩個身影高速滑向$n，手中$w幻化不定，直刺$n的$l",
"$n只覺眼前一花，似乎見到$N身形一幌，但隨即又見$N回到原地，卻似從未離開",
"$N一聲尖叫，飛身縱起，在半空中一轉，快絕無比的飛落下來，手中$w破空直刺$n$l",
"$N忽然化身為二，分出上下兩個身影高速滑向$n，手中$w變幻莫測，直刺$n的$l",
"$N的身形如鬼如魅，飄忽來去，直似輕煙，手中的$w卻總是對著$n身子",
"$N一聲冷笑，驀地裡疾沖上前，當真是動如脫兔，一瞬之間，與$n相距已不到一尺，兩人的鼻子幾乎要碰在一起",
"$N右手伸出，在$n手腕上迅速無比的一按，跟著手臂回轉，又在$n手肘下一推",
"$N一劍挺刺，極盡都雅，神態之中，竟大有華山派女弟子所學‘玉女劍十九式’的風姿，只是帶著三分陰森森的邪氣",
"$N左手一圈，倒轉$w，驀地刺出，刷刷刷急攻三式，招招盡是指向$n的要害"
});

int valid_enable(string usage) 
{ 
    return usage == "sword" || usage == "force" || usage =="parry"; 
}
mapping query_action(object me, object weapon)
{               
       return ([
          "action":msg[random(sizeof(msg))],
          "damage":(random(4)+1)*60,
          "damage_type": "刺傷",
          "dodge": random(30)+10,
          "force":(random(200)+60),
       ]);
}
string query_parry_msg()
{
        return parry_msg[random(sizeof(parry_msg))];
}
int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "sword")
               return notify_fail("你使用的武器不對。\n");
       if ((int)me->query_skill("kuihua-shengong", 1) < 180)
               return notify_fail("你還沒有領會葵花神功的精髓，不能自行練習。\n");
       if ((int)me->query("qi") < 30)
               return notify_fail("你的體力太低了。\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("你的內力不夠了。\n");
       me->receive_damage("qi", 50);
       me->add("neili", -20);
       return 1;
}

int valid_learn(object me)
{
        if ((int)me->query_skill("kuihua-shengong", 1) < 180)
        return notify_fail("葵花神功只能通過研習《葵花寶典》來學習。\n"); 
}

string perform_action_file(string action)
{
        return __DIR__"kuihua-shengong/" + action;
}

string exert_function_file(string func)
{
       return __DIR__"kuihua-shengong/" + func;
}
