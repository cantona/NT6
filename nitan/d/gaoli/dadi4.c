// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "大堤");
        set("long", @LONG
這裏是一個大堤。旁邊就是洶湧的大海，陣陣大風吹來，海浪拍打
着堤岸，濺得你身上都是海水。往南邊望去，一個港口已經映入眼簾了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadi3",
                "southeast":__DIR__"dadi5",
        ]));
       setup();
        
}
