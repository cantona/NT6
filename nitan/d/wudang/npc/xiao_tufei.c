// xiao_tufei.c

inherit NPC;

void create()
{
        set_name("小土匪", ({"xiao tufei", "tufei"}));
        set("gender", "男性" );
        set("age", 22);
        set("long", "這是個膽大包天的小土匪，殺人越或貨，無惡不做。\n");

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set("combat_exp", 750);
                set("shen_type", -1);
        set("str", 25);
        set("dex", 20);
        set("con", 18);
        set("int", 15);
        set("attitude","aggressive");
        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("coin", 30);
}
