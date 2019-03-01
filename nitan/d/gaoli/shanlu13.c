// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。這裡地形崎嶇，偶爾有幾只野兔從你的身旁跑
過。北邊就是高麗的北烽火台了。有幾個官兵在那裡監察情況。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shanlu12",
                "northup":__DIR__"beifenghuotai",
        ]));
       setup();
        
}

