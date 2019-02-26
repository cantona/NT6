#include <ansi.h> 

inherit "/inherit/char/smith.c"; 

void create()
{
        set_name("鐵匠", ({ "tiejiang", "smith" }));
        set("title", "鐵匠鋪老闆");
        set("shen_type", 1);

        set("gender", "男性" );
        set("age", 33);
        set("long", "鐵匠正用鐵鉗夾住一塊紅熱的鐵塊放進爐中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                   "/d/jingzhou/obj/changjian",
                   "/d/jingzhou/obj/gangdao",
                  "/d/jingzhou/obj/armor",
                  "/d/jingzhou/obj/beixin",
                          }));


        setup();

        carry_object("/clone/misc/cloth")->wear();
}