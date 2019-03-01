#include <ansi.h>

inherit SMITH;

void create()
{
        set_name("鐵匠", ({ "tiejiang", "smith" }));
        set("title", "甲胄店老板");
        set("shen_type", 1);
        set("gender", "男性" );
        set("age", 33);
        set("long", "鐵匠正用鐵鉗夾住一塊紅熱的鐵塊放進爐中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                   __DIR__"obj/armor",
                   __DIR__"obj/beixin",
                   "/d/city/npc/obj/jinsijia",
        }));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}