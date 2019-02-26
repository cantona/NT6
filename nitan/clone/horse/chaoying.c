inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIM "超影" NOR, ({ "chao ying", "chao", "ying"}));
        set("long", HIC "八龍之駿，一名超影，逐日而追。\n" HIY
                    "摘自本遊戲網遊小説《終極地獄》。\n" NOR);
        set("tili", 20000);
        set("max_tili", 20000);
        set("level", 5);

        set("can_go_any", 1);

        setup();
}
