// 大唐雙龍傳
 
// han.c 韓老闆

inherit NPC;
inherit F_DEALER;

void create()
{
       set_name("韓老闆", ({"han baoban","han","laoban"}));
       set("shop_id",({"han baoban","han","laoban"}));
       set("shop_title","太白酒樓老闆");
       set("gender", "男性");
        set("combat_exp", 100000);
       set("age", 26);
       set("per", 14);
       set("attitude", "friendly");
       set("shen_type", 1);
       set_skill("unarmed", 100);
        set("vendor_goods", ({
                "/d/gaoli/obj/jiuhu",
                "/d/gaoli/obj/liyu",
                "/d/gaoli/obj/rice",
                "/d/gaoli/obj/liji",
        }));

setup();
        carry_object("/d/gaoli/obj/pao4")->wear();


}

void init()
{
  ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
