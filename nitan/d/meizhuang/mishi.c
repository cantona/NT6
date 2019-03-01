// mishi.c
#include <room.h>

inherit ROOM;
int do_press();
int valid_leave();

void create()
{
       set("short","密室");
        set("long", @LONG
這是一間不大的房間，房間裡擺著一排排的書架(shu jia)和很多
書(book)，在書架的兩旁靠著幾具死人的骸骨，有一具的胸骨之中還
插著一柄劍。
LONG );
        set("exits", ([
                "out" : __DIR__"neitang",
        ]));
        set("item_desc", ([
                "shu jia" :
        "書架上擺著各種各樣的書。\n",
                "book" :
        "都是一些很平常的書，到處都可以見到。\n",
        ]) );
        set("objects", ([
                __DIR__"obj/tizi" : 1,
        ]));

        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}


int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return 0;
        if( arg=="shu jia")
        {
            if( query_temp("marks/跳1", me)){
                if (me->query_skill("dodge",1)<100)
                    write("你試圖跳上書架的頂端，但老是跳不上去。\n");
                else {
                    write("你縱身躍上了書架頂端。\n");
                    message("vision",
                             me->name() + "一縱身躍上了書架頂端。\n",
                             environment(me), ({me}) );
                    me->move(__DIR__"dingduan");
                    message("vision",
                             me->name() + "從下面躍了上來。\n",
                             environment(me), ({me}) );
                }
                return 1;
           }
        }
}

int valid_leave(object me, string dir)
{
        delete_temp("marks/跳1", me);
        return ::valid_leave(me, dir);
}
