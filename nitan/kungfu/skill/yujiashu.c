// yujiashu.c 瑜珈術

inherit FORCE;

string *dodge_msg = ({
        "$n前後腳腳尖腳跟相靠，身體如行雲流水般滑出丈余。\n",
        "$n雙臂前伸，全身貼地平飛，頓時閃過了$N的凌厲攻勢。\n",
        "$n足不動，手不抬，一轉眼間便繞到了$N的身後。\n",
        "$n一轉身間，四面八方飄動著無數個$n的身影，令$N手無足措。\n",
        "$n全身筆直，拔地而起，在半空中一轉，已落到幾丈遠的地方。\n",
        "$n兩臂鵬舉如翼，在剌剌風聲中，從$N頭頂橫躍而過。\n",
        "$n雙腳點地，全身化為一道白影，急速繞著$N打了幾轉。\n",
        "$n身體如陀螺般急轉，氣流形成一個個漩渦，令$N陷身其間，動彈不得。\n",
});

int valid_enable(string usage)
{
        return usage == "force" || usage == "dodge";
}

int valid_force(string force)
{
        return force == "hunyuan-yiqi" ||
               force == "shaolin-xinfa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("yujiashu", 1);
    return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
            if (me->query_skill("force", 1) < 100)
                return notify_fail("你的基本內功火候不夠，無法學習瑜珈術！\n");

        if( query("gender", me) != "男性" )
                return notify_fail("你不是男性，無法練習瑜珈術神功。\n");

        return ::valid_learn(me);
}


int practice_skill(object me)
{
        return notify_fail("瑜珈術只能用學(learn)的來增加熟練度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"yujiashu/" + func;
}