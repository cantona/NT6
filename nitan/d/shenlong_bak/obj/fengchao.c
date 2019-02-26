// /d/shenlong/obj/fengchao.c
// Last Modified by winder on Jul. 12 2002

inherit ITEM;

void create()
{
        set_name("蜂巢", ({ "fengchao", "chao" }));
        set("unit", "只");
        set("long", "這是一隻六角形的毒蜂巢，是稀有的藥材。\n");
        set("value", 2000);
        setup();
}