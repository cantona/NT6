inherit NPC;

void create()
{
        set_name("丫環", ({ "ya huan","ya","huan"}) );
        set("gender", "女性" );
        set("age", 14+random(10));
        set("long", "這是一個小丫環，容貌清秀脫俗。\n");
        set("shen_type", 1);
        set("combat_exp", 3000);
        set("str", 18);
        set("dex", 18);
        set("con", 18);
        set("int", 19);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}