//TOHSQ3.C

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裡快接近谷低了，但北面瀑布擋住了去路。瀑布如一匹銀練奔
流而下，傾瀉在一深潭之中，水聲轟鳴，簾霧直上重霄。兩旁山石高
聳，陡壁斷崖，象是人工劈就而成。深潭前的青石被磨得□亮，好象
總有人在這裡來往。
LONG );
        set("exits", ([
                "southeast" :__DIR__"tohsq2",
                "west"  : __DIR__"bshantan",
        ]));

        set("outdoors", "mingjiao");
        setup();
}

void init()
{
        add_action("do_jump","jump");
}

int do_jump(string arg)
{
        object me;

        me = this_player();
        if (! arg)
        {
                message_vision("$N一閉眼，向潭中跳了下去，只覺冰冷刺"
                               "骨，趕緊運氣相抗。\n",me);
                me->move(__DIR__"hsqtan1");
                return 1;
        }

        return notify_fail("你要跳到哪兒？\n");
}
