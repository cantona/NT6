inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("菜販子", ({ "cai fan", "cai", "fan" }) );
        set("gender", "男性" );
        set("age", 32);
        set("long",
                "一個老實巴交的農民，賣些新鮮的蔬菜。\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
       set("str", 10);
       set("dex", 10);
       set("con", 10);
       set("int", 10);
        set("attitude", "peaceful");
       set_skill("dodge",20);
       set_skill("unarmed",20);
       set("chat_chance", 10);
       set("chat_msg", ({
                "菜販子叫道：賣新鮮的蘿蔔吆。\n",
                "菜販子叫道：賣新鮮的胡蘿蔔吆。\n",
                "菜販子叫道：賣新鮮的白菜吆。\n",
                "菜販子叫道：賣新鮮的大葱吆。\n",
                "菜販子叫道：賣新鮮的土豆吆。\n",
        }) );       

        set("vendor_goods", ({
                "/d/beijing/obj/luobo",
                "/d/beijing/obj/huluobo",
                "/d/beijing/obj/baicai",
                "/d/beijing/obj/dacong",
                "/d/beijing/obj/tudou",
        }) );

        setup();
       carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("coin", 80);
}
void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
