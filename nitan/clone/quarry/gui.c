#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(NOR + CYN "烏龜" NOR, ({ "wu gui", "wu", "gui" }));
        set("long", CYN "這是一隻大烏龜，看來歲數不小了。\n" NOR);
        set("no_auto_kill", 1);

        set("age", 28);
        set("str", 5);
        set("dex", 2);
        set("con", 20);
        set("max_qi", 300);
        set("max_jing", 300);
        set("combat_exp", 1000);

        set("power", 5);
        set("item1", "/clone/herb/guijia");

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 5);
        set_temp("apply/armor", 200);

        setup();
}