inherit ROOM;

void create()
{
        set("short", "魯氏木器鋪");
        set("long", @LONG
這是一家專售木器的小店，店面不大，卻很整潔。所賣木器不過是些
木刀，木槍之類，魯老闆也整日閒逛，無所事事。但私下聽説他有門祖傳
手藝，確誰也沒見過。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"sroad7",
        ]));
        set("objects", ([
                __DIR__"npc/lu" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}