// pine_road2.c 鬆林小道
// Last Modified by winder on Aug. 18 2002

inherit ROOM;

void create()
{
        set("short", "鬆林小路");
        set("long", @LONG
這是山腳鬆林中的小路，兩邊長滿參天的紅鬆樹，只能看見一線天
空。路旁有道士在奮力砍(chop)樹。南邊通向密林深處，北邊可回大道。
LONG
        );
        
        set("objects", ([
                CLASS_D("wudang") + "/famu" : 1,
                __DIR__"obj/pine" : 2]));
                                        
        
        set("exits", ([
                "south" : __DIR__"pine_forest1",
                "north" : __DIR__"pine_road",
        ]));
        set("outdoors", "wudang");
        setup();
        replace_program(ROOM);
}
