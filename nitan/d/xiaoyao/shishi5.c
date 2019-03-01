// shishi5.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "地下石室");
        set("long", @LONG
這裡是地下石室的最下面一層了，四周是黑乎乎，說不出的陰深恐
怖，你可以聞到強烈的腐爛的東西所發出的氣味。看來還是快點離開比
較好。
LONG );
        set("exits", ([
                "up" : __DIR__"shishi4",
        ]));
        set("objects",([
//                CLASS_D("xiaoyao")+"/xiaoyaozi" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", -21030);
        set("coor/z", -60);
        setup();
        replace_program(ROOM);
}