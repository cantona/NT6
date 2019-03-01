// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// tao2.c 桃幹仙

inherit NPC;
string ask_me();

void create()
{
        set_name("桃幹仙", ({ "tao ganxian", "tao", "ganxian" }));
        set("nickname", "桃谷六仙老二");
        set("long", 
"桃根仙張著一張長長的馬臉，尊容是令人不敢恭維的。與其五兄\n"
"弟行影不離，號稱「桃谷六仙」。\n");
        set("gender", "男性");
        set("age", 63);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 21);
        set("con", 29);
        set("dex", 29);
        set("shen", 0);
        
        set("max_qi", 1500);
        set("max_jing", 800);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("level", 6);
        set("combat_exp", 300000);
        set("score", 5000);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("unarmed", 100);
        set_skill("ding-dodge", 100);
        set_skill("ding-force", 100);
        set_skill("ding-unarmed", 100);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("unarmed", "ding-unarmed");

        set("chat_chance", 5);

        set("chat_msg", ({
                "桃幹仙神氣地說道：咱們桃谷六仙在江湖上威名赫赫！\n",
                "桃幹仙說道：你若是不認識咱們，那你一定是這個．．．這個．．孤陋寡聞。\n",
        }) );

        set("inquiry", ([
                "令狐沖"     : "令狐兄是我的好朋友，常說咱們六兄弟是江湖中的英雄好漢。\n",
                "風清揚"     : (: ask_me :),
                "風前輩"     : (: ask_me :),
                "風清揚前輩" : (: ask_me :),
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

#include "tao.h"
