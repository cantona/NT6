// fangjian1.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "房間");
        set("long", @LONG
可以看出這裏以前曾經是一個下棋的地方，房間除了一張石几，兩
只軟椅之外，空蕩蕩的一無所有，石几上刻着縱橫十九道棋路，棋局上
布着二百多顆棋子，卻是黑白對峙，竟然是一局沒有下完的棋。
LONG );
        set("exits", ([
                "south" : __DIR__"shiji1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50030);
        set("coor/y", -21030);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}