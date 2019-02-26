inherit NPC;

void create()
{
        set_name("衙役", ({ "ya yi", "ya" }));
        set("gender", "男性");
        set("age", 25);
        set("long", "一個高大威猛的漢子，因為久在官府做事，臉\n"
                    "上已經磨鍊得毫無表情。\n");
        set("combat_exp", 7500);
        set("shen_type", 1);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);

        setup();
        carry_object("/d/city/npc/obj/yayifu")->wear();
}