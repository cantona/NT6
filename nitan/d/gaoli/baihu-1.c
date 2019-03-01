// /d/gaoli/baihu-1
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "朝陽大街");
        set("long", @LONG
你走在一條寬闊的石板大街上，西面就快到高麗皇宮了。都可以看
見皇宮的圍牆拉東面是高麗的東門朝陽門,北面是一家民宅,高牆大院好
象是一個富戶。南面是一家商行。運輸各樣的貨物。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"yudao5",
                "east" : __DIR__"baihu-2",
                "north":__DIR__"dafujia1",
                "south":__DIR__"shanghang",    
        ]));
        set("objects",([
          __DIR__"npc/shusheng":1,
          ]));
       setup();
        replace_program(ROOM);
}        
