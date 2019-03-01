#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + YEL "檀木古盒" NOR, ({ "tanmu guhe", "tanmu", "guhe" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "這是一個檀木沉香盒，看樣子已"
                            "有很長的年時了。\n" NOR);
                set("unit", "個");
                set("value", 15000);
                set("material", "wood");
        }
}