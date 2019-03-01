// yayi.c  官府衙役
inherit NPC;

void create()
{
        set_name("衙役", ({ "ya yi", "ya" }));
        set("gender", "男性");
        set("age", 25);

        set("long", "一個高大威猛的漢子，因為久在官府做事，臉上已經磨煉得毫無表情。\n");
        set("combat_exp", 7500);
        set("shen_type", 1);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set("chat_msg_combat", ({
                "衙役說道：你當這裡是什麼地方，敢來這裡騷擾？\n",
                "衙役說道：你要是再無理取鬧，當心捕頭把你抓去坐牢!\n",
                "衙役手中的刀越砍越快，讓你應接不暇。\n",
                "衙役說道：衙門豈是你放肆的地方？！\n"
        }) );
        setup();
        carry_object("/d/city/npc/obj/yayifu")->wear();
}
        