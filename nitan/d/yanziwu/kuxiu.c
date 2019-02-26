//ROOM: /d/yanziwu/kuxiu.c

inherit ROOM;

void create()
{
        set("short", "苦修場");
        set("long", @LONG
這裏的場地有些破落，雖然經常打掃，但是場地仍然看得出不少
痕跡。希望出人頭地的慕容家弟子在武功有了一定的修為以後往往到
這裏來作進一步的修行。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "west" : __DIR__"shijian",
                "east":  __DIR__"kuxiu2",
        ]));

        set("for_family", "慕容世家");
        setup();
        replace_program(ROOM);
}
