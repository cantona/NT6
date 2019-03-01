// yongdao1.c 甬道


inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
這是一條長長的甬道，兩邊點着油燈，光線雖暗，卻也可辨道
路，外面隱約能聽見瀑布的隆隆水聲，洞口水花飛濺，地面甚是濕
潤。
LONG );
        set("exits", ([
               "south" : __DIR__"yongdao2",
               "out" : __DIR__"pubu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3100);
        set("coor/y", -22060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}