inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這是山莊的後院。院後是桃花島的唯一一座山峯：彈指峯。
整個桃花山莊倚山而立，險勢天成。南邊有兩個露天小場，桃
花島的弟子來來往往，非常忙碌，不少人衣衫盡濕，還有些弟
子鼻青臉腫、帶傷而行。
LONG);
        set("outdoors", "taohua");
        set("exits", ([
                "north" :__DIR__"dating",
                "west"  :__DIR__"xiaowu",
                "east"  :__DIR__"siguoshi" ,
                "southeast" : __DIR__"wuchang1",
                "southwest" : __DIR__"wuchang2",
                "south" : __DIR__"wuchang3",
        ]));

        set("objects", ([
                __DIR__"obj/shizi" : 1,
        ]));
        setup();
        replace_program(ROOM);
}