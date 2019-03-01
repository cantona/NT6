// /d/shenlong/obj/zihua.c
// Last Modified by winder on Jul. 12 2002

inherit ITEM;

void create()
{
        set_name("甲骨文", ({ "jiaguwen" }));
        set("weight", 1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","紙上一個個字都如蝌蚪一般。\n這是從五台山錦繡峰普濟寺中石碣上拓下來的甲骨文。\n");
                set("unit", "幅");
                set("value", 20);
        }

        setup();
}