// boy.c

inherit NPC;

void create()
{
        set_name("男孩",({ "boy" }) );
        set("gender", "男性" );
        set("age", 13);
        set("long",
"這是個漁家少年，大概由於長期在室外的緣故，皮膚已曬得黝黑，人也長得很粗壯了。\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);

        set_temp("apply/defense", 10);
        set("combat_exp", 100);
        set("attitude", "peaceful");

        setup();

        carry_object("/clone/misc/cloth")->wear();
        add_money("coin",100);
}
