// Room: /binghuo/yuanye1.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "原野");
        set("long", @LONG
這裡是一片空曠的原野。滿地都是不知名的野草，平整如茵。草
叢之中常有小獸出沒，見人不驚。西南是一片大樹林，北面一片開闊
地，連往遠處的火山口。
LONG );
        set("outdoors", "binghuo");
        set("exits", ([
                "southwest"  : __DIR__"shulin3",
                "southeast"  : __DIR__"caodi2",
                "northeast"  : __DIR__"shulin4",
                "north"      : __DIR__"yuanye2",
        ]));
        set("objects", ([
                "/d/wudang/npc/yetu" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
