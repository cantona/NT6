// /d/gaoli/jiulou
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "天外天");
        set("long", @LONG
這裡便是高麗首曲一指的酒樓天外天了。在一樓的大廳中擺放了十
數張圓桌，旁邊坐滿了客人。幾名店小二達這雪白的毛巾在客人中穿梭
著，好一派生意興隆的景象。
LONG
);
set("exits", ([
                "west":__DIR__"zhuque-1", 
        ]));
set("objects", ([
                "/d/gaoli/npc/han" : 1,
        ]));
       setup();
        replace_program(ROOM);
}
