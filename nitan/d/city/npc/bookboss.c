// This program is a part of NT MudLIB

inherit NPC;
inherit F_DEALER;

int ask_me();
int ask_gong();

void create()
{
        set_name("辛友清", ({ "xin youqing","xin" }) );
        set("title","書局老闆");
        set("gender", "男性" );
        set("book_count", 1);
        set("age", 38);
        set("long", "辛友清一看就是個讀書人，他功名未就，但賣書販畫為生，也頗為自得。\n");
        set("attitude","friendly");
        set("inquiry",([
                "書"    : "我這裏什麼書都有，你想買什麼？\n",
                "here"  : "這是我花了三百兩銀子買來的店鋪。\n",
                "遺物"  : (: ask_me :),
                "恩公"  : (: ask_gong :),
        ]));
        set("vendor_goods",({
                "/clone/book/lbook1",
                "/clone/book/lbook2",
                "/clone/book/lbook6",
                "/clone/book/lbook7",
                "/clone/book/lbook8",
                "/clone/book/blade_book0",
                "/clone/book/blade_book1",
                "/clone/book/dodge_book1",
                "/clone/book/dodge_book2",
                "/clone/book/sword_book1",
                "/clone/book/cuff_book",
                "/clone/book/unarmed_book",
        }));
        set("chat_chance", 15);
        set("chat_msg",(
        {
                "老闆手裏拿着一把雞毛撣子，輕輕撣去牆上，書架上的塵土。\n",
                "老闆笑着問道：“買書？還是看看字畫兒？”\n",
                "老闆輕聲嘟喃着:識貨者分文不取，不識者千金難求。\n",
                "辛友清仰頭歎道:何日才能見到恩公的後人啊。\n",
        }));

        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
}
void init()
{
        ::init();
        add_action("do_list","list");
        add_action("do_buy","buy");
        add_action("do_answer", "answer");
}

int ask_me()
{
        if ((int)this_player()->query_skill("literate",1)<125){
                say("辛友清白了白眼，對" + this_player()->name() + "説道：怎麼看你也不象個讀書人。\n");
                return 1;
        }else{
                say("辛友清看了" + this_player()->name() + "一眼,神神祕祕的説道：\n"
                    "請問您是誰的後人(answer)?\n");
                set_temp("pending/answer", 1, this_player());
                return 1;
        }
}
int ask_gong()
{
        tell_object(this_player(),
                "辛友清看了你一眼,神神祕祕的説道：\n"
                "恩公生前曾在此留有一部書籍，交待要悉心保管以傳給後人。\n"
                "只是不知何時何人會來取書。\n");
        return 1;
}

int do_answer(string arg)
{
        object me, ob, book;
        me = this_object();
        ob = this_player();

        if( !query_temp("pending/answer", ob))return 0;
        delete_temp("pending/answer", ob);
        if (arg == "先祖司馬遷" && query("book_count"))
        {
                addn("book_count", -1);
                book = new("/clone/book/lbook9");
                if ( book->violate_unique())
                {
                        destruct(book);
                        write("辛友清衝着" + ob->name() + "説道：可惜你晚來一步啊。\n");
                        return 1;
                }
                say("辛友清對" + ob->name() + "説道：今兒終於遇到恩人的後代拉。\n"
                    "我把先生的遺書交還給您拉。\n");
                book->move(ob);
                message_vision("$N交給$n一本書。\n", me, ob);
                command("rumor"+query("name", ob)+"拿到史記真篇啦。\n");
                return 1;
        }
        message_vision("$N笑道：原來先祖是"+arg+"啊，失敬失敬。\n",me);
        return 1;
}