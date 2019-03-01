// neiting.c
inherit ROOM;

void create()
{
        set("short", "內廳");
        set("long", @LONG
這是一個石洞，此洞碩大無朋，四周點滿了火把，把整個大廳照
耀得十分明亮，中間放著很多石桌和石凳，有很多的江湖人物在石室
在參悟武功之余，在這裡休息一會。
LONG );
// 大廳門口靠左有一個小洞(hole)。
        set("exits", ([
                "enter" : __DIR__"shihole1",
                "north" : __DIR__"xiuxis2",
                "east"  : __DIR__"shibi",
                "west"  : __DIR__"chashi",
        ]));

        set("objects", ([
                __DIR__"npc/shipotian" : 1,
//                __DIR__"npc/daoseng": 1,
                __DIR__"npc/dizi": 2,
        ]));

        set("coor/x", -3090);
        set("coor/y", -25000);
        set("coor/z", 0);
        setup();
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="hole" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message("vision",
                                me->name() + "運起丐幫縮骨功，一彎腰往洞裡鑽了進去。\n",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/undersld");
                        message("vision",
                                me->name() + "從洞裡走了進來。\n", environment(me), ({me}) );
                        return 1;
                }
                else
                        return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
        }
}