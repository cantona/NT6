// pihuoshang.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("皮貨商", ({ "pihuo shang", "pihuo", "shang" }) );
        set("gender", "男性" );
        set("age", 25);
        set("long",
                "這是一位皮貨商，他自己也是滿身皮裘。\n");
        set("combat_exp", 5000);
        set("attitude", "friendly");
        set_temp("apply/attack", 20);
        set_temp("apply/defense", 20);
        set_temp("apply/armor", 20);
        set_temp("apply/damage", 30);

        set("vendor_goods", ({
                __DIR__"obj/piqiu",
        }));
        set("chat_chance", 20);
        set("chat_msg", ({
                (: random_move :)
        }) );
        setup();
        carry_object(__DIR__"obj/piqiu")->wear();
}
void init()
{        
        object ob; 

        add_action("do_buy", "buy");
        add_action("do_list", "list");
        ::init();
}
