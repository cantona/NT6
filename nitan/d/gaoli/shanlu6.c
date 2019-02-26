// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一條山路上。南邊就是高麗的玉龍門了。有很多行人從你的
身旁走過，説着你聽不懂的高麗語。看來高麗的繁華要略勝過現在戰亂
的中原。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"xuanwumen",
                "northeast":__DIR__"shanlu7",
        ]));
       setup();
        
}

