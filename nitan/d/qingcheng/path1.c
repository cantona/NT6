// Room: /qingcheng/path1.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "盤山磴道");
        set("long", @LONG
你走在盤山磴道上。山木蔽日，幽靜宜人。過了“青城”木牌
樓，西上就是天然圖畫了。東南方向是建福宮。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "southeast" : __DIR__"jianfugong",
                "westup"    : __DIR__"tianran",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8070);
        set("coor/y", -910);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}