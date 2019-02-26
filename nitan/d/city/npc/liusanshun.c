// liusanshun.c 劉三順
// Last Modified by Winder on Jul. 15 2000

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("劉三順", ({ "liu sanshun","liu" }) );
        set("title","夥計");
        set("gender", "男性" );
        set("age", 18);
        set("long", "劉三順是這裏竹器店剛僱的夥計，手腳麻利，跑前跑後的，替老闆省了不少心。\n");
        set("attitude","friendly");
        set("inquiry",([
                "竹器":"小店專賣竹器，您隨便挑！\n",
                "here":"這是我家老爺的店鋪，小的是新來的，還請多多照顧生意。\n",
                "此處":"這是我家老爺的店鋪，小的是新來的，還請多多照顧生意。\n",
        ]));
        set("vendor_goods",({
                __DIR__"obj/zhubang2",
                __DIR__"obj/zhudao2",
                __DIR__"obj/zhujian2",
        }));
        set("chat_chance", 15);
        set("chat_msg",({
                "夥計手裏拿着一把雞毛撣子，麻利地撣去牆上、架上的塵土。\n",
                "夥計笑着問道：“客官想買點什麼？”\n",
        }));
        setup();
        carry_object("clone/cloth/male-cloth")->wear();
}
void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy","buy");
}          