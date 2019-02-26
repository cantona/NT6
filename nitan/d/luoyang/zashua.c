inherit ROOM;

void create()
{
        set("short", "雜耍表演");
        set("long", @LONG
空曠的一塊場地，中間有幾個身強力壯的男子正在着表演、雜技、魔
術、武術、氣功。引得人們爭相觀看，四周圍滿了人羣，有老有少，有男
有女，不時的發出驚訝讚歎聲。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"fengwei",
                  "east" : __DIR__"roudian",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi2" : 1,
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/xianren" : 2,
                "/d/beijing/npc/boy2" : 1,
        ]));
	set("coor/x", -6960);
	set("coor/y", 2180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}