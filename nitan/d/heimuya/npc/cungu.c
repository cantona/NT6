// cungu.c

inherit NPC;

void create()
{
        set_name("村姑", ({ "cun gu","gu","cun" }) );
        set("gender", "女性" );
        set("age", 20);
        set("long", "一個很清秀的年輕農村姑娘，挎着一隻蓋着布小籃子。\n");
        set("shen_type", 1);
        set("combat_exp", 4000);
        set("str", 15);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/d/baituo/obj/caomei");
        carry_object("/d/baituo/obj/turou");
}
