inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這裡是非常氣派的長廊。北邊是間休息室。南邊有一間小小的藥
房，裡面傳來一陣器皿碰擊的聲音。西邊是扇拱月形敞門。東邊是練
功場。
LONG );
        set("exits", ([
                "west"  : __DIR__"ximen",
                "east"  : __DIR__"liangong",
                "north" : __DIR__"restroom",
                "south" : __DIR__"yaofang",
        ]));

        set("coor/x", -49980);
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}