// Room: /d/qilian/yumenguan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "玉門關");
        set("long", @LONG
這是大西北的最外一道關隘，不過現在早已廢棄不用了。過了玉門
關，就是西域，那裏的居民多為碧眼的胡人，“勸君更飲一杯酒，西出
陽關無故人”，再往西去漢人就不多了。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "south"  : __DIR__"danshan",
                "east"   : __DIR__"halahu",
        ]));
        set("coor/x", -20000);
        set("coor/y", 2000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}