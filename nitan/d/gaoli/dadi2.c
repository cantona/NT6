// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "大堤");
        set("long", @LONG
這裡是一個大堤。旁邊就是洶湧的大海，陣陣大風吹來，海浪拍打
著堤岸，濺得你身上都是海水。向南望去，隱約有一個港口。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"dadi",
                "south":__DIR__"dadi3",
        ]));
       setup();
        
}
