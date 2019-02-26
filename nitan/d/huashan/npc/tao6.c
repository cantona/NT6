// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// tao6.c 桃實仙

inherit NPC;
string ask_me();

void create()
{
        set_name("桃實仙", ({ "tao shixian", "tao", "shixian" }));
        set("nickname", "桃谷六仙老六");
        set("long", 
"桃實仙於桃谷六仙中年紀最小，同時膽子也最小。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 27);
        set("int", 20);
        set("con", 27);
        set("dex", 30);
        set("shen", 0);
        
        set("max_qi", 1500);
        set("max_jing", 800);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 50);
        set("level", 6);
        set("combat_exp", 300000);
        set("score", 5000);

        set_skill("force", 95);
        set_skill("dodge", 95);
        set_skill("parry", 95);
        set_skill("unarmed", 95);
        set_skill("ding-dodge", 90);
        set_skill("ding-force", 90);
        set_skill("ding-unarmed", 90);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("unarmed", "ding-unarmed");

        set("chat_chance", 6);

        set("chat_msg", ({
                "桃實仙顧慮地道：他不是太利害吧？\n",
                "桃實仙對大夥説道：你們先上，我來殿後。\n",
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
