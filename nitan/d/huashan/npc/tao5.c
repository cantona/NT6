// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// tao5.c 桃花仙

inherit NPC;
string ask_me();

void create()
{
        set_name("桃花仙", ({ "tao huaxian", "tao", "huaxian" }));
        set("nickname", "桃谷六仙老五");
        set("long", 
"桃花仙排行第五，常自詡其名為眾兄弟中最好聽的。\n");
        set("gender", "男性");
        set("age", 58);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 29);
        set("int", 22);
        set("con", 28);
        set("dex", 27);
        set("shen", 0);
        
        set("max_qi", 1500);
        set("max_jing", 800);
        set("neili", 1300);
        set("max_neili", 1300);
        set("jiali", 50);
        set("level", 6);
        set("combat_exp", 300000);
        set("score", 5000);

        set_skill("force", 95);
        set_skill("dodge", 95);
        set_skill("parry", 95);
        set_skill("unarmed", 95);
        set_skill("ding-dodge", 95);
        set_skill("ding-force", 90);
        set_skill("ding-unarmed", 90);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("unarmed", "ding-unarmed");

        set("chat_chance", 5);

        set("chat_msg", ({
                "桃花仙興高采烈地説道：我的名字是咱們桃谷六仙中最好聽的。\n",
                "桃花仙説道：咱們常跟令狐沖斗酒，喝個十天八夜的也不算什麼。\n",
        }) );

        set("inquiry", ([
                "令狐沖"     : "令狐兄是我的好朋友，常説咱們六兄弟是江湖中的英雄好漢。\n",
                "風清揚"     : (: ask_me :),
                "風前輩"     : (: ask_me :),
                "風清揚前輩" : (: ask_me :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

#include "tao.h"
