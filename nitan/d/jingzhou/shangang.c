#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "山岡");
        set("long", @LONG
這是一片亂石堆成的山岡。幾棵小樹稀稀落落地長在巖石的罅隙裏。
雜草叢裏，露出一塊石碑(bei)的一角。
LONG );
        set("exits", ([
                "north"  : __DIR__"gumiao",
                "east" : __DIR__"shandao",
                "west" : "/d/chengdu/shudao5",
        ]));
        set("outdoors", "jingzhou");
        set("item_desc", ([
                "bei": "象是塊墓碑，只露出一角。\n"
        ]) );
        set("no_clean_up", 0);
        set("coor/x", -7140);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_dig", "dig");
}
void check_trigger()
{
        object room;

        if( (int)query("left_trigger")==3 && (int)query("right_trigger")==2 && !query("exits/down") )
        {
        message("vision", "墓碑被挖得鬆動了，突然往地上一陷，露出一個向下的階梯。\n", this_object() );
        set("exits/down", __DIR__"gumu");
        if( room = find_object(__DIR__"gumu") )
                {
                        set("exits/up", __FILE__, room);
            message("vision", "墓碑突然往地上一陷，露出一個向上的階梯。\n",
                                room );
                }
                delete("left_trigger");
                delete("right_trigger");
                call_out("close_passage", 30);
        }
}

void close_passage()
{
        object room;

        if( !query("exits/down") ) return;
        message("vision", "墓碑軋軋移動，又將向下的通道蓋住了。\n", this_object());
        if( room = find_object(__DIR__"mudao") )
        {
                delete("exits/up", room);
                message("vision", "墓碑軋軋移動，緩緩合攏，你的眼前一片漆黑。\n"
                HIR "你腦海中閃過一個念頭：壞了！出不去了！\n" NOR ,
                        room );
        }
        delete("exits/down");
}

int do_dig(string arg)
{
        object weapon,me = this_player();
        string dir;

        if( !objectp(weapon=query_temp("weapon", me)) || query("name", weapon) != "鋤頭" )
        return notify_fail(HIR"你雙手刨出血來，卻什麼也沒發現。\n"NOR);        
        if( !arg || arg=="" ) return 0;

        if( arg=="bei" )
        {
                write("你試著挖出墓碑，發現它邊上有些鬆動……\n");
                return 1;
        }
        if( this_player()->query_str() <40)
        {
                write("你試著挖出墓碑，可是力氣太小……\n");
                return 1;
        }
        if( sscanf(arg, "bei %s", dir)==1 )
        {
                if( dir=="right" ) {
                        message_vision("$N在墓碑右邊挖了挖……\n", this_player());
                        addn("right_trigger", 1);
                        check_trigger();
                        return 1;
                } else if( dir=="left" ) {
                        message_vision("$N在墓碑左邊挖了挖……\n", this_player());
                        addn("left_trigger", 1);
                        check_trigger();
                        return 1;
                } else {
                        write("你亂挖一氣，累得半死，墓碑還是沒半點動靜。\n");
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