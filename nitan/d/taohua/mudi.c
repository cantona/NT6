#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "墓地");
        set("long", @LONG
這裏是桃花島島主夫人的墓地。墓地周圍種了一些矮矮的
花樹。樹上的白花星星點點。白花中間是塊石碑 (bei)，碑後
是兩扇堅固的石門。墓地乾乾淨淨，顯然天天有人打掃。
LONG);
        set("outdoors", "taohua");
        set("exits", ([
//                "south" : __DIR__"road3",
                "east"  : __DIR__"taolin",
                "north" : __DIR__"road1",
        ]));
        set("item_desc", ([
                "bei": WHT "\n石碑上刻着：「" HIR "桃花島女主馮氏"
                       "埋香之墓" NOR + WHT "」\n" NOR
        ]) );
        set("no_clean_up", 0);
        set("coor/x", 8970);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_push", "push");
}

void check_trigger()
{
        object room;

        if ((int)query("left_trigger") == 3
           && (int)query("right_trigger")==3
           && ! query("exits/down"))
        {
                message("vision", HIY "\n墓門忽然軋軋作響，緩緩向兩邊移動著，露"
                                  "出一個向下的階梯。\n\n" NOR, this_object());
                set("exits/down", __DIR__"mudao");
                if (room = find_object(__DIR__"mudao"))
                {
                        set("exits/up", __FILE__, room);
                        message("vision", HIY "\n墓門忽然軋軋作響，緩緩向兩邊移"
                                          "動著，露出一個向下的階梯。\n\n" NOR,
                                          room);
                }
                delete("left_trigger");
                delete("right_trigger");
                call_out("close_passage", 30);
        }
}

void close_passage()
{
        object room;

        if (! query("exits/down"))
                return;

        message("vision", WHT "\n墓門忽然發出軋軋的聲音，緩緩合攏，將向下的通道"
                          "蓋住了。\n\n" NOR, this_object());

        if (room = find_object(__DIR__"mudao"))
        {
                delete("exits/up", room);
                message("vision", WHT "\n墓門忽然發出軋軋的聲音，緩緩合攏，將向"
                                  "上的通道蓋住了。\n\n" NOR, room);
        }
        delete("exits/down");
}

int do_push(string arg)
{
        string dir;

        if (! arg || arg == "" )
                return 0;

        if (query("exits/down"))
        {
                write("墓門都已經開了，你還推墓碑幹嘛。\n" NOR);
                return 1;
        }

        if (arg == "bei" )
        {
                write(HIC "你試著推動墓碑，發現它可以左右推動。\n" NOR);
                return 1;
        }

        if( query("max_neili", this_player())<1000 )
        {
                write("你試著推動墓碑，可怎麼也推之不動。\n");
                return 1;
        }

        if (sscanf(arg, "bei %s", dir) == 1)
        {
                if (dir == "right")
                {
                        message_vision(WHT "$N" WHT "將墓碑往右推去，忽然軋軋幾聲"
                                       "墓碑又移回原位。\n" NOR, this_player());
                        addn("right_trigger", 1);
                        check_trigger();
                        return 1;
                } else
                if (dir == "left")
                {
                        message_vision(WHT "$N" WHT "將墓碑往左推去，忽然軋軋幾聲"
                                       "墓碑又移回原位。\n" NOR, this_player());
                        addn("left_trigger", 1);
                        check_trigger();
                        return 1;
                } else
                {
                        write("你要將墓碑推向那個方向？\n");
                        return 1;
                }
        }
}

void reset()
{
        ::reset();
        delete("left_trigger");
        delete("right_trigger");
}