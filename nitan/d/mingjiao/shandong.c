// Room: /d/mingjiao/shandong.c
// Date: Java 97/04/9

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "明教密洞");
        set("long", @LONG
這裏是一個小小土洞，周圍黑乎乎的很難看清楚。隱隱約約，可
以看到一扇大石門(men)。
LONG );
        set("exits", ([
                "out"  : __DIR__"huangtulu2",
        ]));
        set("item_desc", ([
                "men"  : "一扇大石門，看來總有兩萬斤重吧。\n",
        ]));
        set("outdoors", "mingjiao");
        setup();
}

void init()
{
        add_action("do_break", "break");
}

int do_break(string arg)
{
        object *ob, me = this_player();
        int i;

        if (arg != "men")
                return notify_fail("你在幹嗎? \n");

        if (query("neili", me) < 2500)
        {
                write("你運了運氣，覺得自己現在的內力不濟。\n");
                return 1;
        }

        addn("neili", -2000, me);
        if (me->query_skill("force", 1) < 300)
        {
                message_vision(CYN "$N" CYN "呀呀嘿嘿廢了半天力氣，結果"
                                  "沒什麼動靜。\n", me);
                tell_object(me, "看來是自己的內功火候還不夠。\n");
                return 1;
        }

        message_vision(CYN "石門在$N" CYN "一擊之下軋軋聲響，緩緩移開。\n" NOR,
                       me);

        set("exits/enter",__DIR__"midao0");
        addn("neili", -400, me);
        remove_call_out("close");
        call_out("close", 5, this_object());
        return 1;
}

void close(object room)
{
        message("vision", "石門又在軋軋聲響，緩緩閉上。\n"NOR, room);
        delete("exits/enter");
}
