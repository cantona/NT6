#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW "劍氣" NOR, ({ "jian qi", "jian", "qi" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("long", HIW "這是一束由內力化成的劍氣。\n" NOR);
                set("value", 0);
                set("no_drop", "劍氣是由你的內力化成，如何能夠丟棄？\n");
                set("material", "air");
                set("power", 1000);
        }
        init_sword(query("power"));
        setup();
}