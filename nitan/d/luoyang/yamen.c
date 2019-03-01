// Room: /u/a/agah/yamen.c

inherit ROOM;

void create()
{
        set("short", "衙門正廳");
        set("long", @LONG
堂上東西有兩根楹住，掛著一幅對聯，但是你無心細看。正牆上懸掛
一個橫匾，上書“正大光明”四個金光閃閃的大字。知府正坐在文案後批
閱文書，師爺隨侍在後，一幫衙役正分立兩旁，在此有什麼冤情你可以直
接向知府大人訴說。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"neizhai",
  "south" : __DIR__"sting",
  "west" : __DIR__"yamendoor",
  "north" : __DIR__"bting",
]));

	set("coor/x", -6970);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}