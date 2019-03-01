// /d/xingxiu/npc/woman.c
// Jay 3/17/96

inherit NPC;

void create()
{
        set_name("維吾爾族婦女", ({ "woman" }) );
        set("gender", "女性" );
        set("age", 40);
        set("long", "一個很胖的維吾爾族中年婦女。\n");
        set("shen", 1000);
        set("combat_exp", 150);
        set("env/wimpy", 60);
        set("chat_chance_combat", 50 );
        set("str", 13);
        set("dex", 12);
        set("con", 14);
        set("int", 13);
        set("attitude", "friendly");
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
                "維吾爾族婦女看著你笑了起來\n",
                "維吾爾族婦女說道：小波郎子呀克西。\n",
                "維吾爾族婦女向你努了努嘴，又指了指北邊。\n",
        }) );
        carry_object(__DIR__"obj/wcloth")->wear();
        add_money("coin", 100);
}
