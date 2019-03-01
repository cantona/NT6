// Room: /d/shaolin/shijie3.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "石階");
        set("long", @LONG
石級到這裡似乎變得寬闊了些。清新的山風撲面而來，令人精神
頓為一爽。遠處傳來淙淙水聲，漸行漸遠。山壁上掛滿了厚密的籐蘿，
隨風輕輕搖弋。
LONG );
        set("exits", ([
                "southdown" : __DIR__"shijie2",
                "westup" : __DIR__"shijie4",
        ]));
        set("objects",([
                __DIR__"npc/xiao-hai" : 1,
        ]));
        set("outdoors", "shaolin");
        setup();
        replace_program(ROOM);
}
