// Room: /d/luoyang/dukou.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "孟津渡口");
        set("long",  @LONG
這是洛陽城郊的孟津渡口，眼前就是黃河，濁浪濤天，近岸邊稀稀
落落長了不少蘆葦。碼頭上正泊着一艘烏篷船。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"      : __DIR__"futusi",
                "southwest" : __DIR__"road6",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6980);
	set("coor/y", 2270);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}