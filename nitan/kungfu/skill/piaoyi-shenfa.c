// piaoyi-shenfa.c 飄翼身法
// by Lonely

inherit SKILL;

string *dodge_msg = ({
        "$n身子猛然貼地向後滑出丈余，好似有人用繩縛住以快迅無綸的手法向後扯動一般。\n",
        "$n雙膝不曲，腰不彎，陡然滑出，身子之僵硬怪詭，又和僵屍無異。\n",
        "不見$n提足抬腳，突然之間倒退丈余，一轉身。已在數丈之外。\n",
        "只聽得呼的一聲，$n身子筆直的向空中飛起，直至丈余高，躲過了這一招。\n",
        "$n陡然身形拔起，在空中急速盤旋，連轉四個圈子，癒轉癒高，一個轉折落在數丈之外。\n",
        "$n繞著圈子，東轉西閃，滑如遊魚，在間不容發之際躲過了這招。\n",
        "$n大吃一驚，不及趨避，足尖使勁，拔身急起，斜飛而上，及時的躲過了這一招。\n",
        "$n有如一溜輕煙，左一閃，右一趨，正轉一圈，反轉一圈，已閃了開去。\n"
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(object me)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太差了，不能練飄翼身法。\n");
        if( query("neili", me)<30 )
                return notify_fail("你的內力不夠。\n");
        me->receive_damage("qi", 30);
        addn("neili", -20, me);
        return 1;
}

int query_effect_dodge(object victim, object me)
{
        int lvl;

        lvl = me->query_skill("piaoyi-shenfa", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 100;
        if (lvl < 280) return 150;
        if (lvl < 350) return 200;
        return 250;
}

