// meigui.c

#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "玫瑰" NOR, ({ "red rose", "rose" }));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", HIR "一朵紅色的玫瑰，花瓣裏透出一股悽然。\n" NOR);
                set("value", 10);
                set("material", "plant");
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", HIC "$N" HIC "輕輕地把一朵$n"
                                HIC "戴在頭上，嫣然一笑。\n");
                set("remove_msg", HIC "$N" HIC "幽幽的歎了"
                                  "口氣，把$n" HIC "從頭上摘了下來。\n");
        }
        setup();
}