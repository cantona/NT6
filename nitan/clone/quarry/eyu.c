#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(NOR + CYN "鱷魚" NOR, ({ "e yu", "e", "yu" }));
        set("long", CYN "這是一只體形龐大的鱷魚，相當的兇猛。\n" NOR);

        set("age", 3);
        set("str", 35);
        set("dex", 50);
        set("max_qi", 6000);
        set("max_jing", 6000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("combat_exp", 600000);

        set("power", 50);
        set("item1", __DIR__"item/eyurou");
        set("item2", __DIR__"item/eyupi");

        set_temp("apply/force", 220);
        set_temp("apply/parry", 220);
        set_temp("apply/dodge", 220);
        set_temp("apply/attack", 280);
        set_temp("apply/defense", 280);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 300);

        setup();
}