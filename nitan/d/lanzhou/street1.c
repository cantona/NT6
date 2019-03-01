//  Room:  /d/lanzhou/street1.c

inherit  ROOM;

void  create  ()
{
        set("short",  "濱河大街東");
        set("long",  @LONG
這是一條寬闊的青石板街道，向東西兩頭延伸。兩旁路樹成蔭，行
人稀少，靜悄悄地很是冷清。北面是一所道觀，南面則是個熱鬧的集市。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"baiyun",
                "south" : __DIR__"market",
                "east"  : __DIR__"eastgate",
                "west"  : __DIR__"street2",
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15740);
	set("coor/y", 3820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}