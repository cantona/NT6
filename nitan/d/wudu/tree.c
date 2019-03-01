inherit ROOM;

void create()
{
        set("short", "榕樹上");
        set("long", @LONG
這裡是大榕樹的頂端，四周是濃密的枝葉和濕漉漉的苔蘚。
突然間一陣微風吹來，樹葉發出唰啦啦的聲音。從上面望下去
你只覺得一陣眼暈，心想還是趕快下去吧。
LONG);
        set("outdoors", "wudujiao");
        set("exits", ([
                "down" : __DIR__"nanyuan",
        ]));
        set("objects", ([
                  __DIR__"obj/xiang": 1,
        ]));
        setup();
        replace_program(ROOM);
}