#include <ansi.h>
inherit KNOWER;

string ask_me();

void create()
{
        set_name("赫爾蘇", ({ "he ersu", "he", "ersu", "heersu" }));
        set("long", "他是一個老參客，可是一貧如洗。\n");
        set("title", WHT "參客" NOR);
        set("age", 65);
        set("combat_exp", 300);
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("attitude", "friendly");
        set("inquiry", ([
                "人參" : (: ask_me :),
                "山參" : (: ask_me :),
        ]));

        if (random(10) > 5)
                set("count", 1);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/stick")->wield();
}

string ask_me()
{
        object me = this_player();

        if (query("count") < 1)
        {
                return "嘿嘿，你下次再來吧，現在我手裡也沒貨。\n";
        } else
        if( query_temp("tmark/參", me) )
        {
                return "你到底打算羅嗦些什麼？\n";
        } else
        {
                set_temp("tmark/參", 1, me);
                return "我這兒倒是留了棵老山參，不過得先交錢。\n";
        }
}

int accept_object(object who, object ob)
{
        object obj;

        if( !query("money_id", ob) )
        {
                write(CYN "赫爾蘇詫異地說道：你給我這個幹什麼？\n" NOR);
                return 0;
        }

        if (query("count") < 1)
        {
                write(CYN "赫爾蘇搖頭道：你等下次吧，現在我手裡也沒貨。\n" NOR);
                return 0;
        }

        if( !query_temp("tmark/參", who) )
        {
                write(CYN "赫爾蘇疑惑道：我又不是乞丐，沒事給我錢作甚？\n" NOR);
                return 0;
        }

        if (ob->value() < 100000)
        {
                write(CYN "赫爾蘇冷笑道：嘿嘿，給我這麼多錢哪？\n" NOR);
                return 0;
        }

        obj = new("/clone/fam/pill/renshen1");
        obj->move(this_object());

        addn("count", -1);
        command("givebainianrenshento"+query("id", who));
        write(CYN "赫爾蘇說道：既然您出得起價，這株百年人參就給您吧。\n" NOR);
        return 1;
}
