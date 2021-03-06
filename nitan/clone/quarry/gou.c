#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name("野狗", ({ "ye gou", "ye", "gou" }));
        set("long", YEL "這是一隻飢餓兇猛，吐着長舌頭的野狗。\n" NOR);

        set("age", 1);
        set("str", 18);
        set("dex", 30);
        set("max_qi", 500);
        set("max_jing", 500);
        set("combat_exp", 6000);

        set("power", 12);
        set("item1", __DIR__"item/gourou");
        set("item2", __DIR__"item/goupi");

        set_temp("apply/parry", 80);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 60);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 60);
        set_temp("apply/armor", 80);

        setup();
}