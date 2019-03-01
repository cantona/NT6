// datie-seng.c

inherit NPC;

int   ask_qiao();
mixed ask_armor();

string* armors = ({
        "/clone/book/book-iron",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
        "/d/shaolin/obj/tieshou",
});

void create()
{
        set_name("打鐵僧", ({ "datie seng", "datie", "seng" }) );
        set("gender", "男性" );
        set("age", 38);
        set("long", "這是個身強力壯、皮膚拗黑的打鐵僧人。\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 15);
        set("shen_type", 1);

        set_skill("unarmed", 50);
        set_skill("dodge", 35);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 5);
        set("combat_exp", 7500);

        set("attitude", "peaceful");
        set("inquiry", ([
                "老喬" : (: ask_qiao :),
                "鐵手掌" : (: ask_armor :),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
                "打鐵僧喃喃自語：讓山腳下的老喬給我買鐵，結果"
                "送過來的都是些鏽得發爛的舊鐵！\n",
                "打鐵僧嘟囔道：寺內上等精鐵都用得差不多了，得"
                "讓慧合尊者派人去市上買些好鐵來 ......！\n"
        }));

        set("hand_count", 20);

        setup();
}


int ask_qiao()
{
        if( query_temp("marks/問過老喬", this_player()) )
        {
                command("say 哎呀，我真記不清楚！\n");
        }
           else
           {
                command("say 老喬就住在少室山山腳下，好象是"
                        "在東頭…還是西頭？看我這記性！\n");
                set_temp("marks/問過老喬", 1, this_player());
        }
        return 1;
}


mixed ask_armor()
{
        object armor, me, ob;

        me = this_object();
        ob = this_player();

        if (present("iron hand", ob))
                return "你不已經有一塊了嗎？ 這玩意兒有啥用？";

        if (present("iron hand", environment(ob)))
                return "地上這不有一塊嗎？ 你要的話就撿走吧。";

        if( time()-query_temp("last_ask/for_hand", ob)<240 )
                return "嗯？我不是剛給你一塊兒嘛，你還要幹啥？";

        if (query("hand_count") < 1)
                return "哦，老喬送了一大堆給我，可是我都送人了。";

        say("鐵手掌？ 這玩意兒有啥用？\n"
            "老喬送了一大堆給我，你要的話，就拿一個去罷。\n");

        addn("hand_count", -1);
        set_temp("last_ask/for_hand", time(), ob);

        armor = new(armors[random(sizeof(armors))]);
        armor->move(ob, 1);

        message_vision("$N交給$n一個鐵手掌。\n", me, ob);
        return 1;
}

void reset()
{
        set("hand_count", 20);
}