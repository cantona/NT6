inherit ROOM;

void create()
{
        set("short", "縣太爺府");
        set("long", @LONG
一進大門，就看見正廳北面的牆上的一副猛虎下山的中堂。
下面的長台上放著兩個大大的唐三彩的駿馬。一張紅木的桌子
就在長台的前面。往門口兩邊是一排椅子，整個大廳的家具都
是紅木的，外面的光照進來反射出一片暗暗的紅光。
LONG);
        set("exits", ([
                "south" : __DIR__"huayuan",
        ]));

        set("coor/x", -9070);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}