// Room: /binghuo/shanlu1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "石山小路");
        set("long", @LONG
走在火山石的寸草片葉不生的山路上。東下就是茂密的大樹林了。
往上是上山的路，山腳下樹林子邊上露出一個石洞(dong)。洞邊樹下
陣陣清香，細審原來是從樹下一大叢不知名的花朵上傳出。洞中黑呼
呼的什麼也瞧不見。
LONG );
        set("outdoors", "binghuo");
        set("no_clean_up", 0);
        set("item_desc", ([
                "dong" : "這個原來是熊窩的石洞被人清潔後成為島上最好的居所。\n",
        ]));
        set("exits", ([
                "southeast" : __DIR__"shulin3",
                "northup"   : __DIR__"shanlu2",
        ]));
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

        if( !arg || arg=="" ) return 0;

        if( arg=="dong" ) 
        {
                message("vision",
                        me->name() + "一彎腰往洞裏走了進去。\n",
                        environment(me), ({me}) );
                me->move(__DIR__"inhole1");
                message("vision",
                        me->name() + "從洞外走了進來。\n",
                        environment(me), ({me}) );
                return 1;
        }
}        