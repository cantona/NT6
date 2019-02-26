// Room: /yangzhou/pingtai.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","平台石欄");
        set("long",@LONG
平台中二具鐵鑊，以太湖石為座，夏植荷花於鑊內，成為絕大盆景。
鐵鑊直徑六七尺，厚二寸，高與人肩齊，相傳為蕭樑時鎮水之物。儀徵
焦汝霖《鐵鑊記》碑石立於其側。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "northup" : __DIR__"taohuawu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 39);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}