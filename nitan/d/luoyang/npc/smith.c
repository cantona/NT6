#include <ansi.h> 

inherit "/inherit/char/smith.c"; 

void create()
{
        set_name("鐵匠", ({ "tiejiang", "smith" }));
        set("title", "打鐵舖老板");
        set("shen_type", 1);
        set("gender", "男性" );
        set("age", 33);
        set("long", "鐵匠正用鐵鉗夾住一塊紅熱的鐵塊放進爐中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/clone/weapon/changjian",
                "/clone/weapon/hammer",
                "/clone/weapon/tudao",
                "/clone/weapon/dagger",
                "/clone/weapon/tiegun",
                "/clone/weapon/gangdao",
                "/clone/cloth/tiejia",
                "/d/item/obj/jingtie",
                "/clone/weapon/arrow",
                "/clone/weapon/wolfarrow",
                "/clone/weapon/bow",
                "/clone/weapon/longbow",
        }));
        setup();

        carry_object("/clone/misc/cloth")->wear();
}
