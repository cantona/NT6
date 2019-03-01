// Room: /d/xiakedao/hanbin.c

inherit BUILD_ROOM;

void create()
{
        set("short", "南海之濱");
        set("long", @LONG
這裡就是大陸的南端，向南望去是一望無際的碧海，與遼闊的藍
天相映，讓人頓生渺小之感。湛藍海水、岸邊礁石、浪拍沙灘卷起層
層細沫，陽光繞出白雲盡情籠照青草綠樹，讓人心生退隱江湖之意，
只想在此隱居修行，追求武道至高境界。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north" : __DIR__"xkroad4",
                "west"  : __DIR__"zhuwu",
        ]));
        set("objects", ([
                __DIR__"npc/sun" : 1, 
                "/adm/npc/beichou" : 1,
        ]));
        set("max_room", 3);
        setup();
        replace_program(BUILD_ROOM);
}