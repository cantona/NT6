// /d/gaoli/xuanwumen
// Room in 高麗
inherit ROOM;

void create()

{
set("short", "山路");

        set("long", @LONG
你正走在一條崎嶇不平的山路上，偶爾聽到一陣陣的野獸叫聲，頭
頂有一些不知名的小鳥在跳來跳去，四周叢林密布，鮮花綠草若隱若現，
隨著山谷裡吹來的陣陣清風，傳來嘩嘩的鬆濤聲和一些淡淡的花香，身
臨其境，古樸、幽靜之感油然而生。
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "southdown" : __DIR__"shanlu1",
                "northup" : __DIR__"xiaoxi",
                "northwest" : __DIR__"milin1",
        ]));
       setup();
        replace_program(ROOM);
}
