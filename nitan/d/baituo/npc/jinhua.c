#include <ansi.h>
inherit NPC;

void create()
{
        set_name("金花", ({ "jin hua", "jin", "hua" }));
        set("gender", "女性" );
        set("age", 24);
        set("long", "一個年少貌美的姑娘。\n");
        set("shen_type", 1);
        set("combat_exp", 800);
        set("str", 18);
        set("dex", 18);
        set("con", 18);
        set("int", 18);
        set("gold_times", 1);
        set("attitude", "friendly");
        set("chat_chance", 1);
        set("chat_msg", ({
                CYN "金花哭泣着：我的命怎麼這麼苦喲。\n" NOR,
                CYN "金花抹着眼淚：娘呀，我好想你呀！\n" NOR,
                CYN "金花歎口氣説道：不知今生今世能否再見到我娘。\n" NOR
        }));

        set("inquiry",([
                "張媽"   : "你知道我娘？你可有她給你的信物？快給我看看。",
                "繡花鞋" : "你真有繡花鞋嗎？快給我看看。",
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;

        ob = this_player();

        ::init();
        if (interactive(ob) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment())
                return;

        say(CYN "金花道：這位" + RANK_D->query_respect(ob) +
            CYN "，我娘是白駝山莊的老傭人。你可有她消息？\n" NOR);
}

int accept_object(object who, object ob)
{
        object obn;

        if (! who || environment(who) != environment())
                return 0;

        if (! objectp(ob))
                return 0;

        if (! present(ob, who))
                return notify_fail("你沒有這件東西。\n");

        if( query("id", ob) != "xiuhuaxie" )
                return notify_fail(CYN "金花説道：你給我這個東西幹嘛？\n" NOR);

        if (query("gold_times") < 1)
                return notify_fail(CYN "金花説道：我已經有繡花鞋了。\n" NOR);

        write (CYN "\n金花雙手捧着繡花鞋，淚如雨下道：娘，您還"
               "掛着女兒啊。\n" NOR);

        message_sort(CYN "\n金花抹了把眼淚，不好意思道：這位" +
                     RANK_D->query_respect(who) + CYN "見笑了"
                     "。我實在沒什麼東西報答你，不過我知道山賊"
                     "頭有個錢箱藏在牀下。我這就搬出來給你。\n"
                     NOR, who);

        message_sort(HIY "\n$N" HIY "幫金花從牀下搬出來一隻錢"
                     "箱，迫不及待地打開一看，裏面竟然擱着一大"
                     "堆白銀。$N" HIY "毫不客氣地把白銀裝進衣"
                     "服裏。\n\n" NOR, who);

        obn = new("/clone/money/silver");
        obn->set_amount(20);
        obn->move(who, 1);

        set("gold_times", 0);
        destruct(ob);
        return 1;
}

void unconcious()
{
        die();
}