// wshangfan.c

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("烏夷商販", ({ "shang fan", "shang", "fan" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "一位烏夷族的商販，挑着一擔皮毛野味在販賣。\n");
        set("combat_exp", 5000);
        set("str", 27);
        set("str", 22);
        set("dex", 11);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/wdahui")->wear();
        add_money("coin", 100);
}
