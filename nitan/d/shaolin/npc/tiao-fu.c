// seller.c

inherit NPC;

void create()
{
        set_name("挑夫", ({ "tiao fu", "porter" }) );
        set("gender", "男性" );
        set("age", 28);
        set("long",
                "這是個老實巴交的窮挑夫，長得膀闊腰圓，一身肌肉。\n");
//        set("shen_type", 1);
        set("combat_exp", 1000);
        set("str", 25);
        set("dex", 22);
        set("con", 20);
        set("int", 15);
        set("attitude", "heroism");

        setup();
        carry_object("/clone/misc/cloth")->wear();

}
