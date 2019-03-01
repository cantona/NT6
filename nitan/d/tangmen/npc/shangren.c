//shangren

inherit NPC;

void create()
{
        set_name("商人", ({ "shangren"}) );
        set("gender", "男性" );
        set("age", 36);
        set("long", "這是一位從中原來的商人。\n");
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set_skill("cuff", 30);
        set_skill("dodge", 50);
        set("chat_chance", 10);
        set("chat_msg", ({
                "商人心有余辜的說道：我幾乎死在唐門的暗器下！\n",
        }) );
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                "商人說道：我有幸從唐門的暗器下生還，現在居然要死在路邊！\n",
                }) );

        setup();
        add_money("silver", 50);
        carry_object("/clone/misc/cloth")->wear();
}
