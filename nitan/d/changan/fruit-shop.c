//Room: fruit-shop.c

inherit ROOM;

void create ()
{
        set ("short", "水果店");
        set("long", @LONG
長安城唯一的一家水果店。店裏面擺滿了一排排的竹筐，筐裏有
各式各樣的水果。這兒的水果為了保持新鮮，都是每天從城外的果園
用快車運來的。水果店女老闆張蘭香正熱情的招呼着客人。
LONG );
        set("exits", ([
                "north"   : "/d/changan/qixiang2",
        ]));
        set("objects", ([
                "/d/changan/npc/lanxiang"   : 1,
        ]));

        set("coor/x", -10740);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}