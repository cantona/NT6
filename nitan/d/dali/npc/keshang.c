// keshang.c

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("盛皮羅客商", ({ "ke shang", "shang" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long","這是一位從印度來的客商，皮膚黝黑，白布包頭，大理把印度人叫作盛皮羅。\n");
        set("combat_exp", 7000);
        set("str", 17);
        set("dex", 25);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver", 10);
}
