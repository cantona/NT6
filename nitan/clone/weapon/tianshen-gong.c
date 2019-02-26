// longbow.c

#include <ansi.h>

inherit __DIR__"bow";

void create()
{
        set_name(HIY "天神弓" NOR, ({ "tianshen gong", "bow", "tianshen", "gong" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "張");
                set("long", "這是一張巨大的弓，命曰：天神，傳説乃上天賜予成吉思汗的寶物，據説此弓百發百中，例無虛發。。\n");
                                set("value", 80000);
                set("accuracy", 2000);   // 準確度150%
        }
        setup();
}
