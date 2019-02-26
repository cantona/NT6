// npc: /d/xingxiu/npc/shachong.c

inherit NPC;

void create()
{
        set_name("沙蟲", ({ "sha chong", "chong", "bug" }) );
        set("race", "昆蟲");
        set("subrace", "爬蟲");
        set("age", 3);
        set("long", "一隻黃褐色的小甲蟲，尾巴上有黃藍相間的環紋。你的直覺告訴\n"
"你它一定有毒。\n");
        set("attitude", "peaceful");
        set("combat_exp", 300);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 2);
        set_temp("apply/armor", 1);

        setup();
}

void die()
{
        object ob;
        message_vision("$N冒出一股綠水，死了。\n", this_object());
        ob = new(__DIR__"shachongke");
        ob->move(environment(this_object()));
        destruct(this_object());
}
