// shusheng.c

inherit NPC;

void create()
{
        set_name("賣畫書生", ({ "maihua shusheng", "shusheng" }) );
        set("gender", "男性" );
        set("age", 32);
        set("int", 28);
        set("long", "一個窮魄聊倒的書生，只能靠一手丹青在風景區四周賣賣字畫為生，眼中常流出一些無奈的神情。\n");

        set("attitude", "peaceful");
        set_skill("literate", 40);
        setup();
}
