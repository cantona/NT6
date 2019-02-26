inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
洛陽東城的一條由碎石鋪砌的小巷，非常僻靜。剛下過雨，路面看起
來還滿乾淨的。前面是一大片頗為茂密的綠竹林。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"xiaoxiang3",
                  "north" : __DIR__"zhulin1",
        ]));

	set("coor/x", -6960);
	set("coor/y", 2120);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}