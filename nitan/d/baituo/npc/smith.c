inherit "/inherit/char/smith.c";

void create()
{
        set_name("鐵匠", ({ "tie jiang", "tie", "jiang", "smith" }));
        set("title", "鐵匠鋪老闆");
        set("shen_type", 1);

        set("gender", "男性" );
        set("age", 33);
        set("long", "鐵匠正用鐵鉗夾住一塊紅熱的鐵塊放進爐中。\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                   "/clone/weapon/changjian",
                   "/clone/weapon/tudao",
                   "/clone/weapon/tiegun",
                   "/clone/weapon/gangdao",
                   "/clone/cloth/tiejia",
        }));

        set("inquiry", ([
                "工作" : (: ask_me :),
                "job"  : (: ask_me :),
        ]));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}