inherit KNOWER;

void create()
{
        set_name("茶博士", ({ "cha boshi", "cha", "boshi" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "一個在茶館裏以説書為生的老頭。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
       set("str", 10);
       set("dex", 10);
       set("con", 10);
       set("int", 10);
        set("attitude", "peaceful");
       set_skill("dodge",20);
       set_skill("unarmed",20);
       set("chat_chance", 1);
       set("chat_msg", ({
                "茶博士搖頭晃腦的説着書。\n",
        }) );       
        setup();
       carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("silver", 2);
}
