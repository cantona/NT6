// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "大堤");
        set("long", @LONG
這裡是一個大堤。旁邊就是洶湧的大海，陣陣大風吹來，海浪拍打
著堤岸，濺得你身上都是海水。放眼望去，大海一望無際，海的那邊就
是戰亂的中原了。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadi2",
                "south":__DIR__"dadi4",
        ]));
       setup();
        
}
