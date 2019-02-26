// /d/beihai/baita.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "瓊島白塔");
        set("long", @LONG
百塔為以瓊華島為主體組成的四面景觀的中心。位於北海瓊華島之
巔。白塔上為喇嘛塔，下為高大的磚石台基，塔座為折角式須彌座，其
上承託覆缽式塔身，正面中有壺門式眼光門，門內刻有藏文咒語。塔身
上部為細長的十三天，上為兩層銅質傘蓋，邊緣懸銅鐘十四個，最上為
鎏金火焰寶珠塔剎。
LONG
        );
        set("exits", ([
                "northdown" : __DIR__"yilan",
                "southdown" : __DIR__"yongansi",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);
        set("coor/x", -190);
        set("coor/y", 4090);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}