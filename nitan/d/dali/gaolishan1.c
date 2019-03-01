//Room: /d/dali/gaolishan1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","高黎山東坡");
        set("long",@LONG
這裡是高黎山的東坡，向東俯視奔淌而過的東瀘水，遠遠眺望跨
谷相對的碧羅雪山。此去再向西全是崇山峻嶺，人煙稀少。山間林深
獸多，烏夷族的獵人經常進山打獵。
LONG);
        set("objects", ([
           __DIR__"npc/shanyang": 1,
        ]));
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "west"      : __DIR__"gaolishan2",
            "eastdown"  : __DIR__"atoubu",
        ]));
	set("coor/x", -19220);
	set("coor/y", -6890);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}