// gongnv.c
inherit NPC;

void create()
{
        set_name("宮女", ({ "gong nv", "nv"}) );
        set("gender", "女性" );
        set("age", 14+random(10));
        set("long", "這是一個宮女,容貌很清秀,看來挺能幹.\n");
        set("shen_type", 1);
        set("combat_exp", 3000);
        set("per", 26);
        set("str", 18);
        set("dex", 18);
        set("con", 18);
        set("int", 19);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}