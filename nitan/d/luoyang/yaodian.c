inherit ROOM;

void create()
{
        set("short", "同仁堂藥店");
        set("long", @LONG
這是一家老字號的藥店。未入此處，清新的藥香已沁人心裨。店中有
各種名藥，玲琅滿目，不乏珍奇異種。有些有起死回生的功效。藥店中的
擺設也十分考究，桌椅被勤快的夥計擦的乾乾淨淨。牆上掛滿了別人送來
的謝匾。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"sroad2",
        ]));
        set("objects", ([
                "/d/city/npc/huoji" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}