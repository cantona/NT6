// hubian.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "湖邊");
        set("long", @LONG
這個就是谷底的大湖，湖水一平入鏡，月光映入湖中，湖心也是一
輪皎潔的圓月。湖畔還生着一叢叢的各式各樣的茶花。在月光下搖曳生
姿。此湖呈橢圓形狀，大部分隱入了花樹叢中。東南西北四面全是巖石
(stone) 和懸崖(xuanya)，但是懸崖十分陡峭，即使是絕頂的高手，也
無法攀緣而上。
LONG );
        set ("item_desc", ([
                "stone" : "四面都是巖石。。。。不過，好像有一塊有點與眾不同。\n"
        ])  ) ;
        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"gudi",
        ]));
        set("objects", ([
                __DIR__"obj/chahua1" : 1,
                __DIR__"obj/chahua2" : 1,
        ]));
        set("outdoors", "wuliang" );
        set("coor/x", -50020);
        set("coor/y", -21060);
        set("coor/z", -40);
        setup();
}

void init()
{
        add_action("do_push","push");
        add_action("do_zuan",({"zuan","enter"}));
}

int do_push(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg!="stone") return 0;
        write("你運力雙臂，雙手扶着一塊巖石，大喝一聲：“動！”\n");
       if( random(query("kar", me))<10 )
                {
                write("巖石晃動了一下，但是一晃即回。\n");
                return 1;
                };
        write("巖石緩緩轉動，只轉到一半，便見巖石後露出一個三尺來高的洞穴(hole)。\n");
        set_temp("marks/push", 1, me);
        return 1;
}

int do_zuan(string arg)
{
        object me;
        me = this_player();
        if( !query_temp("marks/push", me))return 0;
        if ( arg != "hole") return 0;
        message_vision("$N大喜之下，也沒去考慮洞中有無危險，便一閃身鑽進了山洞裏。\n", me);
        me->move(__DIR__"yandong");
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("marks/push", me))delete_temp("marks/push", me);
        return ::valid_leave();
}