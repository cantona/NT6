inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
這是一條寬大堅實的石階路，不時地有進香客和遊人從你的身邊
走過。抬頭西望，雄偉的三清殿頂浮現在香煙裊繞之中，巍峨壯觀。
東邊一條石階通往武當山腳下，隱約可見遠處桃花片片，賞心悦目。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "west" : __DIR__"tyroad1",
                "east" : __DIR__"tyroad3",
        ]));
        set("objects", ([
                __DIR__"npc/guest" : 1
        ]));
        set("coor/x", -350);
        set("coor/y", -290);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}