// xishanxinglvtu.c
// Last Modified by winder on Nov. 17 2000

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIG"溪山行旅圖"NOR,({"painting","xi shan xing lv tu","tu"}) );
        set("taskobj", 1);
        set("long","這是據説已經失傳了的范寬真跡，對於愛畫之人，算是無價之寶了。\n");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "幅");
                set("value", 0);
                set_weight(20);
        }
        setup();
}
