// Room: /wuliang/shanlu7.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
上山的山路從這裡開始有了青石舖墊。不過腳底仍是生澀難耐。
向下的山路轉入一個山坳。山坳裡冒著青煙，竟有十幾束之多，在這
山清水秀的地方，隱隱覺得有點不對勁。
LONG );
        set("outdoors", "wuliang");
        set("exits", ([
                "northup"   : __DIR__"shanlu8",
                "southdown" : __DIR__"shanlu6",
        ]));
        set("objects", ([
                __DIR__"npc/rong" : 1,
        ]));
        set("coor/x", -71000);
        set("coor/y", -79970);
        set("coor/z", 60);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if (objectp(present("rong ziju", environment(me))) &&
                dir == "northup")
           return notify_fail("容子矩攔住你說：神農幫肆虐，你是何人？難保不是姦細，不得上山！\n");
        return ::valid_leave(me, dir);
}