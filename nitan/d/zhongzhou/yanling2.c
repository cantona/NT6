inherit ROOM;

void create()
{
        set("short", "延陵西路");
        set("long", @LONG
這裏就是延陵東路，是中州的一條老街。兩邊的房屋看上
去已經很陳舊了。路上冷冷清清的，偶爾有一兩個人路過。再
往前走，就能隱隱的看見西城樓了。要是想出城的話，就要趕
緊走了。要不然等城門關了，想出城都不行了。
LONG);
        set("no_clean_up", 0);
        set("outdoors", "zhongzhou");
        set("exits", ([
                  "north" : __DIR__"gongyuan4",
                  "west" : __DIR__"chenglou",
                  "east" : __DIR__"yanling1",
        ]));
        set("coor/x", -9070);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}