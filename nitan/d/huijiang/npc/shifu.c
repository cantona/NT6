// shifu.c 大師傅

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("大師傅", ({ "shi fu", "shifu" }) );
        set("gender", "男性" );
        set("age", 42);
        set("long","這位大師傅是隨紅花會從江南來的，做得一手好蘇杭菜。\n他的絕活是東坡肉。可惜地處西北，回民禁豬，連豬肉都找不到。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("vendor_goods", ({
                "/d/hangzhou/npc/obj/fish",
                "/d/hangzhou/npc/obj/shrimp",
                "/d/hangzhou/npc/obj/chicken",
                "/d/hangzhou/npc/obj/geng",
                "/d/hangzhou/npc/obj/jiuping",
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}