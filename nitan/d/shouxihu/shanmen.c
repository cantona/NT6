// Room: /yangzhou/shanmen.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","山門");
        set("long",@LONG
山門上嵌“大明寺”石額，集唐代揚州書法家李邕手跡。山門東西
折牆嵌石刻各一，東為“淮東第一觀”，錄秦觀《次子由平山堂韻》句，
清著名書法家蔣衡書；西為清吏部員外郎王澍書“天下第五泉”。
    康熙時忌諱“大明”二字，沿稱棲靈寺，乾隆巡幸揚州，親筆改題
“法凈寺”，俗稱“平山堂”。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "north"     : __DIR__"tianwangdian",
                "southdown" : __DIR__"pailou",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 140);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}