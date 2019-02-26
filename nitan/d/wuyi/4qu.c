// Room: /d/wuyi/4qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "四曲");
        set("long", @LONG
這裏有深不可測的卧龍潭。相傳原先這裏蟄伏了十條惡龍，為非作
歹，傷害無辜。許仙手執七星寶劍殺其九。小龍痛改前非，許仙於是就
放它一條生路，從此造福百姓。朱熹《九曲棹歌》曰：“……四曲東西
兩石巖，巖花垂露碧闌毿，金雞叫罷無人見，月滿空山水滿潭。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"shijianshi",
                "southup"   : __DIR__"dazangfeng",
                "northeast" : __DIR__"3qu",
                "southwest" : __DIR__"5qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
