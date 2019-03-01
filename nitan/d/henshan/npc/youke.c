inherit NPC;

void create()
{
    set_name("遊客", ({ "you ke","ke","you"}));
    set("gender", "男性");
    set("age", 25);
    set("long", "這是來衡山旅遊的遊客。\n");
    set("combat_exp", 2000);
    set("attitude", "friendly");
    setup();
    carry_object("/clone/misc/cloth")->wear();
    add_money("silver", 5);
}