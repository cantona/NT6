// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "大堤");
        set("long", @LONG
這裡是一個大堤。旁邊就是洶湧的大海，陣陣大風吹來，海浪拍打
著堤岸，濺得你身上都是海水。南邊就是港口了，從這裡可以聽到港口
嘈雜的聲音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northwest" : __DIR__"dadi5",
                "south":__DIR__"gangkou",
        ]));
       setup();
        
}
