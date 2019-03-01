//biaotou.c

inherit NPC;

void create()
{
        string *surname=({"趙","錢","孫","李","周","吳","鄭","王",});
        set_name(surname[random(sizeof(surname))]+"鏢頭", ({ "biaoshi", "biao"}) );
        set("gender", "男性" );
        set("age", 25);
        set("str", 45);
        set("cor", 50);
        set("cps", 35);
        set("int", 20);
        set("per", 20);
        set("kar", 15);
        set("long", "一位訓練有素的鏢頭。\n");
        set("combat_exp", 70000);
        set("attitude", "heroism");
        set_skill("parry", 90);
        set_skill("dodge", 100);
        
        setup();
        carry_object("/d/changan/npc/obj/jinzhuang")->wear();
        add_money("silver",30);
}