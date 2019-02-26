// zhongling.c

inherit NPC;

void create()
{
        set_name("鍾靈", ({ "zhong ling","zhong" }) );
        set("gender", "女性" );
        set("age", 15);
        set("str", 16);
        set("con", 24);
        set("dex", 11);
        set("per", 27);
        set("int", 24);

        set("chat_chance", 1);
        set("chat_msg", ({
                "鍾靈自言自語道：“要是我的閃電貂在這兒就好了。”\n",
        }) );

        set("inquiry", ([
                "段譽" : "段哥哥呢？他在哪兒？",
                "鍾靈" : "我就是鍾靈啊。",
                "甘寶寶" : "甘寶寶是我媽。",
                "鍾萬仇" : "鍾萬仇是我爹。",
                "here" : "這裏是萬劫谷。",
                "木婉清" : "木婉清被關在後面的石屋裏，快去救她！",
        ]));

        set("attitude", "friendly");

        set("max_neili", 200);
        set("neili", 200);
        set("force_factor", 10);

        set("combat_exp", 3500);

        set_skill("finger", 60);
        set_skill("parry", 40);
        set_skill("dodge", 50);
        set_skill("sword", 30);
        set_skill("force", 50);
        set_skill("sun-finger",40);

        map_skill("finger", "sun-finger");
        map_skill("parry", "sun-finger");

        setup();

        carry_object("/d/wanjiegu/npc/obj/moon-dress")->wear();
        carry_object("/d/wanjiegu/npc/obj/shoes")->wear();
        carry_object("/d/wanjiegu/npc/obj/xiu-scarf")->wear();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) ) {
        message_vision("鍾靈對$N説道：快去救木姐姐，木姐姐被關在後面的石屋裏！\n",ob);
        }
}

int accept_object(object who, object ob)
{
        object *inv, sh;
        int i;

        if (userp(ob) || ob->is_character())
                return 0;
        inv = all_inventory(this_object());

        if (ob->name() == "閃電貂") {
            tell_object(who,"鍾靈説道：謝謝你幫我找回了閃電貂！\n");
            tell_object(who,"鍾靈説道：下次你見到段譽時，告訴他我已經回家了。\n");
            if(!sizeof(inv) )
                for ( i=0; i< sizeof(inv); i++ )
                    if ( inv[i]->name() == "繡花鞋" ) {
                        destruct(inv[i]);
                       tell_object(who, "鍾靈脱下一雙繡花鞋。\n");
                        sh = new("/d/wanjiegu/npc/obj/shoes2");
                        tell_object(who, "鍾靈説道：這是我的一雙繡花鞋，請你帶給段譽。\n");
                        sh->move(who);
                        return 1;
                    }
            return 1;
        }
        return 0;
}

void die()
{
        object killer;

        if (objectp(killer = query_last_damage_from()))
                set_temp("marks/murder_zhongling", 1, killer);

        ::die();
}
