// dibao.c

inherit NPC;

void create()
{
        set_name("地保", ({ "dibao" }) );
        set("gender", "男性" );
        set("age", 43);
        set("long", 
"趙洪是這個村子土生土長的人，年輕的時候到外面去闖蕩過一陣。\n"
"在鏢局當過趟子手，攢了點錢，回來後娶了房老婆，物農為生。\n"
"村裏人因他在外見過世面，又會些武功，就推他做了地保。\n");

        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", 1);

        set_skill("unarmed", 30);
        set_skill("dodge", 20);
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set("combat_exp", 2500);

        set("attitude", "peaceful");
        setup();
        add_money("coin", 150);
        carry_object(__DIR__"obj/cloth")->wear();
}
