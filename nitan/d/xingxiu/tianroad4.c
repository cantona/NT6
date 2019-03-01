// room: /d/xingxiu/tianroad4.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void init();
int do_jump(string arg);

void create()
{
        set("short", "天山山路");
        set("long", @LONG
這裡是天山東麓，山風從山上吹來，你冷得瑟瑟發抖。路邊是一片
針葉林。石壁上盛開著一朵潔白的天山雪蓮，一個採藥人正在採藥。東
面一條深澗(valley)擋住了下山的路。
LONG );
        set("exits", ([
            "westup" : __DIR__"tianroad5"
        ]));
        set("objects", ([
                __DIR__"npc/caiyaoren"  : 1,
                __DIR__"obj/xuelian" : 1,
                //"/clone/fam/pill/xuelian1" : 1,
                //"/clone/medicine/vegetable/xuelian" : 1
        ]));

        set("item_desc", ([
        "valley" : "深澗有三丈多寬，不過因為這邊地勢高，應該不難跳(jump)過去。\n"
        ]) );
//        set("no_clean_up", 0);
        set("outdoors", "xingxiu");

        set("coor/x", -52000);
        set("coor/y", 20100);
        set("coor/z", 30);
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

        if( !arg || arg=="" ) return 0;
        if( arg=="valley" )
        {
                message("vision", me->name() + "一提氣，雙足點地跳過了深澗。\n", environment(me), ({me}) );
                me->move("/d/xingxiu/tianroad3");
                message("vision", me->name() + "從深澗上面跳了下來。\n", environment(me), ({me}) );
                return 1;
        }
}
