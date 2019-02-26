// liangongfang.c 練功房
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裏是神龍教祕密的練功房，地下整整齊齊放着幾個蒲團，幾位神
龍教長老正盤膝坐在上面練功。四壁列着一些櫃子，抽屜中放滿了各類
藥酒。櫃子上放着幾本神龍教從各處獵獲的內功心法冊子。
LONG
        );
        set("exits", ([
                "south" : __DIR__"zhulin2",
        ]));
        set("no_clean_up", 0);

        setup();
}

void init()
{
        add_action("do_practice", "practice");
        add_action("do_practice", "lian");
}

int do_practice(string arg)
{
        object me = this_player();
        string skill;
        int lvl;

        if( query("sg/exp", me)<5000 )
        {
                message("vision", 
                        "只見一位神龍教長老把"+me->name() + "一腳踢了出去。\n",
                        environment(me), ({me}));
                me->move(__DIR__"zhulin1");
                message_vision("$N被神龍教長老踢了出來。\n", me);
                return 1;
        }

        if( !arg ) return ("/cmds/skill/enable")->main(me, arg);

        if(arg == "strike" && me->query_skill_mapped(arg) == "huagu-mianzhang" )
                return 0;

        write("這裏是修習化骨綿掌的場所。\n");
        return 1;
}
