// xueshitiao.c 雪獅跳

inherit SKILL;

string *dodge_msg = ({
        "$n一式「冰消雪融」，一下滑到丈外開去，把$N攻勢化於無形。\n",
        "$n使出「金獅狂舞」，一個筋斗從$N頭上一翻而過，$N打$n不着。\n",
        "$n腳步虛踩，忽左而右，使出「雪入黃河」從$N的腋下穿到$P身後。\n",
        "$n微笑中後退兩步，身子一頓，一式「飛雪藏形」躲過$N這一擊。\n",
        "$n掉轉身子，輕輕一躍，一式「獅子搖頭」輕描淡寫地化開$N這一招。\n",
        "$n身子向上一縱，使出一式「踏雪無痕」躍起數尺，飄然落到一旁。\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太差了，不能練雪獅跳。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
        return 1;
}

