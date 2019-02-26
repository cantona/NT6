//Room: /d/quanzhou/westbridge.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","西門吊橋");
        set("long",@LONG
這是泉州西面的一座吊橋，從傍着晉江而建的城樓大門上以兩
個滑輪維繫。日出放下吊，日落絞起。過了橋向西南走可達嶺南廣
東。
LONG);
        set("outdoors", "quanzhou");
        set("exits",([ /* sizeof() == 1 */
            "west"  : "/d/foshan/road14",
            "east"  : __DIR__"westroad2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -930);
	set("coor/y", -7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}