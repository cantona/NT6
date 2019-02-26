#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name("斑鳩", ({ "ban jiu", "ban", "jiu" }));
        set("long", WHT "這是一隻小斑鳩，在田地間跳上跳下。\n" NOR);
        set("no_auto_kill", 1);
        set("aves", 1);

        set("age", 1);
        set("str", 5);
        set("dex", 28);
        set("max_qi", 120);
        set("max_jing", 120);
        set("combat_exp", 1000);

        set("power", 3);

        set_temp("apply/dodge", 60);
        set_temp("apply/defense", 60);

        setup();
}