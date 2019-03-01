//  Room:  /d/lanzhou/street3.c

inherit  ROOM;

void  create  ()
{
        set("short",  "濱河大街西");
        set("long",  @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。兩旁路樹成蔭，行
人稀少，靜悄悄地很是冷清。南面通往貢院，北面是一片樹林，樹林後
隱約可見一座寺院。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"jintian",
                "south" : __DIR__"cuiying",
                "east"  : __DIR__"street2",
                "west"  : __DIR__"westgate",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15760);
	set("coor/y", 3820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}