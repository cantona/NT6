// /d/gaoli/donggongmen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "宮門");
        set("long", @LONG
這是高麗皇宮的正門，北面朱紅的宮門只有在百官早朝時才開啟，
現在大門緊緊的關著，一隊士兵英姿勃勃的站在宮門前，氣氛寧靜而壓
抑，使人盡快離開。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south":__DIR__"yudao1", 
        ]));
set("objects",([
    __DIR__"npc/weishi":1,
    ]));
       setup();
        replace_program(ROOM);
}        
