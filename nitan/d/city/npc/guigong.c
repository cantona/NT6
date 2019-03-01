// guigong.c
inherit BUNCHER;

void create()
{
        set_name("龜公", ({ "gui gong", "gui", "gong" }));
        set("gender", "男性");
        set("age", 25);

        set("long", "一個滿臉橫肉的漢子，在麗春院日子久了，養的白白肥肥。\n");
        set("combat_exp", 30000);
        set("shen_type", 2);
        set_skill("unarmed", 70);
        set_skill("dodge", 70);
        set("chat_msg", ({
             "小娘皮，來了這裡就乖乖地侍侯大爺們吧。",
             "想跑？跑到天涯海角都給你追回來！",
             "哼！你們這些小賤人，活該！",
        }) );
        setup();
        carry_object("/d/city/npc/obj/cloth")->wear();
}