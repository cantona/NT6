// fu-damen 富家大門
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "富家大門");
        set("long", @LONG
這裡是漢中鎮上首富--侯員外家的大門，門上掛著一塊大橫匾，
上面寫著‘侯府’兩個大字。門內立著一面朱紅的影壁，模模糊糊
好象題著一些詩句之類的東西。幾個橫眉立眼的家丁正挺胸凸肚地
站在門口耀武揚威，看來這是一家為富不仁的鄉紳劣霸。
LONG
        );
        set("exits", ([
                "north" : __DIR__"dongjie",
                "south" : __DIR__"fu-xiaoyuan",
        ]));
        set("objects", ([
                __DIR__"npc/jiading" : 3,
        ]));

        set("coor/x", -12240);
	set("coor/y", 800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}