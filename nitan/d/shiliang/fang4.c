// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "側房");
        set("long", @LONG
這裏就是温家老五温方南的住處，他是個愛附庸風雅的人，正
拿着本詩集搖頭晃腦地讀着。
LONG
        );
        set("exits", ([ 
                "west" : __DIR__"zoulang6",
        ]));
        set("objects", ([
                __DIR__"npc/wenfangnan" : 1,
                __DIR__"npc/yahuan" : 1,
        ]));
        set("coor/x", 1630);
        set("coor/y", -1930);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}