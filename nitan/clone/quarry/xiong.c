#include <ansi.h>
inherit QUARRY;

void create()
{
        set_name(NOR + WHT "灰熊" NOR, ({ "hui xiong", "hui", "xiong" }));
        set("long", WHT "這是一隻身材巨大，兇猛異常的灰熊。\n" NOR);

        set("age", 6);
        set("str", 50);
        set("dex", 20);
        set("con", 50);
        set("max_qi", 5000);
        set("max_jing", 5000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("combat_exp", 300000);

        set("power", 45);
        set("item1", __DIR__"item/xiongrou");
        set("item2", __DIR__"item/xiongpi");
        set("item3", "/clone/herb/xiongdan");

        set_temp("apply/force", 120);
        set_temp("apply/parry", 120);
        set_temp("apply/dodge", 120);
        set_temp("apply/attack", 110);
        set_temp("apply/defense", 110);
        set_temp("apply/unarmed_damage", 130);
        set_temp("apply/armor", 130);

        setup();
}