// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

inherit NPC;

void create()
{
        set_name("點蒼漁隱", ({ "diancang yuyin", "yuyin", "fisher"}));
        set("long",
                "他四十來歲年紀，一張黑漆漆的鍋底臉，虯髯滿腮，根根如鐵。\n");
        set("gender", "男性");
        set("age", 45);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1000);
        set("max_jing",1000);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 700000);

        set_temp("apply/armor", 50);
        set_skill("force", 140);
        set_skill("dodge", 180);
        set_skill("ding-dodge", 180);
        set_skill("ding-force", 140);
        set_skill("ding-unarmed", 140);
        set_skill("parry", 140);
        set_skill("unarmed", 140);
        set_skill("staff", 140);
        set_skill("duanjia-jian", 100);
        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("unarmed", "ding-unarmed");
        map_skill("staff", "duanjia-jian");

        setup();
        carry_object("/clone/weapon/tiejiang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_object(object who, object ob)
{
        object thisroom;
        thisroom = find_object("/d/heizhao/yideng1.c");

        if( query("name", ob) == "金娃娃" && query("race", ob) == "野獸" )
        {
                remove_call_out("destroying");
                call_out("destroying", 1, ob);

        write("點蒼漁隱接過金娃娃，上上下下打量了你幾眼，忽的將金娃娃拋\n");
        write("回水中，冷冷的説道：休想以此上去害我師父，拼着給師叔一頓\n");
        write("責罵。 \n");
        write("他轉身拋金娃娃，加上説得口沫橫飛，不小心把小船的入口讓了出來。\n");
        set("exits/enter", "/d/heizhao/smallboat.c", thisroom);
        remove_call_out("closing");
        call_out("closing", 5, thisroom);
        return 1;
        }
}

void closing(object thisroom)
{
        say("點蒼漁隱罵了幾句，回到了他原來坐的地方。\n");
        delete("exits/enter", thisroom);
}

void destroying(object ob)
{
        if (ob)
        destruct(ob);
        return;
}
