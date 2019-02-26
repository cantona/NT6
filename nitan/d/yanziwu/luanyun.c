// Room: /d/yanziwu/luanyun.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "亂雲亭");
        set("long", @LONG
亂雲亭建在蔓陀山峯頂上。在這裏俯瞰五湖風光，但見舟船如織，
蔓陀山莊鑲嵌在萬頃波濤中，恰若水晶盆中一枚青螺。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown"   : __DIR__"path24",
        ]));
        set("coor/x", 1210);
        set("coor/y", -1240);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}