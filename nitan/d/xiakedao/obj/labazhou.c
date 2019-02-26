 // labazhou.c
 // By Plzw 2004-08-29
 
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "臘八粥" NOR, ({ "laba zhou", "zhou" }) );
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "只見熱粥蒸氣上冒，兀自在一個個氣泡從粥底鑽將上來，一碗粥盡作深綠之色，瞧上去説不出的詭異。\n" NOR);
                set("value", 1);
                set("unit", "碗");
                set("only_do_effect", 1); 
        }
}

int do_effect(object me)
{
        // 已經喝過
        if( query("gift/labazhou", me) )
        {
                message_vision(HIY "$N" HIY "端氣粥碗，喝了個碗底朝天，但是覺得沒有什麼作用。\n" NOR, me);
                destruct(this_object());
                return 1;
        }
        // 產生效果
        if( query("story/labazhou", me) )
        {
                message_vision(HIY "$N" HIY "端起粥碗，只覺藥氣刺鼻，入口卻甜甜的並不難吃，頃刻間便喝了個碗底朝天。\n" NOR, me);
                if (random(10) == 1) 
                {
                        message_vision(HIC "$N" HIC "覺得這粥甜甜的，非常好喝。\n"NOR, me);
                        destruct(this_object());
                        return 1;  // 10% 的機率沒有效果
                }

                set("gift/labazhou", 1, me);

                message_vision(HIC "$N" HIC "胸中一股熱氣湧現上來，登時覺得精神為之一振。\n" NOR, me);

                destruct(this_object());
                return 1;
        }
        else
        // 沒有中故事的不能喝
                return notify_fail("這碗粥深綠如此，只映得人面俱碧，藥氣刺鼻，其毒可知，你忍不住便要嘔吐。\n");
}
