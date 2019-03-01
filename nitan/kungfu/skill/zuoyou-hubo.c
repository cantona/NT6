// zuoyou-hubo.c 左右互博
// by Doing Lu

inherit SKILL;

#include <ansi.h>

#define LEVEL_PER_LAYER         30
#define MAX_LAYER               10

int valid_learn(object me)
{
        int layer;
        int lvl;

        lvl = me->query_skill("zuoyou-hubo", 1);
        if( query("gender", me) == "無性" && lvl >= 50 )
                return notify_fail("你默默凝神，試圖分心二"
                                   "用，可是卻覺得陰陽失調，心浮氣躁。\n");

        if( me->query_skill("count",1) && !query("special_skill/capture", me) )
                return notify_fail("你受到陰陽八卦影響甚深，難以嘗" 
                                   "試更高深的分心之術。\n"); 

        if( query("int", me)>24 && query("int", me)<40 )
                return notify_fail("你覺得心煩意亂，難以嘗"
                                   "試更高深的分心之術。\n");

        if ((int)me->query_skill("force") < lvl * 3 / 2)
                return notify_fail("你的內功火候不夠，難以輕鬆自如的分運兩股內力。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("左右互博只能通過學習不斷提高。\n");
}

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("zuoyou-hubo", 1);
        layer = lvl / LEVEL_PER_LAYER;
        if (layer > MAX_LAYER) layer = MAX_LAYER;

        if (! layer)
        {
                tell_object(me, HIM "你潛心領悟左右互"
                                "博，若有所悟。\n" NOR);
        } else
        if ((lvl % LEVEL_PER_LAYER) == 0)
        {
                tell_object(me, HIM "你領悟了第" + chinese_number(layer) +
                            "層境界的左右互博的奧妙。\n" NOR);
        } else
                tell_object(me, HIM "你對第" + chinese_number(layer) +
                            "層境界的左右互博又加深了一點了解。\n" NOR);
}