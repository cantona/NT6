// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// benyin.c

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
        set_name("本因", ({ "ben yin","yin"}) );
        set("gender", "男性" );
        set("title", "天龍寺第十七代住持");
        set("long", "一個神情瀟洒的僧人，他是天龍寺住持方丈。\n");
        set("class", "bonze");
        set("age", 43);
        set("shen_type", 1);
        set("str", 22);
        set("int", 32);
        set("con", 26);
        set("dex", 24);

        set("qi", 3300);
        set("max_qi", 3300);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 40);
        set("level", 20);
        set("combat_exp", 1200000);

        set_skill("force", 220);
        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("finger", 225);
        set_skill("sword", 200);
        set_skill("tiannan-bu", 220);
        set_skill("kurong-changong", 220);
        set_skill("duanjia-jian", 200);
        set_skill("sun-finger", 225);
        set_skill("buddhism", 180);
        set_skill("literate", 120);
        set_skill("martial-cognize", 200); 

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("parry", "sun-finger");
        map_skill("finger", "sun-finger");
        map_skill("sword", "duanjia-jian");
        prepare_skill("finger","sun-finger");
        set("inquiry" ,([
                "舍利子"     : (: ask_me() :),
                "六脈神劍譜" : "哼！\n",
                "六脈神劍"   :  "哼！\n",
        ]));

        create_family("大理段家", 15, "高僧");
        setup();
        carry_object("/d/xueshan/obj/b-jiasha")->wear();
}

string ask_me()
{
        object me = this_player();
        
        if( query_temp("marks/ask_temp0", me) )
        {
                set_temp("marks/ask_temp1", 1, me);
                return "“那是本寺的鎮寺之寶，多年以前不慎丟失。施主如能找回此物，\n         老衲必有重謝。”\n";
        }
        else
                return "“施主不可妄言。”\n";
}

int accept_object(object who, object ob)
{
        if( query("id", ob) == "jinhe" )
        {
                message_vision("本因大喜道：“多謝施主！施主若是有緣人，請到牟尼堂取本寺之寶。\n", who);
                set_temp("marks/find_temp", 1, who);
                who->move("/d/tianlongsi/banruotai");
                return 1;
        }
        return 0;
}

#include "ben.h"
