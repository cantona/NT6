// gongnu.c

inherit NPC;

void create()
{
    set_name("宮女",({ "gong nv", "girl" }) );
        set("gender", "女性" );
        set("age", 17);
        set("long", "一位大理皇宮烏夷族宮女，以酥澤發，盤成兩環，一身宮裝，目無表情。\n");
         set_temp("apply/defense", 5);
        set("combat_exp", 7000);
        set("shen_type", 1);
        set("per", 28);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/whitecloth1")->wear();
}
