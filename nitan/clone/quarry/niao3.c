#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(NOR + CYN "烏鴉" NOR, ({ "wu ya", "wu", "ya" }));
        set("long", CYN "這是一隻黑烏鴉，呱呱叫個不停。\n" NOR);
        set("no_auto_kill", 1);
        set("aves", 1);

        set("age", 1);
        set("str", 5);
        set("dex", 28);
        set("max_qi", 200);
        set("max_jing", 200);
        set("combat_exp", 1000);

        set("power", 4);

        set_temp("apply/dodge", 60);
        set_temp("apply/defense", 60);

        setup();
}