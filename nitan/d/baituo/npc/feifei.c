inherit NPC;

void create()
{
        set_name("廚師", ({ "chu shi", "chu", "shi" }));
        set("gender", "男性" );
        set("age", 35);
        set("long", "一個肥頭大耳的廚師，兩隻小眼睛不停地眨巴着。\n");
        set("shen_type", -1);
        set("combat_exp", 10000);
        set("str", 20);
        set("dex", 22);
        set("con", 20);
        set("int", 21);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 3);
}