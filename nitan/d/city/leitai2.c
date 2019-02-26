// Room: /city/leitai.c
// Date: Feb.27 1998 by Java
// Update by Doing

#include <ansi.h>

inherit ROOM;
string look_tiaofu();

void create()
{
	set("short", "擂台");
        set("long", @LONG
這是一個四丈見方的擂台。粗壯結實的木柱撐起一片平台，四角
的支柱上高掛着四副對聯，四面的觀眾都能清楚地看到台上的手起腳
落。樑上貼着一長條幅(tiaofu)，上面寫了一些東西。
LONG );
        set("outdoors", "city");
	set("item_desc", ([
		"tiaofu" : (: look_tiaofu :),
	]));

	set("exits", ([
                "down" : "/d/city/wudao2",
	]));
	set("objects", ([
		"/adm/npc/referee": 1,
	]));
        set("no_die", 1);
        setup();
}

void init()
{
        add_action("do_lclose", "lclose");
        add_action("do_lopen", "lopen");
        add_action("do_invite", "invite");
        add_action("do_kickout", "kickout");

}

string look_tiaofu()
{
        object ob;

        ob = query("close_by");
        if (! objectp(ob))
                return "本擂台現在自由開放，如有興趣自行比"
                       "武，失手傷人致命，概不負責。\n\n"
                       "注：巫師請用" HIY "lopen" NOR "/"
                       HIY "lclose" NOR "命令開放關閉擂台。\n";

        return "本擂台現在被" + ob->name(1) + "暫時關閉，"
               "組織比武，閒雜人等勿要喧譁。\n"
               "巫師請用" HIY "invite" NOR "命令邀請他人上台，"
               "或在台下使用" HIY "pass" NOR "命令\n"
               "指定某人上台比武，用" HIY "kickout" NOR
               "踢某人下台。\n";
}

int refuse(object ob)
{
        if (! wizardp(ob) && query("close_by"))
                return 1;

        return 0;
}

int do_lclose(string arg)
{
        object me;

        me = this_player();
        if (wiz_level(me) < 3)
                return notify_fail("你沒有資格關閉擂台。\n");

        if (arg != "here")
                return notify_fail("如果你要關閉擂台，請輸入(lclose here)。\n");

        if (objectp(query("close_by")))
                return notify_fail("這個擂台已經被" +
                                   query("close_by")->name(1) +
                                   "關閉用於比武了。\n");

        set("close_by", me);
        message("vision", HIW "【武林盛會】" + me->name(1) +
                "關閉了擂台，開始舉行比武盛會。\n" NOR,
                all_interactive());
        return 1;
}

int do_lopen(string arg)
{
        object me;

        me = this_player();
        if (wiz_level(me) < 3)
                return notify_fail("你沒有資格打開擂台。\n");

        if (! objectp(query("close_by")))
                return notify_fail("這個擂台目前並沒有被關閉。\n");

        if (arg != "here")
                return notify_fail("如果你要打開擂台，請輸入(lopen here)。\n");

        delete("close_by");
        message("vision", HIW "【武林盛會】" + me->name(1) +
                "結束了比武，重新開放了擂台。\n" NOR, all_interactive());
        return 1;
}

object *broadcast_to()
{
        if (! objectp(query("close_by")))
                return 0;

        return ({ find_object("/d/city/wudao1"),
                  find_object("/d/city/wudao2"),
                  find_object("/d/city/wudao3"),
                  find_object("/d/city/wudao4"), });
}

int do_invite(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me))
                return notify_fail("你不是巫師，沒有資格邀請人家上來。\n");

        if (! query("close_by"))
                return notify_fail("現在擂台並沒有關閉，無需特地邀請別人。\n");

        if (! arg ||
            ! objectp(ob = find_player(arg)))
                return notify_fail("你想讓誰上來？\n");

        if (environment(ob) == this_object())
                return notify_fail("嗯？現在不是已經在這裏了麼？\n");

        if (wizardp(ob))
                return notify_fail("人家自己想上來自己會上來，不勞你費心。\n");

        if (! living(ob))
                return notify_fail("好歹你得弄醒人家吧？\n");

        message("vision", HIW + me->name() + "一聲長嘯：" + ob->name() +
                          "，你還不快快上來？\n" NOR, all_interactive());
        message_vision("只見$N急急忙忙的走了開去。\n", ob);
        message("vision", "只見一聲呼哨，" + ob->name() + "應聲躍上台來，矯健之極。\n",
                this_object());
        ob->move(this_object());
        return 1;
}


int do_kickout(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me))
                return notify_fail("你不是巫師，沒有資格踢人家下去。\n");

        if (! arg ||
            ! objectp(ob = present(arg, this_object())))
        {
                write("你想踢誰下去？\n");
                return 1;
        }

        if (! ob->is_character())
        {
                write("你看清楚了，那並不是活人！\n");
                return 1;
        }

        message_vision("$N大喝一聲，飛起一腳將$n踢得咕嚕咕嚕滾下台去！\n",
                       me, ob);
        if (ob->is_fighting())
                ob->remove_all_enemy(1);
        ob->move("/d/city/wudao4");
        message("vision", "擂台上面一陣喧鬧過後，只見" + ob->name() +
                          "咕嚕咕嚕的滾了下來，身上青一塊兒紫一塊兒的。\n",
                environment(ob), ({ ob }));
        return 1;
}