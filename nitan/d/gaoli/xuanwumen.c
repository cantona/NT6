// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "玉龍門");
        set("long", @LONG
這裏是高麗的玉龍門。南面就到了城中，遠望人山人海，往來行人
車流不絕。北面一條大路通向何方。城門下有一些執勤的兵士。兵將警
惕的盯着往來人士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"xuanwu-2",
                "north" : __DIR__"shanlu1",
                "northeast":__DIR__"shanlu6",
                "northwest":__DIR__"shanlu9",
        ]));
set("objects",([
  __DIR__"npc/guanbing":4,
  __DIR__"npc/wujiang":1,
  ]));
       setup();
        
}

