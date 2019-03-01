inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
洛陽東城的一條由碎石舖砌的小巷，非常僻靜。剛下過雨，路面看起
來還滿幹凈的。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"suishi4",
                  "north" : __DIR__"xiaoxiang4",
        ]));

	set("coor/x", -6960);
	set("coor/y", 2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}