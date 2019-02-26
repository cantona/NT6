// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "廣場");
        set("long", @LONG
這裏一個大廣場。廣場佔地很大，估計可以容納上千人。北邊是高
麗的天台，是高麗求神祭天的地方。每次求神祭天，都有上千人來這裏
祭拜，場面很是壯觀。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"shanlu8",
                "northup":__DIR__"tiantai",
        ]));
       setup();
        
}

