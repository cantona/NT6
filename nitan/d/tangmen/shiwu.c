//shiwu.c                四川唐門—石屋

inherit ROOM;

void create()
{
        set("short", "石屋");
        set("long",
"這是一間用翠竹搭成的小舍,一進門,便聞到一陣濃烈的花香，房中掛\n"
"着一幅仕女圖,椅上鋪了繡花錦墊,東邊有一扇門,掛着繡了一叢牡丹的錦\n"
"緞門幃.難道這是誰家姑娘的閨房？\n"
);
        set("exits", ([
                "north" :__DIR__"huayuan",   
           ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tanglyz" : 1,
         ]));
        setup();
        replace_program(ROOM);
}