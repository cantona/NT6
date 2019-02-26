inherit NPC;

void create()
{
        set_name("陳老頭", ({ "chen laotou", "chen", "laotou" }) );
         set("title", "客店老闆");
        set("gender", "男性" );
        set("age", 32);
        set("long",
              "一個年過六旬的小老頭，他就是這家小客店的老闆。\n");
        set("shen_type", 1);
        set("combat_exp", 3000);
        set("str", 10);
        set("dex", 10);
        set("con", 10);
        set("int", 10);
        set("attitude", "peaceful");
        set_skill("dodge",10);
        set_skill("unarmed",10);
        set("chat_chance", 10);
        set("chat_msg", ({
                "陳老頭苦笑着對你説道：這位客官，真是對不住，小店已經客滿了。\n",
                "陳老頭一邊哼着小調一邊拿着抹布打整衞生。\n",
                "陳老頭一個人嘀咕道：桌子也該換得了。\n",
        }) );       

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("silver", 20);
}
