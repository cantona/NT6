inherit NPC;

void create()
{
        set_name("富家弟子", ({ "fujia dizi", "dizi", "fujia" }) );
        set("gender", "男性" );
        set("age", 21);
        set("long",
                "一個白白胖胖的年輕人，一看就知道是嬌生慣養慣了的。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 10);
        set("dex", 10);
        set("con", 10);
        set("int", 10);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);

        setup();
        carry_object("/d/beijing/npc/obj/cloth4")->wear();
        add_money("silver", 20);
}
