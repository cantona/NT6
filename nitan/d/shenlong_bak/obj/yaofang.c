// /d/shenlong/obj/yaofang.c  藥方
// Last Modified by winder on Jul. 12 2002

inherit ITEM;

void create()
{
        set_name("藥方", ({"yaofang"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long","上面密密麻麻寫滿了字，列出各類藥草，配制方法和服法用途。\n");
                set("material", "paper");
        }
}