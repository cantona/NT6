// yrose.c

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIY "玫瑰" NOR, ({ "yellow rose", "rose" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", HIY "一朵黃色的玫瑰。\n" NOR);
                set("value", 10);
                set("material", "plant");
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", HIC "$N" HIC "輕輕地把一朵$n"
                                HIC "戴在頭上，襯得明眸皓齒更加動人。\n");
                set("remove_msg", HIC "$N" HIC "輕輕的嘆了"
                                  "口氣，把$n" HIC "從頭上摘了下來。\n");
        }
        setup();
}