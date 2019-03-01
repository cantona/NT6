// tshangfan.c

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("台夷商販", ({ "shang fan", "shang", "fan" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "一位台夷族的商販，正在販賣一竹簍剛打上來的活蹦亂跳的鮮魚。\n");
        set("combat_exp", 3000);
        set("per", 17);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/ttoujin")->wear();
        carry_object("/d/dali/npc/obj/tduanqun")->wear();
        add_money("coin", 100);
}
