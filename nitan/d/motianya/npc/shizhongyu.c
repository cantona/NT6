// shizhongyu.c 石中玉

inherit NPC;

void create()
{
        set_name("石中玉", ({ "shi zhongyu", "shi", "zhongyu" }));
        set("gender", "男性");
        set("age", 20);
        set("str", 15);
        set("int", 45);
        set("con", 18);
        set("dex", 20);
        set("per", 30);
        set("long", "這是一個年輕公子，大約二十左右歲，面若中秋之月，色如春曉
之花，鬢若刀裁，眉如墨畫，鼻如懸膽，情若秋波，雖怒而時笑，即視而有情。\n");
        set("combat_exp", 100000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 30);
        set_skill("force", 30);
        set_skill("blade", 20);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("literate",100);

        set_skill("wuhu-duanmendao", 50);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 5);
        set_temp("apply/damage", 10);
        map_skill("blade", "wuhu-duanmendao");

        set("neili", 200);
        set("max_neili", 200);
        set("jiali", 20);
        set("inquiry", ([
                "俠客島" : "在泉州附近的一個小島。\n",
                "石破天" : "他...\n",
                "叮噹"   : "我好久沒見到她了，不知道她現在怎麼樣了。\n",
        ]) );
        set("chat_chance", 8);
        set("chat_msg", ({
                "\n石中玉説道: 叮噹，你在哪呀，我好想你呀。\n",
                "\n石中玉歎道: 也不知道我的叮噹怎麼樣了。\n",
                "\n石中玉説道: 臘八粥可是好東西...\n",
                "\n石中玉説道: 唉，誰能幫我殺了外面的老頭，兄弟我謝謝你了！\n",

        }));
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 10);
}

void die()
{
        say("\n石中玉説道：我還有個心願沒了，希望你能幫我照顧叮噹！\n");

        message_vision("石中玉喊着叮噹的名字，死了！\n", this_object());
        ::die();
}