// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// skull.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit TESSERA;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(HIR "神之紅寶石" NOR, ({ "magic ruby" }) );  /* NAME_EXIT  */
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", HIR "一顆煥發著奇異的光彩的紅寶石，給人以不同尋常的感覺。\n" NOR);  /* DBASE_EXIT  */
                set("value", 200000);
                set("unit", "顆");
                set("level", 4);
                set("material", "mruby");
                set("can_be_enchased", 1);
                set("magic/type", "fire");
                set("magic/power", 500);
                set("auto_load", 1);
        }
        set("no_identify", 1);
	setup();
}

