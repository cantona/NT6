// boy.c

inherit NPC;

void create()
{
        set_name("男孩",({ "boy" }) );
        set("gender", "男性" );
        set("age", 13);
        set("long",
"這是個農家少年，大概因從小物農，雖然年紀不大，可已長的很粗壯了。\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
//      set("shen", 100);
        set_temp("apply/defense", 10);
        set("combat_exp", 100);
        set("attitude", "peaceful");

        setup();

        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("coin",100);
}
