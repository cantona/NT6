// Room: /d/yueyang/longwangmiao.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "龍王廟");
        set("long", @LONG
龍王廟建在香爐山上。香爐山原名雞子山，似形而名。君山為佛之
勝地，山上建有龍王廟，但是凡賤民不能登山朝拜，只能行舟于雞子山
下，隔山朝拜，燒香祈禱平安。由于天長地久，水石相搏，雞子山也就
越來越小了，釧靈毓秀，山勢形如香爐，人們又經常燒香，所以就稱為
香爐山了。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"xianglushan",
        ]));
        set("coor/x", -1790);
        set("coor/y", 2260);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}