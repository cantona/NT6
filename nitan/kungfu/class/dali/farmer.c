// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

inherit NPC;

int do_push(string);

void create()
{
        set_name("武三通", ({ "wu santong", "nong", "farmer", "wu" }));
        set("long",
                        "一個中年農夫。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);

        set("max_qi", 2000);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 120);
        set("combat_exp", 350000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("axe", 160);
        set_skill("finger", 130);
        set_skill("sun-finger", 120);
        set_skill("tiannan-bu", 100);
        set_skill("kurong-changong", 80);

        map_skill("dodge", "tiannan-bu");
        map_skill("force", "kurong-changong");
        map_skill("finger", "sun-finger");
        prepare_skill("finger", "sun-finger");

        set("inquiry", ([
                "上山" : "什麼上山下山，沒看見我都快挺不住了嗎？！\n",
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_push", "push");
}

int do_push(string arg)
{
        object me;
        me=this_player();

        if (arg!="rock") { return 0; }
        if (environment(me)!=find_object("/d/heizhao/yideng5.c")) { return 0; }
        if( me->query_str()>25 && query("max_neili", me) >= 1000){
                write("你大喊一聲：大叔，頂住，我來幫你！！！\n");
                write("你使出全身力氣，雙掌上推，幫農夫將大石推起尺許來高！\n");
                write("農夫身形一晃，閃在大石之外，卻不去牽牛，把一雙大眼將你上下不停地打量！\n\n");
                me->move("/d/heizhao/yideng6.c");
                return 1;
        }

        write("你試圖用力助農夫推開大石，無奈顯然功力不夠，怎樣用力也沒效果。\n");
        return 1;
}
