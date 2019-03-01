//yahuan.c

inherit NPC;

void create()
{
        set_name("丫環", ({"yahuan"}));
        set("long","一個小丫環，正在打掃房間．\n");
        set("gender", "女性");
        set("age", 16);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("combat_exp", 500);

        setup();
        carry_object("/d/changan/npc/obj/skirt")->wear();
}