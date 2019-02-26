inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("胡掌櫃", ({ "hu zhanggui", "hu" }));
        set("title", "雜貨鋪老闆");
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 45);
        set("long",
                "別看胡掌櫃整天懶洋洋的，他心裏可盤算得精着呢。\n"+
                "在這北京城能混出個樣兒來，再怎麼也得有幾分本事。\n");
        set_skill("unarmed", 60);
        set_skill("parry", 60);
        set_skill("dodge", 60);
        set_temp("apply/damage", 25);

        set("combat_exp", 50000);
        set("attitude", "friendly");
        set("vendor_goods", ({
                "/d/city/obj/beixin",
              "/d/quanzhou/obj/xiuhua",
              "/d/city/obj/flower_shoe",
              "/d/city/obj/pink_cloth",
          }));
        
        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
