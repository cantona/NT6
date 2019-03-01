inherit ROOM;

void create()
{
        set("short", "學堂");
        set("long", @LONG
這裡是一座簡陋的學堂，似乎是用祠堂改成。正中供桌(zhuo)上
還供著一些牌位，上面落滿了灰塵。幾個八、九歲的農家小孩正跟著
先生在念書。 
LONG);

        set("exits", ([
                "west" : __DIR__"cun7",
        ]));
        set("objects", ([
                __DIR__"npc/xuetong": 3,
                __DIR__"npc/xiansheng": 1,
        ]));
         set("item_desc", ([
                "zhuo": "一個陳舊的供桌，上面搭著黑糊糊的台布一直垂到地面。\n"
        ]) );

        setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg == "" ) return 0;
        if( arg=="zhuo" )
        {
                message("vision", me->name() + "一彎腰往供桌下面鑽了進去。\n",
                environment(me), ({me}) );
                me->move(__DIR__"minju9");
                message("vision", me->name() + "從外面鑽了進來。\n",
                environment(me), ({me}) );
                return 1;
        }
}       