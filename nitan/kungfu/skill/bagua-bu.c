inherit SKILL;

string *dodge_msg = ({
    "$n雙臂置於身後，不急不緩，昂首從$N眼前跨過，正是八卦步起手式「開步」。\n",
    "$n一式「闔步」，左手一揚，身行一晃，緩緩的向後一退，輕鬆讓過了$N的凌厲攻勢。\n",
    "$n一式「四正步」，前後腳腳尖腳跟相靠，身體如行雲流水般向左滑出四步。\n",
    "$n足不動，手不抬，一轉眼間便繞到了$N的身後，卻是一式「四奇步」的身法。\n",
    "$n一式「天地風雲」，全身化為一道白影，忽的拔地而起,在半空中一個空翻，已落到幾丈遠的地方。\n",
    "$n一式「龍虎鳥蜿」，身體如一隻金雁般行雲流水，又宛若一條矯矢蒼龍急速盤旋，瞬間滑出丈餘。\n",
    "$n一招「坐乾踏坤」，身隨意轉，瞻之在前，忽焉在後，倏地往一旁挪開了三尺。\n",
    "可是$n的身形陡地變得飄忽不定，竟絲毫不着力，令$N無法看清，正是一式「移艮走巽」的身法。\n",
    "$n一式「跑坎遊離」，雙臂前伸，全身貼地平飛，猶如在水面滑行一般，頓時閃過了$N的凌厲攻勢。\n",
    "$n一式「離震回兑」，兩臂鵬舉如翼，在剌剌風聲中，輕盈地一躍，$N以為$n要繞到自己的身後，但再定睛\n"
    "一看，$n卻又回到了原來的位置。\n",
    "$n陡然使出一式「八面埋伏」，身形由一分二，由二變四，又四為八，猶如鬼魅忽隱忽現，令人難以琢磨。\n"
});

int valid_enable(string usage)
{
        return (usage == "dodge") ||
               (usage == "move");
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( query("qi", me)<50 )
        return notify_fail("你的體力太差了，不能練八卦步。\n");

    me->receive_damage("qi", 40);
    return 1;
}