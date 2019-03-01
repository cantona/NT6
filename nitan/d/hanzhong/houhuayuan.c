// houhuayuan.c 後花園
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "後花園");
        set("long", @LONG
這裡是一個小花園，雜亂地種著各種花草，看來無人打理，
雜草已經長得很高了。有一些紅的，白的鮮花夾雜在草叢中，陣
陣花香不斷地飄過。東面有一道小門，南面是一座兩層小樓。
LONG
        );
        set("outdoors", "hanzhong");
        set("exits", ([
                "northwest" : __DIR__"fu-houyuan",
                "south"     : __DIR__"guanjinglou",
                "east"      : __DIR__"houhuayuan1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -12230);
	set("coor/y", 760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}