// /d/gaoli/xuanwumen
// Room in 高麗
inherit ROOM;

void create()

{
set("short", "山路");

        set("long", @LONG
你正走在一條崎嶇不平的山路上，偶爾聽到一陣陣的野獸叫聲，頭
頂有一些不知名的小鳥在跳來跳去，四周叢林密佈，鮮花綠草若隱若現，
隨着山谷裏吹來的陣陣清風，傳來嘩嘩的松濤聲和一些淡淡的花香，身
臨其境，古樸、幽靜之感油然而生。
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"xuanwumen",
                  "northup" : __DIR__"shanlu2",
        ]));
       setup();
        replace_program(ROOM);
}
