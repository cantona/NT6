// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// tao3.c 桃枝仙

inherit NPC;
string ask_me();

void create()
{
        set_name("桃枝仙", ({ "tao zhixian", "tao", "zhixian" }));
        set("nickname", "桃谷六仙不知是老三還是老四");
        set("long", 
"桃枝仙與桃葉仙不知誰是老三，誰是老四。但他常説自己是老三\n"
"，和桃葉仙常常為此爭論。\n");
        set("gender", "男性");
        set("age", 60);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 21);
        set("con", 29);
        set("dex", 29);
        set("shen", 0);
        
        set("max_qi", 1500);
        set("max_jing", 800);
        set("neili", 1400);
        set("max_neili", 1400);
        set("jiali", 50);
        set("level", 6);
        set("combat_exp", 300000);
        set("score", 5000);

        set_skill("force", 95);
        set_skill("dodge", 100);
        set_skill("parry", 95);
        set_skill("unarmed", 100);
        set_skill("ding-dodge", 95);
        set_skill("ding-force", 95);
        set_skill("ding-unarmed", 95);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("unarmed", "ding-unarmed");

        set("chat_chance", 5);

        set("chat_msg", ({
                "桃枝仙指着桃葉仙説道：我是老三，他是老四。\n",
                "桃枝仙説道：我們父母本來記得誰是老三誰是老三，後來卻忘了。\n",
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
