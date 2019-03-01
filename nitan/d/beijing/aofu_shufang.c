#include <ansi.h>
#include <room.h>
inherit ROOM;

string look_hua();
int valid_leave();

void create()
{
        set("short", "鰲拜書房");
        set("long", @LONG
這裡是鰲拜書房，卻沒有一本書。各種古玩琳琅滿目，商
周青銅、漢瓦當、唐三彩，珍珠寶石，應有盡有，只要擁有其
中一件，就夠你吃一輩子了。北面牆上有一副畫(hua)。
LONG);

        set("exits", ([
                "east" : __DIR__"aofu_zoulang3",
        ]));
        set("objects", ([
                "/d/beijing/npc/shizhe" : 1,
        ]));
        set("item_desc", ([
                "hua" : (: look_hua :),
        ]));
        set("coor/x", -2840);
        set("coor/y", 7790);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_xian", "xian");
        add_action("do_turn", "turn");
}

string look_hua()
{
        object me = this_player();

        if (query("score", me) < 3000)
                return WHT "\n這是一幅陳舊的畫卷，沒有"
                       "什麼不同。\n" NOR;

        set_temp("marks/畫1", 1, me);
        return WHT "\n這是一幅陳舊的畫卷，畫中一處微微"
               "隆起，你忍不住便想掀開看看。\n" NOR;
}

int do_xian(string arg)
{
        object me = this_player();

        if (! arg || arg != "hua")
                return 0;

        if( !query_temp("marks/畫1", me) )
                return 0;

        write(HIC "\n你掀開畫卷，發現後面竟隱藏著一個把"
              "手，似乎可以轉動。\n" NOR);
        set_temp("marks/畫2", 1, me);
        return 1;
}

int do_turn(string arg)
{
        object ob, me = this_player();

        if (! arg || arg != "bashou")
                return 0;

        if( !query_temp("marks/畫2", me) )
                return 0;

        if (query("exits/down"))
                return notify_fail("你拉了拉把手，但似乎沒什麼作用。\n");

        message_vision(HIY "\n$N" HIY "拉了拉把手，地面忽然「喀"
                       "喀喀」現出一個洞口。\n\n" NOR, me);
        set("exits/down", __DIR__"aofu_mishi");
        remove_call_out("close");
        call_out("close", 8, this_object());

        return 1;
}

void close(object room)
{
        message("vision", WHT "地面忽然「喀喀喀」縮回原地，把密道的入口擋"
                          "住了。\n" NOR, room);
        delete("exits/down", room);
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/畫1", me);
        delete_temp("marks/畫2", me);
        return ::valid_leave(me, dir);
}
