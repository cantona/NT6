// Code of ShenZhou
// Room: didao1.c 地道
// Zhangchi 3/00

inherit ROOM;

void create()
{
        set("short", "地道");
        set("long", @LONG
這裏是厚土旗挖的地道，裏面黑漆漆的，只有幾柄火把插在牆上。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "up": "/d/mingjiao/didao/didao",
                "east": "/d/mingjiao/didao/didao_e",
                "west": "/d/mingjiao/didao/didao_w",
                "north": "/d/mingjiao/didao/didao_n",
                "south": "/d/mingjiao/didao/didao_s",
]));
        
        set("cost", 1);

        setup();
//        replace_program(ROOM);
}