#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name("梅花鹿", ({ "meihua lu", "meihua", "lu" }));
        set("long", YEL "這是一隻行動敏捷的梅花鹿。\n" NOR);
        set("no_auto_kill", 1);

        set("age", 3);
        set("str", 20);
        set("dex", 25);
        set("max_qi", 800);
        set("max_jing", 800);
        set("combat_exp", 10000);

        set("power", 12);
        set("item1", __DIR__"item/lurou");
        set("item2", "/clone/herb/lurong");

        set_temp("apply/parry", 80);
        set_temp("apply/dodge", 100);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 100);
        set_temp("apply/unarmed_damage", 80);
        set_temp("apply/armor", 80);

        setup();
}