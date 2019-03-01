// smith.c

inherit SMITH;

void create()
{
        set_name("鐵匠", ({ "tie jiang", "smith" }));
        set("title", "鐵匠舖老板");
        set("shen_type", 1);

        set("gender", "男性" );
        set("age", 33);
        set("long", "鐵匠正用鐵鉗夾住一塊紅熱的鐵塊放進爐中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/d/city/obj/changjian",
                "/d/city/obj/hammer",
                "/d/beijing/obj/tudao",
                "/d/city/obj/dagger",
                "/d/xingxiu/obj/tiegun",
                "/d/city/obj/gangdao",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}
