// Last Modified by Winder on May. 15 2001
// /d/suzhou/obj/axiang_xin.c

inherit ITEM;

void create()
{
        set_name("阿祥的信", ({ "letter", "axiang letter", "xin" }) );
        set("long", "這是阿祥寫給華赫艮的一封信，希望能送一套盜墓工具給持信人。\n");
        set_weight(2);
        seteuid(getuid());
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "封");
        }
        setup();
}
