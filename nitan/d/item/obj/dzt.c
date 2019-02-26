// /u/hotjc/dzt.c

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG "打造台" NOR, ({ "dazao tai", "tai" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
          set("long", HIG @LONG
這是一個鍛造、改造、強化、升級裝備的打造台。
鑲嵌物品              enchase
附魔屬性              enchant
裝備打孔              notch
寶石合併              combine
洗 裝 備              melt
裝備強化              steady
裝備改造              increase
裝備升級              forging
LONG NOR );
                set("value", 2000);
                set("unit", "片");
                set("no_get", 1);
                set("auto_load", 1);
        }
        setup();
}