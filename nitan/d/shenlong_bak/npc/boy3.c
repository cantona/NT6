// boy3
#include <ansi.h>

inherit NPC;

void create()
{
        set_name("少年", ({"young boy","boy","young"}));
        set("long", "這是一個神龍教弟子，一襲白衣，混身透着一股邪氣。\n");
        set("gender", "男性");
        set("attitude", "peaceful");

        set("age", 10+random(10));
        set("shen_type", -1);
        set("str", 25+random(10));
        set("dex", 25+random(10));
        set("max_qi", 200);
        set("max_jing", 150);
        set("neili", 200);
        set("max_neili", 200);
        set("jiaji", 5+random(5));
        set("combat_exp", 20000+random(10000));

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("hand", 40);
        set_skill("parry", 40);
        set_skill("staff", 60);
        set_skill("shenlong-bashi", 40);
        set_skill("shedao-qigong", 30);
        map_skill("staff","shedao-qigong");
        map_skill("parry","shenlong-bashi");
        map_skill("hand","shenlong-bashi");
        prepare_skill("hand","shenlong-bashi");
        set("chat_chance", 3);
        set("chat_msg", ({
                "少年説道：洪教主身通護佑，眾弟子勇氣百倍，以一當百，以百當萬。\n",
                "少年説道：洪教主神目如電，燭照四方。\n",
                "少年説道：我弟子殺敵護教，洪教主親加提拔，升任聖職。\n",
                "少年説道：我教弟子護教而死，同升天堂。\n",
                "少年高聲叫道：教主寶訓，時刻在心，建功克敵，無事不成！\n",
                "少年忽然齊聲叫道：眾志齊心可成城，威震天下無比倫！\n",
                "少年忽然齊聲叫道：神龍飛天齊仰望，教主聲威蓋八方！\n",
                "少年忽然齊聲叫道：乘風破浪逞英豪，教主如同日月光！\n",
                "少年齊聲叫道：教主永享仙福，壽與天齊！\n",
        }) );
        set("party/party_name", HIY"神龍教"NOR);
        set("party/rank", HIW"白龍門"NOR"教眾");
        set("party/level", 1);
        create_family("神龍教",3,"弟子");

        setup();
        carry_object(VEGETABLE_DIR"xionghuang");
        carry_object(__DIR__"obj/wcloth")->wear();
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 10, ob);
        }
}

void greeting(object ob)
{
        object obj;
        if( !ob ) return;
        if (interactive(ob))
        {
        if (obj = present("usedgao", ob))          
                unconcious();
        }
        return;
}
