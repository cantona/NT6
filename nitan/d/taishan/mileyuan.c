// Room: /d/taishan/hongmen.c
// Last Modified by winder on Aug. 25 2001

inherit ROOM;

void create()
{
        set("short", "彌勒院");
        set("long", @LONG
彌勒院由祀觀音大士之飛雲閣與紅門宮相連。東院正殿原祀木雕彌
勒佛；東有穿堂式更衣亭，舊時帝王官宦登山至此更衣；南有穿堂式過
庭。
LONG );
        set("exits", ([
                "west"      : __DIR__"hongmen",
                "southeast" : __DIR__"bailuo",
        ]));
        set("outdoors", "taishan");
        set("no_clean_up", 0);
        set("coor/x", 80);
	set("coor/y", 80);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}