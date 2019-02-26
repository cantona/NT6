// tianchang-zhangpu.c 天長掌法譜
// By sir 5/20/2001

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"天長掌法譜" NOR, ({ "tianchang zhangpu","zhangpu", }));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
             set("unit", "本");
             set("long",
        "這是一本很破舊的小冊，上面好像還有一些小人揮舞拳腳的圖形。\n",
         );
         set("value", 0);
         set("material", "paper");
         set("skill", ([
                        "name":       "tianchang-zhang",
                        "family_name" : "關外胡家", 
                        "exp_required" : 10000,
                        "jing_cost":  30,
                        "difficulty": 20,
                        "max_skill":  80
                ]) );
        }
}