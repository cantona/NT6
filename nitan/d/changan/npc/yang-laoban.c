//yang-laoban.c

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("楊老闆", ({ "yang laoban", "yang","laoban" }));
        set("title", "望星樓老闆");
        set("shen_type", 1);
        set("str", 24);
        set("gender", "男性");
        set("age", 55);
        set("long", "楊老闆不但是這兒的掌櫃，還是這兒的大廚，\n並且燒得一手好菜。\n");
        set("combat_exp", 50000);
        set("attitude", "friendly");
        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set("vendor_goods", ({
                "/d/changan/npc/obj/zuixunfeng",
                "/d/changan/npc/obj/snxiangji",
                "/d/changan/npc/obj/lhjiyu",
        }));

       setup();
       carry_object("/d/changan/npc/obj/choupao")->wear();
       add_money("silver", 50);
}

void init()
{
       add_action("do_buy", "buy");
       add_action("do_list", "list");         
}