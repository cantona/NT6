// shane-bu.c 賞善罰惡簿

#include <armor.h>
#include <ansi.h>

inherit NECK;

void create()
{
        set_name("賞善罰惡簿", ({ "shane bu", "bu" }));
        set("long", "這是一本賞善罰惡簿，裏頭記載着江湖善惡。\n");
        set("weight", 300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("value", 500);
                set("material", "paper");
        }
        setup();
}