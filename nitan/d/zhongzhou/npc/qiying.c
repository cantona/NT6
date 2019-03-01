inherit NPC;

void create()
{
        set_name("棄嬰", ({ "qi ying", "qi", "ying", "baby" }));
        set("gender", "男性");
        set("age", 3);
        set("long", "不知是誰家小姐的私生子，不要了丟在街上。\n");
        set("combat_exp", 0);
        set("attitude", "friendly");
        setup();
}