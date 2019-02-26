// Room: /d/gumu/obj/bed.c 寒玉牀
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC"寒玉牀"NOR, ({"hanyu chuang","bed","chuang"}));
        set_weight(2500000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", HIC"此牀看上去普普通通尤如青石，卻是江湖中人人夢寐以求的武林至寶寒玉牀，傳説中此牀可療任何內外傷病，有迴天之效，小龍女當年遭受金輪法王和全真五子合力一擊，能逃出生天，此牀功不可沒，更有人言此牀可速成武功，大益於內功修為。\n"NOR);
                set("no_get", 1);
                set("value", 800000);
                setup();
        }
}
