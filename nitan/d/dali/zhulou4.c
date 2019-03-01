//Room: /d/dali/zhulou4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","議事堂");
        set("long",@LONG
這間大竹樓的中層是普麼部的議事堂，村中長老逢要日便在此聚
議族內大事，也在此接待外族貴客，或會晤大理國官府派來的使者。
屋內以本族的圖騰壁畫、鳥獸皮毛裝飾四壁。
LONG);
        set("objects", ([
           __DIR__"npc/zuzhang": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "up"    : __DIR__"zhulou5",
            "down"  : __DIR__"zhulou3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19120);
	set("coor/y", -6950);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}